/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetBaseSignal.h
 */

#ifndef JPETBASESIGNAL_H
#define JPETBASESIGNAL_H

#include "JPetPM/JPetPM.h"
#include "JPetSigCh/JPetSigCh.h"
#include "JPetSlot/JPetSlot.h"
#include <TObject.h>
#include <TRef.h>

/**
 * @brief Base class for all signal data classes
 *
 * Class provides basic construction and methods for more specific Signal classes,
 * such as Raw and Physical Signals. A signal have to assigned to a Barrel Slot
 * and a PhotoMultiplier.
 */
class JPetBaseSignal : public TObject
{
public:
  enum RecoFlag
  {
    Good,
    Corrupted,
    Unknown
  };

  JPetBaseSignal();
  explicit JPetBaseSignal(bool isNull);
  virtual ~JPetBaseSignal();
  void setRecoFlag(JPetBaseSignal::RecoFlag flag);
  JPetBaseSignal::RecoFlag getRecoFlag() const;
  bool isNullObject() const;
  static JPetBaseSignal& getDummyResult();
  void Clear(Option_t* opt = "");

  /**
   * @brief Set the reference to the PhotoMultiplier parametric object
   */
  inline void setPM(const JPetPM& pm) { fPM = const_cast<JPetPM*>(&pm); }

  inline void setTime(double time) { fTime = time; }
  inline void setTOT(double tot) { fTOT = tot; }

  /**
   * @brief Obtain a reference to the PhotoMultiplier parametric object
   */
  inline const JPetPM& getPM() const { return (JPetPM&)*fPM.GetObject(); }

  inline const double getTime() const { return fTime; }
  inline const double getTOT() const { return fTOT; }

private:
  TRef fPM;
  RecoFlag fFlag = JPetBaseSignal::Unknown;

protected:
#ifndef __CINT__
  bool fIsNullObject = false;
  double fTime = 0.0;
  double fTOT = 0.0;
#else
  bool fIsNullObject;
  double fTime;
  double fTOT;
#endif

  ClassDef(JPetBaseSignal, 7);
};
#endif /* !JPETBASESIGNAL_H */

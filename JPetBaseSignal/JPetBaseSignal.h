/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include <TObject.h>
#include <TRef.h>

/**
 * @brief Base class for all signal data classes
 */
class JPetBaseSignal: public TObject
{
public:

  JPetBaseSignal();
  virtual ~JPetBaseSignal();
  explicit JPetBaseSignal(bool isNull);
  /**
   * @brief Set number of the Time Slot this signal belongs to.
   *
   * Should be set to the value returned by JPetTimeWindow::getIndex() for the respective Time Window
   */
  bool isNullObject() const;
  static  JPetBaseSignal& getDummyResult();
  inline void setTimeWindowIndex(unsigned int index) {
    fTimeWindowIndex = index;
  }

  /**
   * @brief Get the number of the Time Window this signal belongs to.
   */
  inline unsigned int getTimeWindowIndex() const {
    return fTimeWindowIndex;
  }

  inline void setPM(const JPetPM & pm) {
    fPM = const_cast<JPetPM*>(&pm);
  }

  inline void setBarrelSlot(const JPetBarrelSlot & bs) {
    fBarrelSlot = const_cast<JPetBarrelSlot*>(&bs);
  }

  /**
   * @brief Obtain a reference to the PhotoMultiplier parametric object related to this signal
   *
   */
  inline const JPetPM & getPM() const {
    return (JPetPM&) *fPM.GetObject();
  }

  /**
   * @brief Obtain a reference to the BarrelSlot parametric object related to this signal
   *
   */
  inline const JPetBarrelSlot & getBarrelSlot() const {
    return (JPetBarrelSlot&) *fBarrelSlot.GetObject();
  }

private:
  // references to parametric objects
  TRef fPM; ///< Photomultiplier which recorded this signal
  TRef fBarrelSlot; ///< BarrelSlot containing the PM which recorded this signal

  unsigned int fTimeWindowIndex; // index of original TSlot

protected:

#ifndef __CINT__
bool fIsNullObject = false;
#else
bool fIsNullObject;
#endif

ClassDef(JPetBaseSignal, 2);

};
#endif /*  !JPETBASESIGNAL_H */

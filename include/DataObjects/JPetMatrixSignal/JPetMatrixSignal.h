/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetMatrixSignal.h
 */

#ifndef JPETMATRIXSIGNAL_H
#define JPETMATRIXSIGNAL_H

#include "JPetRawSignal/JPetRawSignal.h"
#include "JPetScin/JPetScin.h"

/**
 * @brief Data class representing a physical signal reconstructed
 * in a matrix of SiPMs on a one side of a scintillator in a modular layer
 *
 */
class JPetMatrixSignal: public JPetBaseSignal
{
public:
  JPetMatrixSignal();
  explicit JPetMatrixSignal(float time, float timeStdDev, float tot);
  virtual ~JPetMatrixSignal();
  bool isNullObject() const;
  explicit JPetMatrixSignal(bool isNull);

  float getTime() const;
  float getTimeStdDev() const;
  float getTOT() const;
  bool addRawSignal(const JPetRawSignal& rawSignal);
  std::map<int, JPetRawSignal> getRawSignals() const;
  void Clear(Option_t * opt = "");

private:
  float fTime;
  float fTimeStdDev;
  float fTOT;
  std::map<int, JPetRawSignal> fRawSignalsMap;
  void setSignalTimeAndTOT();

protected:
  #ifndef __CINT__
  bool fIsNullObject = false;
  #else
  bool fIsNullObject;
  #endif

  ClassDef(JPetMatrixSignal, 2);

};
#endif /* !JPETMATRIXSIGNAL_H */

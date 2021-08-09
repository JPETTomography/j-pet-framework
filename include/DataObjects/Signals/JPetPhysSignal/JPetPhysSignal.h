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
 *  @file JPetPhysSignal.h
 */

#ifndef JPETPHYSSIGNAL_H
#define JPETPHYSSIGNAL_H

#include "Signals/JPetRecoSignal/JPetRecoSignal.h"
#include "Signals/JPetShapedSignal/JPetShapedSignal.h"

/**
 * @brief Data class representing a physical signal reconstructed
 * in a single photomultiplier.
 *
 * This class contains the reconstructed physical quantities that characterize
 * the signal and are needed for further reconstruction of hits. One JPetPhysRignal
 * object should be created based on the information from one JPetRecoSignal object.
 * User can set reconstructed values and qualities of signal time and number of
 * photoelectrons.
 */
class JPetPhysSignal : public JPetRecoSignal
{
public:
  JPetPhysSignal();
  JPetPhysSignal(double time, double qTime, double phe, double qPhe);
  virtual ~JPetPhysSignal();

  void setQualityOfTime(double qualityOfTime);
  void setPhe(double phe);
  void setQualityOfPhe(double qualityOfPhe);
  double getQualityOfTime() const;
  double getPhe() const;
  double getQualityOfPhe() const;
  void Clear(Option_t* opt = "");

private:
  double fQualityOfTime;
  double fPhe;
  double fQualityOfPhe;

  ClassDef(JPetPhysSignal, 5);
};
#endif /* !JPETPHYSSIGNAL_H */

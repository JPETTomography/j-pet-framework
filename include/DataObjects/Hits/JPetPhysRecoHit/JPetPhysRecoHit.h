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
 *  @file JPetPhysRecoHit.h
 */

#ifndef JPETPHYSRECOHIT_H
#define JPETPHYSRECOHIT_H

#include "Hits/JPetRecoHit/JPetRecoHit.h"
#include "Signals/JPetMatrixSignal/JPetMatrixSignal.h"

class JPetRecoHit;

/**
 * @brief JPetPhysRecoHit is extending reco hit class to contain inrfomation
 * about result of reconstruction of measurement data.
 *
 * Physical hit contains additional to basic hit reconstruction specific information,
 * like A-B sides signals time difference, ToT calculation, quality quantifiers for all fields
 * and references to signal objects. Method for checking consistency of a constructed hit
 * prints out warnings to log file.
 */
class JPetPhysRecoHit : public JPetRecoHit
{
public:
  enum Signal
  {
    SideA,
    SideB
  };
  JPetPhysRecoHit();
  virtual ~JPetPhysRecoHit();
  virtual JPetPhysRecoHit* clone() const override;

  void setTimeDiff(float timeDiff);
  void setToT(float tot);

  void setQualityOfTime(float qualityOfTime);
  void setQualityOfTimeDiff(float qualityOfTimeDiff);
  void setQualityOfEnergy(float qualityOfEnergy);
  void setQualityOfToT(float qualityOfToT);

  void setSignals(const JPetMatrixSignal& sigA, const JPetMatrixSignal& sigB);
  void setSignalA(const JPetMatrixSignal& sig);
  void setSignalB(const JPetMatrixSignal& sig);

  float getTimeDiff() const;
  float getToT() const;

  float getQualityOfTime() const;
  float getQualityOfTimeDiff() const;
  float getQualityOfEnergy() const;
  float getQualityOfToT() const;

  const JPetMatrixSignal& getSignal(Signal signal) const;
  const JPetMatrixSignal& getSignalA() const;
  const JPetMatrixSignal& getSignalB() const;

  bool isSignalASet() const;
  bool isSignalBSet() const;
  void checkConsistency() const;
  void Clear(Option_t*) override;

private:
  float fTimeDiff = 0.0;
  float fToT = 0.0;
  float fQualityOfTime = 0.0;
  float fQualityOfTimeDiff = 0.0;
  float fQualityOfEnergy = 0.0;
  float fQualityOfToT = 0.0;
  bool fIsSignalAset = false;
  bool fIsSignalBset = false;
  JPetMatrixSignal fSignalA;
  JPetMatrixSignal fSignalB;

  ClassDef(JPetPhysRecoHit, 2);
};

#endif /* !JPETPHYSRECOHIT_H */

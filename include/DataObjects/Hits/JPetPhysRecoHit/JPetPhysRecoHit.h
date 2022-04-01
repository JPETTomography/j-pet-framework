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

  void setTimeDiff(double timeDiff);
  void setToT(double tot);

  void setQualityOfTime(double qualityOfTime);
  void setQualityOfTimeDiff(double qualityOfTimeDiff);
  void setQualityOfEnergy(double qualityOfEnergy);
  void setQualityOfToT(double qualityOfToT);

  void setSignals(const JPetMatrixSignal& sigA, const JPetMatrixSignal& sigB);
  void setSignalA(const JPetMatrixSignal& sig);
  void setSignalB(const JPetMatrixSignal& sig);

  double getTimeDiff() const;
  double getToT() const;

  double getQualityOfTime() const;
  double getQualityOfTimeDiff() const;
  double getQualityOfEnergy() const;
  double getQualityOfToT() const;

  const JPetMatrixSignal& getSignal(Signal signal) const;
  const JPetMatrixSignal& getSignalA() const;
  const JPetMatrixSignal& getSignalB() const;

  bool isSignalASet() const;
  bool isSignalBSet() const;
  void checkConsistency() const;
  void Clear(Option_t*) override;

private:
  double fTimeDiff = 0.0;
  double fToT = 0.0;
  double fQualityOfTime = 0.0;
  double fQualityOfTimeDiff = 0.0;
  double fQualityOfEnergy = 0.0;
  double fQualityOfToT = 0.0;
  bool fIsSignalAset = false;
  bool fIsSignalBset = false;
  JPetMatrixSignal fSignalA;
  JPetMatrixSignal fSignalB;

  ClassDef(JPetPhysRecoHit, 2);
};

#endif /* !JPETPHYSRECOHIT_H */

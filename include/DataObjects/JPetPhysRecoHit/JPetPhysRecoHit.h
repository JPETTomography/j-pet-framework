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

#include "JPetPhysSignal/JPetPhysSignal.h"
#include "JPetRecoHit/JPetRecoHit.h"

class JPetRecoHit;

/**
 * @brief JPetPhysRecoHit
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

  double getTimeDiff() const;
  double getToT() const;

  double getQualityOfTime() const;
  double getQualityOfTimeDiff() const;
  double getQualityOfEnergy() const;
  double getQualityOfToT() const;

  const JPetPhysSignal& getSignal(Signal side) const;
  const JPetPhysSignal& getSignalA() const;
  const JPetPhysSignal& getSignalB() const;

  void setTimeDiff(double timeDiff);
  void setToT(double tot);

  void setQualityOfTime(double qualityOfTime);
  void setQualityOfTimeDiff(double qualityOfTimeDiff);
  void setQualityOfEnergy(double qualityOfEnergy);
  void setQualityOfToT(double qualityOfToT);

  void setSignals(const JPetPhysSignal& sigA, const JPetPhysSignal& sigB);
  void setSignalA(const JPetPhysSignal& sigA);
  void setSignalB(const JPetPhysSignal& sigB);

  bool isSignalASet() const;
  bool isSignalBSet() const;
  bool checkConsistency() const;
  void Clear(Option_t* opt = "");

private:
  double fTimeDiff = 0.0;
  double fToT = 0.0;
  double fQualityOfTime = 0.0;
  double fQualityOfTimeDiff = 0.0;
  double fQualityOfEnergy = 0.0;
  double fQualityOfToT = 0.0;
  bool fIsSignalAset = false;
  bool fIsSignalBset = false;
  JPetPhysSignal fSignalA;
  JPetPhysSignal fSignalB;

  ClassDef(JPetPhysRecoHit, 1);
};

#endif /* !JPETPHYSRECOHIT_H */

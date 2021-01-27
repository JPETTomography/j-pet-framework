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
 *  @file JPetPhysRecoHit.cpp
 */

#include "JPetPhysRecoHit/JPetPhysRecoHit.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetPhysRecoHit);

JPetPhysRecoHit::JPetPhysRecoHit() : JPetRecoHit() {}

JPetPhysRecoHit::~JPetPhysRecoHit() {}

double JPetPhysRecoHit::getTimeDiff() const { return fTimeDiff; }

double JPetPhysRecoHit::getToT() const { return fToT; }

double JPetPhysRecoHit::getQualityOfTime() const { return fQualityOfTime; }

double JPetPhysRecoHit::getQualityOfTimeDiff() const { return fQualityOfTimeDiff; }

double JPetPhysRecoHit::getQualityOfEnergy() const { return fQualityOfEnergy; }

double JPetPhysRecoHit::getQualityOfToT() const { return fQualityOfToT; }

/**
 * Get one of the signals, that construct this hit, from the side A or B
 */
const JPetPhysSignal& JPetPhysRecoHit::getSignal(Signal side) const
{
  if (side == SideA)
  {
    return fSignalA;
  }
  else
  {
    return fSignalB;
  }
}

const JPetPhysSignal& JPetPhysRecoHit::getSignalA() const { return fSignalA; }

const JPetPhysSignal& JPetPhysRecoHit::getSignalB() const { return fSignalB; }

void JPetPhysRecoHit::setTimeDiff(double timeDiff) { fTimeDiff = timeDiff; }

void JPetPhysRecoHit::setToT(double tot) { fToT = tot; }

void JPetPhysRecoHit::setQualityOfTime(double qualityOfTime) { fQualityOfTime = qualityOfTime; }

void JPetPhysRecoHit::setQualityOfTimeDiff(double qualityOfTimeDiff) { fQualityOfTimeDiff = qualityOfTimeDiff; }

void JPetPhysRecoHit::setQualityOfEnergy(double qualityOfEnergy) { fQualityOfEnergy = qualityOfEnergy; }

void JPetPhysRecoHit::setQualityOfToT(double qualityOfToT) { fQualityOfToT = qualityOfToT; }

/**
 * Set both signals for this hit
 */
void JPetPhysRecoHit::setSignals(const JPetPhysSignal& signalA, const JPetPhysSignal& signalB)
{
  fSignalA = signalA;
  fIsSignalAset = true;
  fSignalB = signalB;
  fIsSignalBset = true;
  if (!checkConsistency())
  {
    return;
  }
}

void JPetPhysRecoHit::setSignalA(const JPetPhysSignal& signalA)
{
  fSignalA = signalA;
  fIsSignalAset = true;
  if (!checkConsistency())
  {
    return;
  }
}

void JPetPhysRecoHit::setSignalB(const JPetPhysSignal& signalB)
{
  fSignalB = signalB;
  fIsSignalBset = true;
  if (!checkConsistency())
  {
    return;
  }
}

bool JPetPhysRecoHit::isSignalASet() const { return fIsSignalAset; }

bool JPetPhysRecoHit::isSignalBSet() const { return fIsSignalBset; }

/**
 * @brief Checks consistency of the hit object
 *
 * Method check whether information contained in the hit and logs
 * an error message if the construction makes no physical sense, that is:
 * - if signals come from the different scintillator
 * - if the two signals come from opposite-sided PMTs
 * - if both signals belong to the different time window
 * Successful check returns true value. If any condition is violated,
 * false is returned and an appropriate message is written to the log file.
 * If signals are not set (or one of them is not set), returns true.
 */
bool JPetPhysRecoHit::checkConsistency() const
{
  if (!fIsSignalAset || !fIsSignalBset)
  {
    return true;
  }

  if (getSignalA().isNullObject())
  {
    ERROR("Signal A is a Null Object");
    return false;
  }

  if (getSignalB().isNullObject())
  {
    ERROR("Signal B is a Null Object");
    return false;
  }

  if (getSignalA().getPM().isNullObject())
  {
    ERROR("PM from Signal A is a Null Object");
    return false;
  }

  if (getSignalB().getPM().isNullObject())
  {
    ERROR("PM from Signal B is a Null Object");
    return false;
  }

  auto scinA = getSignalA().getPM().getScin().getID();
  auto scinB = getSignalB().getPM().getScin().getID();

  if (scinA != scinB)
  {
    ERROR(Form("Signals added to Hit come from different scintillators: %d and %d.", scinA, scinB));
    return false;
  }

  if (getSignalA().getPM().getSide() == getSignalB().getPM().getSide())
  {
    ERROR(Form("Signals added to Hit come from PMTs at the same side. PMTs: %d and %d.", getSignalA().getPM().getID(), getSignalB().getPM().getID()));
    return false;
  }
  return true;
}

/**
 * Set values of the hit to zero/false/null
 */
void JPetPhysRecoHit::Clear(Option_t*)
{
  fTimeDiff = 0.0;
  fToT = 0.0;
  fQualityOfTime = 0.0;
  fQualityOfTimeDiff = 0.0;
  fQualityOfEnergy = 0.0;
  fQualityOfToT = 0.0;
  fSignalA = JPetPhysSignal();
  fSignalB = JPetPhysSignal();
  fIsSignalAset = false;
  fIsSignalBset = false;
}

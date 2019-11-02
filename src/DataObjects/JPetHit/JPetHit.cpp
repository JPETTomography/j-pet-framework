/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetHit.cpp
 */

#include "JPetLoggerInclude.h"
#include "JPetHit/JPetHit.h"
#include "TString.h"

ClassImp(JPetHit);

JPetHit::JPetHit(): TObject(), fFlag(JPetHit::Unknown) {}

/**
 * Constructor with checking the consistency of the hit being created.
 */
JPetHit::JPetHit(
  float energy, float qualityOfEnergy, float time, float qualityOfTime,
  TVector3& position, JPetPhysSignal& signalA, JPetPhysSignal& signalB,
  JPetScin& scin):
  TObject(), fFlag(JPetHit::Unknown), fEnergy(energy), fQualityOfEnergy(qualityOfEnergy),
  fTime(time), fQualityOfTime(qualityOfTime), fPos(position),
  fSignalA(signalA), fSignalB(signalB), fScin(&scin)
{
  fIsSignalAset = true;
  fIsSignalBset = true;
  if (!checkConsistency()) {
    ERROR("Problem with creating Hit - consistency check failed.");
  }
}

JPetHit::~JPetHit() {}

/**
 * Get the reconstruction flag
 */
JPetHit::RecoFlag JPetHit::getRecoFlag() const
{
  return fFlag;
}

/**
 * Get hit energy in [keV]
 */
float JPetHit::getEnergy() const
{
  return fEnergy;
}

/**
 * Get the quality of the hit energy in [kev]
 */
float JPetHit::getQualityOfEnergy() const
{
  return fQualityOfEnergy;
}

/**
 * Get the reconstructed time of the hit in [ps]
 */
float JPetHit::getTime() const
{
  return fTime;
}

/**
 * Get the time difference of the two signals, that construct the hit, unit is [ps]
 */
float JPetHit::getTimeDiff() const
{
  return fTimeDiff;
}

/**
 * Get the quality of the hit time in [ps]
 */
float JPetHit::getQualityOfTime() const
{
  return fQualityOfTime;
}

/**
 * Get the quality of the hit signals time difference in [ps]
 */
float JPetHit::getQualityOfTimeDiff() const
{
  return fQualityOfTimeDiff;
}

/**
 * Get x-axis hit position
 */
float JPetHit::getPosX() const
{
  return fPos.X();
}

/**
 * Get y-axis hit position
 */
float JPetHit::getPosY() const
{
  return fPos.Y();
}

/**
 * Get z-axis hit position
 */
float JPetHit::getPosZ() const
{
  return fPos.Z();
}

/**
 * Get position along the axis indicated by index argument
 */
float JPetHit::getPos(int index) const
{
  return fPos(index);
}

/**
 * Get the 3-d position of the hit in the strip in [cm] as an vector (ROOT class TVector3)
 */
const TVector3& JPetHit::getPos() const
{
  return fPos;
}

/**
 * Get one of the signals, that construct this hit, from the side A or B
 */
const JPetPhysSignal& JPetHit::getSignal(Signal sig) const
{
  if (sig == SideA) return fSignalA;
  else return fSignalB;
}

/**
 * Get the signal from the side A
 */
const JPetPhysSignal& JPetHit::getSignalA() const
{
  return fSignalA;
}

/**
 * Get the signal from the side B
 */
const JPetPhysSignal& JPetHit::getSignalB() const
{
  return fSignalB;
}

/**
 * Get the scintillator object, associated with this hit
 */
const JPetScin& JPetHit::getScin() const
{
  if(fScin.GetObject()) {
    return (JPetScin&) * fScin.GetObject();
  } else {
    ERROR("No JPetScin slot set, Null object will be returned");
    return JPetScin::getDummyResult();
  }
}

/**
 * Check if signal on side A is set
 */
bool JPetHit::isSignalASet() const
{
  return fIsSignalAset;
}

/**
 * Check if signal on side B is set
 */
bool JPetHit::isSignalBSet() const
{
  return fIsSignalBset;
}

/**
 * Set the reconstruction flag with enum
 */
void JPetHit::setRecoFlag(JPetHit::RecoFlag flag)
{
  fFlag = flag;
}

/**
 * Set the reconstructed energy in [keV]
 */
void JPetHit::setEnergy(float energy)
{
  fEnergy = energy;
}

/**
 * Set the value, that describes quality of reconstructed energy
 */
void JPetHit::setQualityOfEnergy(float qualityOfEnergy)
{
  fQualityOfEnergy = qualityOfEnergy;
}

/**
 * Set the reconstructed time of the hit in [ps]
 */
void JPetHit::setTime(float time)
{
  fTime = time;
}

/**
 * Set the value, that describes quality of reconstructed time
 */
void JPetHit::setQualityOfTime(float qualityOfTime)
{
  fQualityOfTime = qualityOfTime;
}

/**
 * Set the time difference between signals in [ps]
 */
void JPetHit::setTimeDiff(float td)
{
  fTimeDiff = td;
}

/**
 * Set the value, that describes the quality of time difference reconstruction
 */
void JPetHit::setQualityOfTimeDiff(float qtd)
{
  fQualityOfTimeDiff = qtd;
}

/**
 * Set the x-axis position of the hit
 */
void JPetHit::setPosX(float x)
{
  fPos.SetX(x);
}

/**
 * Set the y-axis position of the hit
 */
void JPetHit::setPosY(float y)
{
  fPos.SetY(y);
}

/**
 * Set the z-axis position of the hit
 */
void JPetHit::setPosZ(float z)
{
  fPos.SetZ(z);
}

/**
 * Set the position of the hit
 */
void JPetHit::setPos(float x, float y, float z)
{
  fPos.SetXYZ(x, y, z);
}

/**
 * Set the scintillator object for this hit
 */
void JPetHit::setScin(JPetScin& scin)
{
  fScin = &scin;
}

/**
 * @brief Checks consistency of the hit object
 *
 * Method check whether information contained in the hit and logs
 * an error message if the construction makes no physical sense, that is:
 * - if signals come from the different slots
 * - if the two signals do not come from opposite-sided PMTs
 * Successful check returns true value. If any condition is violated,
 * false is returned and an appropriate message is written to the log file.
 * If signals are not set (or one of them is not set), returns true.
 */
bool JPetHit::checkConsistency() const
{
  if (!fIsSignalAset || !fIsSignalBset) {
    return true;
  }

  if (getSignalA().isNullObject() || getSignalB().isNullObject()) {
    ERROR("one of the signal is a Null Object");
    return false;
  }

  if (getSignalA().getPM().isNullObject() || getSignalB().getPM().isNullObject()) {
    ERROR("PM of signal is a Null Object");
    return false;
  }

  if (getSignalA().getPM().getScin().isNullObject()
    || getSignalB().getPM().getScin().isNullObject()) {
    ERROR("Scintillator from a PM is a Null Object");
    return false;
  }

  if (getSignalA().getPM().getSide() == getSignalB().getPM().getSide()) {
    ERROR(
      Form("Signals added to Hit come from PMTs at the same side. PMTs: %i and %i.",
      getSignalA().getPM().getID(), getSignalB().getPM().getID())
    );
    return false;
  }

  const int scinAID = getSignalA().getPM().getScin().getID();
  const int scinBID = getSignalB().getPM().getScin().getID();

  if (scinAID != scinBID) {
    ERROR(
      Form("Signals added to Hit come from different slots: %i and %i.",
           scinAID, scinBID)
    );
    return false;
  }

  return true;
}

/**
 * Set both signals for this hit
 */
void JPetHit::setSignals(const JPetPhysSignal& sigA, const JPetPhysSignal& sigB)
{
  fSignalA = sigA;
  fIsSignalAset = true;
  fSignalB = sigB;
  fIsSignalBset = true;
  if (!checkConsistency()) { return; }
}

/**
 * Set signal A for this hit
 */
void JPetHit::setSignalA(const JPetPhysSignal& sig)
{
  fSignalA = sig;
  fIsSignalAset = true;
}

/**
 * Set signal B for this hit
 */
void JPetHit::setSignalB(const JPetPhysSignal& sig)
{
  fSignalB = sig;
  fIsSignalBset = true;
}

/**
 * Set fields of the hit to zero/false/null
 */
void JPetHit::Clear(Option_t*)
{
  fEnergy = 0.0f;
  fQualityOfEnergy = 0.0f;
  fTime = 0.0f;
  fQualityOfTime = 0.0f;
  fTimeDiff = 0.0f;
  fQualityOfTimeDiff = 0.0f;
  fPos = TVector3();
  fSignalA = JPetPhysSignal();
  fSignalB = JPetPhysSignal();
  fIsSignalAset = false;
  fIsSignalBset = false;
  fScin = NULL;
}

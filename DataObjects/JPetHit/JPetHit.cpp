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
 *  @file JPetHit.cpp
 */

#include "./JPetHit.h"
#include "./JPetLoggerInclude.h"

#include "TString.h"

ClassImp(JPetHit);

JPetHit::JPetHit() : TObject()
{
}

JPetHit::JPetHit(float e, float qe, float t, float qt, TVector3 &pos, JPetPhysSignal &siga, JPetPhysSignal &sigb,
                 JPetBarrelSlot &bslot, JPetScin &scin) : TObject(), fEnergy(e), fQualityOfEnergy(qe), fTime(t),
                                                          fQualityOfTime(qt), fPos(pos), fSignalA(siga), fSignalB(sigb), fBarrelSlot(&bslot), fScintillator(&scin)
{
  fIsSignalAset = true;
  fIsSignalBset = true;
  if (!checkConsistency())
    ERROR("Problem with creating Hit.");
}

JPetHit::~JPetHit()
{
}
float JPetHit::getEnergy() const
{
  return fEnergy;
}
float JPetHit::getQualityOfEnergy() const
{
  return fQualityOfEnergy;
}
float JPetHit::getTime() const
{
  return fTime;
}
float JPetHit::getTimeDiff() const
{
  return fTimeDiff;
}
float JPetHit::getQualityOfTime() const
{
  return fQualityOfTime;
}
float JPetHit::getQualityOfTimeDiff() const
{
  return fQualityOfTimeDiff;
}
float JPetHit::getPosX() const
{
  return fPos.X();
}
float JPetHit::getPosY() const
{
  return fPos.Y();
}
float JPetHit::getPosZ() const
{
  return fPos.Z();
}
float JPetHit::getPos(int index) const
{
  return fPos(index);
}
const TVector3 &JPetHit::getPos() const
{
  return fPos;
}
const JPetPhysSignal &JPetHit::getSignal(Signal pos) const
{
  if (pos == SideA)
    return fSignalA;
  else
    return fSignalB;
}
const JPetPhysSignal &JPetHit::getSignalA() const
{
  return fSignalA;
}
const JPetPhysSignal &JPetHit::getSignalB() const
{
  return fSignalB;
}
const JPetScin &JPetHit::getScintillator() const
{
  if (fScintillator.GetObject())
    return (JPetScin &)*fScintillator.GetObject();
  else
  {
    ERROR("No JPetScin slot set, Null object will be returned");
    return JPetScin::getDummyResult();
  }
}
const JPetBarrelSlot &JPetHit::getBarrelSlot() const
{
  if (fBarrelSlot.GetObject())
    return (JPetBarrelSlot &)*fBarrelSlot.GetObject();
  else
  {
    ERROR("No JPetBarrelSlot slot set, Null object will be returned");
    return JPetBarrelSlot::getDummyResult();
  }
}
bool JPetHit::isSignalASet() const
{
  return fIsSignalAset;
}
bool JPetHit::isSignalBSet() const
{
  return fIsSignalBset;
}

void JPetHit::setEnergy(float energy)
{
  fEnergy = energy;
}
void JPetHit::setQualityOfEnergy(float qualityOfEnergy)
{
  fQualityOfEnergy = qualityOfEnergy;
}
void JPetHit::setTime(float time)
{
  fTime = time;
}
void JPetHit::setQualityOfTime(float qualityOfTime)
{
  fQualityOfTime = qualityOfTime;
}
void JPetHit::setTimeDiff(float td)
{
  fTimeDiff = td;
}
void JPetHit::setQualityOfTimeDiff(float qtd)
{
  fQualityOfTimeDiff = qtd;
}
void JPetHit::setPosX(float x)
{
  fPos.SetX(x);
}
void JPetHit::setPosY(float y)
{
  fPos.SetY(y);
}
void JPetHit::setPosZ(float z)
{
  fPos.SetZ(z);
}
void JPetHit::setPos(float x, float y, float z)
{
  fPos.SetXYZ(x, y, z);
}
void JPetHit::setBarrelSlot(JPetBarrelSlot &bs)
{
  fBarrelSlot = &bs;
}
void JPetHit::setScintillator(JPetScin &sc)
{
  fScintillator = &sc;
}

bool JPetHit::checkConsistency() const
{
  if (!fIsSignalAset || !fIsSignalBset)
  {
    return true; // do not claim incosistency if signals are not set yet
  }

  if (getSignalA().isNullObject() || getSignalB().isNullObject())
  {
    ERROR("one of the signal is a Null Object");
    return false;
  }

  if (getSignalA().getPM().isNullObject())
  {
    ERROR("PM from signalA  is a Null Object");
    return false;
  }

  if (getSignalB().getPM().isNullObject())
  {
    ERROR("PM from signalB  is a Null Object");
    return false;
  }

  if (getSignalA().getPM().getBarrelSlot().isNullObject())
  {
    ERROR("barrel slot from PM from signalA  is a Null Object");
    return false;
  }

  if (getSignalB().getPM().getBarrelSlot().isNullObject())
  {
    ERROR("barrel slot from PM from signalB  is a Null Object");
    return false;
  }

  const int slot_a = getSignalA().getPM().getBarrelSlot().getID();
  const int slot_b = getSignalB().getPM().getBarrelSlot().getID();

  if (slot_a != slot_b)
  {
    ERROR(Form("Signals added to Hit come from different barrel slots: %d and %d.",
               slot_a, slot_b));
    return false;
  }

  if (getSignalA().getPM().getSide() == getSignalB().getPM().getSide())
  {
    ERROR(Form("Signals added to Hit come from PMTs at the same side. PMTs: %d and %d.",
               getSignalA().getPM().getID(), getSignalB().getPM().getID()));
    return false;
  }

  return true;
}

void JPetHit::setSignals(const JPetPhysSignal &p_sigA, const JPetPhysSignal &p_sigB)
{
  fSignalA = p_sigA;
  fIsSignalAset = true;
  fSignalB = p_sigB;
  fIsSignalBset = true;
  if (!checkConsistency())
    return;
}

void JPetHit::setSignalA(const JPetPhysSignal &p_sig)
{
  fSignalA = p_sig;
  fIsSignalAset = true;
  if (!checkConsistency())
    return;
}

void JPetHit::setSignalB(const JPetPhysSignal &p_sig)
{
  fSignalB = p_sig;
  fIsSignalBset = true;
  if (!checkConsistency())
    return;
}

void JPetHit::Clear(Option_t *)
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

  fBarrelSlot = NULL;
  fScintillator = NULL;
}

float JPetHit::getSumOfToT() const
{
  return getSumOfToTSignalA() + getSumOfToTSignalB();
}
float JPetHit::getSumOfToTSignalA() const
{
  float tot = 0.;
  std::map<int, double> leadingPoints, trailingPoints;
  leadingPoints = fSignalA.getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
  trailingPoints = fSignalA.getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Trailing);
  for (int i = 1; i < 5; i++)
  {
    auto leadSearch = leadingPoints.find(i);
    auto trailSearch = trailingPoints.find(i);

    if (leadSearch != leadingPoints.end() && trailSearch != trailingPoints.end())
      tot += (trailSearch->second - leadSearch->second);
  }
  return tot / 1000.;
}
float JPetHit::getSumOfToTSignalB() const
{
  float tot = 0.;
  std::map<int, double> leadingPoints, trailingPoints;
  leadingPoints = fSignalB.getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
  trailingPoints = fSignalB.getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Trailing);
  for (int i = 1; i < 5; i++)
  {
    auto leadSearch = leadingPoints.find(i);
    auto trailSearch = trailingPoints.find(i);

    if (leadSearch != leadingPoints.end() && trailSearch != trailingPoints.end())
      tot += (trailSearch->second - leadSearch->second);
  }
  return tot / 1000.;
}

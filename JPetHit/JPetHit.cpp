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
#include "../JPetLoggerInclude.h"

#include "TString.h"

ClassImp(JPetHit);

JPetHit::JPetHit() :
  TNamed("JPetHit", "Hit Structure")
{
  fIsSignalAset = false;
  fIsSignalBset = false;
}

JPetHit::JPetHit(float e, float qe, float t, float qt, TVector3& pos, JPetPhysSignal& siga, JPetPhysSignal& sigb,
                 JPetBarrelSlot& bslot, JPetScin& scin) :
  TNamed("JPetHit", "Hit Structure") , fEnergy(e), fQualityOfEnergy(qe), fTime(t),
  fQualityOfTime(qt), fPos(pos), fSignalA(siga), fSignalB(sigb), fBarrelSlot(&bslot), fScintillator(&scin)
{
  fIsSignalAset = true ;
  fIsSignalBset = true ;
  checkConsistency();
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
int JPetHit::getScinID() const
{
  return fScinID;
}
const TVector3& JPetHit::getPos() const
{
  return fPos;
}
const JPetPhysSignal& JPetHit::getSignal(Signal pos) const
{
  if (pos == SideA) return fSignalA;
  else return fSignalB;
}
const JPetPhysSignal& JPetHit::getSignalA() const
{
  return fSignalA;
}
const JPetPhysSignal& JPetHit::getSignalB() const
{
  return fSignalB;
}
const JPetScin& JPetHit::getScintillator() const
{
  return (JPetScin&) * fScintillator.GetObject();
}
const JPetBarrelSlot& JPetHit::getBarrelSlot() const
{
  return (JPetBarrelSlot&) * fBarrelSlot.GetObject();
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
void JPetHit::setPos (float x, float y, float z)
{
  fPos.SetXYZ(x, y, z);
}
void JPetHit::setBarrelSlot(JPetBarrelSlot& bs)
{
  fBarrelSlot = &bs;
}
void JPetHit::setScintillator(JPetScin& sc)
{
  fScintillator = &sc;
}
void JPetHit::setScinID (const int scinID)
{
  fScinID = scinID;
}


bool JPetHit::checkConsistency() const
{
  if ( !fIsSignalAset || !fIsSignalBset ) {
    return true; // do not claim incosistency if signals are not set yet
  }

  const int slot_a = getSignalA().getPM().getBarrelSlot().getID();
  const int slot_b = getSignalB().getPM().getBarrelSlot().getID();

  if ( slot_a != slot_b ) {
    ERROR( Form("Signals added to Hit come from different barrel slots: %d and %d." ,
                slot_a, slot_b) );
    return false;
  }

  if ( getSignalA().getPM().getSide() == getSignalB().getPM().getSide() ) {
    ERROR( Form("Signals added to Hit come from PMTs at the same side. PMTs: %d and %d." ,
                getSignalA().getPM().getID(), getSignalB().getPM().getID()) );
    return false;
  }

  if ( getSignalA().getTimeWindowIndex() != getSignalB().getTimeWindowIndex() ) {
    ERROR( Form("Signals added to Hit come from different time windows: %d and %d." ,
                getSignalA().getTimeWindowIndex(), getSignalB().getTimeWindowIndex()) );
    return false;
  }

  return true;
}

void JPetHit::setSignals(JPetPhysSignal& p_sigA, JPetPhysSignal& p_sigB)
{
  fSignalA = p_sigA;
  fIsSignalAset = true;
  fSignalB = p_sigB;
  fIsSignalBset = true;
  checkConsistency();
}

void JPetHit::setSignalA(JPetPhysSignal& p_sig)
{
  fSignalA = p_sig;
  fIsSignalAset = true;
  checkConsistency();
}

void JPetHit::setSignalB(JPetPhysSignal& p_sig)
{
  fSignalB = p_sig;
  fIsSignalBset = true;
  checkConsistency();
}

unsigned int JPetHit::getTimeWindowIndex() const
{
  return getSignalA().getTimeWindowIndex();
}

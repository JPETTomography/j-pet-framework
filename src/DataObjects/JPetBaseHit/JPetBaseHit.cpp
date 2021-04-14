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
 *  @file JPetBaseHit.cpp
 */

#include "JPetBaseHit/JPetBaseHit.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetBaseHit);

JPetBaseHit::JPetBaseHit() : TObject() {}

JPetBaseHit::JPetBaseHit(double time, double energy, TVector3& position, JPetScin& scin)
    : TObject(), fTime(time), fEnergy(energy), fPos(position), fScin(&scin)
{
}

JPetBaseHit::~JPetBaseHit() {}

/**
 * Get the reconstructed time of the hit in [ps]
 */
double JPetBaseHit::getTime() const { return fTime; }

/**
 * Get hit energy in [keV]
 */
double JPetBaseHit::getEnergy() const { return fEnergy; }

double JPetBaseHit::getPosX() const { return fPos.X(); }
double JPetBaseHit::getPosY() const { return fPos.Y(); }
double JPetBaseHit::getPosZ() const { return fPos.Z(); }
double JPetBaseHit::getPos(int index) const { return fPos(index); }
const TVector3& JPetBaseHit::getPos() const { return fPos; }
const JPetScin& JPetBaseHit::getScin() const
{
  if (fScin.GetObject())
  {
    return static_cast<JPetScin&>(*(fScin.GetObject()));
  }
  else
  {
    ERROR("No JPetScin set, null object will be returned");
    return JPetScin::getDummyResult();
  }
}

/**
 * Set the reconstructed time of the hit in [ps]
 */
void JPetBaseHit::setTime(double time) { fTime = time; }

/**
 * Set the reconstructed energy in [keV]
 */
void JPetBaseHit::setEnergy(double energy) { fEnergy = energy; }

void JPetBaseHit::setPosX(double x) { fPos.SetX(x); }
void JPetBaseHit::setPosY(double y) { fPos.SetY(y); }
void JPetBaseHit::setPosZ(double z) { fPos.SetZ(z); }
void JPetBaseHit::setPos(double x, double y, double z) { fPos.SetXYZ(x, y, z); }
void JPetBaseHit::setPos(TVector3& position) { fPos = position; }

void JPetBaseHit::setScin(JPetScin& scin) { fScin = &scin; }

void JPetBaseHit::Clear(Option_t*)
{
  fTime = 0.0f;
  fEnergy = 0.0f;
  fPos = TVector3();
  fScin = nullptr;
}

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

#include "Hits/JPetBaseHit/JPetBaseHit.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetBaseHit);

JPetBaseHit::JPetBaseHit() : TObject() {}

JPetBaseHit::JPetBaseHit(float time, float energy, const TVector3& position) : TObject(), fTime(time), fEnergy(energy), fPos(position) {}

JPetBaseHit::JPetBaseHit(float time, float energy, const TVector3& position, JPetScin& scin)
    : TObject(), fTime(time), fEnergy(energy), fPos(position), fScin(&scin)
{
}

JPetBaseHit::~JPetBaseHit() {}

/**
 * Get the reconstructed time of the hit in [ps]
 */
float JPetBaseHit::getTime() const { return fTime; }

/**
 * Get hit energy in [keV]
 */
float JPetBaseHit::getEnergy() const { return fEnergy; }

float JPetBaseHit::getPosX() const { return fPos.X(); }

float JPetBaseHit::getPosY() const { return fPos.Y(); }

float JPetBaseHit::getPosZ() const { return fPos.Z(); }

float JPetBaseHit::getPos(int index) const { return fPos(index); }

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
void JPetBaseHit::setTime(float time) { fTime = time; }

/**
 * Set the reconstructed energy in [keV]
 */
void JPetBaseHit::setEnergy(float energy) { fEnergy = energy; }

void JPetBaseHit::setPosX(float x) { fPos.SetX(x); }

void JPetBaseHit::setPosY(float y) { fPos.SetY(y); }

void JPetBaseHit::setPosZ(float z) { fPos.SetZ(z); }

void JPetBaseHit::setPos(float x, float y, float z) { fPos.SetXYZ(x, y, z); }

void JPetBaseHit::setPos(const TVector3& position) { fPos = position; }

void JPetBaseHit::setScin(JPetScin& scin) { fScin = &scin; }

void JPetBaseHit::Clear(Option_t*)
{
  fTime = 0.0f;
  fEnergy = 0.0f;
  fPos = TVector3();
  fScin = nullptr;
}

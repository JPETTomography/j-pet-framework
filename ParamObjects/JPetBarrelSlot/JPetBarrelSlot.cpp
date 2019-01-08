/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetBarrelSlot.cpp
 */

#include "JPetBarrelSlot.h"

JPetBarrelSlot::JPetBarrelSlot() { SetName("JPetBarrelSlot"); }

JPetBarrelSlot::JPetBarrelSlot(int id, bool isActive, std::string name, float theta, int inFrameID):
  fId(id), fIsActive(isActive), fName(name), fTheta(theta), fInFrameID(inFrameID)
{
  SetName("JPetBarrelSlot");
}

JPetBarrelSlot::JPetBarrelSlot(bool isNull): fIsNullObject(isNull)
{
  SetName("JPetBarrelSlot");
}

bool JPetBarrelSlot::operator==(const JPetBarrelSlot& bslot) const
{
  return getID() == bslot.getID();
}

bool JPetBarrelSlot::operator!=(const JPetBarrelSlot& bslot) const
{
  return getID() != bslot.getID();
}

int JPetBarrelSlot::getID() const
{
  return fId;
}

float JPetBarrelSlot::getTheta() const
{
  return fTheta;
}

bool JPetBarrelSlot::isActive() const
{
  return fIsActive;
}

std::string JPetBarrelSlot::getName() const
{
  return fName;
}

int JPetBarrelSlot::getInFrameID() const
{
  return fInFrameID;
}

bool JPetBarrelSlot::hasLayer() const
{
  return fTRefLayer.GetObject() != 0;
}

const JPetLayer& JPetBarrelSlot::getLayer() const
{
  if (fTRefLayer.GetObject()) return static_cast<JPetLayer&>(*(fTRefLayer.GetObject()));
  else  {
    ERROR("No JPetLayer slot set, Null object will be returned");
    return JPetLayer::getDummyResult();
  }
}

bool JPetBarrelSlot::isNullObject() const
{
  return fIsNullObject;
}

JPetBarrelSlot& JPetBarrelSlot::getDummyResult()
{
  static JPetBarrelSlot DummyResult(true);
  return DummyResult;
}

void JPetBarrelSlot::setLayer(JPetLayer& p_layer)
{
  fTRefLayer = &p_layer;
}

ClassImp(JPetBarrelSlot);

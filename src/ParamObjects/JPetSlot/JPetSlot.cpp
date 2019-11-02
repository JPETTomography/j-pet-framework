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
 *  @file JPetSlot.cpp
 */

#include "JPetLoggerInclude.h"
#include "JPetSlot/JPetSlot.h"

ClassImp(JPetSlot);

JPetSlot::JPetSlot() { SetName("JPetSlot"); }

JPetSlot::JPetSlot(int id, float theta, JPetSlot::Type type):
  fID(id), fTheta(theta), fType(type)
{
  SetName("JPetSlot");
}

JPetSlot::JPetSlot(const JPetSlot &slot):
  fID(slot.getID()), fTheta(slot.getTheta()), fType(slot.getType())
{
  SetName("JPetSlot");
}

JPetSlot::JPetSlot(bool isNull): fIsNullObject(isNull)
{
  SetName("JPetSlot");
}

JPetSlot::~JPetSlot() {}

void JPetSlot::setID(int id)
{
  fID = id;
}

void JPetSlot::setTheta(float theta)
{
  fTheta = theta;
}

void JPetSlot::setType(JPetSlot::Type type)
{
  fType = type;
}

void JPetSlot::setLayer(JPetLayer& layer)
{
  fTRefLayer = &layer;
}

int JPetSlot::getID() const
{
  return fID;
}

float JPetSlot::getTheta() const
{
  return fTheta;
}

JPetSlot::Type JPetSlot::getType() const
{
  return fType;
}

const JPetLayer& JPetSlot::getLayer() const
{
  if (fTRefLayer.GetObject()) {
    return static_cast<JPetLayer&>(*(fTRefLayer.GetObject()));
  } else {
    ERROR("No JPetLayer set, Null object will be returned");
    return JPetLayer::getDummyResult();
  }
}

bool JPetSlot::operator==(const JPetSlot& slot) const
{
  return this->getID() == slot.getID()
    && this->getTheta() == slot.getTheta()
    && this->getType() == slot.getType()
    && this->getLayer() == slot.getLayer();
}

bool JPetSlot::operator!=(const JPetSlot& slot) const
{
  return !(*this == slot);
}

bool JPetSlot::isNullObject() const
{
  return fIsNullObject;
}

JPetSlot& JPetSlot::getDummyResult()
{
  static JPetSlot DummyResult(true);
  return DummyResult;
}

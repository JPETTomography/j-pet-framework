/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetLayer.cpp
 */

#include "JPetLayer.h"

JPetLayer::JPetLayer()
{
  SetName("JPetLayer");
}

JPetLayer::JPetLayer(int id, bool isActive, std::string name, float radius):
  fId(id),
  fIsActive(isActive),
  fName(name),
  fRadius(radius),
  fTRefFrame(NULL)
{
  SetName("JPetLayer");
}

JPetLayer::JPetLayer(bool isNull):
  fIsNullObject(isNull)
{
  SetName("JPetLayer");
}

bool JPetLayer::operator==(const JPetLayer& layer) const
{
  if (getID() == layer.getID()) {
    assert(getRadius() == layer.getRadius());
    assert(getName() == layer.getName());
    assert(getIsActive() == layer.getIsActive());
    return true;
  }
  return false;
}

bool JPetLayer::operator!=(const JPetLayer& layer) const
{
  return ! (*this == layer);
}

int JPetLayer::getID() const
{
  return fId;
}

bool JPetLayer::getIsActive() const
{
  return fIsActive;
}

std::string JPetLayer::getName() const
{
  return fName;
}

float JPetLayer::getRadius() const
{
  return fRadius;
}

const JPetFrame& JPetLayer::getFrame() const
{
  if (fTRefFrame.GetObject()) return static_cast<JPetFrame&>(*(fTRefFrame.GetObject()));
  else {
    ERROR("No JPetFrame slot set, Null object will be returned");
    return JPetFrame::getDummyResult();
  }
}

void JPetLayer::setFrame(JPetFrame& frame)
{
  fTRefFrame = &frame;
}

bool JPetLayer::isNullObject() const
{
  return fIsNullObject;
}

JPetLayer& JPetLayer::getDummyResult()
{
  static JPetLayer DummyResult(true);
  return DummyResult;
}

void JPetLayer::clearTRefFrame()
{
  fTRefFrame = NULL;
}

ClassImp(JPetLayer);

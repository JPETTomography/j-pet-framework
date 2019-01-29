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
 *  @file JPetScin.cpp
 */

#include "JPetScin.h"
#include <cassert>

ClassImp(JPetScin);

JPetScin::JPetScin(): fScinSize(0., 0., 0.)
{
  SetName("JPetScin");
}

JPetScin::JPetScin(int id): fID(id), fScinSize(0., 0., 0.)
{
  SetName("JPetScin");
}

JPetScin::JPetScin(int id, float attenLen, float length, float height, float width):
  fID(id), fAttenLen(attenLen), fScinSize(length, height, width)
{
  SetName("JPetScin");
}

JPetScin::JPetScin(bool isNull): fScinSize(0., 0., 0.), fIsNullObject(isNull)
{
  SetName("JPetScin");
}

JPetScin::~JPetScin(){}

float JPetScin::getScinSize(JPetScin::Dimension dim) const
{
  float value = 0;
  switch (dim) {
  case kLength:
    value = fScinSize.fLength;
    break;
  case kHeight:
    value = fScinSize.fHeight;
    break;
  case kWidth:
    value = fScinSize.fWidth;
    break;
  default:
    assert(1 == 0);
  }
  return value;
}


void JPetScin::setScinSize(JPetScin::Dimension dim, float value)
{
  switch (dim) {
  case kLength:
    fScinSize.fLength = value;
    break;
  case kHeight:
    fScinSize.fHeight = value;
    break;
  case kWidth:
    fScinSize.fWidth = value;
    break;
  default:
    assert(1 == 0);
  }
}

bool JPetScin::operator==(const JPetScin& scin) const
{
  return getID() == scin.getID();
}

bool JPetScin::operator!=(const JPetScin& scin) const
{
  return getID() != scin.getID();
}

int JPetScin::getID() const
{
  return fID;
}

float JPetScin::getAttenLen() const
{
  return fAttenLen;
}

JPetScin::ScinDimensions JPetScin::getScinSize() const
{
  return fScinSize;
}

float JPetScin::getScinSize(Dimension dim) const;

void JPetScin::setAttenLen(float attenLen)
{
  fAttenLen = attenLen;
}

void JPetScin::setScinSize(ScinDimensions size)
{
  fScinSize = size;
}

void JPetScin::setScinSize(Dimension dim, float value);

void JPetScin::setBarrelSlot(JPetBarrelSlot& p_barrelSlot)
{
  fTRefBarrelSlot = &p_barrelSlot;
}

JPetBarrelSlot& JPetScin::getBarrelSlot() const
{
  if (fTRefBarrelSlot.GetObject()) return (JPetBarrelSlot&) * (fTRefBarrelSlot.GetObject());
  else {
    ERROR("No JPetBarrelSlot slot set, Null object will be returned");
    return JPetBarrelSlot::getDummyResult();
  }
}

bool JPetScin::isNullObject() const
{
  return fIsNullObject;
}

JPetScin& JPetScin::getDummyResult()
{
  static JPetScin DummyResult(true);
  return DummyResult;
}

void JPetScin::clearTRefBarrelSlot()
{
  fTRefBarrelSlot = NULL;
}

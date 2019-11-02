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
 *  @file JPetScin.cpp
 */

#include "JPetLoggerInclude.h"
#include "JPetScin/JPetScin.h"

ClassImp(JPetScin);

JPetScin::JPetScin()
{
  SetName("JPetScin");
}

JPetScin::JPetScin(
  int id, float length, float height, float width,
  float center_x, float center_y, float center_z):
  fID(id), fLength(length), fHeight(height), fWidth(width),
  fScinCenter(center_x, center_y, center_z)
{
  SetName("JPetScin");
}

JPetScin::JPetScin(const JPetScin &scin):
  fID(scin.getID()), fLength(scin.getLength()),
  fHeight(scin.getHeight()), fWidth(scin.getWidth()),
  fScinCenter(scin.getCenterX(), scin.getCenterY(), scin.getCenterZ())
{
  SetName("JPetScin");
}

JPetScin::JPetScin(bool isNull): fIsNullObject(isNull)
{
  SetName("JPetScin");
}

JPetScin::~JPetScin(){}

void JPetScin::setID(int id)
{
  fID = id;
}

void JPetScin::setLength(float length)
{
  fLength = length;
}

void JPetScin::setHeight(float height)
{
  fHeight = height;
}

void JPetScin::setWidth(float width)
{
  fWidth = width;
}

void JPetScin::setCenter(TVector3 center)
{
  fScinCenter = center;
}

void JPetScin::setCenterX(float centerX)
{
  fScinCenter[0] = centerX;
}

void JPetScin::setCenterY(float centerY)
{
  fScinCenter[1] = centerY;
}

void JPetScin::setCenterZ(float centerZ)
{
  fScinCenter[2] = centerZ;
}

void JPetScin::setSlot(JPetSlot& slot)
{
  fTRefSlot = &slot;
}

int JPetScin::getID() const
{
  return fID;
}

float JPetScin::getLength() const
{
  return fLength;
}

float JPetScin::getHeight() const
{
  return fHeight;
}

float JPetScin::getWidth() const
{
  return fWidth;
}

TVector3 JPetScin::getCenter() const
{
  return fScinCenter;
}

float JPetScin::getCenterX() const
{
  return fScinCenter.X();
}

float JPetScin::getCenterY() const
{
  return fScinCenter.Y();
}

float JPetScin::getCenterZ() const
{
  return fScinCenter.Z();
}

const JPetSlot& JPetScin::getSlot() const
{
  if (fTRefSlot.GetObject()) {
    return static_cast<JPetSlot&>(*(fTRefSlot.GetObject()));
  } else {
    ERROR("No JPetSlot set, Null object will be returned");
    return JPetSlot::getDummyResult();
  }
}

bool JPetScin::operator==(const JPetScin& scin) const
{
  return this->getID() == scin.getID()
    && this->getLength() == scin.getLength()
    && this->getHeight() == scin.getHeight()
    && this->getWidth() == scin.getWidth()
    && this->getCenter() == scin.getCenter()
    && this->getSlot() == scin.getSlot();
}

bool JPetScin::operator!=(const JPetScin& scin) const
{
  return !(*this == scin);
}

JPetScin& JPetScin::getDummyResult()
{
  static JPetScin DummyResult(true);
  return DummyResult;
}

bool JPetScin::isNullObject() const
{
  return fIsNullObject;
}

void JPetScin::clearTRefSlot()
{
  fTRefSlot = NULL;
}

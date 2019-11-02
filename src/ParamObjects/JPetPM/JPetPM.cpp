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
 *  @file JPetPM.cpp
 */

#include "JPetLoggerInclude.h"
#include "JPetPM/JPetPM.h"

ClassImp(JPetPM);

JPetPM::JPetPM()
{
  SetName("JPetPM");
}

JPetPM::JPetPM(int id, Side side, std::string desc, int matrixPosition):
  fID(id), fSide(side), fDesc(desc), fMatrixPosition(matrixPosition)
{
  SetName("JPetPM");
}

JPetPM::JPetPM(const JPetPM &pm):
  fID(pm.getID()), fSide(pm.getSide()), fDesc(pm.getDesc()), fMatrixPosition(pm.getMatrixPosition())
{
  SetName("JPetPM");
}

JPetPM::JPetPM(bool isNull): fIsNullObject(isNull)
{
  SetName("JPetPM");
}

JPetPM::~JPetPM(){}

void JPetPM::setID(int id)
{
  fID = id;
}

void JPetPM::setSide(JPetPM::Side side)
{
  fSide = side;
}

void JPetPM::setDesc(std::string desc)
{
  fDesc = desc;
}

void JPetPM::setMatrixPosition(int position)
{
  fMatrixPosition = position;
}

void JPetPM::setScin(JPetScin& scin)
{
  fTRefScin = &scin;
}

int JPetPM::getID() const
{
  return fID;
}

JPetPM::Side JPetPM::getSide() const
{
  return fSide;
}

std::string JPetPM::getDesc() const
{
  return fDesc;
}

int JPetPM::getMatrixPosition() const
{
  return fMatrixPosition;
}

JPetScin& JPetPM::getScin() const
{
  if (fTRefScin.GetObject()) {
    return static_cast<JPetScin&>(*(fTRefScin.GetObject()));
  } else {
    ERROR("No JPetScin set, Null object will be returned");
    return JPetScin::getDummyResult();
  }
}

bool JPetPM::operator==(const JPetPM& pm) const
{
  return this->getID() == pm.getID()
    && this->getSide() == pm.getSide()
    && this->getMatrixPosition() == pm.getMatrixPosition()
    && this->getScin() == pm.getScin();
}

bool JPetPM::operator!=(const JPetPM& pm) const
{
  return !(*this == pm);
}

bool JPetPM::isNullObject() const
{
  return fIsNullObject;
}

JPetPM& JPetPM::getDummyResult()
{
  static JPetPM DummyResult(true);
  return DummyResult;
}

void JPetPM::clearTRefScin()
{
  fTRefScin = NULL;
}

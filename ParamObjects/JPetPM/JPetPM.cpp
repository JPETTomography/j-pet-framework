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
 *  @file JPetPM.cpp
 */

#include "JPetPM.h"
#include <cassert>

JPetPM::JPetPM(): fHVgain(std::make_pair(0.0, 0.0))
{
  SetName("JPetPM");
}

JPetPM::JPetPM(int id, std::string description):
  fID(id), fHVgain(std::make_pair(0.0, 0.0)), fDescription(description)
{
  SetName("JPetPM");
}

JPetPM::JPetPM(Side side, int id, int HVset, int HVopt,
  std::pair<float, float> HVgainNumber, std::string description):
  fSide(side), fID(id), fHVset(HVset), fHVopt(HVopt),
  fHVgain(HVgainNumber), fDescription(description)
{
  SetName("JPetPM");
}

JPetPM::JPetPM(bool isNull): fHVgain(std::make_pair(0.0, 0.0)), fIsNullObject(isNull)
{
  SetName("JPetPM");
}

JPetPM::JPetPM(const JPetPM& pm): fSide(pm.fSide), fID(pm.fID), fHVset(pm.fHVset),
  fHVopt(pm.fHVopt), fHVgain(pm.fHVgain), fDescription(pm.fDescription),
  fTRefScin(pm.fTRefScin), fTRefBarrelSlot(pm.fTRefBarrelSlot)
{
  SetName("JPetPM");
  if (pm.hasFEB()) { fTRefFEB = pm.fTRefFEB; }
}

JPetPM::~JPetPM(){}

bool JPetPM::operator==(const JPetPM& pm) const
{
  if ( getID() == pm.getID() ) {
    assert(getSide() == pm.getSide());
    assert(getHVopt() == pm.getHVopt());
    assert(getHVset() == pm.getHVset());
    return true;
  }
  return false;
}

bool JPetPM::operator!=(const JPetPM& pm) const
{
  return !(*this == pm);
}

void JPetPM::clearTRefFEBs()
{
  fTRefFEB = NULL;
}

void JPetPM::clearTRefScin()
{
  fTRefScin = NULL;
}

void JPetPM::clearTRefBarrelSlot()
{
  fTRefBarrelSlot = NULL;
}

JPetPM::Side JPetPM::getSide() const
{
  return fSide;
}

int JPetPM::getID() const
{
  return fID;
}

int JPetPM::getHVset() const
{
  return fHVset;
}

int JPetPM::getHVopt() const
{
  return fHVopt;
}

float JPetPM::getHVgain(GainNumber nr)
{
  return (nr == kFirst) ? fHVgain.first : fHVgain.second;
}

std::pair<float, float> JPetPM::getHVgain()
{
  return fHVgain;
}

std::string JPetPM::getDescription() const
{
  return fDescription;
}

void JPetPM::setSide(JPetPM::Side side)
{
  fSide = side;
}

void JPetPM::setHVset(int set)
{
  fHVset = set;
}

void JPetPM::setHVopt(int opt)
{
  fHVopt = opt;
}

void JPetPM::setHVgain(float g1, float g2)
{
  fHVgain.first = g1;
  fHVgain.second = g2;
}

void JPetPM::setHVgain(const std::pair<float, float>& gain)
{
  fHVgain = gain;
}

void JPetPM::setFEB(JPetFEB& p_FEB)
{
  fTRefFEB = &p_FEB;
}

bool JPetPM::hasFEB() const
{
  return fTRefFEB.GetObject() != 0;
}

const JPetFEB& JPetPM::getFEB() const
{
  if (fTRefFEB.GetObject()) return (JPetFEB&) * (fTRefFEB.GetObject());
  else {
    ERROR("No JPetFEB slot set, Null object will be returned");
    return JPetFEB::getDummyResult();
  }
}

void JPetPM::setScin(JPetScin& p_scin)
{
  fTRefScin = &p_scin;
}

JPetScin& JPetPM::getScin() const
{
  if (fTRefScin.GetObject()) return (JPetScin&) * (fTRefScin.GetObject());
  else {
    ERROR("No JPetScin slot set, Null object will be returned");
    return JPetScin::getDummyResult();
  }
}

void JPetPM::setBarrelSlot(JPetBarrelSlot& p_barrelSlot)
{
  fTRefBarrelSlot = &p_barrelSlot;
}

JPetBarrelSlot& JPetPM::getBarrelSlot() const
{
  if (fTRefBarrelSlot.GetObject()) return (JPetBarrelSlot&) * (fTRefBarrelSlot.GetObject());
  else {
    ERROR("No JPetBarrelSlot slot set, Null object will be returned");
    return JPetBarrelSlot::getDummyResult();
  }
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

ClassImp(JPetPM);

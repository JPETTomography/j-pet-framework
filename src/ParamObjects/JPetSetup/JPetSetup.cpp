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
 *  @file JPetSetup.cpp
 */

#include "JPetSetup/JPetSetup.h"

ClassImp(JPetSetup);

JPetSetup::JPetSetup() { SetName("JPetSetup"); }

JPetSetup::JPetSetup(int id, std::string description): fID(id), fDescription(description)
{
  SetName("JPetSetup");
}

JPetSetup::JPetSetup(const JPetSetup &setup):
  fID(setup.getID()), fDescription(setup.getDescription())
{
  SetName("JPetSetup");
}

JPetSetup::JPetSetup(bool isNull): fIsNullObject(isNull)
{
  SetName("JPetSetup");
}

JPetSetup::~JPetSetup() {}

void JPetSetup::setID(int id)
{
  fID = id;
}

void JPetSetup::setDescription(std::string desc)
{
  fDescription = desc;
}

int JPetSetup::getID() const
{
  return fID;
}

std::string JPetSetup::getDescription() const
{
  return fDescription;
}

bool JPetSetup::operator==(const JPetSetup& setup) const
{
  return this->getID() == setup.getID()
    && this->getDescription() == setup.getDescription();
}

bool JPetSetup::operator!=(const JPetSetup& setup) const
{
  return !(*this == setup);
}

bool JPetSetup::isNullObject() const
{
  return fIsNullObject;
}

JPetSetup& JPetSetup::getDummyResult()
{
  static JPetSetup DummyResult(true);
  return DummyResult;
}

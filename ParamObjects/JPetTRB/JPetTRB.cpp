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
 *  @file JPetTRB.cpp
 */

#include "JPetTRB.h"

ClassImp(JPetTRB);

JPetTRB::JPetTRB()
{
  SetName("JPetTRB");
}

JPetTRB::JPetTRB(int id): fID(id)
{
  SetName("JPetTRB");
}

JPetTRB::JPetTRB(int id, int type, int ch): fID(id), fType(type), fChannel(ch)
{
  SetName("JPetTRB");
}

JPetTRB::JPetTRB(bool isNull): fIsNullObject(isNull)
{
  SetName("JPetTRB");
}

JPetTRB::~JPetTRB(){}

int JPetTRB::getID() const
{
  return fID;
}

int JPetTRB::getType() const
{
  return fType;
}

int JPetTRB::getChannel() const
{
  return fChannel;
}

void JPetTRB::setType(int type)
{
  fType = type;
}

void JPetTRB::setChannel(int ch)
{
  fChannel = ch;
}

bool JPetTRB::operator==(const JPetTRB& trb) const
{
  return getID() == trb.getID();
}

bool JPetTRB::operator!=(const JPetTRB& trb) const
{
  return getID() != trb.getID();
}

bool JPetTRB::isNullObject() const
{
  return fIsNullObject;
}

JPetTRB& JPetTRB::getDummyResult()
{
  static JPetTRB DummyResult(true);
  return DummyResult;
}

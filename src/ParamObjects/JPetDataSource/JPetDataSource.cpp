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
 *  @file JPetDataSource.cpp
 */

#include "JPetDataSource/JPetDataSource.h"

JPetDataSource::JPetDataSource() { SetName("JPetDataSource"); }

JPetDataSource::JPetDataSource(int id, std::string type, unsigned long trbNetAddress, unsigned long hubAddress)
    : fID(id), fType(type), fTRBNetAddress(trbNetAddress), fHubAddress(hubAddress), fIsNullObject(false)
{
  SetName("JPetDataSource");
}

JPetDataSource::JPetDataSource(bool isNull) : fIsNullObject(isNull) { SetName("JPetDataSource"); }

bool JPetDataSource::operator==(const JPetDataSource& dataSource)
{
  return this->getID() == dataSource.getID() && this->getType() == dataSource.getType() &&
         this->getTBRNetAddress() == dataSource.getTBRNetAddress() && this->getHubAddress() == dataSource.getHubAddress();
}

bool JPetDataSource::operator!=(const JPetDataSource& dataSource) { return !(*this == dataSource); }

int JPetDataSource::getID() const { return fID; }

std::string JPetDataSource::getType() const { return fType; }

unsigned long JPetDataSource::getTBRNetAddress() const { return fTRBNetAddress; }

unsigned long JPetDataSource::getHubAddress() const { return fHubAddress; }

bool JPetDataSource::isNullObject() const { return fIsNullObject; }

JPetDataSource& JPetDataSource::getDummyResult()
{
  static JPetDataSource dummyResult(true);
  return dummyResult;
}

ClassImp(JPetDataSource);

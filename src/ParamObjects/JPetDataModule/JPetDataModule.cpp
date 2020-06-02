/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetDataModule.cpp
 */

#include "JPetDataModule/JPetDataModule.h"
#include "JPetLoggerInclude.h"

JPetDataModule::JPetDataModule() { SetName("JPetDataModule"); }

JPetDataModule::JPetDataModule(bool isNull): fIsNullObject(isNull)
{
  SetName("JPetDataModule");
}

JPetDataModule::JPetDataModule(
  int id, std::string type, std::string trb, int number, int offset
) : fID(id), fType(type), fTRBNetAddress(trb), fChannelsNumber(number),
  fChannelsOffset(offset), fIsNullObject(false)
{
  SetName("JPetDataModule");
}

bool JPetDataModule::operator==(const JPetDataModule& dataModule) const
{
  return this->getID() == dataModule.getID()
    && this->getType() == dataModule.getType()
    && this->getTBRNetAddress() == dataModule.getTBRNetAddress()
    && this->getChannelsNumber() == dataModule.getChannelsNumber()
    && this->getChannelsOffset() == dataModule.getChannelsOffset();
}

bool JPetDataModule::operator!=(const JPetDataModule& dataModule) const
{
  return !(*this == dataModule);
}

void JPetDataModule::setDataSource(JPetDataSource& dataSource)
{
  fTRefDataSource = &dataSource;
}

int JPetDataModule::getID() const
{
  return fID;
}

std::string JPetDataModule::getType() const
{
  return fType;
}

std::string JPetDataModule::getTBRNetAddress() const
{
  return fTRBNetAddress;
}

int JPetDataModule::getChannelsNumber() const
{
  return fChannelsNumber;
}

int JPetDataModule::getChannelsOffset() const
{
  return fChannelsOffset;
}

bool JPetDataModule::isNullObject() const
{
  return fIsNullObject;
}

JPetDataSource& JPetDataModule::getDataSource() const
{
  if (fTRefDataSource.GetObject()) {
    return static_cast<JPetDataSource&>(*(fTRefDataSource.GetObject()));
  } else {
    ERROR("No JPetDataSource set, Null object will be returned");
    return JPetDataSource::getDummyResult();
  }
}

JPetDataModule& JPetDataModule::getDummyResult()
{
  static JPetDataModule dummyResult(true);
  return dummyResult;
}

void JPetDataModule::clearTRefDataSource()
{
  fTRefDataSource = NULL;
}

ClassImp(JPetDataModule);

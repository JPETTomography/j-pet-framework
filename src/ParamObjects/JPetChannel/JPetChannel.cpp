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
 *  @file JPetChannel.cpp
 */

#include "JPetChannel/JPetChannel.h"
#include "JPetDataModule/JPetDataModule.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetChannel);

JPetChannel::JPetChannel() { SetName("JPetChannel"); }

JPetChannel::JPetChannel(int id, int thrNum, float thrVal) : fID(id), fThresholdNumber(thrNum), fThresholdValue(thrVal)
{
  if (id < 0)
  {
    ERROR("Chanell ID cannot be negative");
  }
  SetName("JPetChannel");
}

JPetChannel::JPetChannel(const JPetChannel& channel)
    : fID(channel.getID()), fThresholdNumber(channel.getThresholdNumber()), fThresholdValue(channel.getThresholdValue())
{
  if (channel.getID() < 0)
  {
    ERROR("Chanell ID cannot be negative");
  }
  SetName("JPetChannel");
}

JPetChannel::JPetChannel(bool isNull) : fIsNullObject(isNull) { SetName("JPetChannel"); }

JPetChannel::~JPetChannel() {}

void JPetChannel::setID(int id) { fID = id; }

void JPetChannel::setThresholdNumber(int thrNum) { fThresholdNumber = thrNum; }

void JPetChannel::setThresholdValue(float thrVal) { fThresholdValue = thrVal; }

void JPetChannel::setPM(JPetPM& pm) { fTRefPM = &pm; }

void JPetChannel::setDataModule(JPetDataModule& dm) { fTrefDataModule = &dm; }

const int JPetChannel::getID() const { return fID; }

int JPetChannel::getThresholdNumber() const { return fThresholdNumber; }

float JPetChannel::getThresholdValue() const { return fThresholdValue; }

const JPetPM& JPetChannel::getPM() const
{
  if (fTRefPM.GetObject())
  {
    return static_cast<JPetPM&>(*(fTRefPM.GetObject()));
  }
  else
  {
    ERROR("No JPetPM set, Null object will be returned");
    return JPetPM::getDummyResult();
  }
}

const JPetDataModule& JPetChannel::getDataModule() const
{
  if (fTrefDataModule.GetObject())
  {
    return static_cast<JPetDataModule&>(*(fTrefDataModule.GetObject()));
  }
  else
  {
    ERROR("No JPetDataModule set, Null object will be returned");
    return JPetDataModule::getDummyResult();
  }
}

bool JPetChannel::operator==(const JPetChannel& channel)
{
  return this->getID() == channel.getID() && this->getThresholdNumber() == channel.getThresholdNumber() &&
         this->getThresholdValue() == channel.getThresholdValue() && this->getPM() == channel.getPM();
}

bool JPetChannel::operator!=(const JPetChannel& channel) { return !(*this == channel); }

bool JPetChannel::isNullObject() const { return fIsNullObject; }

JPetChannel& JPetChannel::getDummyResult()
{
  static JPetChannel dummyResult(true);
  return dummyResult;
}

void JPetChannel::clearTRefPM() { fTRefPM = nullptr; }
void JPetChannel::clearTRefDataModule() { fTrefDataModule = nullptr; }

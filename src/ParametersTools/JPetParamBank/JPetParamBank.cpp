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
 *  @file JPetParamBank.cpp
 */

#include "JPetParamBank/JPetParamBank.h"

ClassImp(JPetParamBank);

JPetParamBank::JPetParamBank() : fDummy(false) {}

JPetParamBank::JPetParamBank(const bool d) : fDummy(d) {}

JPetParamBank::JPetParamBank(const JPetParamBank& paramBank) : fDummy(false)
{
  copyMapValues(fSetups, paramBank.fSetups);
  copyMapValues(fLayers, paramBank.fLayers);
  copyMapValues(fSlots, paramBank.fSlots);
  copyMapValues(fScins, paramBank.fScins);
  copyMapValues(fPMs, paramBank.fPMs);
  copyMapValues(fChannels, paramBank.fChannels);
  copyMapValues(fDataSources, paramBank.fDataSources);
  copyMapValues(fDataModules, paramBank.fDataModules);
}

JPetParamBank::~JPetParamBank() {}

bool JPetParamBank::isDummy() const { return fDummy; }

void JPetParamBank::clear()
{
  fSetups.clear();
  fLayers.clear();
  fSlots.clear();
  fScins.clear();
  fPMs.clear();
  fChannels.clear();
  fDataSources.clear();
  fDataModules.clear();
}

int JPetParamBank::getSize(ParamObjectType type) const
{
  int size = -1;
  switch (type)
  {
  case kSetup:
    size = getSetupsSize();
    break;
  case kLayer:
    size = getLayersSize();
    break;
  case kSlot:
    size = getSlotsSize();
    break;
  case kScin:
    size = getScinsSize();
    break;
  case kPM:
    size = getPMsSize();
    break;
  case kChannel:
    size = getChannelsSize();
    break;
  case kDataSource:
    size = getDataSourcesSize();
    break;
  case kDataModule:
    size = getDataModulesSize();
    break;
  default:
    ERROR("Bad ParamObject type");
    break;
  }
  return size;
}

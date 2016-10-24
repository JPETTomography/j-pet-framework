/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetScopeParamGetter.cpp
 */

#include "./JPetScopeParamGetter.h"
#include "../JPetScopeConfigParser/JPetScopeConfigParser.h"
#include <TThread.h>
#include "../JPetLoggerInclude.h"

std::map<std::string, JPetParamBank*> JPetScopeParamGetter::gParamCache;

void JPetScopeParamGetter::clearParamCache()
{
  TThread::Lock();
  WARNING("JPetScopeParamGetter::gParamCache will be cleared");
  for (auto & pair : JPetScopeParamGetter::gParamCache) {
    if (pair.second) {
      delete pair.second;
      pair.second = 0;
    }
  }
  JPetScopeParamGetter::gParamCache.clear();
  TThread::UnLock();
}

JPetScopeParamGetter::JPetScopeParamGetter()
{
  /**/
}

JPetScopeParamGetter::~JPetScopeParamGetter()
{
  DEBUG("destructor");
}

JPetParamBank* JPetScopeParamGetter::generateParamBank(const std::string& scopeConfFile)
{
  TThread::Lock();
  JPetScopeConfigParser parser;
  auto config = parser.getConfig(scopeConfFile);
  auto configName = config.fName;
  JPetParamBank* returnedParamBank = 0;
  if ( parser.areObjectsWithDuplicatedIds(config) ) {
    ERROR("Duplicated ids has been found while parsing the configuration scope file! The param bank will not be properly initialized!");
    //returnedParamBank = new JPetParamBank();
  } else {
    if (JPetScopeParamGetter::gParamCache.find(configName) == JPetScopeParamGetter::gParamCache.end()) {
      JPetParamBank* param_bank = new JPetParamBank();
      for (const auto &  bslot : config.fBSlots) {
        JPetBarrelSlot tmp(bslot.fId, bslot.fActive, bslot.fName, bslot.fTheta, bslot.fFrame);
        param_bank->addBarrelSlot(tmp);
      }
      for (const auto &  pm : config.fPMs) {
        JPetPM tmp(pm.fId);
        param_bank->addPM(tmp);
      }

      for (const auto &  scin : config.fScins) {
        JPetScin tmp(scin.fId);
        param_bank->addScintillator(tmp);
      }

      /**
      * A		B
      * PM1	PM2
      * PM3	PM4
      */
      assert(config.fPMs.size() == 4);
      (param_bank->getPM(config.fPMs[0].fId)).setSide(JPetPM::SideA);
      (param_bank->getPM(config.fPMs[1].fId)).setSide(JPetPM::SideB);
      (param_bank->getPM(config.fPMs[2].fId)).setSide(JPetPM::SideA);
      (param_bank->getPM(config.fPMs[3].fId)).setSide(JPetPM::SideB);
      assert(config.fScins.size() == 2);
      (param_bank->getPM(config.fPMs[0].fId)).setScin(param_bank->getScintillator(config.fScins[0].fId));
      (param_bank->getPM(config.fPMs[1].fId)).setScin(param_bank->getScintillator(config.fScins[0].fId));
      (param_bank->getPM(config.fPMs[2].fId)).setScin(param_bank->getScintillator(config.fScins[1].fId));
      (param_bank->getPM(config.fPMs[3].fId)).setScin(param_bank->getScintillator(config.fScins[1].fId));
      assert(config.fBSlots.size() == 2);
      (param_bank->getPM(config.fPMs[0].fId)).setBarrelSlot(param_bank->getBarrelSlot(config.fBSlots[0].fId));
      (param_bank->getPM(config.fPMs[1].fId)).setBarrelSlot(param_bank->getBarrelSlot(config.fBSlots[0].fId));
      (param_bank->getPM(config.fPMs[2].fId)).setBarrelSlot(param_bank->getBarrelSlot(config.fBSlots[1].fId));
      (param_bank->getPM(config.fPMs[3].fId)).setBarrelSlot(param_bank->getBarrelSlot(config.fBSlots[1].fId));

      (param_bank->getScintillator(config.fScins[0].fId)).setBarrelSlot(param_bank->getBarrelSlot(config.fBSlots[0].fId));
      (param_bank->getScintillator(config.fScins[1].fId)).setBarrelSlot(param_bank->getBarrelSlot(config.fBSlots[1].fId));
      JPetScopeParamGetter::gParamCache[configName] = param_bank;
    }
    returnedParamBank = new JPetParamBank(*JPetScopeParamGetter::gParamCache[configName]);
  }
  TThread::UnLock();
  return returnedParamBank;
}

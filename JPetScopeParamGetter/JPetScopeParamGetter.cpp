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
#include <TThread.h>

std::map<std::string, JPetParamBank*> JPetScopeParamGetter::fParamCache;

JPetScopeParamGetter::JPetScopeParamGetter()
{
  /**/
}

JPetScopeParamGetter::~JPetScopeParamGetter()
{
  /**/
}

JPetParamBank* JPetScopeParamGetter::generateParamBank(const scope_config::Config& config)
{
  TThread::Lock();
  auto configName = config.fName;
  if (fParamCache.find(configName) == fParamCache.end()) {
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
    (param_bank->getPM(0)).setSide(JPetPM::SideA);
    (param_bank->getPM(1)).setSide(JPetPM::SideB);
    (param_bank->getPM(2)).setSide(JPetPM::SideA);
    (param_bank->getPM(3)).setSide(JPetPM::SideB);

    (param_bank->getPM(0)).setScin(param_bank->getScintillator(0));
    (param_bank->getPM(1)).setScin(param_bank->getScintillator(0));
    (param_bank->getPM(2)).setScin(param_bank->getScintillator(1));
    (param_bank->getPM(3)).setScin(param_bank->getScintillator(1));

    (param_bank->getPM(0)).setBarrelSlot(param_bank->getBarrelSlot(0));
    (param_bank->getPM(1)).setBarrelSlot(param_bank->getBarrelSlot(0));
    (param_bank->getPM(2)).setBarrelSlot(param_bank->getBarrelSlot(1));
    (param_bank->getPM(3)).setBarrelSlot(param_bank->getBarrelSlot(1));

    (param_bank->getScintillator(0)).setBarrelSlot(param_bank->getBarrelSlot(0));
    (param_bank->getScintillator(1)).setBarrelSlot(param_bank->getBarrelSlot(1));
    fParamCache[configName] = param_bank;
  }
  JPetParamBank* returnedParamBank = new JPetParamBank(*fParamCache[configName]);

  TThread::UnLock();
  return returnedParamBank;
}

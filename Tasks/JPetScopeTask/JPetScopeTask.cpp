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
 *  @file JPetScopeTask.cpp
 */

#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetScopeData/JPetScopeData.h"
#include "JPetScopeTaskUtils.h"
#include <boost/filesystem.hpp>
#include "JPetScopeTask.h"
#include <iostream>
#include <memory>

using namespace boost::filesystem;

JPetScopeTask::JPetScopeTask(const char* name): JPetUserTask(name){}

bool JPetScopeTask::run(const JPetDataInterface& inData)
{
  auto& currData = dynamic_cast<const JPetScopeData&>(inData);
  fInputFilesInCurrentWindow = currData.getEvent();
  return exec();
}

bool JPetScopeTask::init()
{
  INFO("Scope Task started");
  fOutputEvents = new JPetTimeWindow("JPetRecoSignal");
  return true;
}

bool JPetScopeTask::exec()
{
  DEBUG("JPetScopeTask getParamBank() called");
  auto& bank = getParamBank();
  if (bank.isDummy()) {
    ERROR("bank is Dummy");
  } else {
    DEBUG(std::string("time window index:") + std::to_string(fInputFilesInCurrentWindow.first));
    auto files = fInputFilesInCurrentWindow.second;
    for (const auto& file : files ) {
      DEBUG(std::string("file to open:") + file.first);
      JPetRecoSignal sig = RecoSignalUtils::generateSignal(file.first.c_str());
      DEBUG("before setPM");
      const JPetPM& pm = bank.getPM(file.second);
      const JPetBarrelSlot& bs = pm.getBarrelSlot();
      sig.setPM(pm);
      sig.setBarrelSlot(bs);
      DEBUG("after setPM");
      fOutputEvents->add<JPetRecoSignal>(sig);
    }
  }
  return true;
}

bool JPetScopeTask::terminate()
{
  INFO("Scope Task finished");
  return true;
}

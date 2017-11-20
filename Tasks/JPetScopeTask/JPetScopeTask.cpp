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
 *  @file JPetScopeTask.cpp
 *  @brief Module for oscilloscope data
 *  Reads oscilloscope ASCII files and produces JPetRecoSignal objects.
 */

#include "JPetScopeTask.h"
#include "./JPetParamManager/JPetParamManager.h"

#include <iostream>
#include "JPetScopeTaskUtils.h"
#include "./JPetCommonTools/JPetCommonTools.h"

#include <boost/filesystem.hpp>
using namespace boost::filesystem;


JPetScopeTask::JPetScopeTask(const char* name):
  JPetTask(name)
{
}

bool JPetScopeTask::init(const JPetParamsInterface& inOptions)
{
  fParams = dynamic_cast<const JPetParams&>(inOptions);
  return init();
}

bool JPetScopeTask::run(const JPetDataInterface&)
{
  return exec();
}

bool JPetScopeTask::terminate(JPetParamsInterface&)
{
  return terminate();
}

int JPetScopeTask::getTimeWindowIndex(const std::string&  pathAndFileName)
{
  DEBUG("JPetScopeTask");
  int time_window_index = -1;
  if (!boost::filesystem::exists(pathAndFileName)) {
    ERROR("File does not exist ");
  }
  int res = sscanf(JPetCommonTools::extractFileNameFromFullPath(pathAndFileName).c_str(), "%*3s %d", &time_window_index);
  if (res <= 0) {
    ERROR("scanf failed");
    return -1;
  } else {
    return time_window_index;
  }
}

bool JPetScopeTask::init()
{
  return true;
}

bool JPetScopeTask::exec()
{
  DEBUG("JPetScopeTask getParamBank() called");
  auto& bank = getParamBank();
  if (bank.isDummy()) {
    ERROR("bank is Dummy");
  } else {
    auto inputFilesInTimeWindowOrder = getFilesInTimeWindowOrder(fInputFiles);
    for (const auto& file : inputFilesInTimeWindowOrder) {
      DEBUG(std::string("file to open:") + file.first);
      JPetRecoSignal sig = RecoSignalUtils::generateSignal(file.first.c_str());
      DEBUG("before setPM");
      const JPetPM& pm = bank.getPM(file.second);
      const JPetBarrelSlot& bs = pm.getBarrelSlot();
      sig.setPM(pm);
      sig.setBarrelSlot(bs);
      DEBUG("after setPM");
      assert(fWriter);
      fWriter->write(sig);
    }
  }
  return true;
}

bool JPetScopeTask::terminate()
{
  return true;
}

std::multimap<std::string, int, cmpByTimeWindowIndex> JPetScopeTask::getFilesInTimeWindowOrder(const std::map<std::string, int>& inputFiles) const
{
  std::multimap<std::string, int, cmpByTimeWindowIndex> orderedMap(inputFiles.begin(), inputFiles.end());
  return orderedMap;
}

void JPetScopeTask::setStatistics(JPetStatistics* statistics)
{
  fStatistics = statistics;
}

JPetStatistics& JPetScopeTask::getStatistics()
{
  assert(fStatistics);
  return *fStatistics;
}

const JPetParamBank& JPetScopeTask::getParamBank()
{
  DEBUG("JPetScopeTask");
  auto paramManager = fParams.getParamManager();
  assert(paramManager);
  return paramManager->getParamBank();
}

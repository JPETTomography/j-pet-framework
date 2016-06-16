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
#include "../JPetParamManager/JPetParamManager.h"

#include <iostream>
#include "JPetScopeTaskUtils.h"
#include "../JPetCommonTools/JPetCommonTools.h"

#include <boost/filesystem.hpp>
using namespace boost::filesystem;


JPetScopeTask::JPetScopeTask(const char * name, const char * description):
  JPetTask(name, description),
  fWriter(0)
{
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

void JPetScopeTask::exec() 
{
  DEBUG("JPetScopeTask getParamBank() called"); 
  assert(fParamManager);
  auto& bank = fParamManager->getParamBank(); 
  if (bank.isDummy()) {
    ERROR("bank is Dummy");
  } else {
    auto inputFilesInTimeWindowOrder = getFilesInTimeWindowOrder(fInputFiles);
    for(const auto & file : inputFilesInTimeWindowOrder){
      DEBUG(std::string("file to open:")+file.first);
      JPetRecoSignal sig = RecoSignalUtils::generateSignal(file.first.c_str());
      sig.setTimeWindowIndex(getTimeWindowIndex(file.first));
      DEBUG("before setPM");
      const JPetPM & pm = bank.getPM(file.second);
      sig.setPM(pm);
      DEBUG("after setPM");
      assert(fWriter);
      fWriter->write(sig);
    }
  }
}


std::multimap<std::string, int, cmpByTimeWindowIndex> JPetScopeTask::getFilesInTimeWindowOrder(const std::map<std::string, int>& inputFiles) const
{
  std::multimap<std::string, int, cmpByTimeWindowIndex> orderedMap(inputFiles.begin(), inputFiles.end());
  return orderedMap;
}

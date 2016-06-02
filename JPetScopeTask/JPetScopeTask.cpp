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
#include <string>
#include "JPetScopeTaskUtils.h"

#include <boost/filesystem.hpp>
using namespace boost::filesystem;


JPetScopeTask::JPetScopeTask(const char * name, const char * description):
  JPetTask(name, description),
  fWriter(0)
{
}

int JPetScopeTask::getTimeWindowIndex(const std::string&  pathAndFileName) const
{
  int time_window_index = -1;
  sscanf(path(pathAndFileName).filename().string().c_str(), "%*3s %d", &time_window_index);
  return time_window_index;
}

void JPetScopeTask::exec() 
{
  assert(fParamManager);
  const std::vector<JPetPM*> pms = fParamManager->getParamBank().getPMs(); 
  assert(pms.size() == 4);
  for(size_t i = 0u; i < pms.size(); ++i ) {
    JPetPM* pm = pms[i];
    assert(pm);
    if (fInputFiles.find(i) != fInputFiles.end()) {
      const auto& files = fInputFiles.find(i)->second; 
      for (const auto& file: files) {
        JPetRecoSignal sig = RecoSignalUtils::generateSignal(file.c_str());
        sig.setTimeWindowIndex(getTimeWindowIndex(file));
        sig.setPM(*pm);
        assert(fWriter);
        fWriter->write(sig);
      }
    } else {
      ERROR("Could not find the Input Files for given set");
    }
  }
}

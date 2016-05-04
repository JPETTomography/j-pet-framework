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
#include <boost/iterator/zip_iterator.hpp> ///for zip iterator
#include <iterator> /// for zip iterator


JPetScopeTask::JPetScopeTask(const char * name, const char * description):
  JPetTask(name, description),
  fWriter(0),
  fParamManager(0)
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
  assert(fInputFiles.size() == 4);
  assert(pms.size() == fInputFiles.size());
  for(size_t i = 0u; i < fInputFiles.size(); ++i ) {
    std::string file = fInputFiles[i];
    JPetRecoSignal sig = RecoSignalUtils::generateSignal(file.c_str());
    sig.setTimeWindowIndex(getTimeWindowIndex(file));
    JPetPM* pm = pms[i];
    assert(pm);
    sig.setPM(*pm);
    assert(fWriter);
    fWriter->write(sig);
  }  
  
  //std::string osc_file = *(fConfig->pIter);
  //std::string filename;
  
  //int time_window_index = getTimeWindowIndex(osc_file);
  
  //JPetRecoSignal rsig1 = RecoSignalUtils::generateSignal(osc_file.c_str());
  //rsig1.setPM(*(fConfig->pPM1));
  //rsig1.setTimeWindowIndex(time_window_index);
  
  //filename = path(*(fConfig->pIter)).filename().string();
  //filename[1] = (fConfig->pPrefix2)[1];
  //osc_file = path(*(fConfig->pIter)).parent_path().string();
  //osc_file+= "/";
  //osc_file+= filename;
  
  //JPetRecoSignal rsig2 = RecoSignalUtils::generateSignal(osc_file.c_str());
  //rsig2.setPM(*(fConfig->pPM2));
  //rsig2.setTimeWindowIndex(time_window_index);
  
  //filename = path(*(fConfig->pIter)).filename().string();
  //filename[1] = (fConfig->pPrefix3)[1];
  //osc_file = path(*(fConfig->pIter)).parent_path().string();
  //osc_file+= "/";
  //osc_file+= filename;
  
  //JPetRecoSignal rsig3 = RecoSignalUtils::generateSignal(osc_file.c_str());
  //rsig3.setPM(*(fConfig->pPM3));
  //rsig3.setTimeWindowIndex(time_window_index);
  
  //filename = path(*(fConfig->pIter)).filename().string();
  //filename[1] = (fConfig->pPrefix4)[1];
  //osc_file = path(*(fConfig->pIter)).parent_path().string();
  //osc_file+= "/";
  //osc_file+= filename;
  
  //JPetRecoSignal rsig4 = RecoSignalUtils::generateSignal(osc_file.c_str());
  //rsig4.setPM(*(fConfig->pPM4));
  //rsig4.setTimeWindowIndex(time_window_index);
  
  //fWriter->write(rsig1);
  //fWriter->write(rsig2);
  //fWriter->write(rsig3);
  //fWriter->write(rsig4);
}

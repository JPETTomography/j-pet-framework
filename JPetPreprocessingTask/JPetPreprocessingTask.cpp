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
 *  @file JPetPreprocessingTask.cpp
 */


#include "JPetPreprocessingTask.h"
#include "../JPetCommonTools/JPetCommonTools.h"

JPetPreprocessingTask::JPetPreprocessingTask(const char* name) : JPetTask(name)
{

}

bool JPetPreprocessingTask::init(const JPetParamsInterface& inOptions)
{
  auto params = dynamic_cast<const JPetParams&>(inOptions);
  using namespace jpet_options_tools;
  auto options = params.getOptions();
  auto paramMgr = params.getParamManager();
  if (!paramMgr) {
    ERROR("Param manager is not set");
    return false;
  }
  auto runNum = getRunNumber(options);
  if (runNum >= 0) {
    try {
      paramMgr->fillParameterBank(runNum);
    } catch (const std::exception& e) {
      ERROR(std::string("Param bank was not generated correctly with error: ") + e.what() + "\n The run number used:" + JPetCommonTools::intToString(runNum));
      return false;
    }
    if (isLocalDBCreate(options)) {
      JPetParamSaverAscii saver;
      saver.saveParamBank(paramMgr->getParamBank(), runNum, getLocalDBCreate(options));
    }
  }
  return true;
}

bool JPetPreprocessingTask::run(const JPetDataInterface& inData)
{
  return true;
}

bool JPetPreprocessingTask::terminate(JPetParamsInterface& outOptions)
{
  return true;
}
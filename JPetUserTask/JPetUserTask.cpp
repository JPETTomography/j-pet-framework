/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetUserTask.cpp
 */

#include "./JPetUserTask.h"

JPetUserTask::JPetUserTask(const char* name):
  JPetTask(name)
{
}

bool JPetUserTask::init(const JPetParamsInterface& inOptions)
{
  fParams = dynamic_cast<const JPetParams&>(inOptions);
  return init(); /// virtual function must be defined in the descendent class
}

bool JPetUserTask::run()
{
  return exec();
}


bool JPetUserTask::terminate(JPetParamsInterface& outOptions)
{
  outOptions = fParams;
  return terminate(); /// virtual function must be defined in the descendent class
}

const JPetParamBank& JPetUserTask::getParamBank()
{
  DEBUG("JPetTask");
  auto paramManager = fParams.getParamManager();
  assert(paramManager);
  return paramManager->getParamBank();
}

void JPetUserTask::setStatistics(std::unique_ptr<JPetStatistics> statistics)
{
  fStatistics = std::move(statistics);
}

JPetStatistics& JPetUserTask::getStatistics()
{
  assert(fStatistics);
  return *fStatistics;
}

void JPetUserTask::setEvent(TObject* ev)
{
  fEvent = ev;
}

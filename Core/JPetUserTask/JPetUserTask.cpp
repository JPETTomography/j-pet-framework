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
 *  @file JPetUserTask.cpp
 */

#include "./JPetData/JPetData.h"
#include "./JPetUserTask.h"

JPetUserTask::JPetUserTask(const char* name): JPetTask(name) {}

/**
 * Virtual function must be defined in the descendent class
 */
bool JPetUserTask::init(const JPetParamsInterface& inOptions)
{
  fParams = dynamic_cast<const JPetParams&>(inOptions);
  return init();
}

/**
 * Virtual function must be defined in the descendent class
 */
bool JPetUserTask::run(const JPetDataInterface& inData)
{
  clearOutputEvents();
  auto event = dynamic_cast<const JPetData&>(inData);
  setEvent(&(event.getEvent()));
  return exec();
}

/**
 * Virtual function must be defined in the descendent class
 */
bool JPetUserTask::terminate(JPetParamsInterface& outOptions)
{
  outOptions = fParams;
  return terminate();
}

const JPetParamBank& JPetUserTask::getParamBank()
{
  DEBUG("JPetUserTask");
  auto paramManager = fParams.getParamManager();
  assert(paramManager);
  return paramManager->getParamBank();
}

void JPetUserTask::setStatistics(JPetStatistics* statistics)
{
  fStatistics = statistics;
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

jpet_options_tools::OptsStrAny JPetUserTask::getOptions() const
{
  return fParams.getOptions();
}

JPetTimeWindow* JPetUserTask::getOutputEvents()
{
  return fOutputEvents;
}

void JPetUserTask::clearOutputEvents()
{
  if (fOutputEvents) {
    fOutputEvents->Clear();
  }
}

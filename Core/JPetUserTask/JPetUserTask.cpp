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

bool JPetUserTask::init(const JPetParams& inOptions)
{
  fParams = inOptions;
  return init();
}

bool JPetUserTask::run(const JPetDataInterface& inData)
{
  clearOutputEvents();
  try {
    auto event = dynamic_cast<const JPetData&>(inData);
    setEvent(&(event.getEvent()));
  } catch (const std::bad_cast& ex) {
    WARNING("Input data type is not the expected one in User Task,  No event is set.");
  }
  return exec();
}

bool JPetUserTask::terminate(JPetParams& outOptions)
{
  bool result = terminate();
  outOptions = fParams;
  return result;
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

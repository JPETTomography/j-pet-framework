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
 *  @file JPetTaskLooper.cpp
 */

#include "JPetTaskLooper.h"
#include "JPetLoggerInclude.h"
#include "JPetParams/JPetParams.h"
#include "JPetData/JPetData.h"

JPetTaskLooper::JPetTaskLooper(const char* name, std::unique_ptr<JPetTask> subtask, Predicate isCondition):
  JPetTask(name),
  fIsCondition(isCondition)
{
  addSubTask(std::move(subtask));
}

bool JPetTaskLooper::init(const JPetParamsInterface&)
{
  return true;
}

bool JPetTaskLooper::run(const JPetDataInterface&)
{
  JPetParams inParams;
  JPetParams outParams;
  JPetDataInterface nullDataObject;
  auto subTasks = getSubTasks();
  if (subTasks.empty()) {
    WARNING("No subtask defined in JPetTaskLooper");
  }
  for (const auto& subTask : subTasks) {
    if (!subTask) {
      ERROR("some subTasks are nullptr");
      return false;
    }
  }
  while (fIsCondition(inParams)) {
    for (const auto& subTask : subTasks) {
      subTask->init(inParams);
      subTask->run(nullDataObject);
      subTask->terminate(outParams);
      inParams = outParams;
    }
  }
  return true;
}

bool JPetTaskLooper::terminate(JPetParamsInterface&)
{
  return true;
}

void JPetTaskLooper::setConditionFunction(Predicate isCondition)
{
  fIsCondition = isCondition;
}


Predicate JPetTaskLooper::getMaxIterationPredicate(int maxIteration)
{
  assert(maxIteration >=0);
  int counter = 0;
  auto iterationFunction = [maxIteration, counter](const JPetParamsInterface&) mutable ->bool {
    if (counter < maxIteration) {
      counter++;
      return true;
    } else {
      return false;
    }
  };
  return iterationFunction; 
}

Predicate JPetTaskLooper::getStopOnOptionPredicate(const std::string stopIterationOptName)
{
  auto stopFunction = [stopIterationOptName](const JPetParamsInterface& params)->bool {
    using namespace jpet_options_tools;
    auto options = (static_cast<const JPetParams&>(params)).getOptions();
    bool continueIteration = !(isOptionSet(options, stopIterationOptName) && (getOptionAsBool(options, stopIterationOptName)));
    return continueIteration;
  };
  return stopFunction; 
}

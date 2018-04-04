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
  for (auto subTask : subTasks) {
    if (!subTask) {
      ERROR("some subTasks are nullptr");
      return false;
    }
  }
  /// The last subtask can set inParams in its terminate() method.
  /// The inParams are passed to fIsCondtion function and can be used
  /// inside it as a 'flag' to mark the end of iterations.
  while (fIsCondition(inParams)) {
    for (auto subTask : subTasks) {
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

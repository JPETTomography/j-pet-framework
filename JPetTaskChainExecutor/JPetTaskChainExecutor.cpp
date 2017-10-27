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
 *  @file JPetTaskChainExecutor.cpp
 */

#include "JPetTaskChainExecutor.h"

#include <cassert>
#include <memory>
#include <chrono>

#include "JPetTaskChainExecutorUtils.h"
#include "../JPetLoggerInclude.h"

JPetTaskChainExecutor::JPetTaskChainExecutor(TaskGeneratorChain* taskGeneratorChain, int processedFileId, const OptionsPerFile& opts):
  fInputSeqId(processedFileId),
  ftaskGeneratorChain(taskGeneratorChain)
{
  assert(taskGeneratorChain->size() == opts.size());
  /// ParamManager is generated and added to fParams
  fParams = JPetTaskChainExecutorUtils::generateParams(opts);
  assert(fParams.front().getParamManager());
  if (taskGeneratorChain) {
    for (auto taskGenerator : *ftaskGeneratorChain) {
      auto task = taskGenerator();
      fTasks.push_back(task);
    }
  } else {
    ERROR("taskGeneratorChain is null while constructing JPetTaskChainExecutor");
  }
}

bool JPetTaskChainExecutor::process()
{
  JPetTimer timer;
  JPetDataInterface nullDataObject;
  JPetParams controlParams; /// Parameters used to control the input file type and event range.

  assert(fTasks.size() == fParams.size());
  auto currParamsIt = fParams.begin();

  /// We iterate over both tasks and parameters
  for (auto currentTaskIt = fTasks.begin(); currentTaskIt != fTasks.end(); currentTaskIt++) {

    auto currentTask  =  *currentTaskIt;
    auto taskName = currentTask->getName();

    assert(currParamsIt != fParams.end());
    auto currParams = *currParamsIt;
    /// We generate input parameters based on the current parameter set and the controlParams produced by
    /// the previous task.
    auto inputParams = JPetTaskChainExecutorUtils::generateParams(currParams, controlParams);
    jpet_options_tools::printOptionsToLog(currParams.getOptions(), std::string("Options for ") + taskName);
    currParamsIt++;

    timer.startMeasurement();
    INFO(Form("Starting task: %s", taskName.c_str()));
    if (!currentTask->init(inputParams)) {
      ERROR("In task initialization");
      return false;
    }
    if (!currentTask->run(nullDataObject)) {
      ERROR("In task run()");
      return false;
    }
    if (!currentTask->terminate(controlParams)) { /// Here controParams can be modified by the current task.
      ERROR("In task terminate() ");
      return false;
    }

    timer.stopMeasurement("task " + taskName);
  }
  INFO(timer.getAllMeasuredTimes());
  INFO(timer.getTotalMeasuredTime());
  return true;
}

void* JPetTaskChainExecutor::processProxy(void* runner)
{
  assert(runner);
  static_cast<JPetTaskChainExecutor*>(runner)->process();
  return 0;
}

TThread* JPetTaskChainExecutor::run()
{
  TThread* thread = new TThread(std::to_string(fInputSeqId).c_str(), processProxy, (void*)this);
  assert(thread);
  thread->Run();
  return thread;
}

JPetTaskChainExecutor::~JPetTaskChainExecutor()
{
  for (auto& task : fTasks) {
    if (task) {
      delete task;
      task = 0;
    }
  }
}

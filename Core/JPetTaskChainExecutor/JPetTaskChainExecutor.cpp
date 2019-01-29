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
 *  @file JPetTaskChainExecutor.cpp
 */

#include "JPetTaskChainExecutor.h"

#include <cassert>
#include <memory>

#include "./JPetParamsFactory/JPetParamsFactory.h"
#include "./JPetLoggerInclude.h"
#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"

JPetTaskChainExecutor::JPetTaskChainExecutor(const TaskGeneratorChain& taskGeneratorChain, int processedFileId, const jpet_options_tools::OptsStrAny& opts):
  fInputSeqId(processedFileId),
  ftaskGeneratorChain(taskGeneratorChain)
{
  /// ParamManager is generated and added to fParams
  fParams = jpet_params_factory::generateParams(opts);
  assert(fParams.getParamManager());
  for (auto taskGenerator : ftaskGeneratorChain) {
    auto task = taskGenerator();
    fTasks.push_back(std::move(task));
  }
}

bool JPetTaskChainExecutor::process()
{
  JPetTimer timer;
  JPetDataInterface nullDataObject;
  JPetParams controlParams; /// Parameters used to control the input file type and event range.

  /// We iterate over both tasks and parameters
  for (const auto& currentTask : fTasks) {
    auto taskName = currentTask->getName();
    auto& currParams = fParams;
    /// We generate input parameters based on the current parameter set and the controlParams produced by
    /// the previous task.
    currParams = jpet_params_factory::generateParams(currParams, controlParams);
    jpet_options_tools::printOptionsToLog(currParams.getOptions(), std::string("Options for ") + taskName);
    timer.startMeasurement();
    INFO(Form("Starting task: %s", taskName.c_str()));
    if (!currentTask->init(currParams)) {
      ERROR("In task " + taskName + " init()");
      return false;
    }
    if (!currentTask->run(nullDataObject)) {
      ERROR("In task " + taskName + " run()");
      return false;
    }
    if (!currentTask->terminate(controlParams)) { /// Here controParams can be modified by the current task.
      ERROR("In task " + taskName + " terminate()");
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
}

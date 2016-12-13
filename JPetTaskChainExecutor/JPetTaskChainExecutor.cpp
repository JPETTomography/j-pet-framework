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
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include "../JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "../JPetParamGetterAscii/JPetParamSaverAscii.h"
#include "../JPetLoggerInclude.h"
#include "JPetTaskChainExecutorUtils.h"
#include <memory>


JPetTaskChainExecutor::JPetTaskChainExecutor(TaskGeneratorChain* taskGeneratorChain, int processedFileId, JPetOptions opt) :
  fInputSeqId(processedFileId),
  fParamManager(0),
  ftaskGeneratorChain(taskGeneratorChain),
  fOptions(opt)
{
  fParamManager = JPetTaskChainExecutorUtils::generateParamManager(fOptions);
  if (taskGeneratorChain) {
    for (auto taskGenerator : *ftaskGeneratorChain) {
      auto task = taskGenerator();
      ///@todo change it
      (dynamic_cast<JPetTaskIO*>(task))->setParamManager(fParamManager);
      fTasks.push_back(task);
    }
  } else {
    ERROR("taskGeneratorChain is null while constructing JPetTaskChainExecutor");
  }
}

bool JPetTaskChainExecutor::preprocessing(const JPetOptions& options, JPetParamManager* manager, std::list<JPetTaskRunnerInterface*>& tasks)
{
  JPetTaskChainExecutorUtils utils;
  return utils.process(options, manager, tasks);
}

bool JPetTaskChainExecutor::process()
{
  if (!preprocessing(fOptions, fParamManager, fTasks)) {
    ERROR("Error in preprocessing");
    return false;
  }
  for (auto currentTask = fTasks.begin(); currentTask != fTasks.end(); currentTask++) {
    JPetOptions::Options currOpts = fOptions.getOptions();
    if (currentTask != fTasks.begin()) {
      /// Ignore the event range options for all but the first task.
      currOpts = JPetOptions::resetEventRange(currOpts);
      /// For all but the first task,
      /// the input path must be changed if
      /// the output path argument -o was given, because the input
      /// data for them will lay in the location defined by -o.
      auto outPath  = currOpts.at("outputPath");
      if (!outPath.empty()) {
        currOpts.at("inputFile") = outPath + JPetCommonTools::extractPathFromFile(currOpts.at("inputFile")) + JPetCommonTools::extractFileNameFromFullPath(currOpts.at("inputFile"));
      }
    }
    //auto taskCurr = dynamic_cast<JPetTask*> (dynamic_cast<JPetTaskLoader*>(*currentTask)->getTask());
    auto taskCurr = std::dynamic_pointer_cast<JPetTask>((*currentTask)->getTask());
    auto taskName = taskCurr->GetName();
    INFO(Form("Starting task: %s", taskName));
    /// @todo fix it
    auto taskRunnerCurr =  dynamic_cast<JPetTaskIO*> (*currentTask);
    taskRunnerCurr->init(currOpts);
    taskRunnerCurr->exec();
    taskRunnerCurr->terminate();
    INFO(Form("Finished task: %s", taskName));
  }
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
  TThread* thread = new TThread(to_string(fInputSeqId).c_str(), processProxy, (void*)this);
  assert(thread);
  thread->Run();
  return thread;
}

JPetTaskChainExecutor::~JPetTaskChainExecutor()
{
  for (auto & task : fTasks) {
    if (task) {
      delete task;
      task = 0;
    }
  }
}


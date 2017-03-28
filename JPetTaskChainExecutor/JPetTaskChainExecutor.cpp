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
#include <chrono>


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
  namespace stdc = std::chrono;
  std::vector<std::pair<std::string, stdc::seconds>> elapsedTime;
  auto startTime = stdc::system_clock::now();

  if (!preprocessing(fOptions, fParamManager, fTasks)) {
    ERROR("Error in preprocessing");
    return false;
  }

  elapsedTime.push_back(std::make_pair("Preprocessing", stdc::duration_cast< stdc::seconds > (stdc::system_clock::now() - startTime)));

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
    auto taskCurr = dynamic_cast<JPetTask*> (dynamic_cast<JPetTaskLoader*>(*currentTask)->getTask());
    //auto taskCurr = std::dynamic_pointer_cast<JPetTask>((*currentTask)->getTask());
    auto taskName = taskCurr->GetName();
    startTime = stdc::system_clock::now();
    INFO(Form("Starting task: %s", taskName));
    JPetTaskChainExecutor::printCurrentOptionsToLog(currOpts);
    /// @todo fix it
    auto taskRunnerCurr =  dynamic_cast<JPetTaskIO*> (*currentTask);
    taskRunnerCurr->init(currOpts);
    taskRunnerCurr->exec();
    taskRunnerCurr->terminate();

    elapsedTime.push_back(std::make_pair("task " + std::string(taskName), stdc::duration_cast< stdc::seconds > (stdc::system_clock::now() - startTime)));
    INFO(Form("Finished task: %s", taskName));
  }
  for (auto & el : elapsedTime) {
    INFO("Elapsed time for " + el.first + ":" + el.second.count() + " [s]");
  }
  auto total = std::accumulate(elapsedTime.begin(),
                               elapsedTime.end(),
                               stdc::seconds (0),
  [](const stdc::seconds prev, const std::pair <std::string, stdc::seconds>& el) {
    return prev + el.second;
  }
                              );
  INFO(std::string("Total elapsed time:") + total.count() + " [s]");

  return true;
}

void JPetTaskChainExecutor::printCurrentOptionsToLog(const JPetOptions::Options& currOpts)
{
  INFO("Current options:");
  for (const auto & el : currOpts) {
    INFO(el.first + "=" + el.second);
  }
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
  for (auto & task : fTasks) {
    if (task) {
      delete task;
      task = 0;
    }
  }
}


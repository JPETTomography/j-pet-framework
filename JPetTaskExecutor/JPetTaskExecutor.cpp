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
 *  @file JPetTaskExecutor.cpp
 */

#include "JPetTaskExecutor.h"
#include <cassert>
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include "../JPetScopeLoader/JPetScopeLoader.h"
#include "../JPetTaskLoader/JPetTaskLoader.h"
#include "../JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "../JPetParamGetterAscii/JPetParamSaverAscii.h"
#include "../JPetLoggerInclude.h"


JPetTaskExecutor::JPetTaskExecutor(TaskGeneratorChain* taskGeneratorChain, int processedFileId, JPetOptions opt) :
  fProcessedFile(processedFileId),
  ftaskGeneratorChain(taskGeneratorChain),
  fOptions(opt)
{
		if (fOptions.isLocalDB()) {
				fParamManager = new JPetParamManager(new JPetParamGetterAscii(fOptions.getLocalDB()));
		} else {
				fParamManager = new JPetParamManager();
		}
  if (taskGeneratorChain) {
    for (auto taskGenerator : *ftaskGeneratorChain) {
      auto task = taskGenerator();
      task->setParamManager(fParamManager); // maybe that should not be here
      fTasks.push_back(task);
    }
  } else {
    ERROR("taskGeneratorChain is null while constructing JPetTaskExecutor");
  }
}

void JPetTaskExecutor::process()
{
  processFromCmdLineArgs(fProcessedFile);
  for (auto currentTask = fTasks.begin(); currentTask != fTasks.end(); currentTask++) {
    // ignore the event range options for all but the first processed task
    if(currentTask != fTasks.begin()){
      fOptions.resetEventRange();
    }

    INFO(Form("Starting task: %s", dynamic_cast<JPetTaskLoader*>(*currentTask)->getSubTask()->GetName()));
    (*currentTask)->init(fOptions.getOptions());
    (*currentTask)->exec();
    (*currentTask)->terminate();
    INFO(Form("Finished task: %s", dynamic_cast<JPetTaskLoader*>(*currentTask)->getSubTask()->GetName()));
  }
}

void* JPetTaskExecutor::processProxy(void* runner)
{
  assert(runner);
  static_cast<JPetTaskExecutor*>(runner)->process();
  return 0;
}

TThread* JPetTaskExecutor::run()
{
  TThread* thread = new TThread(to_string(fProcessedFile).c_str(), processProxy, (void*)this);
  assert(thread);
  thread->Run();
  return thread;
}

void JPetTaskExecutor::processFromCmdLineArgs(int)
{
  auto runNum = fOptions.getRunNumber();
  if (runNum >= 0) {
    fParamManager->fillParameterBank(runNum); /// @todo some error handling
				if (fOptions.isLocalDBCreate()) {
						JPetParamSaverAscii saver;
						saver.saveParamBank(fParamManager->getParamBank(), runNum, fOptions.getLocalDBCreate());
				}
  }
  auto inputFileType = fOptions.getInputFileType();
  auto inputFile = fOptions.getInputFile();
  if (inputFileType == JPetOptions::kScope) {
    createScopeTaskAndAddToTaskList();
  } else if (inputFileType == JPetOptions::kHld) {
    long long nevents = fOptions.getTotalEvents();
    if (nevents > 0) {
      fUnpacker.setParams(fOptions.getInputFile(), nevents);
      WARNING(std::string("Even that range of events was set, only the first ")+ JPetCommonTools::intToString(nevents) + std::string(" will be unpacked by the unpacker. \n the unpacker always starts from the beginning of the file"));
    } else {
      fUnpacker.setParams(fOptions.getInputFile());
    }
    unpackFile();
  }
}

void JPetTaskExecutor::createScopeTaskAndAddToTaskList()
{
  JPetScopeLoader* module = new JPetScopeLoader(new JPetScopeTask("JPetScopeReader", "Process Oscilloscope ASCII data into JPetRecoSignal structures."));
  assert(module); 
  module->setParamManager(fParamManager); 
  auto scopeFile = fOptions.getScopeConfigFile();
  if (!fParamManager->getParametersFromScopeConfig(scopeFile)) {
    ERROR("Unable to generate Param Bank from Scope Config");
  }
  fTasks.push_front(module);
}

void JPetTaskExecutor::unpackFile()
{
  if (fOptions.getInputFileType() == JPetOptions::kHld) {
    fUnpacker.exec();
  } else {
    WARNING("Input file is not hld and unpacker was supposed to be called!");
  }
}

JPetTaskExecutor::~JPetTaskExecutor()
{
  for (auto& task : fTasks) {
    if (task) {
      delete task;
      task = 0;
    }
  }
}

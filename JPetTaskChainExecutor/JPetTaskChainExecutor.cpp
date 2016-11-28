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
#include "../JPetScopeLoader/JPetScopeLoader.h"
#include "../JPetTaskLoader/JPetTaskLoader.h"
#include "../JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "../JPetParamGetterAscii/JPetParamSaverAscii.h"
#include "../JPetLoggerInclude.h"


JPetTaskChainExecutor::JPetTaskChainExecutor(TaskGeneratorChain* taskGeneratorChain, int processedFileId, JPetOptions opt) :
  fInputSeqId(processedFileId),
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
      ///@todo change it
      (dynamic_cast<JPetTaskIO*>(task))->setParamManager(fParamManager);
      fTasks.push_back(task);
    }
  } else {
    ERROR("taskGeneratorChain is null while constructing JPetTaskChainExecutor");
  }
}

bool JPetTaskChainExecutor::process()
{
  if (!processFromCmdLineArgs()) {
    ERROR("Error in processFromCmdLineArgs");
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
    auto taskCurr = dynamic_cast<JPetTask*> (dynamic_cast<JPetTaskLoader*>(*currentTask)->getTask());
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

bool JPetTaskChainExecutor::processFromCmdLineArgs()
{
  auto runNum = fOptions.getRunNumber();
  if (runNum >= 0) {
    try {
      fParamManager->fillParameterBank(runNum);
    } catch (...) {
      ERROR("Param bank was not generated correctly.\n The run number used:" + JPetCommonTools::intToString(runNum));
      return false;
    }
    if (fOptions.isLocalDBCreate()) {
      JPetParamSaverAscii saver;
      saver.saveParamBank(fParamManager->getParamBank(), runNum, fOptions.getLocalDBCreate());
    }
  }

  auto inputFileType = fOptions.getInputFileType();
  auto inputFile = fOptions.getInputFile();
  if (inputFileType == JPetOptions::kScope) {
    if (!createScopeTaskAndAddToTaskList()) {
      ERROR("Scope task not added correctly!!!");
      return false;
    }
  } else if (inputFileType == JPetOptions::kHld) {
    long long nevents = fOptions.getTotalEvents();
    unpackFile(inputFile, nevents);
  }
  //Assumption that only HLD files can be zipped!!!!!! - Sz.N.
  else if ( inputFileType == JPetOptions::kZip) {
    INFO( std::string("Unzipping file before unpacking") );
    if ( !JPetCommonTools::unzipFile(inputFile) )
      ERROR( std::string("Problem with unpacking file: ") + inputFile );
    long long nevents = fOptions.getTotalEvents();
    INFO( std::string("Unpacking") );
    unpackFile( JPetCommonTools::stripFileNameSuffix( std::string(inputFile) ).c_str(), nevents);
  }

  if (fOptions.getInputFileType() == JPetOptions::kUndefinedFileType)
    ERROR( Form("Unknown file type provided for file: %s", fOptions.getInputFile()) );

  return true;
}

bool JPetTaskChainExecutor::createScopeTaskAndAddToTaskList()
{
  JPetScopeLoader* module = new JPetScopeLoader(new JPetScopeTask("JPetScopeReader", "Process Oscilloscope ASCII data into JPetRecoSignal structures."));
  assert(module);
  module->setParamManager(fParamManager);
  auto scopeFile = fOptions.getScopeConfigFile();
  if (!fParamManager->getParametersFromScopeConfig(scopeFile)) {
    ERROR("Unable to generate Param Bank from Scope Config");
    return false;
  }
  fTasks.push_front(module);
  return true;
}

void JPetTaskChainExecutor::unpackFile(const char* filename, const long long nevents)
{
  if (nevents > 0) {
    fUnpacker.setParams( filename, nevents);
    WARNING(std::string("Even though the range of events was set, only the first ") + JPetCommonTools::intToString(nevents) + std::string(" will be unpacked by the unpacker. \n The unpacker always starts from the beginning of the file."));
  } else {
    fUnpacker.setParams( filename );
  }
  fUnpacker.exec();
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

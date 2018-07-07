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
 *  @file JPetManager.cpp
 */

#include "./JPetManager.h"

#include <cassert>
#include <string>
#include <exception>

#include "./JPetLoggerInclude.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetCmdParser/JPetCmdParser.h"
#include "./JPetOptionsGenerator/JPetOptionsGenerator.h"

#include <TThread.h>

using namespace jpet_options_tools;

JPetManager::JPetManager()
{
}

JPetManager& JPetManager::getManager()
{
  static JPetManager instance;
  return instance;
}

bool JPetManager::areThreadsEnabled() const
{
  return fThreadsEnabled;
}

void JPetManager::setThreadsEnabled(bool enable)
{
  fThreadsEnabled = enable;
}

bool JPetManager::run(int argc, const char** argv)
{
  if (!parseCmdLine(argc, argv)) {
    ERROR("While parsing command line arguments");
    return false;
  }

  ///Here we should do:
  ///1.Add missing default tasks based on options
  ///2.Generate generatorChain based on  
  ///3.create options

  INFO( "======== Starting processing all tasks: " + JPetCommonTools::getTimeString() + " ========\n" );
  std::vector<JPetTaskChainExecutor*> executors;
  std::vector<TThread*> threads;
  auto inputDataSeq = 0;
  /// For every input option, new TaskChainExecutor is created, which creates the chain of previously
  /// registered tasks. The inputDataSeq is the identifier of given chain.
  for (auto opt : fOptions) {
    JPetTaskChainExecutor* executor = new JPetTaskChainExecutor(fTaskFactory.getTaskGeneratorChain(), inputDataSeq, opt.second);
    executors.push_back(executor);
    if (areThreadsEnabled()) {
      auto thr = executor->run();
      if (thr) {
        threads.push_back(thr);
      } else {
        ERROR("thread pointer is null");
      }
    } else {
      if (!executor->process()) {
        ERROR("While running process");
        return false;
      }
    }
    inputDataSeq++;
  }
  if (areThreadsEnabled()) {
    for (auto thread : threads) {
      assert(thread);
      thread->Join();
    }
  }
  for (auto& executor : executors) {
    if (executor) {
      delete executor;
      executor = 0;
    }
  }
  INFO( "======== Finished processing all tasks: " + JPetCommonTools::getTimeString() + " ========\n" );
  return true;
}

bool JPetManager::parseCmdLine(int argc, const char** argv)
{
  try {
    JPetOptionsGenerator optionsGenerator;
    JPetCmdParser parser;
    auto optionsFromCmdLine = parser.parseCmdLineArgs(argc, argv);
    /// One  common map of all options
    auto allValidatedOptions = optionsGenerator.generateAndValidateOptions(optionsFromCmdLine);
    ///@todo change it to return allValidatedOptions + bool and later call fTaskFactory;
    generateOptionsForTasks(allValidatedOptions);
  } catch (std::exception& e) {
    ERROR(e.what());
    return false;
  }
  return true;
}

void JPetManager::generateOptionsForTasks(const std::map<std::string, boost::any>& allValidatedOptions) 
{
  JPetOptionsGenerator optionsGenerator;
  fTaskFactory.addDefaultTasksFromOptions(allValidatedOptions);

  int numberOfRegisteredTasks = 1;
  if (fTaskFactory.getTaskGeneratorChain().size() > 0) {
    numberOfRegisteredTasks = fTaskFactory.getTaskGeneratorChain().size();
  }
  fOptions = optionsGenerator.generateOptionsForTasks(allValidatedOptions, numberOfRegisteredTasks);
}

JPetManager::~JPetManager() {}

void JPetManager::useTask(const char* name, const char* inputFileType, const char* outputFileType)
{
  fTaskFactory.useTask(name, inputFileType, outputFileType);
}

JPetManager::Options JPetManager::getOptions() const
{
  return fOptions;
}

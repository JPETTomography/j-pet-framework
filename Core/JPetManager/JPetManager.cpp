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
#include <TThread.h>

#include "./JPetTaskChainExecutor/JPetTaskChainExecutor.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetCmdParser/JPetCmdParser.h"
#include "./JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "./JPetLoggerInclude.h"


using namespace jpet_options_tools;

JPetManager::JPetManager()
{
}

JPetManager& JPetManager::getManager()
{
  static JPetManager instance;
  return instance;
}

bool JPetManager::run(int argc, const char** argv)
{
  bool isOk = true;
  std::map<std::string, boost::any> allValidatedOptions;
  std::tie(isOk, allValidatedOptions) = parseCmdLine(argc, argv);
  if (!isOk) {
    ERROR("While parsing command line arguments");
    return false;
  }
  auto chainOfTasks = fTaskFactory.createTaskGeneratorChain(allValidatedOptions);
  JPetOptionsGenerator optionsGenerator;
  auto options = optionsGenerator.generateOptionsForTasks(allValidatedOptions, chainOfTasks.size());

  INFO( "======== Starting processing all tasks: " + JPetCommonTools::getTimeString() + " ========\n" );
  std::vector<TThread*> threads;
  auto inputDataSeq = 0;
  /// For every input option, new TaskChainExecutor is created, which creates the chain of previously
  /// registered tasks. The inputDataSeq is the identifier of given chain.
  for (auto opt : options) {
    auto executor = jpet_common_tools::make_unique<JPetTaskChainExecutor>(chainOfTasks, inputDataSeq, opt.second);
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
  INFO( "======== Finished processing all tasks: " + JPetCommonTools::getTimeString() + " ========\n" );
  return true;
}

std::pair<bool, std::map<std::string, boost::any> >  JPetManager::parseCmdLine(int argc, const char** argv)
{
  std::map<std::string, boost::any> allValidatedOptions;
  try {
    JPetOptionsGenerator optionsGenerator;
    JPetCmdParser parser;
    auto optionsFromCmdLine = parser.parseCmdLineArgs(argc, argv);
    /// One  common map of all options
    allValidatedOptions = optionsGenerator.generateAndValidateOptions(optionsFromCmdLine);
  } catch (std::exception& e) {
    ERROR(e.what());
    return std::make_pair(false, std::map<std::string, boost::any> {});
  }
  return std::make_pair(true, allValidatedOptions);
}

void JPetManager::useTask(const char* name, const char* inputFileType, const char* outputFileType)
{
  if (!fTaskFactory.addTaskInfo(name, inputFileType, outputFileType)) {
    std::cerr <<"Stopping program, unrecoverable error has occurred while calling useTask! Check the log!" <<std::endl;
    exit(1);
  }
}

bool JPetManager::areThreadsEnabled() const
{
  return fThreadsEnabled;
}

void JPetManager::setThreadsEnabled(bool enable)
{
  fThreadsEnabled = enable;
}

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
 *  @file JPetManager.cpp
 */

#include "./JPetManager.h"
#include "./JPetGeantParser/JPetGeantParser.h"

#include <TThread.h>
#include <cassert>
#include <exception>
#include <string>

#include "./GeantParser/JPetGeantParser/JPetGeantParser.h"
#include "./JPetCmdParser/JPetCmdParser.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetLoggerInclude.h"
#include "./JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "./JPetTaskChainExecutor/JPetTaskChainExecutor.h"

using namespace jpet_options_tools;

JPetManager::JPetManager() {}

JPetManager &JPetManager::getManager() {
  static JPetManager instance;
  return instance;
}

void JPetManager::run(int argc, const char **argv) {
  bool isOk = true;
  std::map<std::string, boost::any> allValidatedOptions;
  std::tie(isOk, allValidatedOptions) = parseCmdLine(argc, argv);
  if (!isOk) {
    ERROR("While parsing command line arguments");
    std::cerr << "Error has occurred while parsing command line! Check the log!"
              << std::endl;
    throw std::invalid_argument(
        "Error in parsing command line arguments"); /// temporary change to
                                                    /// check if the examples
                                                    /// are working
  }
  JPetManager::registerDefaultTasks();
  useTasksFromUserParams(allValidatedOptions);
  auto chainOfTasks =
      fTaskFactory.createTaskGeneratorChain(allValidatedOptions);
  JPetOptionsGenerator optionsGenerator;
  auto options = optionsGenerator.generateOptionsForTasks(allValidatedOptions,
                                                          chainOfTasks.size());

  INFO("======== Starting processing all tasks: " +
       JPetCommonTools::getTimeString() + " ========\n");
  std::vector<TThread *> threads;
  auto inputDataSeq = 0;
  /// For every input option, new TaskChainExecutor is created, which creates
  /// the chain of previously registered tasks. The inputDataSeq is the
  /// identifier of given chain.
  for (auto opt : options) {
    auto executor = jpet_common_tools::make_unique<JPetTaskChainExecutor>(
        chainOfTasks, inputDataSeq, opt.second);
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
        std::cerr << "Stopping program, error has occurred while calling "
                     "executor->process! Check the log!"
                  << std::endl;
        throw std::runtime_error("Error in executor->process");
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
  INFO("======== Finished processing all tasks: " +
       JPetCommonTools::getTimeString() + " ========\n");
}

std::pair<bool, std::map<std::string, boost::any>>
JPetManager::parseCmdLine(int argc, const char **argv) {
  std::map<std::string, boost::any> allValidatedOptions;
  try {
    JPetOptionsGenerator optionsGenerator;
    JPetCmdParser parser;
    auto optionsFromCmdLine = parser.parseCmdLineArgs(argc, argv);
    allValidatedOptions =
        optionsGenerator.generateAndValidateOptions(optionsFromCmdLine);
  } catch (std::exception &e) {
    ERROR(e.what());
    return std::make_pair(false, std::map<std::string, boost::any>{});
  }
  return std::make_pair(true, allValidatedOptions);
}

void JPetManager::useTask(const std::string &name,
                          const std::string &inputFileType,
                          const std::string &outputFileType, int numTimes) {
  if (!fTaskFactory.addTaskInfo(name, inputFileType, outputFileType,
                                numTimes)) {
    std::cerr << "Error has occurred while calling useTask! Check the log!"
              << std::endl;
    throw std::runtime_error("error in addTaskInfo");
  }
}

bool JPetManager::areThreadsEnabled() const { return fThreadsEnabled; }

void JPetManager::setThreadsEnabled(bool enable) {
  fThreadsEnabled = enable;
  ENABLE_THREADS_INFO(enable);
}

void JPetManager::registerDefaultTasks() {
  JPetManager::getManager().registerTask<JPetGeantParser>("JPetGeantParser");
}

void JPetManager::useTasksFromUserParams(
    const std::map<std::string, boost::any> &opts) {
  using namespace jpet_options_tools;
  std::vector<std::string> useTasksValue;
  if (isOptionSet(opts, kUseTasksFromParamsKey)) {
    useTasksValue = getOptionAsVectorOfStrings(opts, kUseTasksFromParamsKey);
  }
  if (useTasksValue.size() % 3 != 0) {
    ERROR("WRONG number of parameters in " + kUseTasksFromParamsKey +
          " userparam, do not adding any tasks from userParams");
    return;
  }
  for (unsigned int i = 0; i < useTasksValue.size(); i += 3) {
    useTask(useTasksValue[i], useTasksValue[i + 1], useTasksValue[i + 2]);
  }
}

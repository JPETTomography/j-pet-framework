/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetTaskFactory.cpp
 */

#include "JPetParamBankHandlerTask/JPetParamBankHandlerTask.h"
#include "JPetTaskFactory/JPetTaskFactory.h"
#include "JPetScopeLoader/JPetScopeLoader.h"
#include "JPetGeantParser/JPetGeantParser.h"
#include "JPetTaskLooper/JPetTaskLooper.h"
#include "JPetUnpackTask/JPetUnpackTask.h"
#include "JPetUnzipTask/JPetUnzipTask.h"
#include "JPetTaskIO/JPetTaskIO.h"

using TaskGenerator = std::function<std::unique_ptr<JPetTaskInterface>()>;
using TaskGeneratorChain = std::vector<TaskGenerator>;

namespace jpet_task_factory
{

JPetTaskFactory::JPetTaskFactory(){};

std::vector<TaskGenerator> JPetTaskFactory::createTaskGeneratorChain(
  const std::map<std::string, boost::any>& options
) const {
  return generateTaskGeneratorChain(fTasksToUse, fTasksDictionary, options);
}

bool JPetTaskFactory::addTaskInfo(
  const std::string& name, const std::string& inputFileType,
  const std::string& outputFileType, int numIter
) {
  if (fTasksDictionary.find(name) != fTasksDictionary.end()) {
    fTasksToUse.push_back(TaskInfo(name, inputFileType, outputFileType, numIter));
  } else {
    ERROR("Task with the name " + std::string(name) + " is not registered!");
    return false;
  }
  return true;
}

std::vector<TaskInfo> JPetTaskFactory::getTasksToUse() const { return fTasksToUse; }

std::map<std::string, TaskGenerator> JPetTaskFactory::getTasksDictionary() const
{
  return fTasksDictionary;
}

void JPetTaskFactory::clear()
{
  fTasksDictionary.clear();
  fTasksToUse.clear();
}

TaskGeneratorChain generateTaskGeneratorChain(
  const std::vector<TaskInfo>& taskInfoVect,
  const std::map<std::string, TaskGenerator>& generatorsMap,
  const std::map<std::string, boost::any>& options
) {
  TaskGeneratorChain chain;
  addDefaultTasksFromOptions(options, generatorsMap, chain);
  for (const auto& taskInfo : taskInfoVect) {
    addTaskToChain(generatorsMap, taskInfo, chain);
  }
  return chain;
}

void addDefaultTasksFromOptions(
  const std::map<std::string, boost::any>& options,
  const std::map<std::string, TaskGenerator>& generatorsMap,
  TaskGeneratorChain& outChain
) {
  using namespace jpet_options_tools;
  auto addDefaultTasksFromOptions = [&](const std::map<std::string, boost::any>& options) {

    auto fileType = FileTypeChecker::getInputFileType(options);
    if (fileType == FileTypeChecker::kUndefinedFileType) {
      ERROR(Form("Unknown file type provided for file: %s", getInputFile(options).c_str()));
      return;
    }

    // Create task for Param Bank
    auto paramBankTask = []() {
      return jpet_common_tools::make_unique<JPetParamBankHandlerTask>("ParamBank Filling");
    };
    outChain.insert(outChain.begin(), paramBankTask);

    // Create Scope task if indicated by the filetype
    if (fileType == FileTypeChecker::kScope) {
      auto scopeTask = []() {
        return jpet_common_tools::make_unique<JPetScopeLoader>(
          std::unique_ptr<JPetScopeTask>(new JPetScopeTask("JPetScopeReader"))
        );
      };
      outChain.insert(outChain.begin(), scopeTask);
    }

    // Create Geant Parser task if indicated by filetype
    if (fileType == FileTypeChecker::kMCGeant) {
      auto genatTask = []() {
        return jpet_common_tools::make_unique<JPetGeantParser>("JPetGeantParser");
      };
      outChain.insert(outChain.end(), genatTask);
      // auto mcInfo = TaskInfo("JPetGeantParser", "mcGeant", "mc.hits", 1);
      // addTaskToChain(generatorsMap, mcInfo, outChain);
    }

    // Create task to unzip file if indicated by the filetype
    if (fileType == FileTypeChecker::kZip) {
      auto unzip = []() {
        return jpet_common_tools::make_unique<JPetUnzipTask>("JPetUnzipTask");
      };
      outChain.insert(outChain.end(), unzip);
    }

    // Create Unpack task if indicated by the filetype
    if (fileType == FileTypeChecker::kHld || fileType == FileTypeChecker::kZip) {
      auto unpack = []() {
        return jpet_common_tools::make_unique<JPetUnpackTask>("JPetUnpackTask");
      };
      outChain.insert(outChain.end(), unpack);
    }
  };
  addDefaultTasksFromOptions(options);
}

void addTaskToChain(
  const std::map<std::string, TaskGenerator>& generatorsMap,
  const TaskInfo& info, TaskGeneratorChain& outChain
) {
  auto name = info.name;
  auto inT = info.inputFileType;
  auto outT = info.outputFileType;
  auto numOfIterations = info.numOfIterations;

  if (generatorsMap.find(name) != generatorsMap.end()) {
    TaskGenerator userTaskGen = generatorsMap.at(name);
    if (numOfIterations == 1) {
      outChain.push_back(
        [name, inT, outT, userTaskGen]() {
          auto task = jpet_common_tools::make_unique<JPetTaskIO>(
            name.c_str(), inT.c_str(), outT.c_str()
          );
          task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
          return task;
        }
      );
    } else {
      if (numOfIterations < 0) {
        outChain.push_back(
        [name, inT, outT, userTaskGen]() {
          auto task = jpet_common_tools::make_unique<JPetTaskIO>(name.c_str(), inT.c_str(), outT.c_str());
          task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
          auto looperTask = jpet_common_tools::make_unique<JPetTaskLooper>(
            name.c_str(), std::move(task), JPetTaskLooper::getStopOnOptionPredicate(kStopIterationOptionName)
          );
          return looperTask;
        });
      } else {
        outChain.push_back([name, inT, outT, numOfIterations, userTaskGen]() {
          auto task = jpet_common_tools::make_unique<JPetTaskIO>(
            name.c_str(), inT.c_str(), outT.c_str()
          );
          task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
          auto looperTask = jpet_common_tools::make_unique<JPetTaskLooper>(
            name.c_str(), std::move(task),
            JPetTaskLooper::getMaxIterationPredicate(numOfIterations)
          );
          return looperTask;
        });
      }
    }
  } else {
    ERROR(
      Form(
        "The requested task %s is not registered! The output chain might be broken!",
        name.c_str()
      )
    );
    return;
  }
}

} // namespace jpet_task_factory

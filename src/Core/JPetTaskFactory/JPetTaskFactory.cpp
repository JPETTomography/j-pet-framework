/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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

#include "JPetTaskFactory/JPetTaskFactory.h"
#include "JPetGeantParser/JPetGeantParser.h"
#include "JPetOptionsTools/JPetOptionsTools.h"
#include "JPetParamBankHandlerTask/JPetParamBankHandlerTask.h"
#include "JPetScopeLoader/JPetScopeLoader.h"
#include "JPetTaskIOLoopPerSubTask/JPetTaskIOLoopPerSubTask.h"
#include "JPetTaskLooper/JPetTaskLooper.h"
#include "JPetTaskStreamIO/JPetTaskStreamIO.h"
#include "JPetUnpackTask/JPetUnpackTask.h"
#include "JPetUnzipTask/JPetUnzipTask.h"

using TaskGenerator = std::function<std::unique_ptr<JPetTaskInterface>()>;
using TaskGeneratorChain = std::vector<TaskGenerator>;

namespace jpet_task_factory
{

JPetTaskFactory::JPetTaskFactory(){};

std::vector<TaskGenerator> JPetTaskFactory::createTaskGeneratorChain(
  const std::map<std::string, boost::any>& options
) const {

  if (jpet_options_tools::isDirectProcessing(options))
  {
    return generateDirectTaskGeneratorChain(fTasksToUse, fTasksDictionary, options);
  }

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

  TaskGeneratorChain generateDirectTaskGeneratorChain(
                                                      const std::vector<TaskInfo>& taskInfoVect,
                                                      const std::map<std::string, TaskGenerator>& generatorsMap,
                                                      const std::map<std::string, boost::any>& options)
  {
  TaskGeneratorChain chain;
  addDefaultTasksFromOptions(options, generatorsMap, chain);

  auto inT = taskInfoVect.front().inputFileType;
  auto outT = taskInfoVect.back().outputFileType;
  std::string name = "Direct Task Chain";

  chain.push_back(
  [name, inT, outT, generatorsMap, taskInfoVect]() {
    auto task = jpet_common_tools::make_unique<JPetTaskStreamIO>(name.c_str(), inT.c_str(), outT.c_str());

    for (const auto& taskInfo : taskInfoVect) {
      auto task_name = taskInfo.name;

      if (generatorsMap.find(task_name) != generatorsMap.end()) {
        TaskGenerator userTaskGen = generatorsMap.at(task_name);

        task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
      } else {
        ERROR(Form("The requested task %s is not registered! The output chain might be broken!", name.c_str()));
        return task;
      }
    }
    return task;
  });

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

    // Create Scope task if indicated by the filetype
    if (fileType == FileTypeChecker::kScope) {
      auto scopeTask = []() {
        return std::make_unique<JPetScopeLoader>(
          std::unique_ptr<JPetScopeTask>(new JPetScopeTask("JPetScopeReader"))
        );
      };
      outChain.insert(outChain.begin(), scopeTask);
    }

    // Create Geant Parser task if indicated by filetype
    if (fileType == FileTypeChecker::kMCGeant) {
      auto mcInfo = TaskInfo("JPetGeantParser", "mcGeant", "hits", 1);
      addTaskToChain(generatorsMap, mcInfo, outChain);
    }

    // Create task to unzip file if indicated by the filetype
    if (fileType == FileTypeChecker::kZip) {
      auto unzip = []() {
        return std::make_unique<JPetUnzipTask>("JPetUnzipTask");
      };
      outChain.insert(outChain.end(), unzip);
    }

    // Create Unpack task if indicated by the filetype
    if (fileType == FileTypeChecker::kHld || fileType == FileTypeChecker::kZip) {
      auto unpack = []() {
        return std::make_unique<JPetUnpackTask>("JPetUnpackTask");
      };
      outChain.insert(outChain.end(), unpack);
    }

    // Create task for Param Bank
    auto paramBankTask = []() {
      return std::make_unique<JPetParamBankHandlerTask>("ParamBank Filling");
    };
    outChain.insert(outChain.begin(), paramBankTask);

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
      outChain.push_back([name, inT, outT, userTaskGen]() {
        auto task = std::make_unique<JPetTaskIOLoopPerSubTask>(name.c_str(), inT.c_str(), outT.c_str());
        task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
        return task;
      });
    } else {
      if (numOfIterations < 0) {
        outChain.push_back([name, inT, outT, userTaskGen]() {
          auto task = std::make_unique<JPetTaskIOLoopPerSubTask>(name.c_str(), inT.c_str(), outT.c_str());
          task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
          auto looperTask = std::make_unique<JPetTaskLooper>(
            name.c_str(), std::move(task), JPetTaskLooper::getStopOnOptionPredicate(kStopIterationOptionName)
          );
          return looperTask;
        });
      } else {
        outChain.push_back([name, inT, outT, numOfIterations, userTaskGen]() {
          auto task = std::make_unique<JPetTaskIOLoopPerSubTask>(name.c_str(), inT.c_str(), outT.c_str());
          task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
          auto looperTask = std::make_unique<JPetTaskLooper>(
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

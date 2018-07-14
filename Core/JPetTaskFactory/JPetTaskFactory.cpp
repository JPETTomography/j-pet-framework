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
 *  @file JPetTaskFactory.cpp
 */

#include "./JPetTaskFactory.h"
#include "./JPetTaskIO/JPetTaskIO.h"
#include "./JPetScopeLoader/JPetScopeLoader.h"
#include "./JPetUnzipAndUnpackTask/JPetUnzipAndUnpackTask.h"
#include "./JPetParamBankHandlerTask/JPetParamBankHandlerTask.h"
#include "./JPetTaskLooper/JPetTaskLooper.h"

using TaskGenerator = std::function< std::unique_ptr<JPetTaskInterface>() >;
using TaskGeneratorChain = std::vector<TaskGenerator>;

namespace jpet_task_factory
{

JPetTaskFactory::JPetTaskFactory() { };

std::vector<TaskGenerator> JPetTaskFactory::createTaskGeneratorChain(const std::map<std::string, boost::any>& options) const
{
  return generateTaskGeneratorChain(fTasksToUse, fTasksDictionary, options);
}

bool JPetTaskFactory::addTaskInfo(const char* name, const char* inputFileType, const char* outputFileType, int numIter)
{
  if (fTasksDictionary.find(name)!=fTasksDictionary.end()){ 
    fTasksToUse.push_back(TaskInfo(name, inputFileType, outputFileType, numIter));
  } else {
    ERROR("Task with the name " +std::string(name) + " is not registered!");
    return false;
  }
  return true;
}

std::vector<TaskInfo> JPetTaskFactory::getTasksToUse() const
{
  return fTasksToUse;
}

std::map<std::string, TaskGenerator> JPetTaskFactory::getTasksDictionary() const
{
  return  fTasksDictionary;
}


void JPetTaskFactory::clear()
{
  fTasksDictionary.clear();
  fTasksToUse.clear();
}

TaskGeneratorChain generateTaskGeneratorChain(const std::vector<TaskInfo>& taskInfoVect, const std::map<std::string, TaskGenerator>& generatorsMap, const std::map<std::string, boost::any>& options)
{
  TaskGeneratorChain chain;
  addDefaultTasksFromOptions(options, chain);
  for (const auto& taskInfo : taskInfoVect) {
    addTaskToChain(generatorsMap, taskInfo, chain);
  }
  return chain;
}

void addDefaultTasksFromOptions(const std::map<std::string, boost::any>& options, TaskGeneratorChain& outChain)
{
  using namespace jpet_options_tools;
  auto addDefaultTasksFromOptions = [&](const std::map<std::string, boost::any>& options) {
    auto fileType = FileTypeChecker::getInputFileType(options);
    if (fileType == FileTypeChecker::kScope) {
      auto task2 = []() {
        return jpet_common_tools::make_unique<JPetScopeLoader>(std::unique_ptr<JPetScopeTask>(new JPetScopeTask("JPetScopeReader")));
      };
      outChain.insert(outChain.begin(), task2);
    }
    auto paramBankHandlerTask = []() {
      return jpet_common_tools::make_unique<JPetParamBankHandlerTask>("ParamBank Filling");
    };
    outChain.insert(outChain.begin(), paramBankHandlerTask);
    /// add task to unzip or unpack if needed
    auto task = []() {
      return jpet_common_tools::make_unique<JPetUnzipAndUnpackTask>("UnpackerAndUnzipper");
    };
    outChain.insert(outChain.begin(), task);
  };

  addDefaultTasksFromOptions(options);
}

void addTaskToChain(const std::map<std::string, TaskGenerator>& generatorsMap, const TaskInfo& info, TaskGeneratorChain& outChain)
{
  auto name = info.name.c_str();
  auto inT = info.inputFileType.c_str();
  auto outT = info.outputFileType.c_str();
  auto numOfIterations = info.numOfIterations; 

  if (generatorsMap.find(name) != generatorsMap.end()) {
    TaskGenerator userTaskGen = generatorsMap.at(name);
    if (numOfIterations == 1) {
      outChain.push_back(
      [name, inT, outT, userTaskGen]() {
        auto task = jpet_common_tools::make_unique<JPetTaskIO>(name, inT, outT);
        task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
        return task;
      });
    } else {
      if (numOfIterations < 0) {
        outChain.push_back(
        [name, inT, outT, userTaskGen]() {
          auto task = jpet_common_tools::make_unique<JPetTaskIO>(name, inT, outT);
          task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
          auto looperTask = jpet_common_tools::make_unique<JPetTaskLooper>(name, std::move(task), JPetTaskLooper::getStopOnOptionPredicate(kStopIterationOptionName));
          return looperTask;
        });
      } else {
        outChain.push_back(
        [name, inT, outT, numOfIterations, userTaskGen]() {
          auto task = jpet_common_tools::make_unique<JPetTaskIO>(name, inT, outT);
          task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
          auto looperTask = jpet_common_tools::make_unique<JPetTaskLooper>(name, std::move(task), JPetTaskLooper::getMaxIterationPredicate(numOfIterations));
          return looperTask;
        });
      }
    }
  } else {
    ERROR(Form("The requested task %s is not registered! The output chain might be broken!", name));
    return;
  }
}

}

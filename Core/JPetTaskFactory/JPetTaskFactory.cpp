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
#include <cassert>
#include "./JPetTaskIO/JPetTaskIO.h"
#include "./JPetScopeLoader/JPetScopeLoader.h"
#include "./JPetUnzipAndUnpackTask/JPetUnzipAndUnpackTask.h"
#include "./JPetParamBankHandlerTask/JPetParamBankHandlerTask.h"

using TaskGenerator = std::function< JPetTaskInterface*() >;
using TaskGeneratorChain = std::vector<TaskGenerator>;

namespace jpet_task_factory
{

std::vector<TaskGenerator> JPetTaskFactory::createTaskGeneratorChain(const std::map<std::string, boost::any>& options) const
{
  return generateTaskGeneratorChain(fTasksToUse, fTasksDictionary, options);
}

void JPetTaskFactory::addTaskInfo(const char* name, const char* inputFileType, const char* outputFileType)
{
  fTasksToUse.push_back(TaskInfo(name, inputFileType, outputFileType, 1));
}

TaskGeneratorChain generateTaskGeneratorChain(const std::vector<TaskInfo>& taskInfoVect, const std::map<std::string, TaskGenerator>& generatorsMap, const std::map<std::string, boost::any>& options)
{
  TaskGeneratorChain chain;
  addDefaultTasksFromOptions(options, chain);
  for(const auto& taskInfo: taskInfoVect) {
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
        return new JPetScopeLoader(std::unique_ptr<JPetScopeTask>(new JPetScopeTask("JPetScopeReader")));
      };
      outChain.insert(outChain.begin(), task2);
    }
    auto paramBankHandlerTask = []() {
      return new JPetParamBankHandlerTask("ParamBank Filling");
    };
    outChain.insert(outChain.begin(), paramBankHandlerTask);
    /// add task to unzip or unpack if needed
    auto task = []() {
      return new JPetUnzipAndUnpackTask("UnpackerAndUnzipper");
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

  if (generatorsMap.count(name) > 0 ) {
    TaskGenerator userTaskGen = generatorsMap.at(name);
    // wrap the JPetUserTask-based task in a JPetTaskIO
    outChain.push_back( 
        [name, inT, outT, userTaskGen](){
        //std::unique_ptr<JPetTaskIO> task(new JPetTaskIO{name, inputFileType, outputFileType});
        JPetTaskIO* task = new JPetTaskIO(name, inT, outT);
      task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
      return task;
    });
  } else {
    ERROR(Form("The requested task %s is unknown", name));
    exit(1);
  }
} 


}

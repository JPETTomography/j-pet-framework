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


JPetTaskFactory::JPetTaskFactory()
{
  fTaskGeneratorChain = new TaskGeneratorChain;
}

void JPetTaskFactory::useTask(const char* name, const char* inputFileType, const char* outputFileType)
{
  assert(fTaskGeneratorChain);
  if ( fTasksDictionary.count(name) > 0 ) {
    TaskGenerator userTaskGen = fTasksDictionary.at(name);
    // wrap the JPetUserTask-based task in a JPetTaskIO
    fTaskGeneratorChain->push_back( 
        [name, inputFileType, outputFileType, userTaskGen](){
        //std::unique_ptr<JPetTaskIO> task(new JPetTaskIO{name, inputFileType, outputFileType});
        JPetTaskIO* task = new JPetTaskIO(name, inputFileType, outputFileType);
      task->addSubTask(std::unique_ptr<JPetTaskInterface>(userTaskGen()));
      return task;
    });
  } else {
    ERROR(Form("The requested task %s is unknown", name));
    exit(1);
  }
}

void JPetTaskFactory::addDefaultTasksFromOptions(const std::map<std::string, boost::any>& options)
{
  using namespace jpet_options_tools;
  auto addDefaultTasksFromOptions = [&](const std::map<std::string, boost::any>& options) {
    auto fileType = FileTypeChecker::getInputFileType(options);
    if (fileType == FileTypeChecker::kScope) {
      auto task2 = []() {
        return new JPetScopeLoader(std::unique_ptr<JPetScopeTask>(new JPetScopeTask("JPetScopeReader")));
      };
      fTaskGeneratorChain->insert(fTaskGeneratorChain->begin(), task2);
    }
    auto paramBankHandlerTask = []() {
      return new JPetParamBankHandlerTask("ParamBank Filling");
    };
    fTaskGeneratorChain->insert(fTaskGeneratorChain->begin(), paramBankHandlerTask);
    /// add task to unzip or unpack if needed
    auto task = []() {
      return new JPetUnzipAndUnpackTask("UnpackerAndUnzipper");
    };
    fTaskGeneratorChain->insert(fTaskGeneratorChain->begin(), task);
  };

  addDefaultTasksFromOptions(options);
}

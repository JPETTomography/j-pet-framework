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
 *  @file JPetTaskExecutor.h
 */

#ifndef FRAMEWORK_JPETTASKEXECUTOR_H
#define FRAMEWORK_JPETTASKEXECUTOR_H

#include <list>
#include <TThread.h>
#include <functional> // for TaskGenerator declaration
#include <vector> // for TaskGeneratorChain declaration
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetUnpacker/JPetUnpacker.h"
#include "../JPetOptions/JPetOptions.h"

class JPetTaskInterface;
using TaskGenerator = std::function< JPetTaskInterface* () >;
using TaskGeneratorChain = std::vector<TaskGenerator>;


class JPetTaskExecutor
{
public :
  JPetTaskExecutor(TaskGeneratorChain* taskGeneratorChain, int processedFile, JPetOptions opts);
  TThread* run();
  virtual ~JPetTaskExecutor();

  bool process(); /// That was private. I made it public to run without threads.
private:
  bool createScopeTaskAndAddToTaskList();
  static void* processProxy(void*);
  bool processFromCmdLineArgs(int);
  void unpackFile(const char* filename, const long long nevents);
  int fProcessedFile;
  JPetParamManager* fParamManager;
  JPetUnpacker fUnpacker;
  std::list<JPetTaskInterface*> fTasks;
  TaskGeneratorChain* ftaskGeneratorChain;
  JPetOptions fOptions;
};


#endif //FRAMEWORK_JPETTASKEXECUTOR_H

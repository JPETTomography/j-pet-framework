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
 *  @file JPetTaskChainExecutor.h
 */

#ifndef FRAMEWORK_JPETTASCHAINKEXECUTOR_H
#define FRAMEWORK_JPETTASKCHAINEXECUTOR_H

#include <list>
#include <TThread.h>
#include <functional> // for TaskGenerator declaration
#include <vector> // for TaskGeneratorChain declaration
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetOptions/JPetOptions.h"

#include "../JPetTaskRunnerInterface/JPetTaskRunnerInterface.h"
using TaskGenerator = std::function< JPetTaskRunnerInterface* () >;
using TaskGeneratorChain = std::vector<TaskGenerator>;

/**
 * JPetTaskChainExecutor generates the previously registered chain of tasks.
 * One chain can be run as a thread independently
 */
class JPetTaskChainExecutor
{
public :
  JPetTaskChainExecutor(TaskGeneratorChain* taskGeneratorChain, int processedFile, JPetOptions opts);
  TThread* run();
  virtual ~JPetTaskChainExecutor();

  bool process(); /// That was private. I made it public to run without threads.
  static void printCurrentOptionsToLog(const JPetOptions::Options& currOpts);
private:
  static void* processProxy(void*);
  bool preprocessing(const JPetOptions& options, JPetParamManager* manager, std::list<JPetTaskRunnerInterface*>& tasks);

  int fInputSeqId;
  JPetParamManager* fParamManager;
  std::list<JPetTaskRunnerInterface*> fTasks;
  TaskGeneratorChain* ftaskGeneratorChain;
  JPetOptions fOptions;
};


#endif //FRAMEWORK_JPETTASCHAINKEXECUTOR_H

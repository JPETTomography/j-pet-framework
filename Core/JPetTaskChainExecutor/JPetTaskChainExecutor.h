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
 *  @file JPetTaskChainExecutor.h
 */

#ifndef JPETTASKCHAINEXECUTOR_H
#define JPETTASKCHAINEXECUTOR_H

#include <list>
#include <TThread.h>
#include <functional> // for TaskGenerator declaration
#include <vector> // for TaskGeneratorChain declaration
#include "./JPetParams/JPetParams.h"
#include "./JPetTaskInterface/JPetTaskInterface.h"
#include "./JPetTimer/JPetTimer.h"

using TaskGenerator = std::function< std::unique_ptr<JPetTaskInterface>() >;
using TaskGeneratorChain = std::vector<TaskGenerator>;

/**
 * @brief Class to execute registered tasks.
 *
 * JPetTaskChainExecutor generates the previously registered chain of tasks.
 * One chain can be run as a thread independently.
 */
class JPetTaskChainExecutor
{
public :
  JPetTaskChainExecutor(const TaskGeneratorChain& taskGeneratorChain, int processedFile, const jpet_options_tools::OptsStrAny&);
  TThread* run();
  virtual ~JPetTaskChainExecutor();
  bool process(); /// Method to be called directly only in case of non-thread running;
private:
  static void* processProxy(void*);

  int fInputSeqId = -1;
  std::list<std::unique_ptr<JPetTaskInterface> > fTasks;
  TaskGeneratorChain ftaskGeneratorChain;
  JPetParams fParams;
};

#endif /* JPETTASKCHAINEXECUTOR_H */

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
 *  @file JPetTaskLooper.h
 */

#ifndef JPETTASKLOOPER_H 
#define JPETTASKLOOPER_H 
#include "./JPetTask/JPetTask.h"
#include <memory> 

using Predicate=std::function<bool(const JPetParamsInterface& params)>;
/**
 * @brief Special type of Task that allows to run some subtasks in a loop, till the condition is fullfilled.
 * The condition is defined by  a special function that takes JPetParamsInterface reference and returns bool.
 * The function must be provided by the user and it is passed to JPetTaskLooper in the constructor.
 * The function is called in every iteration using as arguments the outParams values set by the subtask terminate method.   
 * The iteration stops when the function returns false. 
 * See unit tests for simple usage examples.
 */
class JPetTaskLooper: public JPetTask {
public:

  /// If no Predicate is given, by default the iteration will never enter the loop. 
  JPetTaskLooper(const char* name, std::unique_ptr<JPetTask> subtask, Predicate isCondition = [](const JPetParamsInterface&){return false;});
  virtual ~JPetTaskLooper(){}
  bool init(const JPetParamsInterface& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParamsInterface& outOptions) override;
protected:  
  Predicate fIsCondition; /// If this function returns false, the iteration is stopped.
};
#endif /*  !JPETTASKLOOPER_H */

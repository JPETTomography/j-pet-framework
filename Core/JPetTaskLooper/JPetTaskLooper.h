/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
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
#include "./JPetParams/JPetParams.h"

using Predicate=std::function<bool(const JPetParams& params)>;

class JPetTaskLooper: public JPetTask
{
public:
  static Predicate getMaxIterationPredicate(int maxIteration);
  static Predicate getStopOnOptionPredicate(const std::string optionName);

  JPetTaskLooper(const char* name, std::unique_ptr<JPetTask> subtask, Predicate isCondition = [](const JPetParams&){return false;});
  virtual ~JPetTaskLooper(){}
  bool init(const JPetParams& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParams& outOptions) override;
  void setConditionFunction(Predicate isCondition);
protected:
  Predicate fIsCondition;
  JPetParams fParams;
};
#endif /*  !JPETTASKLOOPER_H */

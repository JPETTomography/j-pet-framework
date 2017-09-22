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
 *  @file JPetTaskRunner.h
 */

#ifndef JPETTASKRUNNER_H
#define JPETTASKRUNNER_H

#include <memory>
#include "../JPetTaskInterface/JPetTaskInterface.h"

/**
 * @brief Interface class representing a computing task unit which can contain some subtasks
 *
 * *
 */
class JPetTaskRunner: public JPetTaskInterface
{
public:
  JPetTaskRunner();
  virtual ~JPetTaskRunner();
  void addSubTask(std::unique_ptr<JPetTaskInterface> subTask) override;
  virtual const std::vector<JPetTaskInterface*> getSubTasks() const override;
  virtual bool init(const JPetParamsInterface& inOptions) = 0;
  virtual bool exec() = 0;
  virtual bool terminate(JPetParamsInterface& outOptions) = 0;

protected:
  std::vector<std::unique_ptr<JPetTaskInterface>> fSubTasks;

private:
  void operator=(const JPetTaskRunner&);
  JPetTaskRunner(const JPetTaskRunner&);
};
#endif /*  !JPETTASKRUNNER_H */

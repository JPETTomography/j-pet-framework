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
 *  @file JPetTask.h
 */

#ifndef JPETTASK_H
#define JPETTASK_H
#include "./JPetParams/JPetParams.h"
#include "./JPetTaskInterface/JPetTaskInterface.h"
#include "./JPetDataInterface/JPetDataInterface.h"
#include <string>
#include <vector>

class JPetWriter;

/**
 * @brief Abstract class being an implementation of a computing task unit.
 *
 * Basic class for creating a task for computation or analyses. It is a parent
 * class for User Tasks and oters. The implementation should include
 * init, exec and terminate methods in the inherited class.
 * @todo Add tests for this class. Any.
 */
class JPetTask: public JPetTaskInterface
{
public:
  JPetTask(const char* name = "");
  virtual ~JPetTask() {}
  virtual bool init(const JPetParams& inOptions) = 0;
  virtual bool run(const JPetDataInterface& inData) = 0;
  virtual bool terminate(JPetParams& outOptions) = 0;
  virtual void addSubTask(std::unique_ptr<JPetTaskInterface> subTask) override;
  virtual const std::vector<JPetTaskInterface*> getSubTasks() const override;
  void setName(const std::string& name);
  std::string getName() const override;

protected:
  std::string fName;
  std::vector<std::unique_ptr<JPetTaskInterface>> fSubTasks;
};
#endif /* !JPETTASK_H */

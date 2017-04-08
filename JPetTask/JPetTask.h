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
 *  @file JPetTask.h
 */

#ifndef JPETTASK_H
#define JPETTASK_H
#include "../JPetParamsInterface/JPetParamsInterface.h"
#include "../JPetTimeWindow/JPetTimeWindow.h"
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include "../JPetDataInterface/JPetDataInterface.h"
#include <string>

class JPetWriter;

/**
 * @brief abstract class being an implementation of a computing task unit.
 * The user should implement init, exec and terminate methods in the inherited class.
 */
class JPetTask: public JPetTaskInterface
{
public:
  JPetTask(const char* name = "");
  virtual ~JPetTask() {}
  virtual bool init(const JPetParamsInterface& inOptions) = 0;
  virtual bool run(const JPetDataInterface& inData) = 0;
  virtual bool terminate(JPetParamsInterface& outOptions) = 0;

  virtual void setSubTask(std::unique_ptr<JPetTaskInterface> subTask) override;
  virtual JPetTaskInterface* getSubTask() const override;

  void setName(const std::string& name);
  std::string getName() const override;

  virtual JPetTimeWindow * getOutputEvents(){
    return fOutputEvents;
  }

protected:
  std::string fName;
  std::unique_ptr<JPetTaskInterface> fSubTask = 0;
  JPetTimeWindow * fOutputEvents;
};
#endif /*  !JPETTASK_H */

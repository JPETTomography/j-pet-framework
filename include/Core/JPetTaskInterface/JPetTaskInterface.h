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
 *  @file JPetTaskInterface.h
 */

#ifndef JPETTASKINTERFACE_H
#define JPETTASKINTERFACE_H

#include "./JPetParams/JPetParams.h"
#include "./JPetDataInterface/JPetDataInterface.h"
#include <string>
#include <memory>
#include <vector>

/**
 * @brief Interface class representing a computing task unit.
 */
class JPetTaskInterface
{
public:
  virtual ~JPetTaskInterface() {}
  virtual bool init(const JPetParams& inOptions) = 0;
  virtual bool run(const JPetDataInterface& inData) = 0;
  virtual bool terminate(JPetParams& outOptions) = 0;
  virtual void addSubTask(std::unique_ptr<JPetTaskInterface> subTask) = 0;
  virtual const std::vector<JPetTaskInterface*> getSubTasks() const = 0;
  virtual std::string getName() const = 0;
};
#endif /* !JPETTASKINTERFACE_H */

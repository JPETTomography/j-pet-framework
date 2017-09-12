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
 *  @file JPetTaskInterface.h
 */

#ifndef JPETTASKINTERFACE_H
#define JPETTASKINTERFACE_H

#include "../JPetParamsInterface/JPetParamsInterface.h"
#include <memory>


/**
 * @brief Interface class representing a computing task unit.
 *
 */
class JPetTaskInterface
{
public:
  virtual ~JPetTaskInterface() {}
  virtual bool init(const JPetParamsInterface& inOptions) = 0;
  virtual bool exec() = 0;
  virtual bool terminate(JPetParamsInterface& outOptions) = 0;
  virtual void setSubTask(std::unique_ptr<JPetTaskInterface> subTask) = 0;
  virtual JPetTaskInterface* getSubTask() const = 0;
};
#endif /*  !JPETTASKINTERFACE_H */

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

#include <map> ///@todo to remove
#include <string> ///@todo to remove
#include <boost/any.hpp> ///@todo to remove
#include "../JPetOptionsInterface/JPetOptionsInterface.h"
#include <memory>

class JPetParamManager;

/**
 * @brief Interface class representing a computing task unit.
 *
 */
class JPetTaskInterface
{
public:
  typedef std::map<std::string, boost::any> Options; /// @todo to remove
  virtual ~JPetTaskInterface() {}
  virtual void init(const JPetOptionsInterface& inOptions) = 0;
  virtual void exec() = 0;
  virtual std::unique_ptr<JPetOptionsInterface> terminate() = 0;
  virtual void setParamManager(JPetParamManager* paramManager) = 0;
};
#endif /*  !JPETTASKINTERFACE_H */

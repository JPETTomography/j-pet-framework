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
 *  @file JPetScopeData.h
 */

#ifndef JPETSCOPEDATA_H
#define JPETSCOPEDATA_H
#include "./JPetDataInterface/JPetDataInterface.h"
#include <string>
#include <map>

/**
 * @brief Wrapper class that contains data sent to JPetScopeTask.
 */
class JPetScopeData : public JPetDataInterface
{
public:
  explicit JPetScopeData(const std::pair<int, std::map<std::string, int>>& event);
  std::pair<int, std::map<std::string, int> > getEvent() const;
protected:
  std::pair<int, std::map<std::string, int>> fEvent;
};
#endif /* !JPETSCOPEDATA_H */

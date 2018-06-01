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
 *  @file JPetScopeData.cpp
 */

#include "./JPetScopeData.h"

JPetScopeData::JPetScopeData(
  const std::pair<int, std::map<std::string, int>>& event): fEvent(event) {}

std::pair<int, std::map<std::string, int>> JPetScopeData::getEvent() const
{
  return fEvent;
}

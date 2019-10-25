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
 *  @file JPetProgressBarManager.cpp
 */

#include "JPetProgressBarManager/JPetProgressBarManager.h"
#include <iostream>

void JPetProgressBarManager::display(const std::string& taskName, long long currentNumber, long long totalNumber) const
{
  std::cout << std::string(30, '\b');
  std::cout << std::string(30, ' ');
  std::cout << '\r' << taskName << " " << getCurrentValue(currentNumber, totalNumber) << '%' << std::flush;
}

float JPetProgressBarManager::getCurrentValue(int currentEventNumber, int numberOfEvents) const
{
  return (((float)currentEventNumber) / numberOfEvents) * 100;
}

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
 *  @file JPetTimer.cpp
 */


#include "JPetTimer.h"

JPetTimer::JPetTimer() { }

JPetTimer::~JPetTimer() { }

void JPetTimer::startMeasurement()
{
  startTime = std::chrono::system_clock::now();
}

void JPetTimer::stopMeasurement(std::string measurementName)
{
  elapsedTimes.push_back(make_pair(measurementName, std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime)));
}

void JPetTimer::printElapsedTimeToInfo()
{
  for (auto& el : elapsedTimes) {
    INFO("Elapsed time for " + el.first + ":" + std::to_string(el.second.count()) + " [s]");
  }
}

void JPetTimer::printTotalElapsedTimeToInfo()
{
  auto total = std::accumulate(elapsedTimes.begin(),
                               elapsedTimes.end(),
                               std::chrono::seconds(0),
  [](const std::chrono::seconds prev, const std::pair<std::string, std::chrono::seconds>& el) {
    return prev + el.second;
  });
  INFO(std::string("Total elapsed time:") + std::to_string(total.count()) + " [s]");
}

long int JPetTimer::getElapsedTimeInSeconds()
{
  auto total = std::accumulate(elapsedTimes.begin(),
                               elapsedTimes.end(),
                               std::chrono::seconds(0),
  [](const std::chrono::seconds prev, const std::pair<std::string, std::chrono::seconds>& el) {
    return prev + el.second;
  });
  return total.count();
}

JPetTimer::vectorElapsedTimes
JPetTimer::getElapsedTimes()
{
  return elapsedTimes;
}

JPetTimer::startTimeType JPetTimer::getStartTime()
{
  return startTime;
}

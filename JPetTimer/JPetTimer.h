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
 *  @file JPetTimer.h
 */


#ifndef _JPET_TIMER_H_
#define _JPET_TIMER_H_

#include <vector>
#include <string>
#include <chrono>
#include <numeric>

class JPetTimer
{
public:
  using vectorElapsedTimes = std::vector<std::pair<std::string, std::chrono::seconds>>;
  using startTimeType = std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1l, 1000000000l>>>;

  JPetTimer();
  ~JPetTimer();
  JPetTimer(const JPetTimer&) = default;
  JPetTimer& operator=(const JPetTimer&) = default;

  void startMeasurement();
  void stopMeasurement(std::string measurementName);

  std::string getAllMeasuredTimes();
  std::string getTotalMeasuredTime();

  vectorElapsedTimes getVectorOfMeasuredTimes();
  startTimeType getCurrentStartTime();
  long int getTotalMeasuredTimeInSeconds();

private:

  startTimeType fStartTime;
  vectorElapsedTimes fElapsedTimes;
};

#endif /*  !_JPET_TIMER_H_ */

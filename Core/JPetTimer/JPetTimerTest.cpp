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
 *  @file JPetTimerTest.h
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTimerTest

#include <boost/test/unit_test.hpp>
#include "./JPetTimer.h"
#include <thread>
#include <chrono>

BOOST_AUTO_TEST_SUITE(JPetTimerTestSuite)

BOOST_AUTO_TEST_CASE(constructors)
{
  JPetTimer timer;
  timer.startMeasurement();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  timer.stopMeasurement("test");
  BOOST_REQUIRE_EQUAL(timer.getVectorOfMeasuredTimes().size(), 1);
  BOOST_REQUIRE_EQUAL(timer.getTotalMeasuredTimeInSeconds(), 1);
  BOOST_REQUIRE_EQUAL(timer.getVectorOfMeasuredTimes()[0].second.count(), 1);
  BOOST_REQUIRE_EQUAL(timer.getVectorOfMeasuredTimes()[0].first, "test");
  JPetTimer copy = timer;
  BOOST_REQUIRE_EQUAL(copy.getVectorOfMeasuredTimes().size(), 1);
  BOOST_REQUIRE_EQUAL(copy.getTotalMeasuredTimeInSeconds(), 1);
  BOOST_REQUIRE_EQUAL(copy.getVectorOfMeasuredTimes()[0].second.count(), 1);
  BOOST_REQUIRE_EQUAL(copy.getVectorOfMeasuredTimes()[0].first, "test");
  copy.startMeasurement();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  copy.stopMeasurement("test2");
  BOOST_REQUIRE_EQUAL(copy.getVectorOfMeasuredTimes().size(), 2);
  BOOST_REQUIRE_EQUAL(copy.getTotalMeasuredTimeInSeconds(), 2);
  BOOST_REQUIRE_EQUAL(copy.getVectorOfMeasuredTimes()[0].second.count(), 1);
  BOOST_REQUIRE_EQUAL(copy.getVectorOfMeasuredTimes()[1].second.count(), 1);
  BOOST_REQUIRE_EQUAL(copy.getVectorOfMeasuredTimes()[0].first, "test");
  BOOST_REQUIRE_EQUAL(copy.getVectorOfMeasuredTimes()[1].first, "test2");
  JPetTimer copyConstructor(copy);
  BOOST_REQUIRE_EQUAL(copyConstructor.getVectorOfMeasuredTimes().size(), 2);
  BOOST_REQUIRE_EQUAL(copyConstructor.getTotalMeasuredTimeInSeconds(), 2);
  BOOST_REQUIRE_EQUAL(copyConstructor.getVectorOfMeasuredTimes()[0].second.count(), 1);
  BOOST_REQUIRE_EQUAL(copyConstructor.getVectorOfMeasuredTimes()[1].second.count(), 1);
  BOOST_REQUIRE_EQUAL(copyConstructor.getVectorOfMeasuredTimes()[0].first, "test");
  BOOST_REQUIRE_EQUAL(copyConstructor.getVectorOfMeasuredTimes()[1].first, "test2");
}

BOOST_AUTO_TEST_SUITE_END()

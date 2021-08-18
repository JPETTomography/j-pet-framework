/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetRecoSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetRecoSignalTest

#include "Signals/JPetRecoSignal/JPetRecoSignal.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

double epsilon = 0.00001;

BOOST_AUTO_TEST_CASE(constructor_test)
{
  JPetRecoSignal signal1;
  BOOST_REQUIRE_CLOSE(signal1.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_EQUAL(signal1.getRecoFlag(), JPetRecoSignal::Unknown);

  JPetRecoSignal signal2(JPetRecoSignal::Good);
  BOOST_REQUIRE_CLOSE(signal2.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_EQUAL(signal2.getRecoFlag(), JPetRecoSignal::Good);

  JPetRecoSignal signal3(123.4);
  BOOST_REQUIRE_CLOSE(signal3.getTime(), 123.4, epsilon);

  JPetRecoSignal signal4(JPetRecoSignal::Corrupted, 123.4);
  BOOST_REQUIRE_CLOSE(signal4.getTime(), 123.4, epsilon);
  BOOST_REQUIRE_EQUAL(signal4.getRecoFlag(), JPetRecoSignal::Corrupted);
}

BOOST_AUTO_TEST_CASE(set_clear_test)
{
  JPetRecoSignal signal;
  signal.setTime(123.4);
  signal.setRecoFlag(JPetRecoSignal::Good);
  BOOST_REQUIRE_CLOSE(signal.getTime(), 123.4, epsilon);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetRecoSignal::Good);
  signal.Clear("");
  BOOST_REQUIRE_CLOSE(signal.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetRecoSignal::Unknown);
}

BOOST_AUTO_TEST_SUITE_END()

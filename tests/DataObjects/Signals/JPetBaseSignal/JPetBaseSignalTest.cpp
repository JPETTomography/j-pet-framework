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
 *  @file JPetBaseSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetBaseSignalTest

#include "Signals/JPetBaseSignal/JPetBaseSignal.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(BaseSignalTest)

double epsilon = 0000.1;

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetBaseSignal signal;
  BOOST_REQUIRE_CLOSE(signal.getTime(), 0.0, epsilon);
  BOOST_REQUIRE(!signal.isNullObject());
}

BOOST_AUTO_TEST_CASE(dummy_signal_test)
{
  JPetBaseSignal signal = JPetBaseSignal::getDummyResult();
  BOOST_REQUIRE(signal.isNullObject());
}

BOOST_AUTO_TEST_CASE(set_and_clear_test)
{
  JPetBaseSignal signal;
  signal.setTime(123.4);
  BOOST_REQUIRE_CLOSE(signal.getTime(), 123.4, epsilon);
  signal.Clear("");
  BOOST_REQUIRE_CLOSE(signal.getTime(), 0.0, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

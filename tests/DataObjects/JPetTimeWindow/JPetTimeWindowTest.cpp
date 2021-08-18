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
 *  @file JPetTimeWindowTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTSlotTest

#include "JPetTimeWindow/JPetTimeWindow.h"
#include "Hits/JPetBaseHit/JPetBaseHit.h"
#include "Signals/JPetChannelSignal/JPetChannelSignal.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetTimeWindow test;
  BOOST_REQUIRE(test.getNumberOfEvents() == 0);
}

BOOST_AUTO_TEST_CASE(test_with_objects)
{
  JPetTimeWindow test("JPetChannelSignal");
  JPetChannelSignal ch_test1(JPetChannelSignal::Trailing, 1.2);
  JPetChannelSignal ch_test2(JPetChannelSignal::Leading, 1.5);
  JPetChannelSignal ch_test3(JPetChannelSignal::Leading, 98.0);
  test.add<JPetChannelSignal>(ch_test1);
  test.add<JPetChannelSignal>(ch_test2);
  test.add<JPetChannelSignal>(ch_test3);
  BOOST_REQUIRE_EQUAL(test.getNumberOfEvents(), 3);

  double epsilon = 0.001;
  BOOST_REQUIRE_CLOSE((dynamic_cast<const JPetChannelSignal&>(test[0])).getTime(), 1.2, epsilon);
  BOOST_REQUIRE_CLOSE((dynamic_cast<const JPetChannelSignal&>(test[1])).getTime(), 1.5, epsilon);
  BOOST_REQUIRE_CLOSE((dynamic_cast<const JPetChannelSignal&>(test[2])).getTime(), 98.0, epsilon);
  BOOST_REQUIRE_CLOSE(test.getEvent<JPetChannelSignal>(0).getTime(), 1.2, epsilon);
  BOOST_REQUIRE_CLOSE(test.getEvent<JPetChannelSignal>(1).getTime(), 1.5, epsilon);
  BOOST_REQUIRE_CLOSE(test.getEvent<JPetChannelSignal>(2).getTime(), 98.0, epsilon);
}

BOOST_AUTO_TEST_CASE(clearing)
{
  JPetTimeWindow test("JPetBaseHit");
  JPetBaseHit hit1;
  JPetBaseHit hit2;
  test.add<JPetBaseHit>(hit1);
  test.add<JPetBaseHit>(hit2);
  BOOST_REQUIRE_EQUAL(test.getNumberOfEvents(), 2);
  test.Clear();
  BOOST_REQUIRE_EQUAL(test.getNumberOfEvents(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

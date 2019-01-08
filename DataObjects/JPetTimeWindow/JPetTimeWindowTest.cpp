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
 *  @file JPetTimeWindowTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTSlotTest

#include "./JPetTimeWindow/JPetTimeWindow.h"
#include <boost/test/unit_test.hpp>
#include "./JPetSigCh/JPetSigCh.h"
#include "./JPetHit/JPetHit.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetTimeWindow test;
  BOOST_REQUIRE(test.getNumberOfEvents() == 0);
}

BOOST_AUTO_TEST_CASE(some_channels)
{
  JPetTimeWindow test("JPetSigCh");
  JPetSigCh ch_test(JPetSigCh::Trailing, 1.2),
    ch_test2(JPetSigCh::Leading, 1.5),
    ch_test3(JPetSigCh::Leading, 98);
  test.add<JPetSigCh>(ch_test);
  test.add<JPetSigCh>(ch_test2);
  test.add<JPetSigCh>(ch_test3);
  BOOST_REQUIRE_EQUAL(test.getNumberOfEvents(), 3);
  double epsilon = 0.001;
  BOOST_REQUIRE_CLOSE((dynamic_cast<const JPetSigCh&>(test[0])).getValue(), 1.2, epsilon);
  BOOST_REQUIRE_CLOSE(test.getEvent<JPetSigCh>(1).getValue(), 1.5, epsilon);
  BOOST_REQUIRE_CLOSE(test.getEvent<JPetSigCh>(2).getValue(), 98, epsilon);
}

BOOST_AUTO_TEST_CASE(clearing)
{
  JPetTimeWindow test("JPetHit");
  JPetHit hit1;
  JPetHit hit2;
  test.add<JPetHit>(hit1);
  test.add<JPetHit>(hit2);
  BOOST_REQUIRE_EQUAL(test.getNumberOfEvents(), 2);
  test.Clear();
  BOOST_REQUIRE_EQUAL(test.getNumberOfEvents(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

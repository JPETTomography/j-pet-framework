/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetScopeTaskTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetScopeTaskTest
#include <boost/test/unit_test.hpp>
#include "JPetScopeTask.h"
#include "../JPetScopeConfigParser/JPetScopeConfigParser.h"
#include <algorithm>

BOOST_AUTO_TEST_SUITE(JPetScopeTaskTestTestSuite)

BOOST_AUTO_TEST_CASE(defaultConstructor)
{
  JPetScopeTask sTask("blabla", "ble");
  ///check all gets
}

BOOST_AUTO_TEST_CASE(getTimeWindowIndex)
{
  JPetScopeTask sTask("testScopeTask", "It is a test scope task");
  ///always 4th character if it is a number or digit
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex(""), -1);
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex("02"), -1);
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex("023"), -1);
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex("_000a"), 0);
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex("0040a"), 0);
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex("C1_0002"), 2);
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex("C4_0004"), 4);
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex("_0004"), 4);
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex("_000a"), 0);
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex("107349"), 349);
  BOOST_REQUIRE_EQUAL(sTask.getTimeWindowIndex("C1_0003.txt"), 3);
}

BOOST_AUTO_TEST_SUITE_END()

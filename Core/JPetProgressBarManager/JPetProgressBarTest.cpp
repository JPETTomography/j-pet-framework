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
 *  @file JPetProgressBarTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetProgressBarManagerTest
#include "./JPetProgressBarManager/JPetProgressBarManager.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(progressBarTest)
{
  JPetProgressBarManager bar;
  BOOST_REQUIRE_EQUAL(bar.getCurrentValue(5, 100), 5);
  BOOST_REQUIRE_EQUAL(bar.getCurrentValue(5, 5), 100);
  BOOST_REQUIRE_EQUAL(bar.getCurrentValue(1, 5), 20);
  BOOST_REQUIRE_EQUAL(bar.getCurrentValue(0, 5), 0);
  BOOST_REQUIRE_EQUAL(bar.getCurrentValue(0, 2), 0);
}

BOOST_AUTO_TEST_SUITE_END()

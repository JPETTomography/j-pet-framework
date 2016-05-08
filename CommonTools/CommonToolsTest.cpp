/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
 *  @file CommonToolsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CommonToolsTest
#include <boost/test/unit_test.hpp>
#include <map>
#include "CommonTools.h"


BOOST_AUTO_TEST_SUITE(CommonToolsTestSuite)

BOOST_AUTO_TEST_CASE(mapComparatorTest)
{
  std::map<int, int> mapTestLeft, mapTestRight;
  bool areMapsEqual = CommonTools::mapComparator(mapTestLeft, mapTestRight);
  BOOST_REQUIRE_EQUAL(areMapsEqual, true);
}

BOOST_AUTO_TEST_SUITE_END()

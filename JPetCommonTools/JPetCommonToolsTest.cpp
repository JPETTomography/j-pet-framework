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
 *  @file JPetCommonToolsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetCommonToolsTest
#include <boost/test/unit_test.hpp>
#include <map>
#include "JPetCommonTools.h"

//CMakeLists.txt
//file(GLOB UNIT_TEST_SOURCES JPetCommonToolsTest.cpp)

BOOST_AUTO_TEST_SUITE(CommonToolsTestSuite)

BOOST_AUTO_TEST_CASE(mapAreEqualTest)
{
  std::map<int, int> mapTestLeft, mapTestRight;
  bool areMapsEqual = JPetCommonTools::mapComparator(mapTestLeft, mapTestRight);
  BOOST_REQUIRE_EQUAL(areMapsEqual, true);
}

BOOST_AUTO_TEST_CASE(mapsAreNotEqualTest)
{
  std::map<char,int> first;
  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;
  std::map<char,int> second;
  
  bool areMapsEqual = JPetCommonTools::mapComparator(first, second);
  BOOST_REQUIRE_EQUAL(areMapsEqual, false);
}

BOOST_AUTO_TEST_SUITE_END()

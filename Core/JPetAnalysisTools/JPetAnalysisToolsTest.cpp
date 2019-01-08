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
 *  @file JPetAnalysisToolsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetEventTest
#include "./JPetAnalysisTools/JPetAnalysisTools.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(constructor_getHitsOrderedByTime)
{
  std::vector<JPetHit> hits(4);
  hits[0].setTime(2);
  hits[1].setTime(1);
  hits[2].setTime(4);
  hits[3].setTime(3);
  auto results = JPetAnalysisTools::getHitsOrderedByTime(hits);
  double epsilon = 0.0001;
  BOOST_REQUIRE_CLOSE(results[0].getTime(), 1, epsilon);
  BOOST_REQUIRE_CLOSE(results[1].getTime(), 2, epsilon);
  BOOST_REQUIRE_CLOSE(results[2].getTime(), 3, epsilon);
  BOOST_REQUIRE_CLOSE(results[3].getTime(), 4, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

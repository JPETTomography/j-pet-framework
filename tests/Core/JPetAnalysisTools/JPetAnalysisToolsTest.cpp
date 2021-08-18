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
 *  @file JPetAnalysisToolsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetEventTest

#include "JPetAnalysisTools/JPetAnalysisTools.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(constructor_getHitsOrderedByTime)
{
  TVector3 position(1.0, 1.0, 1.0);
  std::vector<JPetBaseHit*> hits;
  JPetBaseHit hit1(2.2, 511.0, position);
  JPetBaseHit hit2(1.1, 511.0, position);
  JPetBaseHit hit3(4.4, 511.0, position);
  JPetBaseHit hit4(3.3, 511.0, position);
  hits.push_back(&hit1);
  hits.push_back(&hit2);
  hits.push_back(&hit3);
  hits.push_back(&hit4);
  auto results = JPetAnalysisTools::getHitsOrderedByTime(hits);
  double epsilon = 0.0001;
  BOOST_REQUIRE_CLOSE(results[0]->getTime(), 1.1, epsilon);
  BOOST_REQUIRE_CLOSE(results[1]->getTime(), 2.2, epsilon);
  BOOST_REQUIRE_CLOSE(results[2]->getTime(), 3.3, epsilon);
  BOOST_REQUIRE_CLOSE(results[3]->getTime(), 4.4, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

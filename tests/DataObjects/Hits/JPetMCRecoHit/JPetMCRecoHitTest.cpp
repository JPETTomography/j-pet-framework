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
 *  @file JPetMCRecoHitTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetMCRecoHitTest

#include "Hits/JPetMCRecoHit/JPetMCRecoHit.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(MCRecoHitTestSuite)

BOOST_AUTO_TEST_CASE(test_one)
{
  JPetMCRecoHit hit;
  BOOST_REQUIRE_EQUAL(hit.getMCindex(), 888888);
  hit.setMCindex(1234);
  BOOST_REQUIRE_EQUAL(hit.getMCindex(), 1234);
}

BOOST_AUTO_TEST_CASE(ClearTest)
{
  double epsilon = 0.0001;
  JPetMCRecoHit hit(1234);
  hit.setTime(11.1);
  hit.setEnergy(22.2);
  hit.setRecoFlag(JPetRecoHit::MC);
  hit.Clear("");
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0, epsilon);
  BOOST_REQUIRE_EQUAL(hit.getRecoFlag(), JPetRecoHit::Unknown);
  BOOST_REQUIRE_EQUAL(hit.getMCindex(), 888888);
}

BOOST_AUTO_TEST_SUITE_END()

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
 *  @file JPetRecoHitTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetRecoHitTest

#include "JPetRecoHit/JPetRecoHit.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(RecoHitTestSuite)

BOOST_AUTO_TEST_CASE(flag_test)
{
  JPetRecoHit recoHit1;
  JPetRecoHit recoHit2(JPetRecoHit::Good);
  JPetRecoHit recoHit3(JPetRecoHit::Corrupted);
  JPetRecoHit recoHit4(JPetRecoHit::MC);

  BOOST_REQUIRE_EQUAL(recoHit1.getRecoFlag(), JPetRecoHit::Unknown);
  recoHit1.setRecoFlag(JPetRecoHit::Good);
  BOOST_REQUIRE_EQUAL(recoHit1.getRecoFlag(), JPetRecoHit::Good);
  recoHit1.setRecoFlag(JPetRecoHit::Corrupted);
  BOOST_REQUIRE_EQUAL(recoHit1.getRecoFlag(), JPetRecoHit::Corrupted);
  recoHit1.setRecoFlag(JPetRecoHit::MC);
  BOOST_REQUIRE_EQUAL(recoHit1.getRecoFlag(), JPetRecoHit::MC);

  BOOST_REQUIRE_EQUAL(recoHit2.getRecoFlag(), JPetRecoHit::Good);
  BOOST_REQUIRE_EQUAL(recoHit3.getRecoFlag(), JPetRecoHit::Corrupted);
  BOOST_REQUIRE_EQUAL(recoHit4.getRecoFlag(), JPetRecoHit::MC);
}

BOOST_AUTO_TEST_CASE(ClearTest)
{
  double epsilon = 0.0001;
  JPetRecoHit hit(JPetRecoHit::Good);
  hit.setTime(11.1);
  hit.setEnergy(22.2);
  hit.Clear("");
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0, epsilon);
  BOOST_REQUIRE_EQUAL(hit.getRecoFlag(), JPetRecoHit::Unknown);
};

BOOST_AUTO_TEST_SUITE_END()

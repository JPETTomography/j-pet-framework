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
 *  @file JPetLORTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetLORTest

#include "JPetLOR/JPetLOR.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetLOR lor;
  BOOST_REQUIRE_EQUAL(lor.getRecoFlag(), JPetLOR::Unknown);
  BOOST_REQUIRE_EQUAL(lor.getTime(), 0.0f);
  BOOST_REQUIRE_EQUAL(lor.getQualityOfTime(), 0.0f);
  BOOST_REQUIRE_EQUAL(lor.isFromSameBarrelSlot(), true);
}

BOOST_AUTO_TEST_CASE(constructor)
{
  JPetBarrelSlot slot1(43, true, "", 0, 43);
  JPetBarrelSlot slot2(44, true, "", 0, 44);
  JPetHit firstHit;
  JPetHit secondHit;
  firstHit.setBarrelSlot(slot1);
  secondHit.setBarrelSlot(slot2);
  JPetLOR lor(8.5f, 4.5f, firstHit, secondHit);
  BOOST_REQUIRE_EQUAL(lor.isFromSameBarrelSlot(), true);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(lor.getTime(), 8.5f, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTime(), 4.5f, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getTimeDiff(), 0.f, epsilon);
  BOOST_REQUIRE_EQUAL(lor.getQualityOfTimeDiff(), 0.f);
  BOOST_REQUIRE_EQUAL(lor.isHitSet(0), 1);
  BOOST_REQUIRE_EQUAL(lor.isHitSet(1), 1);
}

BOOST_AUTO_TEST_CASE(recoFlagSetterTest)
{
  JPetLOR lor;
  BOOST_REQUIRE_EQUAL(lor.getRecoFlag(), JPetLOR::Unknown);
  lor.setRecoFlag(JPetLOR::Good);
  BOOST_REQUIRE_EQUAL(lor.getRecoFlag(), JPetLOR::Good);
  lor.setRecoFlag(JPetLOR::Corrupted);
  BOOST_REQUIRE_EQUAL(lor.getRecoFlag(), JPetLOR::Corrupted);
}

BOOST_AUTO_TEST_CASE(hitTest)
{
  JPetHit firstHit;
  JPetHit secondHit;
  JPetLOR lor(8.5f, 4.5f, firstHit, secondHit);
  BOOST_REQUIRE(lor.getFirstHit().getEnergy() == firstHit.getEnergy());
  BOOST_REQUIRE(lor.getSecondHit().getEnergy() == firstHit.getEnergy());
  JPetHit fh;
  JPetHit sh;
  JPetScin scin1(8);
  JPetScin scin2(16);
  fh.setScintillator(scin1);
  sh.setScintillator(scin2);
  lor.setHits(fh, sh);
  BOOST_REQUIRE(lor.getFirstHit().getScintillator().getID() == fh.getScintillator().getID());
  BOOST_REQUIRE(lor.getSecondHit().getScintillator().getID() == sh.getScintillator().getID());
  JPetScin scin3(32);
  JPetScin scin4(64);
  fh.setScintillator(scin3);
  sh.setScintillator(scin4);
  lor.setFirstHit(fh);
  lor.setSecondHit(sh);
  BOOST_REQUIRE(lor.getFirstHit().getScintillator().getID() == fh.getScintillator().getID());
  BOOST_REQUIRE(lor.getSecondHit().getScintillator().getID() == sh.getScintillator().getID());
}

BOOST_AUTO_TEST_CASE(timeDiffTest)
{
  JPetLOR lor;
  lor.setTimeDiff(111.f);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(lor.getTimeDiff(), 111.f, epsilon);
}

BOOST_AUTO_TEST_CASE(qualityOfTimeTest)
{
  JPetLOR lor;
  lor.setQualityOfTimeDiff(111.f);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTime(), 111.f, epsilon);
}

BOOST_AUTO_TEST_CASE(timeTest)
{
  JPetLOR lor;
  lor.setTime(111.f);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(lor.getTime(), 111.f, epsilon);
}

BOOST_AUTO_TEST_CASE(consistency_check_test)
{
  JPetBarrelSlot slot1(43, true, "", 0, 43);
  JPetBarrelSlot slot2(44, true, "", 0, 44);
  JPetHit firstHit;
  JPetHit secondHit;
  firstHit.setBarrelSlot(slot1);
  secondHit.setBarrelSlot(slot2);
  JPetLOR lor(8.5f, 4.5f, firstHit, secondHit);
  BOOST_REQUIRE_EQUAL(lor.isFromSameBarrelSlot(), true);
  secondHit.setBarrelSlot(slot1);
  lor.setSecondHit(secondHit);
  BOOST_REQUIRE_EQUAL(lor.isFromSameBarrelSlot(), false);
  secondHit.setBarrelSlot(slot2);
  lor.setSecondHit(secondHit);
  BOOST_REQUIRE_EQUAL(lor.isFromSameBarrelSlot(), true);
  firstHit.setTime(10.001);
  secondHit.setTime(10.002);
  lor.setHits(firstHit, secondHit);
  BOOST_REQUIRE_EQUAL(lor.isFromSameBarrelSlot(), true);
  lor.setHits(secondHit, firstHit);
  BOOST_REQUIRE_EQUAL(lor.isFromSameBarrelSlot(), false);
}

BOOST_AUTO_TEST_SUITE_END()

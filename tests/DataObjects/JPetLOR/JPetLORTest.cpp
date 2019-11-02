/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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

#include <boost/test/unit_test.hpp>
#include "JPetLOR/JPetLOR.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

float epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetLOR lor;
  BOOST_REQUIRE_EQUAL(lor.getRecoFlag(), JPetLOR::Unknown);
  BOOST_REQUIRE_CLOSE(lor.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTime(), 0.0, epsilon);
  BOOST_REQUIRE(lor.checkConsistency());
}

BOOST_AUTO_TEST_CASE(constructor)
{
  JPetScin scin1(1, 30.0, 15.0, 7.0, 1.0, -1.0, 1.0);
  JPetScin scin2(2, 30.0, 15.0, 7.0, 2.0, -2.0, 2.0);
  JPetHit firstHit;
  JPetHit secondHit;
  firstHit.setScin(scin1);
  secondHit.setScin(scin2);
  JPetLOR lor1(111.1, 11.1, firstHit, secondHit);
  BOOST_REQUIRE_CLOSE(lor1.getTime(), 111.1, epsilon);
  BOOST_REQUIRE_CLOSE(lor1.getQualityOfTime(), 11.1, epsilon);
  BOOST_REQUIRE_CLOSE(lor1.getTimeDiff(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(lor1.getQualityOfTimeDiff(), 0.0, epsilon);
  BOOST_REQUIRE(lor1.checkConsistency());
  BOOST_REQUIRE(lor1.isHitSet(0));
  BOOST_REQUIRE(lor1.isHitSet(1));
  JPetLOR lor2(111.1, 11.1, 123.1, 12.3, firstHit, secondHit, JPetLOR::Good);
  BOOST_REQUIRE_CLOSE(lor2.getTime(), 111.1, epsilon);
  BOOST_REQUIRE_CLOSE(lor2.getQualityOfTime(), 11.1, epsilon);
  BOOST_REQUIRE_CLOSE(lor2.getTimeDiff(), 123.1, epsilon);
  BOOST_REQUIRE_CLOSE(lor2.getQualityOfTimeDiff(), 12.3, epsilon);
  BOOST_REQUIRE(lor2.checkConsistency());
  BOOST_REQUIRE(lor2.isHitSet(0));
  BOOST_REQUIRE(lor2.isHitSet(1));
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

BOOST_AUTO_TEST_CASE(settersTest)
{
  JPetLOR lor;
  lor.setTime(100.0);
  BOOST_REQUIRE_CLOSE(lor.getTime(), 100.0, epsilon);
  lor.setTime(200.0);
  BOOST_REQUIRE_CLOSE(lor.getTime(), 200.0, epsilon);
  lor.setQualityOfTime(1.5);
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTime(), 1.5, epsilon);
  lor.setQualityOfTime(5.5);
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTime(), 5.5, epsilon);
  lor.setTimeDiff(24.5);
  BOOST_REQUIRE_CLOSE(lor.getTimeDiff(), 24.5, epsilon);
  lor.setTimeDiff(57.5);
  BOOST_REQUIRE_CLOSE(lor.getTimeDiff(), 57.5, epsilon);
  lor.setQualityOfTimeDiff(2.3);
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTimeDiff(), 2.3, epsilon);
  lor.setQualityOfTimeDiff(12.3);
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTimeDiff(), 12.3, epsilon);

  BOOST_REQUIRE(!lor.isHitSet(0));
  BOOST_REQUIRE(!lor.isHitSet(1));
  JPetHit firstHit1;
  JPetHit secondHit1;
  JPetHit firstHit2;
  JPetHit secondHit2;
  firstHit1.setTime(111.1);
  secondHit1.setTime(222.2);
  firstHit2.setTime(333.3);
  secondHit2.setTime(444.4);
  lor.setHits(firstHit1, secondHit1);
  BOOST_REQUIRE(lor.isHitSet(0));
  BOOST_REQUIRE(lor.isHitSet(1));
  BOOST_REQUIRE_CLOSE(lor.getFirstHit().getTime(), 111.1, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getSecondHit().getTime(), 222.2, epsilon);

  lor.setFirstHit(firstHit2);
  lor.setSecondHit(secondHit2);
  BOOST_REQUIRE(lor.isHitSet(0));
  BOOST_REQUIRE(lor.isHitSet(1));
  BOOST_REQUIRE_CLOSE(lor.getFirstHit().getTime(), 333.3, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getSecondHit().getTime(), 444.4, epsilon);
}

BOOST_AUTO_TEST_CASE(consistency_check_test_1)
{
  // no hits set - true
  JPetLOR lor;
  BOOST_REQUIRE(lor.checkConsistency());
}

BOOST_AUTO_TEST_CASE(consistency_check_test_2)
{
  // hits from the same scintillator - false
  JPetScin scin(1, 30.0, 15.0, 7.0, 1.0, -1.0, 1.0);
  JPetHit firstHit;
  JPetHit secondHit;
  firstHit.setScin(scin);
  secondHit.setScin(scin);
  JPetLOR lor;
  lor.setHits(firstHit, secondHit);
  BOOST_REQUIRE(!lor.checkConsistency());
}

BOOST_AUTO_TEST_CASE(consistency_check_test_3)
{
  // wrong time order - false
  JPetScin scin1(1, 30.0, 15.0, 7.0, 1.0, -1.0, 1.0);
  JPetScin scin2(2, 30.0, 15.0, 7.0, 2.0, -2.0, 2.0);
  JPetHit firstHit;
  JPetHit secondHit;
  firstHit.setScin(scin1);
  secondHit.setScin(scin2);
  firstHit.setTime(500.0);
  secondHit.setTime(100.0);
  JPetLOR lor;
  lor.setHits(firstHit, secondHit);
  BOOST_REQUIRE(!lor.checkConsistency());
}

BOOST_AUTO_TEST_CASE(consistency_check_test_4)
{
  // all good - true
  JPetScin scin1(1, 30.0, 15.0, 7.0, 1.0, -1.0, 1.0);
  JPetScin scin2(2, 30.0, 15.0, 7.0, 2.0, -2.0, 2.0);
  JPetHit firstHit;
  JPetHit secondHit;
  firstHit.setScin(scin1);
  secondHit.setScin(scin2);
  firstHit.setTime(100.0);
  secondHit.setTime(200.0);
  JPetLOR lor;
  lor.setHits(firstHit, secondHit);
  BOOST_REQUIRE(lor.checkConsistency());
}

BOOST_AUTO_TEST_CASE(clear_test)
{
  JPetScin scin1(1, 30.0, 15.0, 7.0, 1.0, -1.0, 1.0);
  JPetScin scin2(2, 30.0, 15.0, 7.0, 2.0, -2.0, 2.0);
  JPetHit firstHit;
  JPetHit secondHit;
  firstHit.setScin(scin1);
  secondHit.setScin(scin2);
  firstHit.setTime(100.0);
  secondHit.setTime(200.0);
  JPetLOR lor(111.1, 11.1, 123.1, 12.3, firstHit, secondHit, JPetLOR::Good);
  lor.setHits(firstHit, secondHit);
  BOOST_REQUIRE_EQUAL(lor.getRecoFlag(), JPetLOR::Good);
  BOOST_REQUIRE_CLOSE(lor.getTime(), 111.1, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTime(), 11.1, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getTimeDiff(), 123.1, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTimeDiff(), 12.3, epsilon);
  BOOST_REQUIRE(lor.checkConsistency());
  BOOST_REQUIRE(lor.isHitSet(0));
  BOOST_REQUIRE(lor.isHitSet(1));
  lor.Clear();
  BOOST_REQUIRE_EQUAL(lor.getRecoFlag(), JPetLOR::Unknown);
  BOOST_REQUIRE_CLOSE(lor.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getTimeDiff(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(lor.getQualityOfTimeDiff(), 0.0, epsilon);
  BOOST_REQUIRE(lor.checkConsistency());
  BOOST_REQUIRE(!lor.isHitSet(0));
  BOOST_REQUIRE(!lor.isHitSet(1));
}

BOOST_AUTO_TEST_SUITE_END()

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
 *  @file JPetPhysRecoHitTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPhysRecoHit

#include "JPetPhysRecoHit/JPetPhysRecoHit.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetPhysRecoHit hit;
  double epsilon = 0.0001;
  BOOST_REQUIRE_CLOSE(hit.getTimeDiff(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getToT(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTimeDiff(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfToT(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0f, epsilon);
  BOOST_REQUIRE_EQUAL(hit.isSignalASet(), false);
  BOOST_REQUIRE_EQUAL(hit.isSignalBSet(), false);
}

BOOST_AUTO_TEST_CASE(consistency_check_test)
{
  JPetScin scin1(1, 2.0, 50.0, 1.9, 0.7);
  JPetScin scin2(2, 2.0, 50.0, 1.9, 0.7);

  JPetPM pm1(JPetPM::SideA, 101, 0, 0, std::pair<float, float>(0, 0), "");
  JPetPM pm2(JPetPM::SideB, 102, 0, 0, std::pair<float, float>(0, 0), "");
  JPetPM pm3(JPetPM::SideB, 103, 0, 0, std::pair<float, float>(0, 0), "");
  pm1.setScin(scin1);
  pm2.setScin(scin1);
  pm3.setScin(scin2);

  JPetPhysSignal signal1;
  JPetPhysSignal signal2;
  JPetPhysSignal signal3;
  signal1.setPM(pm1);
  signal2.setPM(pm2);
  signal3.setPM(pm3);

  JPetPhysRecoHit hit;
  // Hit with unset signals checks true
  BOOST_REQUIRE_EQUAL(hit.checkConsistency(), true);
  hit.setSignalA(signal1);
  BOOST_REQUIRE_EQUAL(hit.checkConsistency(), true);
  hit.setSignalB(signal2);
  BOOST_REQUIRE_EQUAL(hit.checkConsistency(), true);

  // Unconsistent settings
  hit.setSignalA(signal1);
  hit.setSignalB(signal3);
  BOOST_REQUIRE_EQUAL(hit.checkConsistency(), false);

  hit.setSignalA(signal2);
  hit.setSignalB(signal3);
  BOOST_REQUIRE_EQUAL(hit.checkConsistency(), false);
}

BOOST_AUTO_TEST_CASE(set_get_test)
{
  JPetPhysRecoHit hit;
  double td = 1.1;
  double tot = 2.2;
  double qt = 3.3;
  double qtd = 4.4;
  double qe = 5.5;
  double qtot = 6.6;

  hit.setTimeDiff(td);
  hit.setToT(tot);
  hit.setQualityOfTime(qt);
  hit.setQualityOfTimeDiff(qtd);
  hit.setQualityOfEnergy(qe);
  hit.setQualityOfToT(qtot);

  double epsilon = 0.0001;
  BOOST_REQUIRE_CLOSE(hit.getTimeDiff(), td, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getToT(), tot, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), qt, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTimeDiff(), qtd, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), qe, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfToT(), qtot, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

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

BOOST_AUTO_TEST_CASE(ClearTest)
{
  double epsilon = 0.0001;

  JPetBarrelSlot slot(99, true, "stefan", 90.1, 1);
  JPetScin scin(88, 11.1, 22.2, 33.3, 44.4);
  scin.setBarrelSlot(slot);

  JPetPM pm1(77, "green");
  JPetPM pm2(66, "red");
  pm1.setScin(scin);
  pm2.setScin(scin);
  pm1.setBarrelSlot(slot);
  pm2.setBarrelSlot(slot);

  JPetPhysRecoHit hit;
  hit.setTime(11.1);
  hit.setEnergy(22.2);
  hit.setTimeDiff(33.3);
  hit.setToT(44.4);
  hit.setQualityOfTime(0.1);
  hit.setQualityOfTimeDiff(0.2);
  hit.setQualityOfEnergy(0.3);
  hit.setQualityOfToT(0.4);

  JPetPhysSignal signalA;
  JPetPhysSignal signalB;
  signalA.setPM(pm1);
  signalB.setPM(pm2);
  signalA.setBarrelSlot(slot);
  signalB.setBarrelSlot(slot);

  hit.setSignals(signalA, signalB);

  hit.Clear("");
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTimeDiff(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getToT(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTimeDiff(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfToT(), 0.0, epsilon);
  BOOST_REQUIRE(!hit.isSignalASet());
  BOOST_REQUIRE(!hit.isSignalBSet());
}

BOOST_AUTO_TEST_SUITE_END()

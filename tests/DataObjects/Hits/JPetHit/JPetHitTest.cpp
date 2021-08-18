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
 *  @file JPetHitTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetHitTest

#include <boost/test/unit_test.hpp>
#include "JPetSlot/JPetSlot.h"
#include "JPetScin/JPetScin.h"
#include "JPetHit/JPetHit.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

double epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetHit hit;
  BOOST_REQUIRE_EQUAL(hit.getRecoFlag(), JPetHit::Unknown);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosX(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosY(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), 0.0, epsilon);
  BOOST_REQUIRE(!hit.isSignalASet());
  BOOST_REQUIRE(!hit.isSignalBSet());
}

BOOST_AUTO_TEST_CASE(recoFlagSetterTest)
{
  JPetHit hit;
  BOOST_REQUIRE_EQUAL(hit.getRecoFlag(), JPetHit::Unknown);
  hit.setRecoFlag(JPetHit::Good);
  BOOST_REQUIRE_EQUAL(hit.getRecoFlag(), JPetHit::Good);
  hit.setRecoFlag(JPetHit::Corrupted);
  BOOST_REQUIRE_EQUAL(hit.getRecoFlag(), JPetHit::Corrupted);
}

BOOST_AUTO_TEST_CASE(consistency_check_1)
{
  // default constructor
  JPetHit hit;
  BOOST_REQUIRE(hit.checkConsistency());
}

BOOST_AUTO_TEST_CASE(consistency_check_2)
{
  // null signals error
  JPetPhysSignal signalA(true);
  JPetPhysSignal signalB(true);
  JPetHit hit;
  hit.setSignalA(signalA);
  hit.setSignalB(signalB);
  BOOST_REQUIRE(!hit.checkConsistency());
}

BOOST_AUTO_TEST_CASE(consistency_check_3)
{
  // null pms error
  JPetPM pmA(true);
  JPetPM pmB(true);
  JPetPhysSignal signalA;
  JPetPhysSignal signalB;
  signalA.setPM(pmA);
  signalB.setPM(pmB);
  JPetHit hit;
  hit.setSignalA(signalA);
  hit.setSignalB(signalB);
  BOOST_REQUIRE(!hit.checkConsistency());
}

BOOST_AUTO_TEST_CASE(consistency_check_4)
{
  // null scins error
  JPetScin scin(true);
  JPetPM pmA(1, JPetPM::SideA, "nice", 1);
  JPetPM pmB(2, JPetPM::SideB, "not nice", 2);
  pmA.setScin(scin);
  pmB.setScin(scin);
  JPetPhysSignal signalA;
  JPetPhysSignal signalB;
  signalA.setPM(pmA);
  signalB.setPM(pmB);
  JPetHit hit4;
  hit4.setSignalA(signalA);
  hit4.setSignalB(signalB);
  BOOST_REQUIRE(!hit4.checkConsistency());
}

BOOST_AUTO_TEST_CASE(consistency_check_5)
{
  // signls from the same side
  JPetScin scin(1, 12.0, 6.0, 3.0, 1.0, -1.0, 1.0);
  JPetPM pm1(1, JPetPM::SideA, "nice", 1);
  JPetPM pm2(2, JPetPM::SideA, "not nice", 2);
  pm1.setScin(scin);
  pm2.setScin(scin);
  JPetPhysSignal signal1;
  JPetPhysSignal signal2;
  signal1.setPM(pm1);
  signal2.setPM(pm2);
  JPetHit hit;
  hit.setSignalA(signal1);
  hit.setSignalB(signal2);
  BOOST_REQUIRE(!hit.checkConsistency());
}

BOOST_AUTO_TEST_CASE(consistency_check_6)
{
  // different scins
  JPetScin scin1(1, 12.0, 6.0, 3.0, 1.0, -1.0, 1.0);
  JPetScin scin2(2, 12.0, 6.0, 3.0, 3.0, -3.0, 3.0);
  JPetPM pmA(1, JPetPM::SideA, "nice", 1);
  JPetPM pmB(2, JPetPM::SideB, "not nice", 2);
  pmA.setScin(scin1);
  pmB.setScin(scin2);
  JPetPhysSignal signalA;
  JPetPhysSignal signalB;
  signalA.setPM(pmA);
  signalB.setPM(pmB);
  JPetHit hit;
  hit.setSignalA(signalA);
  hit.setSignalB(signalB);
  BOOST_REQUIRE(!hit.checkConsistency());
}

BOOST_AUTO_TEST_CASE(consistency_check_7)
{
  // all good
  JPetScin scin(1, 12.0, 6.0, 3.0, 1.0, -1.0, 1.0);
  JPetPM pmA(1, JPetPM::SideA, "nice", 1);
  JPetPM pmB(2, JPetPM::SideB, "not nice", 2);
  pmA.setScin(scin);
  pmB.setScin(scin);
  JPetPhysSignal signalA;
  JPetPhysSignal signalB;
  signalA.setPM(pmA);
  signalB.setPM(pmB);
  JPetHit hit;
  hit.setSignalA(signalA);
  hit.setSignalB(signalB);
  BOOST_REQUIRE(hit.checkConsistency());
}

BOOST_AUTO_TEST_CASE(hitSettersTest)
{
  JPetHit hit;
  float time = 0.1;
  float timeDiff = 0.2;
  float timeQual = 0.3;
  float timeDiffQual = 0.4;
  float energy = 0.5;
  float energyQual = 0.6;
  hit.setTime(time);
  hit.setQualityOfTime(timeQual);
  hit.setTimeDiff(timeDiff);
  hit.setQualityOfTimeDiff(timeDiffQual);
  hit.setEnergy(energy);
  hit.setQualityOfEnergy(energyQual);
  hit.setPos(1.0, 2.0, 3.0);
  BOOST_REQUIRE_CLOSE(hit.getTime(), time, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), timeQual, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTimeDiff(), timeDiff, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTimeDiff(), timeDiffQual, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), energy, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), energyQual, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosX(), 1.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosY(), 2.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), 3.0, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

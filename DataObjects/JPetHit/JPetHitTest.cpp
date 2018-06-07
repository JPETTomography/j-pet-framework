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
 *  @file JPetHitTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetHitTest

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include <boost/test/unit_test.hpp>
#include "./JPetScin/JPetScin.h"
#include "./JPetHit/JPetHit.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetHit hit;
  double epsilon = 0.0001;
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosX(), 0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosY(), 0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), 0, epsilon);
  BOOST_REQUIRE_EQUAL(hit.isSignalASet(), false);
  BOOST_REQUIRE_EQUAL(hit.isSignalBSet(), false);
}

BOOST_AUTO_TEST_CASE(consistency_check_test)
{
  JPetPhysSignal leftSignal;
  JPetPhysSignal rightSignal;
  JPetBarrelSlot slot1(43, true, "", 0, 43);
  JPetBarrelSlot slot2(44, true, "", 0, 44);
  JPetPM pmA(JPetPM::SideA, 101, 0, 0, std::pair<float, float>(0, 0), "");
  JPetPM pmB(JPetPM::SideB, 102, 0, 0, std::pair<float, float>(0, 0), "");
  leftSignal.setPM(pmA);
  rightSignal.setPM(pmB);
  pmA.setBarrelSlot(slot1);
  pmB.setBarrelSlot(slot1);
  JPetHit hit1;
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), true);
  hit1.setSignalA(leftSignal);
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), true);
  hit1.setSignalB(rightSignal);
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), true);
  pmB.setBarrelSlot(slot2);
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), false );
  pmB.setBarrelSlot(slot1);
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), true );
  pmB.setSide(JPetPM::SideA);
  BOOST_REQUIRE_EQUAL( hit1.checkConsistency(), false );
}

BOOST_AUTO_TEST_CASE(set_get_scalars_test)
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
  BOOST_REQUIRE_EQUAL(hit.getTime(), time);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfTime(), timeQual);
  BOOST_REQUIRE_EQUAL(hit.getTimeDiff(), timeDiff);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfTimeDiff(), timeDiffQual);
  BOOST_REQUIRE_EQUAL(hit.getEnergy(), energy);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfEnergy(), energyQual);
}

BOOST_AUTO_TEST_CASE(set_get_objects_test)
{
  TVector3 position(1.0f, 2.0f, 3.0f);
  JPetPhysSignal leftSignal;
  JPetPhysSignal rightSignal;
  float timeA = 123.0;
  float timeB = 456.0;
  leftSignal.setTime(timeA);
  rightSignal.setTime(timeB);
  int scinID = 42;
  JPetScin scin(scinID);
  JPetBarrelSlot slot;
  JPetPM pmA(JPetPM::SideA, 101, 0, 0, std::pair<float, float>(0, 0), "");
  JPetPM pmB(JPetPM::SideB, 102, 0, 0, std::pair<float, float>(0, 0), "");
  pmA.setBarrelSlot(slot);
  pmB.setBarrelSlot(slot);
  leftSignal.setPM(pmA);
  rightSignal.setPM(pmB);
  JPetHit hit;
  hit.setSignalA(leftSignal);
  hit.setSignalB(rightSignal);
  hit.setScintillator(scin);
  hit.setBarrelSlot(slot);
  BOOST_REQUIRE_EQUAL(hit.getScintillator().getID(), scinID);
  BOOST_REQUIRE_EQUAL(&(hit.getScintillator()), &scin);
  BOOST_REQUIRE_EQUAL(&(hit.getBarrelSlot()), &slot);
  BOOST_REQUIRE_EQUAL(hit.getSignalA().getTime(), timeA);
  BOOST_REQUIRE_EQUAL(hit.getSignalB().getTime(), timeB);
}

BOOST_AUTO_TEST_CASE(not_default_constructor)
{
  TVector3 position(6.0, 7.0, 8.0);
  JPetPhysSignal p_sigA(true);
  JPetPhysSignal p_sigB(true);
  JPetBarrelSlot bs(1, true, "name", 2, 3);
  JPetScin sc(1, 2, 3, 4, 5);
  JPetHit hit(0.0f, 1.0f, 2.0f, 3.0f, position, p_sigA, p_sigB, bs, sc);
  BOOST_REQUIRE_EQUAL(hit.getEnergy(), 0.0f);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfEnergy(), 1.0f);
  BOOST_REQUIRE_EQUAL(hit.getTime(), 2.0f);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfTime(), 3.0f);
  BOOST_REQUIRE_EQUAL(hit.getPosX(), 6.0);
  BOOST_REQUIRE_EQUAL(hit.getPosY(), 7.0);
  BOOST_REQUIRE_EQUAL(hit.getPosZ(), 8.0);
  BOOST_REQUIRE(hit.isSignalASet());
  BOOST_REQUIRE(hit.isSignalBSet());
  BOOST_REQUIRE_EQUAL(hit.getBarrelSlot().getID(), bs.getID());
  BOOST_REQUIRE_EQUAL(hit.getBarrelSlot().isActive(), bs.isActive());
  BOOST_REQUIRE_EQUAL(hit.getBarrelSlot().getName(), bs.getName());
  BOOST_REQUIRE_EQUAL(hit.getBarrelSlot().getTheta(), bs.getTheta());
  BOOST_REQUIRE_EQUAL(hit.getScintillator().getID(), sc.getID());
  BOOST_REQUIRE_EQUAL(hit.getScintillator().getAttenLen(), sc.getAttenLen());
  BOOST_REQUIRE_EQUAL(hit.getSignalA().getTime(), p_sigA.getTime());
  BOOST_REQUIRE_EQUAL(hit.getSignalA().getPhe(), p_sigA.getPhe());
  BOOST_REQUIRE_EQUAL(hit.getSignalB().getTime(), p_sigB.getTime());
  BOOST_REQUIRE_EQUAL(hit.getSignalB().getPhe(), p_sigB.getPhe());
}

BOOST_AUTO_TEST_SUITE_END()

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

#include "Hits/JPetPhysRecoHit/JPetPhysRecoHit.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestSuite)

double epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetPhysRecoHit hit;
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getToT(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfToT(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTimeDiff(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTimeDiff(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_EQUAL(hit.isSignalASet(), false);
  BOOST_REQUIRE_EQUAL(hit.isSignalBSet(), false);
}

BOOST_AUTO_TEST_CASE(set_get_test)
{
  JPetPhysRecoHit hit;
  hit.setTime(1.1);
  hit.setQualityOfTime(2.2);
  hit.setTimeDiff(3.3);
  hit.setQualityOfTimeDiff(4.4);
  hit.setToT(5.5);
  hit.setQualityOfToT(6.6);
  hit.setEnergy(7.7);
  hit.setQualityOfEnergy(8.8);
  BOOST_REQUIRE_CLOSE(hit.getTime(), 1.1, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 2.2, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTimeDiff(), 3.3, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTimeDiff(), 4.4, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getToT(), 5.5, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfToT(), 6.6, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 7.7, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 8.8, epsilon);
}

BOOST_AUTO_TEST_CASE(ClearTest)
{
  JPetScin scin(1, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9);

  JPetMatrix mtx1(1, JPetMatrix::SideA);
  JPetMatrix mtx2(1, JPetMatrix::SideB);
  mtx1.setScin(scin);
  mtx2.setScin(scin);

  JPetPhysRecoHit hit;
  hit.setTime(11.1);
  hit.setQualityOfTime(0.1);
  hit.setTimeDiff(22.2);
  hit.setQualityOfTimeDiff(0.2);
  hit.setEnergy(33.3);
  hit.setQualityOfEnergy(0.3);
  hit.setToT(44.4);
  hit.setQualityOfToT(0.4);

  JPetMatrixSignal signalA;
  JPetMatrixSignal signalB;
  signalA.setMatrix(mtx1);
  signalB.setMatrix(mtx2);
  hit.setSignals(signalA, signalB);
  hit.Clear("");

  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTimeDiff(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTimeDiff(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getToT(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfToT(), 0.0, epsilon);
  BOOST_REQUIRE(!hit.isSignalASet());
  BOOST_REQUIRE(!hit.isSignalBSet());
}

BOOST_AUTO_TEST_SUITE_END()

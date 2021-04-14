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
 *  @file JPetBaseHitTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetBaseHitTest

#include "JPetBaseHit/JPetBaseHit.h"
#include "JPetScin/JPetScin.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(BaseHitTest)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  double epsilon = 0.0001;
  JPetBaseHit hit;
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0, epsilon);
}

BOOST_AUTO_TEST_CASE(constructor)
{
  double epsilon = 0.0001;
  JPetScin scin(456, 1.0, 2.0, 3.0, 4.0);
  TVector3 position(11.0, 22.0, 33.0);
  JPetBaseHit hit(10.0, 511.0, position, scin);
  BOOST_REQUIRE_CLOSE(hit.getTime(), 10.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 511.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosX(), 11.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosY(), 22.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), 33.0, epsilon);
  BOOST_REQUIRE_EQUAL(hit.getScin().getID(), scin.getID());
}

BOOST_AUTO_TEST_CASE(SetAndGetTest)
{
  double epsilon = 0.0001;

  JPetBaseHit hit;
  hit.setTime(33.3);
  hit.setEnergy(511.0);
  BOOST_REQUIRE_CLOSE(hit.getTime(), 33.3, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 511.0, epsilon);

  hit.setPos(1.0, 2.0, 3.0);
  BOOST_REQUIRE_CLOSE(hit.getPosX(), 1.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosY(), 2.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), 3.0, epsilon);

  hit.setPosX(4.0);
  hit.setPosY(5.0);
  hit.setPosZ(6.0);
  BOOST_REQUIRE_CLOSE(hit.getPosX(), 4.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosY(), 5.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), 6.0, epsilon);

  TVector3 position(7.0, 8.0, 9.0);
  hit.setPos(position);
  BOOST_REQUIRE_CLOSE(hit.getPosX(), 7.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosY(), 8.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), 9.0, epsilon);

  JPetScin scin(456, 1.0, 2.0, 3.0, 4.0);
  hit.setScin(scin);
  BOOST_REQUIRE_EQUAL(hit.getScin().getID(), scin.getID());
}

BOOST_AUTO_TEST_CASE(ClearTest)
{
  double epsilon = 0.0001;
  JPetScin scin(1, 100.0, 5.5, 6.6, 7.7);
  TVector3 position(1.1, 2.2, 3.3);
  JPetBaseHit hit(11.1, 22.2, position, scin);

  BOOST_REQUIRE_CLOSE(hit.getTime(), 11.1, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 22.2, epsilon);

  hit.Clear("");
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

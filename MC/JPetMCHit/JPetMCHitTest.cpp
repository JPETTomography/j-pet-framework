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
 *  @file JPetMCHitTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetMCHitTest

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include <boost/test/unit_test.hpp>
#include "./JPetMCHit/JPetMCHit.h"
#include "./JPetScin/JPetScin.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetMCHit hit;
  double epsilon = 0.0001;
  BOOST_REQUIRE_EQUAL(hit.getMCDecayTreeIndex(), 0u);
  BOOST_REQUIRE_EQUAL(hit.getMCVtxIndex(), 0);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().X(), 0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Y(), 0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Z(), 0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().X(), 0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Y(), 0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Z(), 0, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosX(), 0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getPosY(), 0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), 0, epsilon );
  BOOST_REQUIRE_EQUAL(hit.isSignalASet(), false);
  BOOST_REQUIRE_EQUAL(hit.isSignalBSet(), false);
}

BOOST_AUTO_TEST_CASE(non_default_constructor)
{
  TVector3 position(6.0, 7.0, 8.0);
  TVector3 polarization(2.0, 3.0, 4.0);
  TVector3 momentum(1.0, -13.0, 13.0);
  auto MCDecayTreeIndex = 7u;
  auto MCVtxIndex = 99u;
  auto energy = 5.5;
  auto time  = 3.3;
  double epsilon = 0.0001;
  JPetMCHit hit(MCDecayTreeIndex, MCVtxIndex, energy , time,
    position, polarization, momentum);
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), energy, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTime(), time, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosX(), position.X(), epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosY(), position.Y() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), position.Z() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().X(), polarization.X(), epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Y(), polarization.Y() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Z(), polarization.Z() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().X(), momentum.X(), epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Y(), momentum.Y() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Z(), momentum.Z() , epsilon);
  BOOST_REQUIRE_EQUAL(hit.getMCDecayTreeIndex(), MCDecayTreeIndex);
  BOOST_REQUIRE_EQUAL(hit.getMCVtxIndex(), MCVtxIndex);
}

BOOST_AUTO_TEST_CASE(getters_setters_mc)
{
  JPetMCHit hit;
  TVector3 pol(2.0, 3.0, 4.0);
  TVector3 mom(1.0, -13.0, 13.0);
  auto MCDecayTreeIndex = 7u;
  auto MCVtxIndex = 99u;
  double epsilon = 0.0001;
  hit.setPolarization(pol.X(), pol.Y(), pol.Z());
  hit.setMomentum(mom.X(), mom.Y(), mom.Z() );
  hit.setMCDecayTreeIndex(MCDecayTreeIndex);
  hit.setMCVtxIndex(MCVtxIndex);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().X(), pol.X(), epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Y(), pol.Y() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Z(), pol.Z() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().X(), mom.X(), epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Y(), mom.Y() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Z(), mom.Z() , epsilon);
  BOOST_REQUIRE_EQUAL(hit.getMCDecayTreeIndex(), MCDecayTreeIndex);
  BOOST_REQUIRE_EQUAL(hit.getMCVtxIndex(), MCVtxIndex);
}

BOOST_AUTO_TEST_SUITE_END()

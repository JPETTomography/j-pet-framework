/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetGeantScinHitsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGeantScinHitsTest
#include <boost/test/unit_test.hpp>

#include "JPetGeantScinHits/JPetGeantScinHits.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetGeantScinHits hit;
  double epsilon = 0.0001;
  BOOST_REQUIRE_CLOSE(hit.getEneDepos(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getEvtID(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getScinID(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTrackID(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTrackPDG(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getHitPosition().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getHitPosition().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getHitPosition().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationIn().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationIn().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationIn().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationOut().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationOut().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationOut().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumIn().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumIn().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumIn().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumOut().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumOut().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumOut().Z(), 0.0f, epsilon);
}

BOOST_AUTO_TEST_CASE(check_setters)
{
  JPetGeantScinHits hit;

  int evtID = 67;
  int scinID = 34;
  int trkID = 34;
  int trkPDG = 20;
  int numOfInt = 50;
  double eneDep = 511;
  double t = 2.0;

  hit.setEvtID(evtID);
  hit.setScinID(scinID);
  hit.setTrackID(trkID);
  hit.setTrackPDG(trkPDG);
  hit.setNumOfInteractions(numOfInt);
  hit.setEneDepos(eneDep);
  hit.setTime(t);

  BOOST_REQUIRE_EQUAL(hit.getEvtID(), evtID);
  BOOST_REQUIRE_EQUAL(hit.getEneDepos(), eneDep);
  BOOST_REQUIRE_EQUAL(hit.getScinID(), scinID);
  BOOST_REQUIRE_EQUAL(hit.getTrackID(), trkID);
  BOOST_REQUIRE_EQUAL(hit.getTrackPDG(), trkPDG);
  BOOST_REQUIRE_EQUAL(hit.getTime(), t);

  double hit_x = 5.6;
  double hit_y = 4.36;
  double hit_z = 35.6;

  double pIn_x = 5.6;
  double pIn_y = 4.36;
  double pIn_z = 35.6;
  double pOut_x = 54.6;
  double pOut_y = 43.36;
  double pOut_z = 45.6;

  double mIn_x = 15.6;
  double mIn_y = 14.36;
  double mIn_z = 135.6;
  double mOut_x = 534.6;
  double mOut_y = 433.36;
  double mOut_z = 435.6;

  hit.setHitPosition(pIn_x, pIn_y, pIn_z);

  hit.setPolarizationIn(pIn_x, pIn_y, pIn_z);
  hit.setPolarizationOut(pOut_x, pOut_y, pOut_z);

  hit.setMomentumIn(mIn_x, mIn_y, mIn_z);
  hit.setMomentumOut(mOut_x, mOut_y, mOut_z);

  BOOST_REQUIRE_EQUAL(hit.getHitPosition().X(), hit_x);
  BOOST_REQUIRE_EQUAL(hit.getHitPosition().Y(), hit_y);
  BOOST_REQUIRE_EQUAL(hit.getHitPosition().Z(), hit_z);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationIn().X(), pIn_x);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationIn().Y(), pIn_y);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationIn().Z(), pIn_z);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationOut().X(), pOut_x);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationOut().Y(), pOut_y);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationOut().Z(), pOut_z);
  BOOST_REQUIRE_EQUAL(hit.getMomentumIn().X(), mIn_x);
  BOOST_REQUIRE_EQUAL(hit.getMomentumIn().Y(), mIn_y);
  BOOST_REQUIRE_EQUAL(hit.getMomentumIn().Z(), mIn_z);
  BOOST_REQUIRE_EQUAL(hit.getMomentumOut().X(), mOut_x);
  BOOST_REQUIRE_EQUAL(hit.getMomentumOut().Y(), mOut_y);
  BOOST_REQUIRE_EQUAL(hit.getMomentumOut().Z(), mOut_z);
}

BOOST_AUTO_TEST_CASE(check_nonstandard_constructor)
{

  int evtID = 67;
  int scinID = 34;
  int trkID = 34;
  int trkPDG = 20;
  int numOfInt = 50;
  double eneDep = 511;
  double t = 2.0;
  double hit_x = 5.6;
  double hit_y = 4.36;
  double hit_z = 35.6;
  double epsilon = 0.0001;

  TVector3 hitPos(hit_x, hit_y, hit_z);

  JPetGeantScinHits hit(evtID, scinID, trkID, trkPDG, numOfInt, eneDep, t, hitPos);

  BOOST_REQUIRE_EQUAL(hit.getEvtID(), evtID);
  BOOST_REQUIRE_EQUAL(hit.getEneDepos(), eneDep);
  BOOST_REQUIRE_EQUAL(hit.getScinID(), scinID);
  BOOST_REQUIRE_EQUAL(hit.getTrackID(), trkID);
  BOOST_REQUIRE_EQUAL(hit.getTrackPDG(), trkPDG);
  BOOST_REQUIRE_EQUAL(hit.getTime(), t);

  BOOST_REQUIRE_EQUAL(hit.getHitPosition().X(), hit_x);
  BOOST_REQUIRE_EQUAL(hit.getHitPosition().Y(), hit_y);
  BOOST_REQUIRE_EQUAL(hit.getHitPosition().Z(), hit_z);

  BOOST_REQUIRE_CLOSE(hit.getPolarizationIn().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationIn().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationIn().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationOut().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationOut().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarizationOut().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumIn().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumIn().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumIn().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumOut().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumOut().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentumOut().Z(), 0.0f, epsilon);
}

BOOST_AUTO_TEST_CASE(check_nonstandard_constructor_2)
{

  int evtID = 67;
  int scinID = 34;
  int trkID = 34;
  int trkPDG = 20;
  int numOfInt = 50;
  double eneDep = 511;
  double t = 2.0;
  double hit_x = 5.6;
  double hit_y = 4.36;
  double hit_z = 35.6;

  double pIn_x = 5.6;
  double pIn_y = 4.36;
  double pIn_z = 35.6;
  double pOut_x = 54.6;
  double pOut_y = 43.36;
  double pOut_z = 45.6;

  double mIn_x = 15.6;
  double mIn_y = 14.36;
  double mIn_z = 135.6;
  double mOut_x = 534.6;
  double mOut_y = 433.36;
  double mOut_z = 435.6;

  TVector3 hitPos(hit_x, hit_y, hit_z);
  TVector3 polIn(pIn_x, pIn_y, pIn_z);
  TVector3 polOut(pOut_x, pOut_y, pOut_z);
  TVector3 molIn(mIn_x, mIn_y, mIn_z);
  TVector3 molOut(mOut_x, mOut_y, mOut_z);

  JPetGeantScinHits hit(evtID, scinID, trkID, trkPDG, numOfInt, eneDep, t, hitPos, polIn, polOut, molIn, molOut);

  BOOST_REQUIRE_EQUAL(hit.getEvtID(), evtID);
  BOOST_REQUIRE_EQUAL(hit.getEneDepos(), eneDep);
  BOOST_REQUIRE_EQUAL(hit.getScinID(), scinID);
  BOOST_REQUIRE_EQUAL(hit.getTrackID(), trkID);
  BOOST_REQUIRE_EQUAL(hit.getTrackPDG(), trkPDG);
  BOOST_REQUIRE_EQUAL(hit.getTime(), t);

  BOOST_REQUIRE_EQUAL(hit.getHitPosition().X(), hit_x);
  BOOST_REQUIRE_EQUAL(hit.getHitPosition().Y(), hit_y);
  BOOST_REQUIRE_EQUAL(hit.getHitPosition().Z(), hit_z);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationIn().X(), pIn_x);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationIn().Y(), pIn_y);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationIn().Z(), pIn_z);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationOut().X(), pOut_x);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationOut().Y(), pOut_y);
  BOOST_REQUIRE_EQUAL(hit.getPolarizationOut().Z(), pOut_z);
  BOOST_REQUIRE_EQUAL(hit.getMomentumIn().X(), mIn_x);
  BOOST_REQUIRE_EQUAL(hit.getMomentumIn().Y(), mIn_y);
  BOOST_REQUIRE_EQUAL(hit.getMomentumIn().Z(), mIn_z);
  BOOST_REQUIRE_EQUAL(hit.getMomentumOut().X(), mOut_x);
  BOOST_REQUIRE_EQUAL(hit.getMomentumOut().Y(), mOut_y);
  BOOST_REQUIRE_EQUAL(hit.getMomentumOut().Z(), mOut_z);
}
BOOST_AUTO_TEST_SUITE_END()

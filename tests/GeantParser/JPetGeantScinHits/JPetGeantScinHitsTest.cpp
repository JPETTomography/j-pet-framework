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

double epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetGeantScinHits hit;
  BOOST_REQUIRE_CLOSE(hit.GetEneDepos(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetEvtID(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetScinID(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetTrackID(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetTrackPDG(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().Z(), 0.0f, epsilon);
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

  hit.SetEvtID(evtID);
  hit.SetScinID(scinID);
  hit.SetTrackID(trkID);
  hit.SetTrackPDG(trkPDG);
  hit.SetNumOfInteractions(numOfInt);
  hit.SetEneDepos(eneDep);
  hit.SetTime(t);

  BOOST_REQUIRE_EQUAL(hit.GetEvtID(), evtID);
  BOOST_REQUIRE_EQUAL(hit.GetEneDepos(), eneDep);
  BOOST_REQUIRE_EQUAL(hit.GetScinID(), scinID);
  BOOST_REQUIRE_EQUAL(hit.GetTrackID(), trkID);
  BOOST_REQUIRE_EQUAL(hit.GetTrackPDG(), trkPDG);
  BOOST_REQUIRE_EQUAL(hit.GetTime(), t);

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

  hit.SetHitPosition(pIn_x, pIn_y, pIn_z);

  hit.SetPolarizationIn(pIn_x, pIn_y, pIn_z);
  hit.SetPolarizationOut(pOut_x, pOut_y, pOut_z);

  hit.SetMomentumIn(mIn_x, mIn_y, mIn_z);
  hit.SetMomentumOut(mOut_x, mOut_y, mOut_z);

  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().X(), hit_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().Y(), hit_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().Z(), hit_z, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().X(), pIn_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().Y(), pIn_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().Z(), pIn_z, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().X(), pOut_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().Y(), pOut_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().Z(), pOut_z, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().X(), mIn_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().Y(), mIn_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().Z(), mIn_z, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().X(), mOut_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().Y(), mOut_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().Z(), mOut_z, epsilon);
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

  TVector3 hitPos(hit_x, hit_y, hit_z);

  JPetGeantScinHits hit(evtID, scinID, trkID, trkPDG, numOfInt, eneDep, t, hitPos);

  BOOST_REQUIRE_EQUAL(hit.GetEvtID(), evtID);
  BOOST_REQUIRE_EQUAL(hit.GetEneDepos(), eneDep);
  BOOST_REQUIRE_EQUAL(hit.GetScinID(), scinID);
  BOOST_REQUIRE_EQUAL(hit.GetTrackID(), trkID);
  BOOST_REQUIRE_EQUAL(hit.GetTrackPDG(), trkPDG);
  BOOST_REQUIRE_EQUAL(hit.GetTime(), t);

  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().X(), hit_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().Y(), hit_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().Z(), hit_z, epsilon);

  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().Z(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().X(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().Y(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().Z(), 0.0f, epsilon);
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

  BOOST_REQUIRE_EQUAL(hit.GetEvtID(), evtID);
  BOOST_REQUIRE_EQUAL(hit.GetEneDepos(), eneDep);
  BOOST_REQUIRE_EQUAL(hit.GetScinID(), scinID);
  BOOST_REQUIRE_EQUAL(hit.GetTrackID(), trkID);
  BOOST_REQUIRE_EQUAL(hit.GetTrackPDG(), trkPDG);
  BOOST_REQUIRE_EQUAL(hit.GetTime(), t);

  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().X(), hit_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().Y(), hit_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetHitPosition().Z(), hit_z, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().X(), pIn_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().Y(), pIn_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationIn().Z(), pIn_z, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().X(), pOut_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().Y(), pOut_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetPolarizationOut().Z(), pOut_z, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().X(), mIn_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().Y(), mIn_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumIn().Z(), mIn_z, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().X(), mOut_x, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().Y(), mOut_y, epsilon);
  BOOST_REQUIRE_CLOSE(hit.GetMomentumOut().Z(), mOut_z, epsilon);
}
BOOST_AUTO_TEST_SUITE_END()

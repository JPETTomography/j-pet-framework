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
 *  @file JPetRawSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetRawSignal/JPetRawSignal.h"
#include <boost/test/unit_test.hpp>
#include "./JPetPM/JPetPM.h"

BOOST_AUTO_TEST_SUITE(ParamDataTS)

BOOST_AUTO_TEST_CASE(GetNumberOfPointsTest)
{
  JPetRawSignal signal;
  BOOST_REQUIRE_EQUAL(signal.getNumberOfPoints(JPetSigCh::Trailing), 0);
  BOOST_REQUIRE_EQUAL(signal.getNumberOfPoints(JPetSigCh::Leading), 0);
}

BOOST_AUTO_TEST_CASE(AddLeadingPointTest)
{
  JPetRawSignal signal;
  const JPetSigCh sigCh;
  signal.addPoint(sigCh);
  BOOST_REQUIRE_EQUAL(signal.getNumberOfPoints(JPetSigCh::Leading), 1);
}

BOOST_AUTO_TEST_CASE(AddTrailingPointTest)
{
  JPetRawSignal signal;
  const JPetSigCh sigCh(JPetSigCh::Trailing, 8.f);
  signal.addPoint(sigCh);
  BOOST_REQUIRE_EQUAL(signal.getNumberOfPoints(JPetSigCh::Trailing), 1);
}

BOOST_AUTO_TEST_CASE(GetVectorOfPointsTest)
{
  JPetRawSignal signal;
  JPetSigCh sigch1(JPetSigCh::Trailing, 8.f);
  sigch1.setThreshold(100.f);
  sigch1.setThresholdNumber(2);
  JPetSigCh sigch2(JPetSigCh::Trailing, 17.f);
  sigch2.setThreshold(200.f);
  sigch2.setThresholdNumber(1);
  signal.addPoint(sigch1);
  signal.addPoint(sigch2);
  BOOST_REQUIRE_EQUAL(
      signal.getPoints(JPetSigCh::Trailing, JPetRawSignal::ByThrNum).at(0).getValue(),
      17.f);
  BOOST_REQUIRE_EQUAL(
      signal.getPoints(JPetSigCh::Trailing, JPetRawSignal::ByThrValue).at(0).getValue(),
      8.f);
  BOOST_REQUIRE_EQUAL(
      signal.getPoints(JPetSigCh::Leading, JPetRawSignal::ByThrValue).size(),
      0u);
}

BOOST_AUTO_TEST_CASE(GetMapOfTimesVsThrNumTest)
{
  JPetRawSignal signal;
  JPetSigCh sigch1(JPetSigCh::Trailing, 8.f);
  sigch1.setThreshold(100.f);
  sigch1.setThresholdNumber(1);
  JPetSigCh sigch2(JPetSigCh::Trailing, 17.f);
  sigch2.setThreshold(200.f);
  sigch2.setThresholdNumber(2);
  JPetSigCh sigch3(JPetSigCh::Trailing, 43.f);
  sigch3.setThreshold(400.f);
  sigch3.setThresholdNumber(4);
  signal.addPoint(sigch1);
  signal.addPoint(sigch2);
  signal.addPoint(sigch3);
  std::map<int, double> map;
  map = signal.getTimesVsThresholdNumber(JPetSigCh::Trailing);
  BOOST_REQUIRE_EQUAL( map[sigch1.getThresholdNumber()], sigch1.getValue() );
  BOOST_REQUIRE_EQUAL( map[sigch2.getThresholdNumber()], sigch2.getValue() );
  BOOST_REQUIRE_EQUAL( map[sigch3.getThresholdNumber()], sigch3.getValue() );
  BOOST_REQUIRE_EQUAL( map[3], 0.f );
}

BOOST_AUTO_TEST_CASE(GetMapOfTimesVsThrValueTest)
{
  JPetRawSignal signal;
  JPetSigCh sigch1(JPetSigCh::Trailing, 8.f);
  sigch1.setThreshold(100.f);
  sigch1.setThresholdNumber(1);
  JPetSigCh sigch2(JPetSigCh::Trailing, 17.f);
  sigch2.setThreshold(200.f);
  sigch2.setThresholdNumber(2);
  JPetSigCh sigch3(JPetSigCh::Trailing, 43.f);
  sigch3.setThreshold(400.f);
  sigch3.setThresholdNumber(4);
  signal.addPoint(sigch1);
  signal.addPoint(sigch2);
  signal.addPoint(sigch3);
  std::map<int, std::pair<float, float>> map;
  map = signal.getTimesVsThresholdValue(JPetSigCh::Trailing);
  BOOST_REQUIRE_EQUAL(map[1].first, sigch1.getThreshold());
  BOOST_REQUIRE_EQUAL(map[1].second, sigch1.getValue());
  BOOST_REQUIRE_EQUAL(map[2].first, sigch2.getThreshold());
  BOOST_REQUIRE_EQUAL(map[2].second, sigch2.getValue());
  BOOST_REQUIRE_EQUAL(map[4].first, sigch3.getThreshold());
  BOOST_REQUIRE_EQUAL(map[4].second, sigch3.getValue());
}

BOOST_AUTO_TEST_CASE(SetAndGetTRefPMObjectTest)
{
  JPetRawSignal signal;
  JPetPM PM;
  signal.setPM(PM);
  PM = signal.getPM();
  BOOST_CHECK(PM.getSide() == JPetPM::SideA);
}

BOOST_AUTO_TEST_CASE(SetAndGetTRefBarrelSlotObjectTest)
{
  JPetRawSignal signal;
  JPetBarrelSlot barrelSlot(2, true, "bs2", 30., 2);
  signal.setBarrelSlot(barrelSlot);
  barrelSlot = signal.getBarrelSlot();
  BOOST_CHECK(barrelSlot.getID() == 2);
}

BOOST_AUTO_TEST_CASE(GetMapOfTOTsVsThrNumOrValueTest)
{
  JPetRawSignal signal;
  JPetSigCh sigch1t(JPetSigCh::Trailing, 8.f);
  sigch1t.setThreshold(400.f);
  sigch1t.setThresholdNumber(1);
  JPetSigCh sigch2t(JPetSigCh::Trailing, 17.f);
  sigch2t.setThreshold(50.f);
  sigch2t.setThresholdNumber(2);
  JPetSigCh sigch3t(JPetSigCh::Trailing, 43.f);
  sigch3t.setThreshold(100.f);
  sigch3t.setThresholdNumber(4);
  JPetSigCh sigch1l(JPetSigCh::Leading, 8.f);
  sigch1l.setThreshold(100.f);
  sigch1l.setThresholdNumber(1);
  JPetSigCh sigch2l(JPetSigCh::Leading, 17.f);
  sigch2l.setThreshold(200.f);
  sigch2l.setThresholdNumber(3);
  JPetSigCh sigch3l(JPetSigCh::Leading, 43.f);
  sigch3l.setThreshold(400.f);
  sigch3l.setThresholdNumber(4);
  signal.addPoint(sigch1t);
  signal.addPoint(sigch2t);
  signal.addPoint(sigch3t);
  signal.addPoint(sigch1l);
  signal.addPoint(sigch2l);
  signal.addPoint(sigch3l);
  std::map<int, double> map;
  map = signal.getTOTsVsThresholdNumber();
  BOOST_REQUIRE_EQUAL( map.size(), 2u );
  BOOST_REQUIRE_EQUAL( map[1], sigch1t.getValue() - sigch1l.getValue() );
  BOOST_REQUIRE_EQUAL( map[4], sigch3t.getValue() - sigch3l.getValue() );
  BOOST_REQUIRE_EQUAL( map.count(2), 0u );
  BOOST_REQUIRE_EQUAL( map.count(3), 0u );
  BOOST_CHECK_THROW( map.at(2), std::out_of_range);
  std::map<int, double> map2;
  map2 = signal.getTOTsVsThresholdValue();
  BOOST_REQUIRE_EQUAL( map2.size(), 2u );
  BOOST_REQUIRE_EQUAL( map2[100.f], sigch3t.getValue() - sigch1l.getValue() );
  BOOST_REQUIRE_EQUAL( map2[400.f], sigch1t.getValue() - sigch3l.getValue() );
  BOOST_REQUIRE_EQUAL( map2.count(50.f), 0u );
  BOOST_REQUIRE_EQUAL( map2.count(200.f), 0u );
}

BOOST_AUTO_TEST_SUITE_END()

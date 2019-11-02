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
 *  @file JPetRawSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest

#include "JPetRawSignal/JPetRawSignal.h"
#include <boost/test/unit_test.hpp>
#include "JPetSlot/JPetSlot.h"
#include "JPetPM/JPetPM.h"

BOOST_AUTO_TEST_SUITE(ParamDataTS)

float epsilon = 0.0001;

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
  JPetChannel channel1(1, 2, 30.0);
  JPetChannel channel2(2, 1, 80.0);
  JPetSigCh sigCh1(JPetSigCh::Trailing, 8.0);
  JPetSigCh sigCh2(JPetSigCh::Trailing, 17.0);
  sigCh1.setChannel(channel1);
  sigCh2.setChannel(channel2);
  JPetRawSignal signal;
  signal.addPoint(sigCh1);
  signal.addPoint(sigCh2);
  BOOST_REQUIRE_CLOSE(
    signal.getPoints(JPetSigCh::Trailing, JPetRawSignal::ByThrNum).at(0).getTime(),
    17.0, epsilon
  );
  BOOST_REQUIRE_CLOSE(
    signal.getPoints(JPetSigCh::Trailing, JPetRawSignal::ByThrValue).at(0).getTime(),
    8.0, epsilon
  );
  BOOST_REQUIRE_EQUAL(
    signal.getPoints(JPetSigCh::Leading, JPetRawSignal::ByThrValue).size(), 0
  );
}

BOOST_AUTO_TEST_CASE(GetMapOfTimesVsThrNumTest)
{
  JPetChannel channel1(1, 1, 30.0);
  JPetChannel channel2(2, 2, 50.0);
  JPetChannel channel3(3, 3, 80.0);

  JPetSigCh sigCh1(JPetSigCh::Trailing, 10.0);
  JPetSigCh sigCh2(JPetSigCh::Trailing, 20.0);
  JPetSigCh sigCh3(JPetSigCh::Trailing, 30.0);
  sigCh1.setChannel(channel1);
  sigCh2.setChannel(channel2);
  sigCh3.setChannel(channel3);

  JPetRawSignal signal;
  signal.addPoint(sigCh1);
  signal.addPoint(sigCh2);
  signal.addPoint(sigCh3);

  auto map = signal.getTimesVsThresholdNumber(JPetSigCh::Trailing);
  BOOST_REQUIRE_EQUAL(map[sigCh1.getChannel().getThresholdNumber()], sigCh1.getTime());
  BOOST_REQUIRE_EQUAL(map[sigCh2.getChannel().getThresholdNumber()], sigCh2.getTime());
  BOOST_REQUIRE_EQUAL(map[sigCh3.getChannel().getThresholdNumber()], sigCh3.getTime());
}

BOOST_AUTO_TEST_CASE(DoubledLeadingsEmptyMapNumberTest)
{
  JPetChannel channel1(1, 1, 30.0);
  JPetChannel channel2(2, 1, 50.0);
  JPetChannel channel3(3, 3, 80.0);

  JPetSigCh sigCh1(JPetSigCh::Leading, 10.0);
  JPetSigCh sigCh2(JPetSigCh::Leading, 20.0);
  JPetSigCh sigCh3(JPetSigCh::Leading, 30.0);
  sigCh1.setChannel(channel1);
  sigCh2.setChannel(channel2);
  sigCh3.setChannel(channel3);

  JPetRawSignal signal;
  signal.addPoint(sigCh1);
  signal.addPoint(sigCh2);
  signal.addPoint(sigCh3);

  auto map1 = signal.getTimesVsThresholdNumber(JPetSigCh::Leading);
  BOOST_REQUIRE_EQUAL(map1.size(), 0);
  auto map2 = signal.getTimesVsThresholdValue(JPetSigCh::Leading);
  BOOST_REQUIRE_EQUAL(map2.size(), 0);
}

BOOST_AUTO_TEST_CASE(MapsOfTimesTest)
{
  JPetChannel channel1(1, 1, 30.0);
  JPetChannel channel2(2, 2, 50.0);
  JPetChannel channel3(3, 3, 80.0);

  JPetSigCh sigChL1(JPetSigCh::Leading, 10.0);
  JPetSigCh sigChT1(JPetSigCh::Trailing, 20.0);
  JPetSigCh sigChL2(JPetSigCh::Leading, 12.0);
  JPetSigCh sigChT2(JPetSigCh::Trailing, 22.0);
  JPetSigCh sigChL3(JPetSigCh::Leading, 15.0);
  JPetSigCh sigChT3(JPetSigCh::Trailing, 35.0);
  sigChL1.setChannel(channel1);
  sigChT1.setChannel(channel1);
  sigChL2.setChannel(channel2);
  sigChT2.setChannel(channel2);
  sigChL3.setChannel(channel3);
  sigChT3.setChannel(channel3);

  JPetRawSignal signal;
  signal.addPoint(sigChL1);
  signal.addPoint(sigChT1);
  signal.addPoint(sigChL2);
  signal.addPoint(sigChT2);
  signal.addPoint(sigChL3);
  signal.addPoint(sigChT3);

  auto mapL1 = signal.getTimesVsThresholdNumber(JPetSigCh::Leading);
  auto mapT1 = signal.getTimesVsThresholdNumber(JPetSigCh::Trailing);
  auto mapL2 = signal.getTimesVsThresholdValue(JPetSigCh::Leading);
  auto mapT2 = signal.getTimesVsThresholdValue(JPetSigCh::Trailing);

  BOOST_REQUIRE_CLOSE(mapL1[1], sigChL1.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(mapL1[2], sigChL2.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(mapL1[3], sigChL3.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(mapT1[1], sigChT1.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(mapT1[2], sigChT2.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(mapT1[3], sigChT3.getTime(), epsilon);

  BOOST_REQUIRE_CLOSE(mapL2[1].first, sigChL1.getChannel().getThresholdValue(), epsilon);
  BOOST_REQUIRE_CLOSE(mapL2[2].first, sigChL2.getChannel().getThresholdValue(), epsilon);
  BOOST_REQUIRE_CLOSE(mapL2[3].first, sigChL3.getChannel().getThresholdValue(), epsilon);
  BOOST_REQUIRE_CLOSE(mapT2[1].first, sigChT1.getChannel().getThresholdValue(), epsilon);
  BOOST_REQUIRE_CLOSE(mapT2[2].first, sigChT2.getChannel().getThresholdValue(), epsilon);
  BOOST_REQUIRE_CLOSE(mapT2[3].first, sigChT3.getChannel().getThresholdValue(), epsilon);

  BOOST_REQUIRE_CLOSE(mapL2[1].second, sigChL1.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(mapL2[2].second, sigChL2.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(mapL2[3].second, sigChL3.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(mapT2[1].second, sigChT1.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(mapT2[2].second, sigChT2.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(mapT2[3].second, sigChT3.getTime(), epsilon);
}

BOOST_AUTO_TEST_CASE(GetMapOfTOTsVsThrNumOrValueTest)
{
  JPetChannel channel1(1, 1, 30.0);
  JPetChannel channel2(2, 2, 50.0);
  JPetChannel channel3(3, 3, 80.0);

  JPetSigCh sigCh1l(JPetSigCh::Leading, 10.0);
  JPetSigCh sigCh1t(JPetSigCh::Trailing, 15.0);
  JPetSigCh sigCh2l(JPetSigCh::Leading, 20.0);
  JPetSigCh sigCh2t(JPetSigCh::Trailing, 25.0);
  JPetSigCh sigCh3l(JPetSigCh::Leading, 30.0);
  JPetSigCh sigCh3t(JPetSigCh::Trailing, 35.0);

  sigCh1l.setChannel(channel1);
  sigCh1t.setChannel(channel1);
  sigCh2l.setChannel(channel2);
  sigCh2t.setChannel(channel2);
  sigCh3l.setChannel(channel3);
  sigCh3t.setChannel(channel3);

  JPetRawSignal signal;
  signal.addPoint(sigCh1l);
  signal.addPoint(sigCh1t);
  signal.addPoint(sigCh2l);
  signal.addPoint(sigCh2t);
  signal.addPoint(sigCh3l);
  signal.addPoint(sigCh3t);

  auto map1 = signal.getTOTsVsThresholdNumber();
  BOOST_REQUIRE_EQUAL(map1.size(), 3);
  BOOST_REQUIRE_CLOSE(map1[1], sigCh1t.getTime() - sigCh1l.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(map1[2], sigCh2t.getTime() - sigCh2l.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(map1[3], sigCh3t.getTime() - sigCh3l.getTime(), epsilon);
  auto map2 = signal.getTOTsVsThresholdValue();
  BOOST_REQUIRE_EQUAL(map2.size(), 3);
  BOOST_REQUIRE_CLOSE(map2[30.0], sigCh1t.getTime() - sigCh1l.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(map2[50.0], sigCh2t.getTime() - sigCh2l.getTime(), epsilon);
  BOOST_REQUIRE_CLOSE(map2[80.0], sigCh3t.getTime() - sigCh3l.getTime(), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

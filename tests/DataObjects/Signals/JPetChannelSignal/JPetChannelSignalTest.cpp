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
 *  @file JPetChannelSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetChannelSignalTest

#include "Signals/JPetChannelSignal/JPetChannelSignal.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ChannelSignalTestSuite)

double epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(constructors_test)
{
  // default
  JPetChannelSignal signal1;
  BOOST_REQUIRE_EQUAL(signal1.getRecoFlag(), JPetRecoSignal::Unknown);
  BOOST_REQUIRE_CLOSE(signal1.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_EQUAL(signal1.getEdgeType(), JPetChannelSignal::Leading);

  JPetChannelSignal signal2(JPetChannelSignal::Trailing, 123.4);
  BOOST_REQUIRE_EQUAL(signal2.getRecoFlag(), JPetRecoSignal::Unknown);
  BOOST_REQUIRE_CLOSE(signal2.getTime(), 123.4, epsilon);
  BOOST_REQUIRE_EQUAL(signal2.getEdgeType(), JPetChannelSignal::Trailing);

  JPetChannelSignal signal3(JPetRecoSignal::Corrupted, JPetChannelSignal::Trailing, 56.7);
  BOOST_REQUIRE_EQUAL(signal3.getRecoFlag(), JPetRecoSignal::Corrupted);
  BOOST_REQUIRE_CLOSE(signal3.getTime(), 56.7, epsilon);
  BOOST_REQUIRE_EQUAL(signal3.getEdgeType(), JPetChannelSignal::Trailing);
}

BOOST_AUTO_TEST_CASE(setters_Test)
{
  JPetChannelSignal signal;
  signal.setRecoFlag(JPetRecoSignal::Corrupted);
  signal.setEdgeType(JPetChannelSignal::Trailing);
  signal.setTime(123.45);
  JPetChannel channel(1, 2, 30.0);
  signal.setChannel(channel);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetRecoSignal::Corrupted);
  BOOST_REQUIRE_EQUAL(signal.getEdgeType(), JPetChannelSignal::Trailing);
  BOOST_REQUIRE_CLOSE(signal.getTime(), 123.45, epsilon);
  BOOST_REQUIRE_EQUAL(signal.getChannel().getID(), 1);
  BOOST_REQUIRE_EQUAL(signal.getChannel().getThresholdNumber(), 2);
  BOOST_REQUIRE_CLOSE(signal.getChannel().getThresholdValue(), 30.0, epsilon);
}

BOOST_AUTO_TEST_CASE(compare_methods_test)
{
  JPetChannel channel1(1, 1, 90.0);
  JPetChannel channel2(2, 2, 50.0);

  JPetChannelSignal sig1(JPetChannelSignal::Leading, 1.0);
  JPetChannelSignal sig2(JPetChannelSignal::Trailing, 2.0);
  JPetChannelSignal sig3(JPetChannelSignal::Leading, 3.0);
  JPetChannelSignal sig4(JPetChannelSignal::Trailing, 4.0);
  sig1.setChannel(channel1);
  sig2.setChannel(channel1);
  sig3.setChannel(channel2);
  sig4.setChannel(channel2);

  std::pair<JPetChannelSignal, JPetChannelSignal> pair1 = std::make_pair(sig1, sig2);
  std::pair<JPetChannelSignal, JPetChannelSignal> pair2 = std::make_pair(sig3, sig4);

  BOOST_REQUIRE(JPetChannelSignal::compareByThresholdNumber(pair1, pair2));
  BOOST_REQUIRE(JPetChannelSignal::compareByThresholdValue(pair2, pair1));
}

BOOST_AUTO_TEST_SUITE_END()

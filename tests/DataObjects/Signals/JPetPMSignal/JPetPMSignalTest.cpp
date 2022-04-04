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
 *  @file JPetPMSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPMSignalTest

#include "Signals/JPetPMSignal/JPetPMSignal.h"
#include "JPetSlot/JPetSlot.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(JPetPMSignalTest)

double epsilon = 0.00001;

BOOST_AUTO_TEST_CASE(constructor_test)
{
  JPetPMSignal signal;
  BOOST_REQUIRE_CLOSE(signal.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(signal.getToT(), 0.0, epsilon);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetRecoSignal::Unknown);
  BOOST_REQUIRE_EQUAL(signal.getLeadTrailPairs().size(), 0);
}

BOOST_AUTO_TEST_CASE(set_get_test)
{
  JPetPM pm(1, "test", 1);
  JPetPMSignal signal;
  signal.setTime(12.34);
  signal.setToT(56.78);
  signal.setRecoFlag(JPetRecoSignal::Corrupted);
  signal.setPM(pm);

  BOOST_REQUIRE_CLOSE(signal.getTime(), 12.34, epsilon);
  BOOST_REQUIRE_CLOSE(signal.getToT(), 56.78, epsilon);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetRecoSignal::Corrupted);
  BOOST_REQUIRE_EQUAL(signal.getPM().getID(), pm.getID());
}

BOOST_AUTO_TEST_CASE(add_channel_sigals_test)
{
  JPetChannel channel1(1, 1, 30.0);
  JPetChannel channel2(2, 2, 50.0);

  JPetChannelSignal chSig1L(JPetChannelSignal::Leading, 11.11);
  JPetChannelSignal chSig1T(JPetChannelSignal::Trailing, 22.22);
  JPetChannelSignal chSig1Ta(JPetChannelSignal::Trailing, 5.5);
  JPetChannelSignal chSig2L(JPetChannelSignal::Leading, 9.9);

  chSig1L.setChannel(channel1);
  chSig1T.setChannel(channel1);
  chSig1Ta.setChannel(channel1);
  chSig2L.setChannel(channel2);

  JPetPMSignal signal;
  // Correct construction
  BOOST_REQUIRE(signal.addLeadTrailPair(chSig1L, chSig1T));
  // Incorrect ones
  BOOST_REQUIRE(!signal.addLeadTrailPair(chSig1L, chSig1Ta));
  BOOST_REQUIRE(!signal.addLeadTrailPair(chSig1Ta, chSig1L));
  BOOST_REQUIRE(!signal.addLeadTrailPair(chSig1Ta, chSig1L));
  BOOST_REQUIRE(!signal.addLeadTrailPair(chSig2L, chSig1T));
}

BOOST_AUTO_TEST_CASE(get_sigals_test)
{
  JPetChannel channel1(1, 1, 50.0);
  JPetChannel channel2(2, 2, 30.0);

  JPetChannelSignal chSig1L(JPetChannelSignal::Leading, 11.11);
  JPetChannelSignal chSig1T(JPetChannelSignal::Trailing, 22.22);
  JPetChannelSignal chSig2L(JPetChannelSignal::Leading, 12.11);
  JPetChannelSignal chSig2T(JPetChannelSignal::Trailing, 23.22);
  chSig1L.setChannel(channel1);
  chSig1T.setChannel(channel1);
  chSig2L.setChannel(channel2);
  chSig2T.setChannel(channel2);

  JPetPMSignal signal;
  signal.addLeadTrailPair(chSig1L, chSig1T);
  signal.addLeadTrailPair(chSig2L, chSig2T);

  auto result1 = signal.getLeadTrailPairs();
  auto result2 = signal.getLeadTrailPairs(JPetPMSignal::ByThrValue);
  auto result3 = signal.getLeadTrailPairs(JPetPMSignal::ByThrNum);

  BOOST_REQUIRE_CLOSE(result1[0].first.getTime(), 12.11, epsilon);
  BOOST_REQUIRE_CLOSE(result1[0].second.getTime(), 23.22, epsilon);
  BOOST_REQUIRE_CLOSE(result1[1].first.getTime(), 11.11, epsilon);
  BOOST_REQUIRE_CLOSE(result1[1].second.getTime(), 22.22, epsilon);

  BOOST_REQUIRE_CLOSE(result2[0].first.getTime(), 12.11, epsilon);
  BOOST_REQUIRE_CLOSE(result2[0].second.getTime(), 23.22, epsilon);
  BOOST_REQUIRE_CLOSE(result2[1].first.getTime(), 11.11, epsilon);
  BOOST_REQUIRE_CLOSE(result2[1].second.getTime(), 22.22, epsilon);

  BOOST_REQUIRE_CLOSE(result3[0].first.getTime(), 11.11, epsilon);
  BOOST_REQUIRE_CLOSE(result3[0].second.getTime(), 22.22, epsilon);
  BOOST_REQUIRE_CLOSE(result3[1].first.getTime(), 12.11, epsilon);
  BOOST_REQUIRE_CLOSE(result3[1].second.getTime(), 23.22, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

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
 *  @file JPetSigChTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSigChTest
#include <boost/test/unit_test.hpp>
#include "./JPetSigCh/JPetSigCh.h"

BOOST_AUTO_TEST_SUITE(SigChTestSuite)

BOOST_AUTO_TEST_CASE(constructor_Test)
{
  JPetSigCh sigCh1;
  BOOST_REQUIRE_EQUAL(sigCh1.getRecoFlag(), JPetSigCh::Unknown);
  BOOST_REQUIRE_EQUAL(sigCh1.getType(), JPetSigCh::Leading);
  BOOST_REQUIRE_EQUAL(sigCh1.getValue(), JPetSigCh::kUnset);
  BOOST_REQUIRE_EQUAL(sigCh1.getThreshold(), JPetSigCh::kUnset);
  BOOST_REQUIRE_EQUAL(sigCh1.getThresholdNumber(), 0);
  BOOST_REQUIRE_EQUAL(sigCh1.getDAQch(), 0);

  JPetSigCh sigCh2(JPetSigCh::Trailing, 15.3);
  float epsilon = 0.001;
  BOOST_REQUIRE_EQUAL(sigCh2.getRecoFlag(), JPetSigCh::Unknown);
  BOOST_REQUIRE_EQUAL(sigCh2.getType(), JPetSigCh::Trailing);
  BOOST_REQUIRE_CLOSE(sigCh2.getValue(), 15.3, epsilon);
  BOOST_REQUIRE_EQUAL(sigCh2.getThreshold(), JPetSigCh::kUnset);
  BOOST_REQUIRE_EQUAL(sigCh2.getThresholdNumber(), 0);
  BOOST_REQUIRE_EQUAL(sigCh2.getDAQch(), 0);
}

BOOST_AUTO_TEST_CASE(setters_Test)
{
  JPetSigCh sigCh;
  sigCh.setRecoFlag(JPetSigCh::Bad);
  sigCh.setType(JPetSigCh::Trailing);
  sigCh.setValue(14.222);
  sigCh.setThreshold(53.2);
  sigCh.setThresholdNumber(3);
  sigCh.setDAQch(1523);
  JPetPM pm(1, "first");
  sigCh.setPM(pm);
  JPetFEB feb(43, true, "", "", 1, 1, 8, 1);
  sigCh.setFEB(feb);
  JPetTRB trb(22, 1, 123);
  sigCh.setTRB(trb);
  JPetTOMBChannel tomb(1234);
  sigCh.setTOMBChannel(tomb);
  float epsilon = 0.001;
  BOOST_REQUIRE_EQUAL(sigCh.getRecoFlag(), JPetSigCh::Bad);
  BOOST_REQUIRE_EQUAL(sigCh.getType(), JPetSigCh::Trailing);
  BOOST_REQUIRE_CLOSE(sigCh.getValue(), 14.222, epsilon);
  BOOST_REQUIRE_CLOSE(sigCh.getThreshold(), 53.2, epsilon);
  BOOST_REQUIRE_EQUAL(sigCh.getThresholdNumber(), 3);
  BOOST_REQUIRE_EQUAL(sigCh.getDAQch(), 1523);
  BOOST_REQUIRE_EQUAL(sigCh.getPM().getID(), 1);
  BOOST_REQUIRE_EQUAL(sigCh.getFEB().getID(), 43);
  BOOST_REQUIRE_EQUAL(sigCh.getTRB().getID(), 22);
  BOOST_REQUIRE_EQUAL(sigCh.getChannel(), 1234);
}

BOOST_AUTO_TEST_CASE(compareByThresholdValue_Test)
{
  JPetSigCh sigCh1(JPetSigCh::Trailing, 12.2);
  JPetSigCh sigCh2(JPetSigCh::Leading, 13.3);
  sigCh1.setThreshold(50.1);
  sigCh2.setThreshold(123.4);
  BOOST_REQUIRE(JPetSigCh::compareByThresholdValue(sigCh1, sigCh2));
  BOOST_REQUIRE(!JPetSigCh::compareByThresholdValue(sigCh2, sigCh1));
}

BOOST_AUTO_TEST_CASE(compareByThresholdNumber_Test)
{
  JPetSigCh sigCh1(JPetSigCh::Trailing, 12.2);
  JPetSigCh sigCh2(JPetSigCh::Leading, 13.3);
  sigCh1.setThresholdNumber(2);
  sigCh2.setThresholdNumber(4);
  BOOST_REQUIRE(JPetSigCh::compareByThresholdNumber(sigCh1, sigCh2));
  BOOST_REQUIRE(!JPetSigCh::compareByThresholdNumber(sigCh2, sigCh1));
}

BOOST_AUTO_TEST_SUITE_END()

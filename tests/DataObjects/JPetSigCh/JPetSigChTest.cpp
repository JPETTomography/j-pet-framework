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
 *  @file JPetSigChTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSigChTest
#include <boost/test/unit_test.hpp>
#include "JPetSigCh/JPetSigCh.h"

BOOST_AUTO_TEST_SUITE(SigChTestSuite)

float epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(constructor_Test)
{
  JPetSigCh sigCh1;
  BOOST_REQUIRE_EQUAL(sigCh1.getRecoFlag(), JPetSigCh::Unknown);
  BOOST_REQUIRE_EQUAL(sigCh1.getType(), JPetSigCh::Leading);
  BOOST_REQUIRE_EQUAL(sigCh1.getTime(), JPetSigCh::kUnset);

  JPetSigCh sigCh2(JPetSigCh::Trailing, 15.3);
  BOOST_REQUIRE_EQUAL(sigCh2.getRecoFlag(), JPetSigCh::Unknown);
  BOOST_REQUIRE_EQUAL(sigCh2.getType(), JPetSigCh::Trailing);
  BOOST_REQUIRE_CLOSE(sigCh2.getTime(), 15.3, epsilon);
}

BOOST_AUTO_TEST_CASE(setters_Test)
{
  JPetSigCh sigCh;
  sigCh.setRecoFlag(JPetSigCh::Corrupted);
  sigCh.setType(JPetSigCh::Trailing);
  sigCh.setTime(14.222);
  JPetChannel channel(1, 2, 30.0);
  sigCh.setChannel(channel);
  BOOST_REQUIRE_EQUAL(sigCh.getRecoFlag(), JPetSigCh::Corrupted);
  BOOST_REQUIRE_EQUAL(sigCh.getType(), JPetSigCh::Trailing);
  BOOST_REQUIRE_CLOSE(sigCh.getTime(), 14.222, epsilon);
  BOOST_REQUIRE_EQUAL(sigCh.getChannel().getID(), 1);
  BOOST_REQUIRE_EQUAL(sigCh.getChannel().getThresholdNumber(), 2);
  BOOST_REQUIRE_CLOSE(sigCh.getChannel().getThresholdValue(), 30.0, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

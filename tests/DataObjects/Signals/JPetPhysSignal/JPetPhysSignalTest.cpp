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
 *  @file JPetPhysSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPhysSignalTest

#include "Signals/JPetPhysSignal/JPetPhysSignal.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE()

double epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(constructor_test)
{
  JPetPhysSignal signal;
  BOOST_REQUIRE_CLOSE(signal.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(signal.getQualityOfTime(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(signal.getPhe(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(signal.getQualityOfPhe(), 0.0, epsilon);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetRecoSignal::Unknown);
}

BOOST_AUTO_TEST_CASE(set_get_test)
{
  JPetPhysSignal signal;
  signal.setTime(11.0);
  signal.setQualityOfTime(1.0);
  signal.setPhe(22.0);
  signal.setQualityOfPhe(2.0);
  signal.setRecoFlag(JPetRecoSignal::Good);
  BOOST_REQUIRE_CLOSE(signal.getTime(), 11.0, epsilon);
  BOOST_REQUIRE_CLOSE(signal.getQualityOfTime(), 1.0, epsilon);
  BOOST_REQUIRE_CLOSE(signal.getPhe(), 22.0, epsilon);
  BOOST_REQUIRE_CLOSE(signal.getQualityOfPhe(), 2.0, epsilon);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetRecoSignal::Good);
}

BOOST_AUTO_TEST_SUITE_END()

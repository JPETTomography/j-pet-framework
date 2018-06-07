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

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(first)
{
  JPetSigCh test;
  BOOST_REQUIRE_EQUAL(test.getValue(), JPetSigCh::kUnset);
  BOOST_REQUIRE_EQUAL(test.getType(), JPetSigCh::Leading);
  BOOST_REQUIRE_EQUAL(test.getThreshold(), JPetSigCh::kUnset);
}

BOOST_AUTO_TEST_CASE(second)
{
  float epsilon = 0.001;
  JPetSigCh test;
  JPetPM pm_test;
  JPetFEB feb_test(43, true, "", "", 1, 1, 8, 1);
  JPetTRB trb_test;
  JPetTOMBChannel tomb_test(12);
  float thr_test = 210.043;
  float time_test = 1.2345;
  test.setPM(pm_test);
  test.setTRB(trb_test);
  test.setFEB(feb_test);
  test.setTOMBChannel(tomb_test);
  test.setThreshold(thr_test);
  test.setType(JPetSigCh::Leading);
  test.setValue(time_test);
  BOOST_REQUIRE_CLOSE(test.getValue(), time_test, epsilon);
  BOOST_REQUIRE_EQUAL(test.getType(), JPetSigCh::Leading);
  BOOST_REQUIRE_EQUAL(test.getChannel(), 12);
  JPetSigCh test2(test);
  BOOST_REQUIRE_EQUAL(test.getPM().getID(), test2.getPM().getID());
  BOOST_REQUIRE_EQUAL(test.getTRB().getID(), test2.getTRB().getID());
  BOOST_REQUIRE_EQUAL(test.getFEB().getID(), test2.getFEB().getID());
  BOOST_REQUIRE_EQUAL(test.getType(), test2.getType());
  BOOST_REQUIRE_CLOSE(test.getValue(), test2.getValue(), epsilon);
  BOOST_REQUIRE_CLOSE(test.getThreshold(), test2.getThreshold(), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

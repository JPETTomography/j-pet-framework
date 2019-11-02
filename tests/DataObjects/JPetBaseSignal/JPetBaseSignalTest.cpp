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
 *  @file JPetBaseSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetBaseSignalTest

#include "JPetBaseSignal/JPetBaseSignal.h"
#include <boost/test/unit_test.hpp>
#include "JPetSlot/JPetSlot.h"
#include "JPetPM/JPetPM.h"

BOOST_AUTO_TEST_SUITE(BaseSignalTest)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetBaseSignal signal;
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetBaseSignal::Unknown);
}

BOOST_AUTO_TEST_CASE(recoFlagSetterTest)
{
  JPetBaseSignal signal;
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetBaseSignal::Unknown);
  signal.setRecoFlag(JPetBaseSignal::Good);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetBaseSignal::Good);
  signal.setRecoFlag(JPetBaseSignal::Corrupted);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetBaseSignal::Corrupted);
}

BOOST_AUTO_TEST_CASE(PM_Test)
{
  JPetBaseSignal signal;
  JPetPM pm(1, JPetPM::SideB, "nice", 1);
  signal.setPM(pm);
  BOOST_REQUIRE_EQUAL(signal.getPM().getID(), 1);
  BOOST_REQUIRE_EQUAL(signal.getPM().getSide(), JPetPM::SideB);
  BOOST_REQUIRE_EQUAL(signal.getPM().getDesc(), "nice");
  BOOST_REQUIRE_EQUAL(signal.getPM().getMatrixPosition(), 1);
}

BOOST_AUTO_TEST_SUITE_END()

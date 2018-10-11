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
 *  @file JPetBaseSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetBaseSignalTest

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetBaseSignal/JPetBaseSignal.h"
#include <boost/test/unit_test.hpp>
#include "./JPetPM/JPetPM.h"

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

BOOST_AUTO_TEST_CASE(SetAndGetTRefPMObjectTest)
{
  JPetBaseSignal signal;
  JPetPM pm;
  signal.setPM(pm);
  BOOST_CHECK(signal.getPM().getSide() == JPetPM::SideA);
}

BOOST_AUTO_TEST_CASE(SetAndGetTRefBarrelSlotObjectTest)
{
  JPetBaseSignal signal;
  JPetBarrelSlot barrelSlot(2, true, "bs2", 30., 2);
  signal.setBarrelSlot(barrelSlot);
  BOOST_CHECK(signal.getBarrelSlot().getID() == 2);
}

BOOST_AUTO_TEST_SUITE_END()

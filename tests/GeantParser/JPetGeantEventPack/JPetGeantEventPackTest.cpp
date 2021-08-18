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
 *  @file JPetGeantEventPackTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGeantEventPackTest

#include "JPetGeantEventPack/JPetGeantEventPack.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetGeantEventPack pack;
  BOOST_REQUIRE_EQUAL(pack.getNumberOfHits(), 0);
  BOOST_REQUIRE_EQUAL(pack.getNumberOfDecayTrees(), 0);
  BOOST_REQUIRE_EQUAL(pack.getEventNumber(), 0);
}

BOOST_AUTO_TEST_CASE(setter)
{
  JPetGeantEventPack pack;
  int evtNr = 944;

  pack.setEventNumber(evtNr);
  BOOST_REQUIRE_EQUAL(pack.getEventNumber(), evtNr);
}

BOOST_AUTO_TEST_CASE(fillingStructues)
{
  JPetGeantEventPack pack;
  pack.constructNextHit();
  BOOST_REQUIRE_EQUAL(pack.getNumberOfHits(), 1);

  pack.constructNextDecayTree();
  BOOST_REQUIRE_EQUAL(pack.getNumberOfDecayTrees(), 1);

  pack.Clear();

  BOOST_REQUIRE_EQUAL(pack.getNumberOfHits(), 0);
  BOOST_REQUIRE_EQUAL(pack.getNumberOfDecayTrees(), 0);
  BOOST_REQUIRE_EQUAL(pack.getEventNumber(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

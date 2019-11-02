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
 *  @file JPetSetupTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSetupTest

#include "./JPetSetup/JPetSetupFactory.h"
#include <boost/test/unit_test.hpp>
#include "./JPetSetup/JPetSetup.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetSetup setup;
  BOOST_REQUIRE_EQUAL(setup.getID(), -1);
  BOOST_REQUIRE(setup.getDescription().empty());
}

BOOST_AUTO_TEST_CASE(second_constructor)
{
  JPetSetup setup(1, "space jpet");
  BOOST_REQUIRE_EQUAL(setup.getID(), 1);
  BOOST_REQUIRE(setup.getDescription() == "space jpet");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter: public JPetParamGetter {
  ParamObjectsDescriptions getAllBasicData(
    ParamObjectType, const int runID) {
    ParamObjectsDescriptions result;
    switch (runID) {
      // No setups
      case 0:
        break;
      // Single object
      case 1:
        result = { { 1, { {"id", "1" }, {"description", "jpet"} } } };
        break;
      // Two objects
      case 2:
        result = {
          { 1, { {"id", "1" }, {"description", "jpet"} } },
          { 5, { {"id", "5" }, {"description", "ipet"} } }
        };
        break;
      // Missing field
      case 3:
        result = { { 1, { {"id", "1" } } } };
        break;
      // Wrong field
      case 4:
        result = { { 1, { {"id", "first" }, {"description", "J-LAB"} } } };
        break;
    }
    return result;
  }
  // Irrelevant for this test
  ParamRelationalData getAllRelationalData(
    ParamObjectType, ParamObjectType, const int
  ) { return ParamRelationalData(); }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE(no_setups)
{
  JPetSetupFactory factory(paramGetter, 0);
  auto& setups = factory.getSetups();
  BOOST_REQUIRE_EQUAL(setups.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetSetupFactory factory(paramGetter, 1);
  auto & setups = factory.getSetups();
  BOOST_REQUIRE_EQUAL(setups.size(), 1u);
  auto setup = setups[1];
  BOOST_REQUIRE_EQUAL(setup->getID(), 1);
  BOOST_REQUIRE(setup->getDescription() == "jpet");
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetSetupFactory factory(paramGetter, 2);
  auto & setups = factory.getSetups();
  BOOST_REQUIRE_EQUAL(setups.size(), 2u);
  auto setup = setups[1];
  BOOST_REQUIRE_EQUAL(setup->getID(), 1);
  BOOST_REQUIRE(setup->getDescription() == "jpet");
  setup = setups[5];
  BOOST_REQUIRE_EQUAL(setup->getID(), 5);
  BOOST_REQUIRE(setup->getDescription() == "ipet");
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetSetupFactory factory(paramGetter, 3);
  BOOST_REQUIRE_THROW(factory.getSetups(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetSetupFactory factory(paramGetter, 4);
  BOOST_REQUIRE_THROW(factory.getSetups(), std::bad_cast);
}

BOOST_AUTO_TEST_SUITE_END()

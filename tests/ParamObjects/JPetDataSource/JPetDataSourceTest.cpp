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
 *  @file JPetDataSourceTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetDataSourceTest

#include "JPetDataSource/JPetDataSourceFactory.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetDataSource dataSource;
  BOOST_REQUIRE_EQUAL(dataSource.getID(), -1);
  BOOST_REQUIRE_EQUAL(dataSource.getType(), "");
  BOOST_REQUIRE_EQUAL(dataSource.getTBRNetAddress(), 0);
  BOOST_REQUIRE_EQUAL(dataSource.getHubAddress(), 0);
  BOOST_REQUIRE_EQUAL(dataSource.isNullObject(), true);
}

BOOST_AUTO_TEST_CASE(first_constructor)
{
  JPetDataSource dataSource(123, "test_type", 32880, 32880);
  BOOST_REQUIRE_EQUAL(dataSource.getID(), 123);
  BOOST_REQUIRE_EQUAL(dataSource.getType(), "test_type");
  BOOST_REQUIRE_EQUAL(dataSource.getTBRNetAddress(), 32880);
  BOOST_REQUIRE_EQUAL(dataSource.getHubAddress(), 32880);
  BOOST_REQUIRE_EQUAL(dataSource.isNullObject(), false);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter : public JPetParamGetter
{
  ParamObjectsDescriptions getAllBasicData(ParamObjectType, const int runID)
  {
    ParamObjectsDescriptions result;
    switch (runID)
    {
    // No setups
    case 0:
      break;
    // Single object
    case 1:
      result = {{1, {{"id", "1"}, {"type", "TRB3_S"}, {"trbnet_address", "8040"}, {"hub_address", "8040"}}}};
      break;
    // Two objects
    case 2:
      result = {{1, {{"id", "1"}, {"type", "TRB3_S"}, {"trbnet_address", "8040"}, {"hub_address", "8040"}}},
                {5, {{"id", "5"}, {"type", "TRB3_M"}, {"trbnet_address", "8090"}, {"hub_address", "8090"}}}};
      break;
    // Missing field
    case 3:
      result = {{1, {{"id", "1"}, {"type", "TRB3_S"}, {"hub_address", "8040"}}}};
      break;
    // Wrong field
    case 4:
      result = {{1, {{"id", "one"}, {"type", "TRB3_S"}, {"trbnet_address", "8040"}, {"hub_address", "8040"}}}};
      break;
    }
    return result;
  }
  // Irrelevant for this test
  ParamRelationalData getAllRelationalData(ParamObjectType, ParamObjectType, const int) { return ParamRelationalData(); }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE(no_data_sources)
{
  JPetDataSourceFactory factory(paramGetter, 0);
  auto& dataSources = factory.getDataSources();
  BOOST_REQUIRE_EQUAL(dataSources.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetDataSourceFactory factory(paramGetter, 1);
  auto& dataSources = factory.getDataSources();
  BOOST_REQUIRE_EQUAL(dataSources.size(), 1u);
  auto dataSource = dataSources[1];
  BOOST_REQUIRE_EQUAL(dataSource->getID(), 1);
  BOOST_REQUIRE_EQUAL(dataSource->getType(), "TRB3_S");
  BOOST_REQUIRE_EQUAL(dataSource->getTBRNetAddress(), 32832);
  BOOST_REQUIRE_EQUAL(dataSource->getHubAddress(), 32832);
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetDataSourceFactory factory(paramGetter, 2);
  auto& dataSources = factory.getDataSources();
  BOOST_REQUIRE_EQUAL(dataSources.size(), 2u);
  auto dataSource = dataSources[1];
  BOOST_REQUIRE_EQUAL(dataSource->getID(), 1);
  BOOST_REQUIRE_EQUAL(dataSource->getType(), "TRB3_S");
  BOOST_REQUIRE_EQUAL(dataSource->getTBRNetAddress(), 32832);
  BOOST_REQUIRE_EQUAL(dataSource->getHubAddress(), 32832);
  dataSource = dataSources[5];
  BOOST_REQUIRE_EQUAL(dataSource->getID(), 5);
  BOOST_REQUIRE_EQUAL(dataSource->getType(), "TRB3_M");
  BOOST_REQUIRE_EQUAL(dataSource->getTBRNetAddress(), 32912);
  BOOST_REQUIRE_EQUAL(dataSource->getHubAddress(), 32912);
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetDataSourceFactory factory(paramGetter, 3);
  BOOST_REQUIRE_THROW(factory.getDataSources(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetDataSourceFactory factory(paramGetter, 4);
  BOOST_REQUIRE_THROW(factory.getDataSources(), std::bad_cast);
}

BOOST_AUTO_TEST_SUITE_END()

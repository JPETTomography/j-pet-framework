/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetDataModuleTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetDataModuleTest

#include "JPetDataModule/JPetDataModuleFactory.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetDataModule module;
  BOOST_REQUIRE_EQUAL(module.getID(), -1);
  BOOST_REQUIRE_EQUAL(module.getType(), "");
  BOOST_REQUIRE_EQUAL(module.getTBRNetAddress(), 0);
  BOOST_REQUIRE_EQUAL(module.getChannelsNumber(), -1);
  BOOST_REQUIRE_EQUAL(module.getChannelsOffset(), -1);
  BOOST_REQUIRE_EQUAL(module.isNullObject(), true);
}

BOOST_AUTO_TEST_CASE(first_constructor)
{
  JPetDataModule module(123, "test_type", 57412, 456, 789);
  BOOST_REQUIRE_EQUAL(module.getID(), 123);
  BOOST_REQUIRE_EQUAL(module.getType(), "test_type");
  BOOST_REQUIRE_EQUAL(module.getTBRNetAddress(), 57412);
  BOOST_REQUIRE_EQUAL(module.getChannelsNumber(), 456);
  BOOST_REQUIRE_EQUAL(module.getChannelsOffset(), 789);
  BOOST_REQUIRE_EQUAL(module.isNullObject(), false);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter : public JPetParamGetter
{
  ParamObjectsDescriptions getAllBasicData(ParamObjectType type, const int runID)
  {
    ParamObjectsDescriptions result;
    switch (type)
    {
    case ParamObjectType::kDataModule:
      switch (runID)
      {
      // No layers
      case 0:
        break;
      // Single object
      case 1:
        result = {{1,
                   {{"id", "1"},
                    {"type", "LATTICE_TDC"},
                    {"trbnet_address", "e044"},
                    {"channels_number", "65"},
                    {"channels_offset", "2080"},
                    {"data_source_id", "1"}}}};
        break;
      // Two objects
      case 2:
        result = {{1,
                   {{"id", "1"},
                    {"type", "LATTE_TDC"},
                    {"trbnet_address", "e044"},
                    {"channels_number", "66"},
                    {"channels_offset", "1000"},
                    {"data_source_id", "1"}}},
                  {5,
                   {{"id", "5"},
                    {"type", "ICE_TDC"},
                    {"trbnet_address", "e051"},
                    {"channels_number", "77"},
                    {"channels_offset", "2000"},
                    {"data_source_id", "1"}}}};
        break;
      // Missing field
      case 3:
        result = {{1, {{"id", "1"}, {"type", "LATTICE_TDC"}, {"trbnet_address", "e044"}, {"channels_number", "65"}, {"data_source_id", "1"}}}};
        break;
      // Wrong field
      case 4:
        result = {{1,
                   {{"id", "1"},
                    {"type", "LATTICE_TDC"},
                    {"trbnet_address", "e044"},
                    {"channels_number", "wrong"},
                    {"channels_offset", "2080"},
                    {"data_source_id", "1"}}}};
        break;
      // Wrong relation
      case 5:
        result = {{1,
                   {{"id", "1"},
                    {"type", "LATTICE_TDC"},
                    {"trbnet_address", "e044"},
                    {"channels_number", "65"},
                    {"channels_offset", "2080"},
                    {"data_source_id", "14"}}}};
        break;
      default:
        break;
      }
      break;
    case ParamObjectType::kDataSource:
      result = {{1, {{"id", "1"}, {"type", "TRB3_S"}, {"trbnet_address", "8040"}, {"hub_address", "8040"}}}};
      break;
    default:
      break;
    }
    return result;
  }

  ParamRelationalData getAllRelationalData(ParamObjectType, ParamObjectType, const int runID)
  {
    ParamRelationalData result;
    switch (runID)
    {
    // No relations
    case 0:
      break;
    // Single object
    case 1:
      result = {{1, 1}};
      break;
    // Two objects
    case 2:
      result = {{1, 1}, {5, 1}};
      break;
    // Wrong relation
    case 5:
      result = {{1, 14}};
      break;
    }
    return result;
  }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE(no_data_modules)
{
  JPetDataSourceFactory setupFactory(paramGetter, 0);
  JPetDataModuleFactory factory(paramGetter, 0, setupFactory);
  auto& dataModules = factory.getDataModules();
  BOOST_REQUIRE_EQUAL(dataModules.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetDataSourceFactory setupFactory(paramGetter, 1);
  JPetDataModuleFactory factory(paramGetter, 1, setupFactory);
  auto& dataModules = factory.getDataModules();
  BOOST_REQUIRE_EQUAL(dataModules.size(), 1u);
  auto dataModule = dataModules[1];
  BOOST_REQUIRE_EQUAL(dataModule->getID(), 1);
  BOOST_REQUIRE_EQUAL(dataModule->getType(), "LATTICE_TDC");
  BOOST_REQUIRE_EQUAL(dataModule->getTBRNetAddress(), 57412);
  BOOST_REQUIRE_EQUAL(dataModule->getChannelsNumber(), 65);
  BOOST_REQUIRE_EQUAL(dataModule->getChannelsOffset(), 2080);
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetDataSourceFactory setupFactory(paramGetter, 2);
  JPetDataModuleFactory factory(paramGetter, 2, setupFactory);
  auto& dataModules = factory.getDataModules();
  BOOST_REQUIRE_EQUAL(dataModules.size(), 2u);
  auto dataModule = dataModules[1];
  BOOST_REQUIRE_EQUAL(dataModule->getID(), 1);
  BOOST_REQUIRE_EQUAL(dataModule->getType(), "LATTE_TDC");
  BOOST_REQUIRE_EQUAL(dataModule->getTBRNetAddress(), 57412);
  BOOST_REQUIRE_EQUAL(dataModule->getChannelsNumber(), 66);
  BOOST_REQUIRE_EQUAL(dataModule->getChannelsOffset(), 1000);
  dataModule = dataModules[5];
  BOOST_REQUIRE_EQUAL(dataModule->getID(), 5);
  BOOST_REQUIRE_EQUAL(dataModule->getType(), "ICE_TDC");
  BOOST_REQUIRE_EQUAL(dataModule->getTBRNetAddress(), 57425);
  BOOST_REQUIRE_EQUAL(dataModule->getChannelsNumber(), 77);
  BOOST_REQUIRE_EQUAL(dataModule->getChannelsOffset(), 2000);
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetDataSourceFactory setupFactory(paramGetter, 3);
  JPetDataModuleFactory factory(paramGetter, 3, setupFactory);
  BOOST_REQUIRE_THROW(factory.getDataModules(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetDataSourceFactory setupFactory(paramGetter, 4);
  JPetDataModuleFactory factory(paramGetter, 4, setupFactory);
  BOOST_REQUIRE_THROW(factory.getDataModules(), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(wrong_relation)
{
  JPetDataSourceFactory setupFactory(paramGetter, 5);
  JPetDataModuleFactory factory(paramGetter, 5, setupFactory);
  BOOST_REQUIRE_THROW(factory.getDataModules(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

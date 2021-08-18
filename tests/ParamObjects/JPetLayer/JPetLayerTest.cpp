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
 *  @file JPetLayerTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetLayerTest

#include "JPetLayer/JPetLayerFactory.h"
#include <boost/test/unit_test.hpp>

double epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE(LayerTestSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetLayer layer;
  BOOST_REQUIRE_EQUAL(layer.getID(), -1);
  BOOST_REQUIRE(layer.getName().empty());
  BOOST_REQUIRE_CLOSE(layer.getRadius(), -1.0, epsilon);
}

BOOST_AUTO_TEST_CASE(second_constructor)
{
  JPetLayer layer(1, "sorbet", 10.5);
  BOOST_REQUIRE_EQUAL(layer.getID(), 1);
  BOOST_REQUIRE_EQUAL(layer.getName(), "sorbet");
  BOOST_REQUIRE_CLOSE(layer.getRadius(), 10.5, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(LayerFactorySuite)

class TestParamGetter : public JPetParamGetter
{

  ParamObjectsDescriptions getAllBasicData(ParamObjectType type, const int runID)
  {
    ParamObjectsDescriptions result;
    switch (type)
    {
    case ParamObjectType::kLayer:
      switch (runID)
      {
      // No layers
      case 0:
        break;
      // Single object
      case 1:
        result = {{1, {{"id", "1"}, {"name", "sorbet"}, {"radius", "10.5"}, {"setup_id", "1"}}}};
        break;
      // Two objects
      case 2:
        result = {{1, {{"id", "1"}, {"name", "sorbet"}, {"radius", "10.5"}, {"setup_id", "1"}}},
                  {5, {{"id", "5"}, {"name", "frosting"}, {"radius", "15.5"}, {"setup_id", "1"}}}};
        break;
      // Missing field
      case 3:
        result = {{1, {{"id", "1"}, {"name", "sorbet"}, {"setup_id", "1"}}}};
        break;
      // Wrong field
      case 4:
        result = {{1, {{"id", "1"}, {"name", "sorbet"}, {"radius", "ice cream"}, {"setup_id", "1"}}}};
        break;
      // Wrong relation
      case 5:
        result = {{1, {{"id", "1"}, {"name", "sorbet"}, {"radius", "10.5"}, {"setup_id", "4"}}}};
        break;
      default:
        break;
      }
      break;
    case ParamObjectType::kSetup:
      result = {{1, {{"id", "1"}, {"description", "jpet"}}}};
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
      result = {{1, 43}};
      break;
    }
    return result;
  }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE(no_layers)
{
  JPetSetupFactory setupFactory(paramGetter, 0);
  JPetLayerFactory factory(paramGetter, 0, setupFactory);
  auto& layers = factory.getLayers();
  BOOST_REQUIRE_EQUAL(layers.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetSetupFactory setupFactory(paramGetter, 1);
  JPetLayerFactory factory(paramGetter, 1, setupFactory);
  auto& layers = factory.getLayers();
  BOOST_REQUIRE_EQUAL(layers.size(), 1u);
  auto layer = layers[1];
  BOOST_REQUIRE_EQUAL(layer->getID(), 1);
  BOOST_REQUIRE(layer->getName() == "sorbet");
  BOOST_REQUIRE_CLOSE(layer->getRadius(), 10.5, epsilon);
  BOOST_REQUIRE_EQUAL(layer->getSetup().getID(), setupFactory.getSetups().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetSetupFactory setupFactory(paramGetter, 2);
  JPetLayerFactory factory(paramGetter, 2, setupFactory);
  auto& layers = factory.getLayers();
  BOOST_REQUIRE_EQUAL(layers.size(), 2u);
  auto layer = layers[1];
  BOOST_REQUIRE_EQUAL(layer->getID(), 1);
  BOOST_REQUIRE(layer->getName() == "sorbet");
  BOOST_REQUIRE_CLOSE(layer->getRadius(), 10.5, epsilon);
  BOOST_REQUIRE_EQUAL(layer->getSetup().getID(), setupFactory.getSetups().at(1)->getID());
  layer = layers[5];
  BOOST_REQUIRE_EQUAL(layer->getID(), 5);
  BOOST_REQUIRE(layer->getName() == "frosting");
  BOOST_REQUIRE_CLOSE(layer->getRadius(), 15.5, epsilon);
  BOOST_REQUIRE_EQUAL(layer->getSetup().getID(), setupFactory.getSetups().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetSetupFactory setupFactory(paramGetter, 3);
  JPetLayerFactory factory(paramGetter, 3, setupFactory);
  BOOST_REQUIRE_THROW(factory.getLayers(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetSetupFactory setupFactory(paramGetter, 4);
  JPetLayerFactory factory(paramGetter, 4, setupFactory);
  BOOST_REQUIRE_THROW(factory.getLayers(), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(wrong_relation)
{
  JPetSetupFactory setupFactory(paramGetter, 5);
  JPetLayerFactory factory(paramGetter, 5, setupFactory);
  BOOST_REQUIRE_THROW(factory.getLayers(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

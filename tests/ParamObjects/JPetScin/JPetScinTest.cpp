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
 *  @file JPetScinTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetScinTest

#include "JPetScin/JPetScinFactory.h"
#include <boost/test/unit_test.hpp>

double epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE(ScinTestSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetScin scin;
  BOOST_REQUIRE_EQUAL(scin.getID(), -1);
  BOOST_REQUIRE_CLOSE(scin.getLength(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin.getHeight(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin.getWidth(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin.getCenterX(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin.getCenterY(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin.getCenterZ(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin.getRotationX(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin.getRotationY(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin.getRotationZ(), 0.0, epsilon);
}

BOOST_AUTO_TEST_CASE(constructors)
{
  JPetScin scin1(123, 50.0, 30.5, 12.3, 0.5, -12.3, 44.4);
  BOOST_REQUIRE_EQUAL(scin1.getID(), 123);
  BOOST_REQUIRE_CLOSE(scin1.getLength(), 50.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin1.getHeight(), 30.5, epsilon);
  BOOST_REQUIRE_CLOSE(scin1.getWidth(), 12.3, epsilon);
  BOOST_REQUIRE_CLOSE(scin1.getCenterX(), 0.5, epsilon);
  BOOST_REQUIRE_CLOSE(scin1.getCenterY(), -12.3, epsilon);
  BOOST_REQUIRE_CLOSE(scin1.getCenterZ(), 44.4, epsilon);
  BOOST_REQUIRE_CLOSE(scin1.getRotationX(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin1.getRotationY(), 0.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin1.getRotationZ(), 0.0, epsilon);

  JPetScin scin2(123, 50.0, 30.5, 12.3, 0.5, -12.3, 44.4, 1.0, 23.0, 49.0);
  BOOST_REQUIRE_EQUAL(scin2.getID(), 123);
  BOOST_REQUIRE_CLOSE(scin2.getLength(), 50.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin2.getHeight(), 30.5, epsilon);
  BOOST_REQUIRE_CLOSE(scin2.getWidth(), 12.3, epsilon);
  BOOST_REQUIRE_CLOSE(scin2.getCenterX(), 0.5, epsilon);
  BOOST_REQUIRE_CLOSE(scin2.getCenterY(), -12.3, epsilon);
  BOOST_REQUIRE_CLOSE(scin2.getCenterZ(), 44.4, epsilon);
  BOOST_REQUIRE_CLOSE(scin2.getRotationX(), 1.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin2.getRotationY(), 23.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin2.getRotationZ(), 49.0, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ScinFactorySuite)

class TestParamGetter : public JPetParamGetter
{
  ParamObjectsDescriptions getAllBasicData(ParamObjectType type, const int runID)
  {
    ParamObjectsDescriptions result;
    switch (type)
    {
    case ParamObjectType::kScin:
      switch (runID)
      {
      // No scins
      case 0:
        break;
      // Single object
      case 1:
        result = {{1,
                   {{"id", "1"},
                    {"length", "50.0"},
                    {"height", "15.0"},
                    {"width", "7.0"},
                    {"xcenter", "5.0"},
                    {"ycenter", "-5.0"},
                    {"zcenter", "15.0"},
                    {"rot_x", "90.0"},
                    {"rot_y", "45.0"},
                    {"rot_z", "60.0"},
                    {"slot_id", "1"}}}};
        break;
      // Two objects
      case 2:
        result = {{1,
                   {{"id", "1"},
                    {"length", "50.0"},
                    {"height", "15.0"},
                    {"width", "7.0"},
                    {"xcenter", "5.0"},
                    {"ycenter", "-5.0"},
                    {"zcenter", "15.0"},
                    {"rot_x", "90.0"},
                    {"rot_y", "45.0"},
                    {"rot_z", "60.0"},
                    {"slot_id", "1"}}},
                  {5,
                   {{"id", "5"},
                    {"length", "150.0"},
                    {"height", "115.0"},
                    {"width", "17.0"},
                    {"xcenter", "15.0"},
                    {"ycenter", "-15.0"},
                    {"zcenter", "115.0"},
                    {"rot_x", "190.0"},
                    {"rot_y", "145.0"},
                    {"rot_z", "160.0"},
                    {"slot_id", "1"}}}};
        break;
      // Missing field
      case 3:
        result = {
            {1, {{"id", "1"}, {"length", "50.0"}, {"height", "15.0"}, {"width", "7.0"}, {"xcenter", "5.0"}, {"zcenter", "15.0"}, {"slot_id", "1"}}}};
        break;
      // Wrong field
      case 4:
        result = {{1,
                   {{"id", "1"},
                    {"length", "50.0"},
                    {"height", "15.0"},
                    {"width", "big"},
                    {"xcenter", "5.0"},
                    {"ycenter", "-5.0"},
                    {"zcenter", "15.0"},
                    {"rot_x", "90.0"},
                    {"rot_y", "45.0"},
                    {"rot_z", "60.0"},
                    {"slot_id", "1"}}}};
        break;
      // Wrong relation
      case 5:
        result = {{1,
                   {{"id", "1"},
                    {"length", "50.0"},
                    {"height", "15.0"},
                    {"width", "7.0"},
                    {"xcenter", "5.0"},
                    {"ycenter", "-5.0"},
                    {"zcenter", "15.0"},
                    {"rot_x", "90.0"},
                    {"rot_y", "45.0"},
                    {"rot_z", "60.0"},
                    {"slot_id", "123"}}}};
        break;
      }
      break;
    case ParamObjectType::kSlot:
      result = {{1, {{"id", "1"}, {"theta", "5.5"}, {"type", "module"}, {"layer_id", "1"}}}};
      break;
    case ParamObjectType::kLayer:
      result = {{1, {{"id", "1"}, {"name", "sorbet"}, {"radius", "10.5"}, {"setup_id", "1"}}}};
      break;
    case ParamObjectType::kSetup:
      result = {{1, {{"id", "1"}, {"description", "jpet"}}}};
      break;
    default:
      break;
    }
    return result;
  }

  ParamRelationalData getAllRelationalData(ParamObjectType type1, ParamObjectType, const int runID)
  {
    ParamRelationalData result;
    switch (type1)
    {
    case ParamObjectType::kScin:
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
        result = {{1, 57}};
        break;
      }
      break;
    default:
      result = {{1, 1}};
      break;
    }
    return result;
  }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE(no_scins)
{
  JPetSetupFactory setupFactory(paramGetter, 0);
  JPetLayerFactory layerFactory(paramGetter, 0, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 0, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 0, slotFactory);
  auto& scins = scinFactory.getScins();
  BOOST_REQUIRE_EQUAL(scins.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetSetupFactory setupFactory(paramGetter, 1);
  JPetLayerFactory layerFactory(paramGetter, 1, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 1, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 1, slotFactory);
  auto& scins = scinFactory.getScins();
  BOOST_REQUIRE_EQUAL(scins.size(), 1);
  auto scin = scins[1];
  BOOST_REQUIRE_EQUAL(scin->getID(), 1);
  BOOST_REQUIRE_CLOSE(scin->getLength(), 50.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getHeight(), 15.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getWidth(), 7.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getCenterX(), 5.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getCenterY(), -5.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getCenterZ(), 15.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getRotationX(), 90.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getRotationY(), 45.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getRotationZ(), 60.0, epsilon);
  BOOST_REQUIRE_EQUAL(scin->getSlot().getID(), slotFactory.getSlots().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetSetupFactory setupFactory(paramGetter, 2);
  JPetLayerFactory layerFactory(paramGetter, 2, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 2, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 2, slotFactory);
  auto& scins = scinFactory.getScins();
  BOOST_REQUIRE_EQUAL(scins.size(), 2u);
  auto scin = scins[1];
  BOOST_REQUIRE_EQUAL(scin->getID(), 1);
  BOOST_REQUIRE_CLOSE(scin->getLength(), 50.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getHeight(), 15.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getWidth(), 7.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getCenterX(), 5.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getCenterY(), -5.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getCenterZ(), 15.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getRotationX(), 90.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getRotationY(), 45.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getRotationZ(), 60.0, epsilon);
  BOOST_REQUIRE_EQUAL(scin->getSlot().getID(), slotFactory.getSlots().at(1)->getID());
  scin = scins[5];
  BOOST_REQUIRE_EQUAL(scin->getID(), 5);
  BOOST_REQUIRE_CLOSE(scin->getLength(), 150.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getHeight(), 115.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getWidth(), 17.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getCenterX(), 15.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getCenterY(), -15.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getCenterZ(), 115.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getRotationX(), 190.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getRotationY(), 145.0, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getRotationZ(), 160.0, epsilon);
  BOOST_REQUIRE_EQUAL(scin->getSlot().getID(), slotFactory.getSlots().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetSetupFactory setupFactory(paramGetter, 3);
  JPetLayerFactory layerFactory(paramGetter, 3, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 3, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 3, slotFactory);
  BOOST_REQUIRE_THROW(scinFactory.getScins(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetSetupFactory setupFactory(paramGetter, 4);
  JPetLayerFactory layerFactory(paramGetter, 4, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 4, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 4, slotFactory);
  BOOST_REQUIRE_THROW(scinFactory.getScins(), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(wrong_relation)
{
  JPetSetupFactory setupFactory(paramGetter, 5);
  JPetLayerFactory layerFactory(paramGetter, 5, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 5, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 5, slotFactory);
  BOOST_REQUIRE_THROW(scinFactory.getScins(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

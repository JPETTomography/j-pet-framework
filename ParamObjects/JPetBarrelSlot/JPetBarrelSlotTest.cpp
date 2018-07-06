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
 *  @file JPetBarrelSlotTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetBarrelSlotTest

#include <boost/test/unit_test.hpp>
#include "JPetBarrelSlotFactory.h"
#include "JPetBarrelSlot.h"

const float epsilon = 0.0001;

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetBarrelSlot slot;
  BOOST_REQUIRE_EQUAL(slot.getID(), -1);
  BOOST_REQUIRE_CLOSE(slot.getTheta(), -1., epsilon);
  BOOST_REQUIRE(!slot.isActive());
  BOOST_REQUIRE(slot.getName().empty());
  BOOST_REQUIRE(slot.getInFrameID() == -1);
  BOOST_REQUIRE(!slot.hasLayer());
}

BOOST_AUTO_TEST_CASE(constructor)
{
  JPetBarrelSlot slot(1, true, "pepe", 5.5, 6);
  BOOST_REQUIRE_EQUAL(slot.getID(), 1);
  BOOST_REQUIRE_CLOSE(slot.getTheta(), 5.5, epsilon);
  BOOST_REQUIRE(slot.isActive());
  BOOST_REQUIRE(slot.getName() == "pepe");
  BOOST_REQUIRE(slot.getInFrameID() == 6);
  BOOST_REQUIRE(!slot.hasLayer());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter: public JPetParamGetter {
  ParamObjectsDescriptions getAllBasicData(ParamObjectType type,
    const int runId) {
    ParamObjectsDescriptions result;
    switch (type) {
    case ParamObjectType::kBarrelSlot:
      switch (runId) {
      case 0:
        break;
      case 1:
      case 5:
        result = {
          {
            1,
            {
              {
                "id",
                "1"
              },
              {
                "active",
                "1"
              },
              {
                "name",
                "pepe"
              },
              {
                "theta1",
                "5.5"
              },
              {
                "frame_id",
                "6"
              }
            }
          }
        };
        break;
      case 2:
        result = {
          {
            1,
            {
              {
                "id",
                "1"
              },
              {
                "active",
                "1"
              },
              {
                "name",
                "pepe"
              },
              {
                "theta1",
                "5.5"
              },
              {
                "frame_id",
                "6"
              }
            }
          },
          {
            5,
            {
              {
                "id",
                "5"
              },
              {
                "active",
                "0"
              },
              {
                "name",
                "smoothface"
              },
              {
                "theta1",
                "6.5"
              },
              {
                "frame_id",
                "7"
              }
            }
          }
        };
        break;
      case 3:
        result = {
          {
            1,
            {
              {
                "id",
                "1"
              },
              {
                "active",
                "1"
              },
              {
                "theta1",
                "5.5"
              },
              {
                "frame_id",
                "6"
              }
            }
          }
        };
        break;
      case 4:
        result = {
          {
            1,
            {
              {
                "id",
                "1"
              },
              {
                "active",
                "probably"
              },
              {
                "name",
                "pepe"
              },
              {
                "theta1",
                "5.5"
              },
              {
                "frame_id",
                "6"
              }
            }
          }
        };
        break;
      }
      break;
    case ParamObjectType::kLayer:
      result = {
        {
          1,
          {
            {
              "id",
              "1"
            },
            {
              "active",
              "1"
            },
            {
              "name",
              "ala"
            },
            {
              "radius",
              "10.5"
            }
          }
        }
      };
      break;
    case ParamObjectType::kFrame:
      result = {
        {
          1,
          {
            {
              "id",
              "1"
            },
            {
              "active",
              "1"
            },
            {
              "status",
              "ok"
            },
            {
              "description",
              "descr1"
            },
            {
              "version",
              "2"
            },
            {
              "creator_id",
              "1"
            }
          }
        }
      };
      break;
    default:
      break;
    }
    return result;
  }

  ParamRelationalData getAllRelationalData(
    ParamObjectType type1, ParamObjectType,
    const int runId) {
    ParamRelationalData result;
    switch (type1) {
    case ParamObjectType::kBarrelSlot:
      switch (runId) {
      case 0:
        break;
      case 1:
        result = {
          {
            1,
            1
          }
        };
        break;
      case 2:
        result = {
          {
            1,
            1
          },
          {
            5,
            1
          }
        };
        break;
      case 5:
        result = {
          {
            1,
            43
          }
        };
        break;
      }
      break;
    case ParamObjectType::kLayer:
      result = {
        {
          1,
          1
        }
      };
      break;
    default:
      break;
    }
    return result;
  }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE(no_barrelSlots)
{
  JPetFrameFactory frameFactory(paramGetter, 0);
  JPetLayerFactory layerFactory(paramGetter, 0, frameFactory);
  JPetBarrelSlotFactory factory(paramGetter, 0, layerFactory);
  auto& barrelSlots = factory.getBarrelSlots();
  BOOST_REQUIRE_EQUAL(barrelSlots.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetFrameFactory frameFactory(paramGetter, 1);
  JPetLayerFactory layerFactory(paramGetter, 1, frameFactory);
  JPetBarrelSlotFactory factory(paramGetter, 1, layerFactory);
  auto &barrelSlots = factory.getBarrelSlots();
  BOOST_REQUIRE_EQUAL(barrelSlots.size(), 1u);
  auto barrelSlot = barrelSlots[1];
  BOOST_REQUIRE_EQUAL(barrelSlot->getID(), 1);
  BOOST_REQUIRE(barrelSlot->isActive());
  BOOST_REQUIRE(barrelSlot->getName() == "pepe");
  BOOST_REQUIRE_CLOSE(barrelSlot->getTheta(), 5.5, epsilon);
  BOOST_REQUIRE_EQUAL(barrelSlot->getInFrameID(), 6);
  BOOST_REQUIRE(barrelSlot->hasLayer());
  BOOST_REQUIRE_EQUAL(barrelSlot->getLayer().getID(), layerFactory.getLayers().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetFrameFactory frameFactory(paramGetter, 2);
  JPetLayerFactory layerFactory(paramGetter, 2, frameFactory);
  JPetBarrelSlotFactory factory(paramGetter, 2, layerFactory);
  auto& barrelSlots = factory.getBarrelSlots();
  BOOST_REQUIRE_EQUAL(barrelSlots.size(), 2u);
  auto barrelSlot = barrelSlots[1];
  BOOST_REQUIRE_EQUAL(barrelSlot->getID(), 1);
  BOOST_REQUIRE(barrelSlot->isActive());
  BOOST_REQUIRE(barrelSlot->getName() == "pepe");
  BOOST_REQUIRE_CLOSE(barrelSlot->getTheta(), 5.5, epsilon);
  BOOST_REQUIRE_EQUAL(barrelSlot->getInFrameID(), 6);
  BOOST_REQUIRE(barrelSlot->hasLayer());
  BOOST_REQUIRE_EQUAL(barrelSlot->getLayer().getID(), layerFactory.getLayers().at(1)->getID());
  barrelSlot = barrelSlots[5];
  BOOST_REQUIRE_EQUAL(barrelSlot->getID(), 5);
  BOOST_REQUIRE(!barrelSlot->isActive());
  BOOST_REQUIRE(barrelSlot->getName() == "smoothface");
  BOOST_REQUIRE_CLOSE(barrelSlot->getTheta(), 6.5, epsilon);
  BOOST_REQUIRE_EQUAL(barrelSlot->getInFrameID(), 7);
  BOOST_REQUIRE(barrelSlot->hasLayer());
  BOOST_REQUIRE_EQUAL(barrelSlot->getLayer().getID(), layerFactory.getLayers().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetFrameFactory frameFactory(paramGetter, 3);
  JPetLayerFactory layerFactory(paramGetter, 3, frameFactory);
  JPetBarrelSlotFactory factory(paramGetter, 3, layerFactory);
  BOOST_REQUIRE_THROW(factory.getBarrelSlots(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetFrameFactory frameFactory(paramGetter, 4);
  JPetLayerFactory layerFactory(paramGetter, 4, frameFactory);
  JPetBarrelSlotFactory factory(paramGetter, 4, layerFactory);
  BOOST_REQUIRE_THROW(factory.getBarrelSlots(), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(wrong_relation)
{
  JPetFrameFactory frameFactory(paramGetter, 5);
  JPetLayerFactory layerFactory(paramGetter, 5, frameFactory);
  JPetBarrelSlotFactory factory(paramGetter, 5, layerFactory);
  BOOST_REQUIRE_THROW(factory.getBarrelSlots(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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

#include <boost/test/unit_test.hpp>
#include "JPetLayerFactory.h"
#include "JPetLayer.h"

const double epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetLayer layer;
  BOOST_REQUIRE_EQUAL(layer.getID(), -1);
  BOOST_REQUIRE(!layer.getIsActive());
  BOOST_REQUIRE(layer.getName().empty());
  BOOST_REQUIRE_CLOSE(layer.getRadius(), -1, epsilon);
}

BOOST_AUTO_TEST_CASE(second_constructor)
{
  JPetLayer layer(1, true, "ala", 10.5);
  BOOST_REQUIRE_EQUAL(layer.getID(), 1);
  BOOST_REQUIRE(layer.getIsActive());
  BOOST_REQUIRE(layer.getName() == "ala");
  BOOST_REQUIRE_CLOSE(layer.getRadius(), 10.5, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter: public JPetParamGetter {
  ParamObjectsDescriptions getAllBasicData(ParamObjectType type,
    const int runId) {
    ParamObjectsDescriptions result;
    switch (type) {
    case ParamObjectType::kLayer:
      switch (runId) {
      case 0: //No layers
        break;
      case 1: //Simple single object
      case 5: //Wrong relation
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
      case 2: //Simple two objects
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
                "alfred"
              },
              {
                "radius",
                "11.5"
              }
            }
          }
        };
        break;
      case 3: //Object with missing field
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
                "radius",
                "10.5"
              }
            }
          }
        };
        break;
      case 4: //Object with wrong field
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
      }
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
    default: //Other cases not needed.
      break;
    }
    return result;
  }
  ParamRelationalData getAllRelationalData(ParamObjectType, ParamObjectType,
    const int runId) {
    ParamRelationalData result;
    switch (runId) {
    case 0: //No relations
      break;
    case 1: //Simple single object
      result = {
        {
          1,
          1
        }
      };
      break;
    case 2: //Simple two objects
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
    case 5: //Wrong relation
      result = {
        {
          1,
          43
        }
      };
      break;
    }
    return result;
  }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE(no_layers)
{
  JPetFrameFactory frameFactory(paramGetter, 0);
  JPetLayerFactory factory(paramGetter, 0, frameFactory);
  auto& layers = factory.getLayers();
  BOOST_REQUIRE_EQUAL(layers.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetFrameFactory frameFactory(paramGetter, 1);
  JPetLayerFactory factory(paramGetter, 1, frameFactory);
  auto& layers = factory.getLayers();
  BOOST_REQUIRE_EQUAL(layers.size(), 1u);
  auto layer = layers[1];
  BOOST_REQUIRE_EQUAL(layer->getID(), 1);
  BOOST_REQUIRE(layer->getIsActive());
  BOOST_REQUIRE(layer->getName() == "ala");
  BOOST_REQUIRE_CLOSE(layer->getRadius(), 10.5, epsilon);
  BOOST_REQUIRE_EQUAL(layer->getFrame().getID(), frameFactory.getFrames().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetFrameFactory frameFactory(paramGetter, 2);
  JPetLayerFactory factory(paramGetter, 2, frameFactory);
  auto& layers = factory.getLayers();
  BOOST_REQUIRE_EQUAL(layers.size(), 2u);
  auto layer = layers[1];
  BOOST_REQUIRE_EQUAL(layer->getID(), 1);
  BOOST_REQUIRE(layer->getIsActive());
  BOOST_REQUIRE(layer->getName() == "ala");
  BOOST_REQUIRE_CLOSE(layer->getRadius(), 10.5, epsilon);
  BOOST_REQUIRE_EQUAL(layer->getFrame().getID(), frameFactory.getFrames().at(1)->getID());
  layer = layers[5];
  BOOST_REQUIRE_EQUAL(layer->getID(), 5);
  BOOST_REQUIRE(!layer->getIsActive());
  BOOST_REQUIRE(layer->getName() == "alfred");
  BOOST_REQUIRE_CLOSE(layer->getRadius(), 11.5, epsilon);
  BOOST_REQUIRE_EQUAL(layer->getFrame().getID(), frameFactory.getFrames().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetFrameFactory frameFactory(paramGetter, 3);
  JPetLayerFactory factory(paramGetter, 3, frameFactory);
  BOOST_REQUIRE_THROW(factory.getLayers(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetFrameFactory frameFactory(paramGetter, 4);
  JPetLayerFactory factory(paramGetter, 4, frameFactory);
  BOOST_REQUIRE_THROW(factory.getLayers(), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(wrong_relation)
{
  JPetFrameFactory frameFactory(paramGetter, 5);
  JPetLayerFactory factory(paramGetter, 5, frameFactory);
  BOOST_REQUIRE_THROW(factory.getLayers(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

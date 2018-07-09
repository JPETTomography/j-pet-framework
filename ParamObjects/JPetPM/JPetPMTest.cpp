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
 *  @file JPetPMTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPMTest

#include <boost/test/unit_test.hpp>
#include "JPetPMFactory.h"
#include "JPetPM.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetPM pm;
  float epsilon = 0.0001;
  BOOST_REQUIRE_EQUAL(pm.getSide(), JPetPM::SideA);
  BOOST_REQUIRE_EQUAL(pm.getID(), 0);
  BOOST_REQUIRE_EQUAL(pm.getHVset(), 0);
  BOOST_REQUIRE_EQUAL(pm.getHVopt(), 0);
  BOOST_REQUIRE_CLOSE(pm.getHVgain(JPetPM::kFirst), 0, epsilon);
  BOOST_REQUIRE_CLOSE(pm.getHVgain(JPetPM::kSecond), 0, epsilon);
  BOOST_REQUIRE_EQUAL(pm.getDescription(), "");
  BOOST_CHECK_EQUAL(pm.isNullObject(), false);
  BOOST_REQUIRE(!pm.hasFEB());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter: public JPetParamGetter {
  ParamObjectsDescriptions getAllBasicData(ParamObjectType type,
    const int runId) {
    ParamObjectsDescriptions result;
    switch (type) {
    case ParamObjectType::kPM:
      switch (runId) {
      case 0: //No PMs
        break;
      case 1: //Simple single object
      case 5: //Wrong FEB relation
      case 6: //Wrong scin relation
      case 7: //Wrong barrel slot relation
        result = {
          {
            1,
            {
              {
                "id",
                "1"
              },
              {
                "is_right_side",
                "1"
              },
              {
                "description",
                "no writing"
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
                "is_right_side",
                "1"
              },
              {
                "description",
                "no writing"
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
                "is_right_side",
                "0"
              },
              {
                "description",
                "some writing"
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
                "description",
                "some writing"
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
                "is_right_side",
                "probably"
              },
              {
                "description",
                "some writing"
              }
            }
          }
        };
        break;
      }
      break;
    case ParamObjectType::kFEB:
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
              "healthy"
            },
            {
              "description",
              "tall"
            },
            {
              "version",
              "27"
            },
            {
              "creator_id",
              "44"
            },
            {
              "time_outputs_per_input",
              "2"
            },
            {
              "no_time_outputs_per_input",
              "3"
            }
          }
        }
      };
      break;
    case ParamObjectType::kTRB:
      result = {
        {
          1,
          {
            {
              "id",
              "1"
            },
            {
              "type",
              "1"
            },
            {
              "channel",
              "224"
            }
          }
        }
      };
      break;
    case ParamObjectType::kScintillator:
      result = {
        {
          1,
          {
            {
              "id",
              "1"
            },
            {
              "attenuation_length",
              "10.34"
            },
            {
              "length",
              "100"
            },
            {
              "width",
              "4.5"
            },
            {
              "height",
              "2.5"
            }
          }
        }
      };
      break;
    case ParamObjectType::kBarrelSlot:
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
    default: //Other cases not needed.
      break;
    }
    return result;
  }
  ParamRelationalData getAllRelationalData(ParamObjectType type1, ParamObjectType type2,
    const int runId) {
    ParamRelationalData result;
    switch (type1) {
    case ParamObjectType::kPM:
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
      case 5: //Wrong FEB relation
        switch (type2) {
        case ParamObjectType::kFEB:
          result = {
            {
              1,
              43
            }
          };
          break;
        default:
          result = {
            {
              1,
              1
            }
          };
          break;
        }
      case 6: //Wrong scin relation
        switch (type2) {
        case ParamObjectType::kScintillator:
          result = {
            {
              1,
              43
            }
          };
          break;
        default:
          result = {
            {
              1,
              1
            }
          };
          break;
        }
      case 7: //Wrong barrel slot relation
        switch (type2) {
        case ParamObjectType::kBarrelSlot:
          result = {
            {
              1,
              43
            }
          };
          break;
        default:
          result = {
            {
              1,
              1
            }
          };
          break;
        }
      }
      break;
    default:
      result = {
        {
          1,
          1
        }
      };
      break;
    }
    return result;
  }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE(no_pms)
{
  JPetTRBFactory trbFactory(paramGetter, 0);
  JPetFEBFactory febFactory(paramGetter, 0, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 0);
  JPetLayerFactory layerFactory(paramGetter, 0, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 0, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 0, barrelSlotFactory);
  JPetPMFactory factory(paramGetter, 0, febFactory, scinFactory, barrelSlotFactory);
  auto& pms = factory.getPMs();
  BOOST_REQUIRE_EQUAL(pms.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetTRBFactory trbFactory(paramGetter, 1);
  JPetFEBFactory febFactory(paramGetter, 1, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 1);
  JPetLayerFactory layerFactory(paramGetter, 1, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 1, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 1, barrelSlotFactory);
  JPetPMFactory factory(paramGetter, 1, febFactory, scinFactory, barrelSlotFactory);
  auto& pms = factory.getPMs();
  BOOST_REQUIRE_EQUAL(pms.size(), 1u);
  auto pm = pms[1];
  BOOST_REQUIRE_EQUAL(pm->getID(), 1);
  BOOST_REQUIRE_EQUAL(pm->getSide(), JPetPM::SideB);
  BOOST_REQUIRE(pm->hasFEB());
  BOOST_REQUIRE_EQUAL(pm->getFEB().getID(), febFactory.getFEBs().at(1)->getID());
  BOOST_REQUIRE_EQUAL(pm->getScin().getID(), scinFactory.getScins().at(1)->getID());
  BOOST_REQUIRE_EQUAL(pm->getBarrelSlot().getID(), barrelSlotFactory.getBarrelSlots().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetTRBFactory trbFactory(paramGetter, 2);
  JPetFEBFactory febFactory(paramGetter, 2, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 2);
  JPetLayerFactory layerFactory(paramGetter, 2, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 2, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 2, barrelSlotFactory);
  JPetPMFactory factory(paramGetter, 2, febFactory, scinFactory, barrelSlotFactory);
  auto& pms = factory.getPMs();
  BOOST_REQUIRE_EQUAL(pms.size(), 2u);
  auto pm = pms[1];
  BOOST_REQUIRE_EQUAL(pm->getID(), 1);
  BOOST_REQUIRE_EQUAL(pm->getSide(), JPetPM::SideB);
  BOOST_REQUIRE(pm->hasFEB());
  BOOST_REQUIRE_EQUAL(pm->getFEB().getID(), febFactory.getFEBs().at(1)->getID());
  BOOST_REQUIRE_EQUAL(pm->getScin().getID(), scinFactory.getScins().at(1)->getID());
  BOOST_REQUIRE_EQUAL(pm->getBarrelSlot().getID(), barrelSlotFactory.getBarrelSlots().at(1)->getID());
  pm = pms[5];
  BOOST_REQUIRE_EQUAL(pm->getID(), 5);
  BOOST_REQUIRE_EQUAL(pm->getSide(), JPetPM::SideA);
  BOOST_REQUIRE(pm->hasFEB());
  BOOST_REQUIRE_EQUAL(pm->getFEB().getID(), febFactory.getFEBs().at(1)->getID());
  BOOST_REQUIRE_EQUAL(pm->getScin().getID(), scinFactory.getScins().at(1)->getID());
  BOOST_REQUIRE_EQUAL(pm->getBarrelSlot().getID(), barrelSlotFactory.getBarrelSlots().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetTRBFactory trbFactory(paramGetter, 3);
  JPetFEBFactory febFactory(paramGetter, 3, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 3);
  JPetLayerFactory layerFactory(paramGetter, 3, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 3, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 3, barrelSlotFactory);
  JPetPMFactory factory(paramGetter, 3, febFactory, scinFactory, barrelSlotFactory);
  BOOST_REQUIRE_THROW(factory.getPMs(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetTRBFactory trbFactory(paramGetter, 4);
  JPetFEBFactory febFactory(paramGetter, 4, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 4);
  JPetLayerFactory layerFactory(paramGetter, 4, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 4, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 4, barrelSlotFactory);
  JPetPMFactory factory(paramGetter, 4, febFactory, scinFactory, barrelSlotFactory);
  BOOST_REQUIRE_THROW(factory.getPMs(), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(wrong_feb_relation)
{
  JPetTRBFactory trbFactory(paramGetter, 5);
  JPetFEBFactory febFactory(paramGetter, 5, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 5);
  JPetLayerFactory layerFactory(paramGetter, 5, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 5, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 5, barrelSlotFactory);
  JPetPMFactory factory(paramGetter, 5, febFactory, scinFactory, barrelSlotFactory);
  BOOST_REQUIRE_THROW(factory.getPMs(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_scin_relation)
{
  JPetTRBFactory trbFactory(paramGetter, 6);
  JPetFEBFactory febFactory(paramGetter, 6, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 6);
  JPetLayerFactory layerFactory(paramGetter, 6, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 6, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 6, barrelSlotFactory);
  JPetPMFactory factory(paramGetter, 6, febFactory, scinFactory, barrelSlotFactory);
  BOOST_REQUIRE_THROW(factory.getPMs(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_barrelSlot_relation)
{
  JPetTRBFactory trbFactory(paramGetter, 7);
  JPetFEBFactory febFactory(paramGetter, 7, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 7);
  JPetLayerFactory layerFactory(paramGetter, 7, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 7, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 7, barrelSlotFactory);
  JPetPMFactory factory(paramGetter, 7, febFactory, scinFactory, barrelSlotFactory);
  BOOST_REQUIRE_THROW(factory.getPMs(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

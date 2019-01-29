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
 *  @file JPetTOMBChannelTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTOMBChannelTest

#include <boost/test/unit_test.hpp>
#include "JPetTOMBChannelFactory.h"
#include "JPetTOMBChannel.h"

const float epsilon = 0.0001;

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter: public JPetParamGetter {
  ParamObjectsDescriptions getAllBasicData(ParamObjectType type,
    const int runId) {
    ParamObjectsDescriptions result;
    switch (type) {
    case ParamObjectType::kTOMBChannel:
      switch (runId) {
      case 0: //No TOMBChannels
        break;
      case 1: //Simple single object
      case 5: //Wrong FEB relation
      case 6: //Wrong TRB relation
      case 7: //Wrong PM relation
        result = {
          {
            1,
            {
              {
                "channel",
                "1"
              },
              {
                "local_number",
                "2"
              },
              {
                "FEB",
                "3"
              },
              {
                "threshold",
                "4"
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
                "channel",
                "1"
              },
              {
                "local_number",
                "2"
              },
              {
                "FEB",
                "3"
              },
              {
                "threshold",
                "4"
              }
            }
          },
          {
            5,
            {
              {
                "channel",
                "5"
              },
              {
                "local_number",
                "3"
              },
              {
                "FEB",
                "4"
              },
              {
                "threshold",
                "5"
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
                "channel",
                "1"
              },
              {
                "FEB",
                "3"
              },
              {
                "threshold",
                "4"
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
                "channel",
                "1"
              },
              {
                "local_number",
                "TVP"
              },
              {
                "FEB",
                "3"
              },
              {
                "threshold",
                "4"
              }
            }
          }
        };
        break;
      }
      break;
    case ParamObjectType::kPM:
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
    case ParamObjectType::kTOMBChannel:
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
      case 6: //Wrong TRB relation
        switch (type2) {
        case ParamObjectType::kTRB:
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
      case 7: //Wrong PM relation
        switch (type2) {
        case ParamObjectType::kPM:
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

BOOST_AUTO_TEST_CASE(no_tombChannels)
{
  JPetTRBFactory trbFactory(paramGetter, 0);
  JPetFEBFactory febFactory(paramGetter, 0, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 0);
  JPetLayerFactory layerFactory(paramGetter, 0, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 0, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 0, barrelSlotFactory);
  JPetPMFactory pmFactory(paramGetter, 0, febFactory, scinFactory, barrelSlotFactory);
  JPetTOMBChannelFactory factory(paramGetter, 0, febFactory, trbFactory, pmFactory);
  auto& tombChannels = factory.getTOMBChannels();
  BOOST_REQUIRE_EQUAL(tombChannels.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetTRBFactory trbFactory(paramGetter, 1);
  JPetFEBFactory febFactory(paramGetter, 1, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 1);
  JPetLayerFactory layerFactory(paramGetter, 1, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 1, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 1, barrelSlotFactory);
  JPetPMFactory pmFactory(paramGetter, 1, febFactory, scinFactory, barrelSlotFactory);
  JPetTOMBChannelFactory factory(paramGetter, 1, febFactory, trbFactory, pmFactory);
  auto& tombChannels = factory.getTOMBChannels();
  BOOST_REQUIRE_EQUAL(tombChannels.size(), 1u);
  auto tombChannel = tombChannels[1];
  BOOST_REQUIRE_EQUAL(tombChannel->getChannel(), 1);
  BOOST_REQUIRE_EQUAL(tombChannel->getLocalChannelNumber(), 2u);
  BOOST_REQUIRE_EQUAL(tombChannel->getFEBInputNumber(), 3u);
  BOOST_REQUIRE_CLOSE(tombChannel->getThreshold(), 4, epsilon);
  BOOST_REQUIRE_EQUAL(tombChannel->getFEB().getID(), febFactory.getFEBs().at(1)->getID());
  BOOST_REQUIRE_EQUAL(tombChannel->getTRB().getID(), trbFactory.getTRBs().at(1)->getID());
  BOOST_REQUIRE_EQUAL(tombChannel->getPM().getID(), pmFactory.getPMs().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetTRBFactory trbFactory(paramGetter, 2);
  JPetFEBFactory febFactory(paramGetter, 2, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 2);
  JPetLayerFactory layerFactory(paramGetter, 2, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 2, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 2, barrelSlotFactory);
  JPetPMFactory pmFactory(paramGetter, 2, febFactory, scinFactory, barrelSlotFactory);
  JPetTOMBChannelFactory factory(paramGetter, 2, febFactory, trbFactory, pmFactory);
  auto& tombChannels = factory.getTOMBChannels();
  BOOST_REQUIRE_EQUAL(tombChannels.size(), 2u);
  auto tombChannel = tombChannels[1];
  BOOST_REQUIRE_EQUAL(tombChannel->getChannel(), 1);
  BOOST_REQUIRE_EQUAL(tombChannel->getLocalChannelNumber(), 2u);
  BOOST_REQUIRE_EQUAL(tombChannel->getFEBInputNumber(), 3u);
  BOOST_REQUIRE_CLOSE(tombChannel->getThreshold(), 4, epsilon);
  BOOST_REQUIRE_EQUAL(tombChannel->getFEB().getID(), febFactory.getFEBs().at(1)->getID());
  BOOST_REQUIRE_EQUAL(tombChannel->getTRB().getID(), trbFactory.getTRBs().at(1)->getID());
  BOOST_REQUIRE_EQUAL(tombChannel->getPM().getID(), pmFactory.getPMs().at(1)->getID());
  tombChannel = tombChannels[5];
  BOOST_REQUIRE_EQUAL(tombChannel->getChannel(), 5);
  BOOST_REQUIRE_EQUAL(tombChannel->getLocalChannelNumber(), 3u);
  BOOST_REQUIRE_EQUAL(tombChannel->getFEBInputNumber(), 4u);
  BOOST_REQUIRE_CLOSE(tombChannel->getThreshold(), 5, epsilon);
  BOOST_REQUIRE_EQUAL(tombChannel->getFEB().getID(), febFactory.getFEBs().at(1)->getID());
  BOOST_REQUIRE_EQUAL(tombChannel->getTRB().getID(), trbFactory.getTRBs().at(1)->getID());
  BOOST_REQUIRE_EQUAL(tombChannel->getPM().getID(), pmFactory.getPMs().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetTRBFactory trbFactory(paramGetter, 3);
  JPetFEBFactory febFactory(paramGetter, 3, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 3);
  JPetLayerFactory layerFactory(paramGetter, 3, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 3, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 3, barrelSlotFactory);
  JPetPMFactory pmFactory(paramGetter, 3, febFactory, scinFactory, barrelSlotFactory);
  JPetTOMBChannelFactory factory(paramGetter, 3, febFactory, trbFactory, pmFactory);
  BOOST_REQUIRE_THROW(factory.getTOMBChannels(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetTRBFactory trbFactory(paramGetter, 4);
  JPetFEBFactory febFactory(paramGetter, 4, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 4);
  JPetLayerFactory layerFactory(paramGetter, 4, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 4, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 4, barrelSlotFactory);
  JPetPMFactory pmFactory(paramGetter, 4, febFactory, scinFactory, barrelSlotFactory);
  JPetTOMBChannelFactory factory(paramGetter, 4, febFactory, trbFactory, pmFactory);
  BOOST_REQUIRE_THROW(factory.getTOMBChannels(), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(wrong_feb_relation)
{
  JPetTRBFactory trbFactory(paramGetter, 5);
  JPetFEBFactory febFactory(paramGetter, 5, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 5);
  JPetLayerFactory layerFactory(paramGetter, 5, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 5, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 5, barrelSlotFactory);
  JPetPMFactory pmFactory(paramGetter, 5, febFactory, scinFactory, barrelSlotFactory);
  JPetTOMBChannelFactory factory(paramGetter, 5, febFactory, trbFactory, pmFactory);
  BOOST_REQUIRE_THROW(factory.getTOMBChannels(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_trb_relation)
{
  JPetTRBFactory trbFactory(paramGetter, 6);
  JPetFEBFactory febFactory(paramGetter, 6, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 6);
  JPetLayerFactory layerFactory(paramGetter, 6, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 6, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 6, barrelSlotFactory);
  JPetPMFactory pmFactory(paramGetter, 6, febFactory, scinFactory, barrelSlotFactory);
  JPetTOMBChannelFactory factory(paramGetter, 6, febFactory, trbFactory, pmFactory);
  BOOST_REQUIRE_THROW(factory.getTOMBChannels(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_pm_relation)
{
  JPetTRBFactory trbFactory(paramGetter, 7);
  JPetFEBFactory febFactory(paramGetter, 7, trbFactory);
  JPetFrameFactory frameFactory(paramGetter, 7);
  JPetLayerFactory layerFactory(paramGetter, 7, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 7, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 7, barrelSlotFactory);
  JPetPMFactory pmFactory(paramGetter, 7, febFactory, scinFactory, barrelSlotFactory);
  JPetTOMBChannelFactory factory(paramGetter, 7, febFactory, trbFactory, pmFactory);
  BOOST_REQUIRE_THROW(factory.getTOMBChannels(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

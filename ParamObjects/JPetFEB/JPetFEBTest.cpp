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
 *  @file JPetFEBTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetFEBTest

#include <boost/test/unit_test.hpp>
#include "JPetFEBFactory.h"
#include "JPetFEB.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(parametrized_constructor)
{
  JPetFEB feb(1, true, "healthy", "tall", 27, 44, 2, 3);
  BOOST_REQUIRE_EQUAL(feb.getID(), 1);
  BOOST_REQUIRE(feb.isActive());
  BOOST_REQUIRE(feb.status()=="healthy");
  BOOST_REQUIRE(feb.description()=="tall");
  BOOST_REQUIRE_EQUAL(feb.version(), 27);
  BOOST_REQUIRE_EQUAL(feb.getCreator(), 44);
  BOOST_REQUIRE_EQUAL(feb.getNtimeOutsPerInput(), 2);
  BOOST_REQUIRE_EQUAL(feb.getNnotimeOutsPerInput(), 3);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter: public JPetParamGetter {
  ParamObjectsDescriptions getAllBasicData(ParamObjectType type,
    const int runId) {
    ParamObjectsDescriptions result;
    switch (type) {
    case ParamObjectType::kFEB:
      switch (runId) {
      case 0: //No febs
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
                "status",
                "fainted"
              },
              {
                "description",
                "scrawny"
              },
              {
                "version",
                "271"
              },
              {
                "creator_id",
                "616"
              },
              {
                "time_outputs_per_input",
                "3"
              },
              {
                "no_time_outputs_per_input",
                "4"
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
                "status",
                "healthy"
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
                "status",
                "healthy"
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
      }
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

BOOST_AUTO_TEST_CASE(no_febs)
{
  JPetTRBFactory trbFactory(paramGetter, 0);
  JPetFEBFactory factory(paramGetter, 0, trbFactory);
  auto & febs = factory.getFEBs();
  BOOST_REQUIRE_EQUAL(febs.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetTRBFactory trbFactory(paramGetter, 1);
  JPetFEBFactory factory(paramGetter, 1, trbFactory);
  auto & febs = factory.getFEBs();
  BOOST_REQUIRE_EQUAL(febs.size(), 1u);
  auto feb = febs[1];
  BOOST_REQUIRE_EQUAL(feb->getID(), 1);
  BOOST_REQUIRE(feb->isActive());
  BOOST_REQUIRE(feb->status()=="healthy");
  BOOST_REQUIRE(feb->description()=="tall");
  BOOST_REQUIRE_EQUAL(feb->version(), 27);
  BOOST_REQUIRE_EQUAL(feb->getCreator(), 44);
  BOOST_REQUIRE_EQUAL(feb->getNtimeOutsPerInput(), 2);
  BOOST_REQUIRE_EQUAL(feb->getNnotimeOutsPerInput(), 3);
  BOOST_REQUIRE_EQUAL(feb->getTRB().getID(), trbFactory.getTRBs().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetTRBFactory trbFactory(paramGetter, 2);
  JPetFEBFactory factory(paramGetter, 2, trbFactory);
  auto & febs = factory.getFEBs();
  BOOST_REQUIRE_EQUAL(febs.size(), 2u);
  auto feb = febs[1];
  BOOST_REQUIRE_EQUAL(feb->getID(), 1);
  BOOST_REQUIRE(feb->isActive());
  BOOST_REQUIRE(feb->status()=="healthy");
  BOOST_REQUIRE(feb->description()=="tall");
  BOOST_REQUIRE_EQUAL(feb->version(), 27);
  BOOST_REQUIRE_EQUAL(feb->getCreator(), 44);
  BOOST_REQUIRE_EQUAL(feb->getNtimeOutsPerInput(), 2);
  BOOST_REQUIRE_EQUAL(feb->getNnotimeOutsPerInput(), 3);
  BOOST_REQUIRE_EQUAL(feb->getTRB().getID(), trbFactory.getTRBs().at(1)->getID());
  feb = febs[5];
  BOOST_REQUIRE_EQUAL(feb->getID(), 5);
  BOOST_REQUIRE(!feb->isActive());
  BOOST_REQUIRE(feb->status()=="fainted");
  BOOST_REQUIRE(feb->description()=="scrawny");
  BOOST_REQUIRE_EQUAL(feb->version(), 271);
  BOOST_REQUIRE_EQUAL(feb->getCreator(), 616);
  BOOST_REQUIRE_EQUAL(feb->getNtimeOutsPerInput(), 3);
  BOOST_REQUIRE_EQUAL(feb->getNnotimeOutsPerInput(), 4);
  BOOST_REQUIRE_EQUAL(feb->getTRB().getID(), trbFactory.getTRBs().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetTRBFactory trbFactory(paramGetter, 3);
  JPetFEBFactory factory(paramGetter, 3, trbFactory);
  BOOST_REQUIRE_THROW(factory.getFEBs(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetTRBFactory trbFactory(paramGetter, 4);
  JPetFEBFactory factory(paramGetter, 4, trbFactory);
  BOOST_REQUIRE_THROW(factory.getFEBs(), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(wrong_relation)
{
  JPetTRBFactory trbFactory(paramGetter, 5);
  JPetFEBFactory factory(paramGetter, 5, trbFactory);
  BOOST_REQUIRE_THROW(factory.getFEBs(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

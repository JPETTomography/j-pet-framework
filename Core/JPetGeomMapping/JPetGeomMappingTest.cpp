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
 *  @file JPetGeomMappingTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGeomMappingTest
#include "./JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "./JPetParamManager/JPetParamManager.h"
#include <boost/test/unit_test.hpp>
#include "./JPetGeomMapping.h"

const std::string dataDir = "unitTestData/JPetGeomMappingTest/";
const std::string dataFileName = dataDir + "data.json";

struct myFixture
{
  myFixture() : fparamManagerInstance(new JPetParamGetterAscii(dataFileName))
  {
    fparamManagerInstance.fillParameterBank(1);
  }
  ~myFixture() {}
  JPetParamManager fparamManagerInstance;
};

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_FIXTURE_TEST_CASE(mappingFirst, myFixture)
{
  auto bank = fparamManagerInstance.getParamBank();
  auto mapping = JPetGeomMapping(bank);
  BOOST_REQUIRE_EQUAL(mapping.getLayersCount(), 3u);
  JPetLayer layerOK(1, true, "Layer01", 42.5);
  JPetLayer layerWrong(2, true, "Layer02", 50);

  BOOST_REQUIRE_EQUAL(mapping.getLayerNumber(layerOK), 1u);
  BOOST_REQUIRE_EQUAL(mapping.getLayerNumber(layerWrong),
                      JPetGeomMapping::kBadLayerNumber);

  BOOST_REQUIRE_EQUAL(mapping.getSlotsCount(0),
                      JPetGeomMapping::kBadSlotNumber);
  BOOST_REQUIRE_EQUAL(mapping.getSlotsCount(1), 2u);
  BOOST_REQUIRE_EQUAL(mapping.getSlotsCount(2), 1u);

  auto sizes = mapping.getLayersSizes();
  BOOST_REQUIRE(!sizes.empty());
  BOOST_REQUIRE_EQUAL(sizes.size(), 3u);
}

BOOST_FIXTURE_TEST_CASE(getSlotNumber, myFixture)
{
  auto bank = fparamManagerInstance.getParamBank();
  auto mapping = JPetGeomMapping(bank);
  JPetLayer layerOK(1, true, "Layer01", 42.5);
  JPetLayer layerWrong(2, true, "Layer02", 50);
  JPetBarrelSlot slotOK1(1, true, "C1_C2", 0, 1);
  slotOK1.setLayer(layerOK);
  JPetBarrelSlot slotOK2(2, true, "C3_C4", 90, 1);
  slotOK2.setLayer(layerOK);
  JPetBarrelSlot slotWrong(3, true, "C2AA", 5, 9);

  BOOST_REQUIRE_EQUAL(mapping.getSlotNumber(slotOK1), 1u);
  BOOST_REQUIRE_EQUAL(mapping.getSlotNumber(slotOK2), 2u);
  BOOST_REQUIRE_EQUAL(mapping.getSlotNumber(slotWrong), JPetGeomMapping::kBadSlotNumber);
}

BOOST_AUTO_TEST_CASE(emptyBank)
{
  JPetParamBank bank;
  auto mapping = JPetGeomMapping(bank);
  BOOST_REQUIRE(mapping.getTOMBMapping().empty());
}

BOOST_FIXTURE_TEST_CASE(minimalBank, myFixture)
{
  auto bank = fparamManagerInstance.getParamBank();
  auto mapper = JPetGeomMapping(bank);
  auto mapping = mapper.getTOMBMapping();
  BOOST_REQUIRE(!mapping.empty());
  BOOST_REQUIRE_EQUAL(mapping.size(), 5u);

  auto layer = 1;
  auto slot = 1;
  auto side = JPetPM::SideB;
  auto thresholdNumber = 1;
  BOOST_REQUIRE_EQUAL(
      mapping.count(std::make_tuple(layer, slot, side, thresholdNumber)),
      1u
    );

  auto result_tomb = mapping.at(
    std::make_tuple(layer, slot, side, thresholdNumber)
  );
  BOOST_REQUIRE_EQUAL(result_tomb, 1);

  layer = 1;
  slot = 1;
  side = JPetPM::SideA;
  thresholdNumber = 1;
  result_tomb = mapping.at(std::make_tuple(layer, slot, side, thresholdNumber));
  BOOST_REQUIRE_EQUAL(result_tomb, 2);

  layer = 1;
  slot = 2;
  side = JPetPM::SideA;
  thresholdNumber = 1;
  result_tomb = mapping.at(std::make_tuple(layer, slot, side, thresholdNumber));
  BOOST_REQUIRE_EQUAL(result_tomb, 3);

  layer = 1;
  slot = 2;
  side = JPetPM::SideB;
  thresholdNumber = 1;
  result_tomb = mapping.at(std::make_tuple(layer, slot, side, thresholdNumber));
  BOOST_REQUIRE_EQUAL(result_tomb, 4);

  layer = 2;
  slot = 1;
  side = JPetPM::SideA;
  thresholdNumber = 1;
  result_tomb = mapping.at(std::make_tuple(layer, slot, side, thresholdNumber));
  BOOST_REQUIRE_EQUAL(result_tomb, 10);
}

BOOST_FIXTURE_TEST_CASE(getTOMB, myFixture)
{
  auto bank = fparamManagerInstance.getParamBank();
  auto mapper = JPetGeomMapping(bank);
  auto layer = 1;
  auto slot = 1;
  auto side = JPetPM::SideB;
  auto thresholdNumber = 1;
  BOOST_REQUIRE_EQUAL(mapper.getTOMB(layer, slot, side, thresholdNumber), 1);

  layer = 1;
  slot = 1;
  side = JPetPM::SideA;
  thresholdNumber = 1;
  BOOST_REQUIRE_EQUAL(mapper.getTOMB(layer, slot, side, thresholdNumber), 2);

  layer = 1;
  slot = 2;
  side = JPetPM::SideA;
  thresholdNumber = 1;
  BOOST_REQUIRE_EQUAL(mapper.getTOMB(layer, slot, side, thresholdNumber), 3);

  layer = 1;
  slot = 2;
  side = JPetPM::SideB;
  thresholdNumber = 1;
  BOOST_REQUIRE_EQUAL(mapper.getTOMB(layer, slot, side, thresholdNumber), 4);

  layer = 2;
  slot = 1;
  side = JPetPM::SideA;
  thresholdNumber = 1;
  BOOST_REQUIRE_EQUAL(mapper.getTOMB(layer, slot, side, thresholdNumber), 10);
}

BOOST_AUTO_TEST_CASE(TestOfLargeBarrelJson)
{
  JPetParamManager fparamManagerInstance(new JPetParamGetterAscii(
      "unitTestData/JPetGeomMappingTest/large_barrel.json"));
  fparamManagerInstance.fillParameterBank(43);
  auto bank = fparamManagerInstance.getParamBank();
  auto mapper = JPetGeomMapping(bank);
  auto tombMap = mapper.getTOMBMapping();
  BOOST_REQUIRE(!tombMap.empty());
  BOOST_REQUIRE_EQUAL(tombMap.size(), 1536u);
}

BOOST_FIXTURE_TEST_CASE(radiusOfLayer, myFixture)
{
  auto bank = fparamManagerInstance.getParamBank();
  auto mapper = JPetGeomMapping(bank);
  BOOST_REQUIRE_EQUAL(mapper.getRadiusOfLayer(1), 42.5);
  BOOST_REQUIRE_EQUAL(mapper.getRadiusOfLayer(2), 46.75);
  BOOST_REQUIRE_EQUAL(mapper.getRadiusOfLayer(3), 57.5);
  BOOST_REQUIRE_EQUAL(mapper.getRadiusOfLayer(4), 0.);
  BOOST_REQUIRE_EQUAL(mapper.getRadiusOfLayer(-1), 0.);
}

BOOST_AUTO_TEST_SUITE_END()

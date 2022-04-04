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
 *  @file JPetParamGetterAsciiTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamGetterAsciiTest

#include "JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "JPetParamGetterAscii/JPetParamSaverAscii.h"
#include "JPetParamManager/JPetParamManager.h"
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

const std::string dataDir = "unitTestData/JPetParamGetterAsciiTest/";

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(noExisting_file_read)
{
  JPetParamGetterAscii getter(dataDir + "noExisting.json");
  BOOST_REQUIRE_EQUAL(getter.getAllBasicData(ParamObjectType::kPM, 1).size(), 0u);
}

BOOST_AUTO_TEST_CASE(empty_file_read)
{
  JPetParamGetterAscii getter(dataDir + "empty.json");
  BOOST_REQUIRE_EQUAL(getter.getAllBasicData(ParamObjectType::kPM, 1).size(), 0u);
}

BOOST_AUTO_TEST_CASE(minimal_basic_data_read)
{
  JPetParamGetterAscii getter(dataDir + "DBv10.json");
  ParamObjectsDescriptions descriptions = getter.getAllBasicData(ParamObjectType::kPM, 1);
  BOOST_REQUIRE_EQUAL(descriptions.size(), 1u);
  ParamObjectDescription& description = descriptions[1];
  BOOST_REQUIRE_EQUAL(description["id"], "1");
  BOOST_REQUIRE_EQUAL(description["pos_in_matrix"], "1");
  BOOST_REQUIRE_EQUAL(description["description"], "no description");
}

BOOST_AUTO_TEST_CASE(minimal_relational_data_read)
{
  JPetParamGetterAscii getter(dataDir + "DBv10.json");
  ParamRelationalData relations = getter.getAllRelationalData(ParamObjectType::kPM, ParamObjectType::kMatrix, 1);
  BOOST_REQUIRE_EQUAL(relations.size(), 1u);
  BOOST_REQUIRE_EQUAL(relations[1], 1);
}

BOOST_AUTO_TEST_CASE(minimal_example_write)
{
  JPetParamManager paramManager(new JPetParamGetterAscii(dataDir + "DBv10.json"));
  paramManager.fillParameterBank(1);

  const JPetParamBank& paramBank = paramManager.getParamBank();
  JPetParamSaverAscii saver;
  std::string writtenFileName(dataDir + "writtenDBv10.json");
  saver.saveParamBank(paramBank, 1, writtenFileName);

  JPetParamManager reparamManager(new JPetParamGetterAscii(writtenFileName.c_str()));
  reparamManager.fillParameterBank(1);

  const JPetParamBank& reparamBank = reparamManager.getParamBank();
  BOOST_REQUIRE_EQUAL(paramBank.getDataModulesSize(), reparamBank.getDataModulesSize());
  BOOST_REQUIRE_EQUAL(paramBank.getDataSourcesSize(), reparamBank.getDataSourcesSize());
  BOOST_REQUIRE_EQUAL(paramBank.getChannelsSize(), reparamBank.getChannelsSize());
  BOOST_REQUIRE_EQUAL(paramBank.getPMsSize(), reparamBank.getPMsSize());
  BOOST_REQUIRE_EQUAL(paramBank.getMatricesSize(), reparamBank.getMatricesSize());
  BOOST_REQUIRE_EQUAL(paramBank.getScinsSize(), reparamBank.getScinsSize());
  BOOST_REQUIRE_EQUAL(paramBank.getSlotsSize(), reparamBank.getSlotsSize());
  BOOST_REQUIRE_EQUAL(paramBank.getLayersSize(), reparamBank.getLayersSize());
  BOOST_REQUIRE_EQUAL(paramBank.getSetupsSize(), reparamBank.getSetupsSize());

  BOOST_REQUIRE(paramBank.getDataModule(1) == reparamBank.getDataModule(1));
  BOOST_REQUIRE(paramBank.getDataSource(1) == reparamBank.getDataSource(1));
  BOOST_REQUIRE(paramBank.getChannel(1) == reparamBank.getChannel(1));
  BOOST_REQUIRE(paramBank.getPM(1) == reparamBank.getPM(1));
  BOOST_REQUIRE(paramBank.getMatrix(1) == reparamBank.getMatrix(1));
  BOOST_REQUIRE(paramBank.getScin(1) == reparamBank.getScin(1));
  BOOST_REQUIRE(paramBank.getSlot(1) == reparamBank.getSlot(1));
  BOOST_REQUIRE(paramBank.getLayer(1) == reparamBank.getLayer(1));
  BOOST_REQUIRE(paramBank.getSetup(1) == reparamBank.getSetup(1));
}

BOOST_AUTO_TEST_SUITE_END()

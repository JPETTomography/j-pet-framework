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
 *  @file JPetParamManagerTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamManagerTest

#include "JPetParamManager/JPetParamManager.h"
#include "JPetOptionsTools/JPetOptionsTools.h"
#include "JPetParamGetterAscii/JPetParamGetterAscii.h"
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <cstddef>
#include <string>

const std::string dataDir = "unitTestData/JPetParamManagerTest/";
const std::string dataFileName = dataDir + "DBv10.json";

BOOST_AUTO_TEST_SUITE(JPetParamManagerTestSuite)

BOOST_AUTO_TEST_CASE(generateParamManager)
{
  std::map<std::string, boost::any> emptyOpts;
  auto paramMgr = JPetParamManager::generateParamManager(emptyOpts);
  BOOST_REQUIRE(paramMgr);
  BOOST_REQUIRE(!paramMgr->isNullObject());
}

BOOST_AUTO_TEST_CASE(generateParamManagerForScopeCase)
{
  using namespace jpet_options_tools;
  std::map<std::string, boost::any> opts;
  opts["inputFileType_std::string"] = std::string("scope");
  opts["localDB_std::string"] = std::string("unitTestData/JPetScopeLoaderTest/test_params.json");
  opts["runID_int"] = int(1);
  std::shared_ptr<JPetParamManager> paramMgr = JPetParamManager::generateParamManager(opts);
  BOOST_REQUIRE(paramMgr);
  BOOST_REQUIRE(!paramMgr->isNullObject());
  BOOST_REQUIRE(!paramMgr->getExpectMissing().empty());
  paramMgr->fillParameterBank(1);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().isDummy(), false);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getDataModulesSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getDataSourcesSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getChannelsSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getMatricesSize(), 2);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getScinsSize(), 2);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getLayersSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getSetupsSize(), 0);
}

BOOST_AUTO_TEST_CASE(generateParamManagerForMCGeantCase)
{
  std::map<std::string, boost::any> opts;
  opts["inputFileType_std::string"] = std::string("mcGeant");
  opts["localDB_std::string"] = dataFileName;
  opts["runID_int"] = int(1);
  std::shared_ptr<JPetParamManager> paramMgr = JPetParamManager::generateParamManager(opts);
  BOOST_REQUIRE(paramMgr);
  BOOST_REQUIRE(!paramMgr->isNullObject());
  BOOST_REQUIRE(!paramMgr->getExpectMissing().empty());
  paramMgr->fillParameterBank(1);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().isDummy(), false);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getDataModulesSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getDataSourcesSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getChannelsSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getPMsSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getMatricesSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getScinsSize(), 1);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getSlotsSize(), 1);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getLayersSize(), 1);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getSetupsSize(), 1);
}

void checkContainersSize(const JPetParamBank& bank)
{
  BOOST_REQUIRE_EQUAL(bank.getSlotsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getScinsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getMatricesSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getChannelsSize(), 1);
}

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetParamManager paramMgr;
  BOOST_REQUIRE(paramMgr.getExpectMissing().empty());
}

BOOST_AUTO_TEST_CASE(generateParamBankTest)
{
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  l_paramManagerInstance.fillParameterBank(1);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  checkContainersSize(l_paramManagerInstance.getParamBank());
  BOOST_REQUIRE(l_paramManagerInstance.getExpectMissing().empty());
}

BOOST_AUTO_TEST_CASE(writeAndReadDataFromFileByFileNameTest)
{
  std::string testDatafile = dataDir + "testDataFile.txt";
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  l_paramManagerInstance.fillParameterBank(1);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);
  boost::filesystem::remove(testDatafile);
}

BOOST_AUTO_TEST_CASE(some_Test_that_had_no_name)
{
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  l_paramManagerInstance.fillParameterBank(1);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  checkContainersSize(l_paramManagerInstance.getParamBank());
  l_paramManagerInstance.clearParameters();
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getScinsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getPMsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getSlotsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getChannelsSize(), 0);
}

BOOST_AUTO_TEST_CASE(getParamBankTest)
{
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  l_paramManagerInstance.fillParameterBank(1);
  const JPetParamBank& bank = l_paramManagerInstance.getParamBank();
  checkContainersSize(bank);
}

BOOST_AUTO_TEST_CASE(getParamBankTestWithScopeSettings)
{
  std::set<ParamObjectType> expectMissing;
  expectMissing.insert(ParamObjectType::kSetup);
  expectMissing.insert(ParamObjectType::kLayer);
  expectMissing.insert(ParamObjectType::kChannel);
  const std::string dataFileNameWithScope("unitTestData/JPetScopeLoaderTest/test_params.json");
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileNameWithScope), expectMissing);
  l_paramManagerInstance.fillParameterBank(1);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  BOOST_REQUIRE(!l_paramManagerInstance.getExpectMissing().empty());
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getScinsSize(), 2);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getChannelsSize(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

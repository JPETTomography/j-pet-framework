/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetTaskChainExecutorUtilsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskChainExecutorUtilsTest
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <list>

#include "../JPetTaskChainExecutor/JPetTaskChainExecutorUtils.h"
#include "../JPetTaskInterface/JPetTaskInterface.h"

BOOST_AUTO_TEST_SUITE(JPetTaskChainExecutorUtilsTestSuite)

BOOST_AUTO_TEST_CASE(generateParamManager)
{
  std::map<std::string, boost::any> emptyOpts;
  auto paramMgr = JPetTaskChainExecutorUtils::generateParamManager(emptyOpts);
  BOOST_REQUIRE(paramMgr);
  BOOST_REQUIRE(!paramMgr->isNullObject());
}

BOOST_AUTO_TEST_CASE(generateParamManagerForScopeCase)
{
  std::map<std::string, boost::any> opts;
  opts["inputFileType_std::string"] = std::string("scope");
  opts["localDB_std::string"] = std::string("unitTestData/JPetScopeLoaderTest/test_params.json");
  opts["runId_int"] = int(1);
  std::shared_ptr<JPetParamManager> paramMgr = JPetTaskChainExecutorUtils::generateParamManager(opts);
  BOOST_REQUIRE(paramMgr);
  BOOST_REQUIRE(!paramMgr->isNullObject());
  BOOST_REQUIRE(!paramMgr->getExpectMissing().empty());
  paramMgr->fillParameterBank(1);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().isDummy(), false);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getScintillatorsSize(), 2);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getPMCalibsSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getFEBsSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getTRBsSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getBarrelSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getTOMBChannelsSize(), 0);
}

BOOST_AUTO_TEST_CASE(generateParams)
{
  std::map<std::string, boost::any> optPerFile;
  std::vector<std::map<std::string, boost::any>> opts = {optPerFile};
  auto params = JPetTaskChainExecutorUtils::generateParams(opts);
  BOOST_REQUIRE_EQUAL(params.size(), 1u);
  auto firstParam = params.front();
  BOOST_REQUIRE(firstParam.getOptions().empty());
  BOOST_REQUIRE(firstParam.getParamManager());
}

BOOST_AUTO_TEST_CASE(generateParams2)
{
  std::map<std::string, boost::any> optPerFile;
  std::vector<std::map<std::string, boost::any>> opts = {optPerFile, optPerFile};
  auto params = JPetTaskChainExecutorUtils::generateParams(opts);
  BOOST_REQUIRE_EQUAL(params.size(), 2u);
  auto first = params.front();
  BOOST_REQUIRE(first.getOptions().empty());
  BOOST_REQUIRE(first.getParamManager());
  auto second = params.back();
  BOOST_REQUIRE(second.getOptions().empty());
  BOOST_REQUIRE(second.getParamManager());
  BOOST_REQUIRE_EQUAL(first.getParamManager(), second.getParamManager());
}

BOOST_AUTO_TEST_SUITE_END()

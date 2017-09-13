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
#include "../JPetTaskChainExecutor/JPetTaskChainExecutorUtils.h"

BOOST_AUTO_TEST_SUITE(JPetTaskChainExecutorTestSuite)

BOOST_AUTO_TEST_CASE(sucessZip)
{
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodZip");
  BOOST_REQUIRE(JPetTaskChainExecutorUtils::unzipFile("unitTestData/JPetTaskChainExecutorUtilsTest/goodZip.gz"));
}

BOOST_AUTO_TEST_CASE(tryToUnzipSomethingNotExistingFile)
{
  std::string initialPath = boost::filesystem::path(boost::filesystem::current_path()).string();
  initialPath = initialPath.substr(0, initialPath.find("build") );
  std::string wrongZipPath = initialPath + "wrongZip.gz";
  BOOST_REQUIRE(!JPetTaskChainExecutorUtils::unzipFile( wrongZipPath.c_str() ));
  BOOST_REQUIRE(!JPetTaskChainExecutorUtils::unzipFile( "unitTestData/JPetTaskChainExecutorUtilsTest/wrongZip.gz" ));
}

BOOST_AUTO_TEST_CASE(sucessXz)
{
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ");
  BOOST_REQUIRE(JPetTaskChainExecutorUtils::unzipFile("unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ.xz"));
}

BOOST_AUTO_TEST_CASE(tryToUnzipSomethingNotExistingFileWithXz)
{
  std::string initialPath = boost::filesystem::path(boost::filesystem::current_path()).string();
  initialPath = initialPath.substr(0, initialPath.find("build") );
  std::string wrongZipPath = initialPath + "unitTestData/JPetTaskChainExecutorUtilsTest/wrongZip.Xz";
  BOOST_REQUIRE(!JPetTaskChainExecutorUtils::unzipFile( wrongZipPath.c_str() ));
  BOOST_REQUIRE(!JPetTaskChainExecutorUtils::unzipFile( "unitTestData/JPetTaskChainExecutorUtilsTest/wrongXZ.xz" ));
}

BOOST_AUTO_TEST_CASE(generateParamManager)
{
  std::map<std::string, boost::any> emptyOpts;
  auto paramMgr = JPetTaskChainExecutorUtils::generateParamManager(emptyOpts);
  BOOST_REQUIRE(paramMgr);
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

BOOST_AUTO_TEST_CASE(process)
{
  JPetParams params;
  std::list<JPetTaskInterface*> tasks;
  BOOST_REQUIRE(!JPetTaskChainExecutorUtils::process(params, tasks));
  BOOST_REQUIRE(tasks.empty());
}

BOOST_AUTO_TEST_SUITE_END()

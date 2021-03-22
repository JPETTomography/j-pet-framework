/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetGateParserTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGateParser

#include "JPetGateParser/JPetGateParser.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(JPetGateParserTaskSuite)

BOOST_AUTO_TEST_CASE(sucessGz)
{
  std::map<std::string, boost::any> opts;
  opts["inputFileType_std::string"] = std::string("mcGeant");
  // opts["localDB_std::string"] = std::string("unitTestData/JPetParamManagerTest/modularSingle.json");
  opts["localDB_std::string"] = std::string("unitTestData/detectorSetupRun2345.json");
  opts["runId_int"] = int(5);
  opts["GateParser_MaxTimeWindow_double"] = 0.0;
  opts["GateParser_MinTimeWindow_double"] = -50000000.0;
  opts["GateParser_SourceActivity_double"] = 4.7;
  std::shared_ptr<JPetParamManager> paramMgr = JPetParamManager::generateParamManager(opts);
  paramMgr->fillParameterBank(5);
  JPetParams params(opts, paramMgr);
  JPetGateParser parser("parser");
  parser.init(params);
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodGZ");
  BOOST_REQUIRE(parser.transformTree2("output_gate.root", "bla.root", JPetGateTreeReader::DetectorGeometry::ThreeLayers, 4.7, -50000000.0, 0.0));
}

// BOOST_AUTO_TEST_CASE(wrongGz)
//{
// BOOST_REQUIRE(!JPetUnzipTask::unzipFile(
//"unitTestData/JPetTaskChainExecutorUtilsTest/wrongGZ.gz", "./"
//));
//}

BOOST_AUTO_TEST_SUITE_END()

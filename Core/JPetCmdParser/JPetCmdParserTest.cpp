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
 *  @file JPetCmdParserTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetCmdParserTest
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetCmdParser/JPetCmdParser.h"
#include "./JPetCmdParser/JPetCmdParser.h"
#include <boost/test/unit_test.hpp>
#include <boost/any.hpp>
#include <cstdlib>

using boost::any_cast;
using namespace std;

BOOST_AUTO_TEST_SUITE(FirstSuite)
BOOST_AUTO_TEST_CASE( testCmd )
{
  auto cmdLine = "main.x -t hld -f unitTestData/JPetCmdParserTest/testfile.hld -i 10";
  auto args_char = JPetCommonTools::createArgs(cmdLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  JPetCmdParser parser;
  auto result = parser.parseCmdLineArgs(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE(result.find("type") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(result.at("type").value()), "hld");
  BOOST_REQUIRE(result.find("runId") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<int>(result.at("runId").value()), 10);
  BOOST_REQUIRE(result.find("file") != result.end());
  auto vectOfFiles =  any_cast<std::vector<std::string>>(result.at("file").value());
  BOOST_REQUIRE_EQUAL(vectOfFiles.size(), 1u);
  BOOST_REQUIRE_EQUAL(vectOfFiles.at(0), "unitTestData/JPetCmdParserTest/testfile.hld");
}

BOOST_AUTO_TEST_CASE( testCmd2 )
{
  auto cmdLine = "main.x -t hld -f unitTestData/JPetCmdParserTest/testfile.hld unitTestData/JPetCmdParserTest/testfile2.hld -i 10";
  auto args_char = JPetCommonTools::createArgs(cmdLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  JPetCmdParser parser;
  auto result = parser.parseCmdLineArgs(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE(result.find("type") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(result.at("type").value()), "hld");
  BOOST_REQUIRE(result.find("runId") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<int>(result.at("runId").value()), 10);
  BOOST_REQUIRE(result.find("file") != result.end());
  auto vectOfFiles =  any_cast<std::vector<std::string>>(result.at("file").value());
  BOOST_REQUIRE_EQUAL(vectOfFiles.size(), 2u);
  BOOST_REQUIRE_EQUAL(vectOfFiles.at(0), "unitTestData/JPetCmdParserTest/testfile.hld");
  BOOST_REQUIRE_EQUAL(vectOfFiles.at(1), "unitTestData/JPetCmdParserTest/testfile2.hld");
}

BOOST_AUTO_TEST_CASE( testCmd3 )
{
  auto cmdLine = "main.x -o ./ -f unitTestData/JPetCmdParserTest/data.hld -t hld -u unitTestData/JPetOptionsToolsTest/newInputTestCfg.json";
  auto args_char = JPetCommonTools::createArgs(cmdLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  JPetCmdParser parser;
  auto result = parser.parseCmdLineArgs(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE(result.find("type") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(result.at("type").value()), "hld");
  BOOST_REQUIRE(result.find("file") != result.end());
  auto vectOfFiles =  any_cast<std::vector<std::string>>(result.at("file").value());
  BOOST_REQUIRE_EQUAL(vectOfFiles.size(), 1u);
  BOOST_REQUIRE_EQUAL(vectOfFiles.at(0), "unitTestData/JPetCmdParserTest/data.hld");
  BOOST_REQUIRE(result.find("userCfg") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(result.at("userCfg").value()), "unitTestData/JPetOptionsToolsTest/newInputTestCfg.json");
}

BOOST_AUTO_TEST_CASE( testCmd4 )
{
  auto cmdLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -r 2 4 -p unitTestData/JPetCmdParserTest/conf.xml -c unitTestData/JPetUnpackerTest/calib.root -i 231 -L output.json";
  auto args_char = JPetCommonTools::createArgs(cmdLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  JPetCmdParser parser;
  auto result = parser.parseCmdLineArgs(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE(result.find("file") != result.end());
  auto vectOfFiles =  any_cast<std::vector<std::string>>(result.at("file").value());
  BOOST_REQUIRE_EQUAL(vectOfFiles.size(), 1u);
  BOOST_REQUIRE_EQUAL(vectOfFiles.at(0), "unitTestData/JPetCmdParserTest/data.hld");

  BOOST_REQUIRE(result.find("type") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(result.at("type").value()), "hld");

  BOOST_REQUIRE(result.find("range") != result.end());
  auto vectRange = any_cast<std::vector<int>>(result.at("range").value());
  BOOST_REQUIRE_EQUAL(vectRange.size(), 2u);
  BOOST_REQUIRE_EQUAL(vectRange.at(0), 2);
  BOOST_REQUIRE_EQUAL(vectRange.at(1), 4);

  BOOST_REQUIRE(result.find("unpackerConfigFile") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(result.at("unpackerConfigFile").value()), "unitTestData/JPetCmdParserTest/conf.xml");

  BOOST_REQUIRE(result.find("unpackerCalibFile") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(result.at("unpackerCalibFile").value()), "unitTestData/JPetUnpackerTest/calib.root");

  BOOST_REQUIRE_EQUAL(any_cast<int>(result.at("runId").value()), 231);
  BOOST_REQUIRE(result.find("file") != result.end());

  BOOST_REQUIRE(result.find("localDBCreate") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(result.at("localDBCreate").value()), "output.json");
}

BOOST_AUTO_TEST_CASE( testCmd5_userCfgScope )
{
  auto cmdLine = "main.x -t scope -f unitTestData/JPetCmdParserTest/testfile.json ";
  auto args_char = JPetCommonTools::createArgs(cmdLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  JPetCmdParser parser;
  auto result = parser.parseCmdLineArgs(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE(result.find("file") != result.end());
  auto vectOfFiles =  any_cast<std::vector<std::string>>(result.at("file").value());
  BOOST_REQUIRE_EQUAL(vectOfFiles.size(), 1u);
  BOOST_REQUIRE_EQUAL(vectOfFiles.at(0), "unitTestData/JPetCmdParserTest/testfile.json");

  BOOST_REQUIRE(result.find("type") != result.end());
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(result.at("type").value()), "scope");

  BOOST_REQUIRE(result.find("range") != result.end());
  auto vectRange = any_cast<std::vector<int>>(result.at("range").value());
  BOOST_REQUIRE_EQUAL(vectRange.size(), 2u);
  BOOST_REQUIRE_EQUAL(vectRange.at(0), -1);
  BOOST_REQUIRE_EQUAL(vectRange.at(1), -1);
  BOOST_REQUIRE(result.find("unpackerConfigFile") == result.end());
  BOOST_REQUIRE(result.find("unpackerCalibFile") == result.end());
  BOOST_REQUIRE(result.find("localDBCreate") == result.end());
}

BOOST_AUTO_TEST_SUITE_END()

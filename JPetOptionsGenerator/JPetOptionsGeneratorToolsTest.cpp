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
 *  @file JPetOptionsGeneratorTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsGeneratorToolsTest
#include <boost/test/unit_test.hpp>
#include <cstdlib>
#include "../JPetCmdParser/JPetCmdParser.h"
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
using boost::any_cast;
using namespace std;
using namespace jpet_options_tools;
using namespace jpet_options_generator_tools;

po::variables_map getCmdLineArgs(const char* cmdLine)
{
  auto args_char = JPetCommonTools::createArgs(cmdLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  JPetCmdParser parser;
  return parser.parseCmdLineArgs(argc, const_cast<const char**>(argv));
}

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(checkIfFunctionToGenerateTransformationMapWork)
{
  OptsStrAny options;
  auto transformationMap = generateTransformationMap(options);
  BOOST_REQUIRE(transformationMap.count("outputPath_std::string"));
  BOOST_REQUIRE(transformationMap.count("range_std::vector<int>"));
  BOOST_REQUIRE(transformationMap.count("type_std::string"));
}

BOOST_AUTO_TEST_CASE(checkIfFunctionToTransformOptionsWork)
{
  OptsStrAny options;
  auto transformationMap = generateTransformationMap(options);
  std::map<std::string, boost::any> emptyOptions;
  BOOST_REQUIRE(transformOptions(transformationMap , emptyOptions).empty());

  std::string pathForCorrection = "a/b/c/d";
  std::vector<int> range = {1, 2};
  std::string inputFileType = "inputFileType";

  std::map<std::string, boost::any> optionForTransformation;
  optionForTransformation["outputPath_std::string"] = pathForCorrection;
  optionForTransformation["range_std::vector<int>"] = range;
  optionForTransformation["type_std::string"] = inputFileType;

  auto mapAfterTransformation = transformOptions(transformationMap, optionForTransformation);
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(mapAfterTransformation.at("outputPath_std::string")), (pathForCorrection + '/'));
  BOOST_REQUIRE_EQUAL(any_cast<int>(mapAfterTransformation.at("lastEvent_int")), 2);
  BOOST_REQUIRE_EQUAL(any_cast<int>(mapAfterTransformation.at("firstEvent_int")), 1);
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(mapAfterTransformation.at("inputFileType_std::string")), inputFileType);
}

BOOST_AUTO_TEST_CASE(checkIfFunctionGetConfigFileNameWork)
{
  auto commandLine = "main.x -u example.json";
  auto args_char = JPetCommonTools::createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  po::options_description description("Allowed options");
  description.add_options()
  ("userCfg_std::string,u", po::value<std::string>(), "Json file with optional user parameters.");
  ;

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  BOOST_REQUIRE_EQUAL(getConfigFileName(transformToStrAnyMap(variablesMap)), "example.json");

  auto commandLine2 = "main.x ";
  auto args_char2 = JPetCommonTools::createArgs(commandLine2);
  auto argc2 = args_char2.size();
  auto argv2 = args_char2.data();

  po::options_description description2("Allowed options");
  description2.add_options()
  ("userCfg_std::string,u", po::value<std::string>(), "Json file with optional user parameters.");
  ;

  po::variables_map variablesMap2;
  po::store(po::parse_command_line(argc2, argv2, description2), variablesMap2);
  po::notify(variablesMap2);

  BOOST_REQUIRE_EQUAL(getConfigFileName(transformToStrAnyMap(variablesMap2)), "");
}

BOOST_AUTO_TEST_CASE(checkIfFunctionToAddOptionsFromCfgFileWork)
{
  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -r 2 -r 4 -p unitTestData/JPetCmdParserTest/data.hld -i 231 -b 1 -l unitTestData/JPetCmdParserTest/input.json -L output.json -u unitTestData/JPetOptionsToolsTest/newInputTestCfg.json";
  auto args_char = JPetCommonTools::createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  po::options_description description("Allowed options");
  description.add_options()
  ("file_std::vector<std::string>,f", po::value<std::vector<std::string>>(), "File(s) to open")
  ("type_std::string,t", po::value<std::string>(), "type of file: hld, zip, root or scope")
  ("range_std::vector<int>,r", po::value<std::vector<int>>(), "Range of events to process.")
  ("param_std::string,p", po::value<std::string>(), "File with TRB numbers.")
  ("runId_int,i", po::value<int>(), "Run id.")
  ("progressBar_bool,b", po::bool_switch()->default_value(false), "Progress bar.")
  ("localDB_std::string,l", po::value<std::string>(), "The file to use as the parameter database.")
  ("localDBCreate_std::string,L", po::value<std::string>(), "Where to save the parameter database.")
  ("userCfg_std::string,u", po::value<std::string>(), "Json file with optional user parameters.");

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  auto options = transformToStrAnyMap(variablesMap);
  auto cfgFileName = getConfigFileName(options);
  if (!cfgFileName.empty()) {
    addNewOptionsFromCfgFile(cfgFileName, options);
  }
  BOOST_REQUIRE(options.count("myOption_std::string"));
  BOOST_REQUIRE(options.count("myAnotherOption_std::string"));
}

BOOST_AUTO_TEST_SUITE_END()

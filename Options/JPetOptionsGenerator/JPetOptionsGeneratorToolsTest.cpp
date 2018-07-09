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
 *  @file JPetOptionsGeneratorTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsGeneratorToolsTest

#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetCmdParser/JPetCmdParser.h"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cstdlib>

using boost::any_cast;
using namespace std;
using namespace jpet_options_tools;
using namespace jpet_options_generator_tools;

OptsStrAny getOptions(const std::string& commandLine)
{
  auto args_char = JPetCommonTools::createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  po::options_description description("Allowed options");
  description.add_options()
  ("help,h", "Displays this help message.")
  ("type,t", po::value<std::string>()->required(), "Type of file: hld, zip, root or scope.")
  ("file,f", po::value< std::vector<std::string> >()->required()->multitoken(), "File(s) to open.")
  ("outputPath,o", po::value<std::string>(), "Location to which the outputFiles will be saved.")
  ("range,r", po::value< std::vector<int> >()->multitoken()->default_value({ -1, -1}, ""), "Range of events to process e.g. -r 1 1000 .")
  ("unpackerConfigFile,p", po::value<std::string>(), "xml file with TRB settings used by the unpacker program.")
  ("unpackerCalibFile,c", po::value<std::string>(), "ROOT file with TRB calibration used by the unpacker program.")
  ("runId,i", po::value<int>(), "Run id.")
  ("progressBar,b", po::bool_switch()->default_value(false), "Progress bar.")
  ("localDB,l", po::value<std::string>(), "The file to use as the parameter database.")
  ("localDBCreate,L", po::value<std::string>(), "File name to which the parameter database will be saved.")
  ("userCfg,u", po::value<std::string>(), "Json file with optional user parameters.");
  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);
  auto options = addTypeSuffixes(transformToStrAnyMap(variablesMap));
  options = addMissingDefaultOptions(options);
  auto transformationMap = generateTransformationMap(options);
  options = transformOptions(transformationMap, options);
  return options;
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

BOOST_AUTO_TEST_CASE(generateOptionsForTask_emptyControlSettings)
{
  std::vector<std::string> tmp = {"aa", "bb"};
  std::map<std::string, boost::any> inOpts = {
    {"my_string", std::string("my_value")},
    {"my_int", int(12)},
  };
  std::map<std::string, boost::any> controlSettings;
  auto result = generateOptionsForTask(inOpts, controlSettings);
  for (auto it_r = result.cbegin(), end_r = result.cend(),  it_inOpts = inOpts.cbegin(), end_inOpts = inOpts.cend(); it_r != end_r || it_inOpts != end_inOpts; ) {
    BOOST_REQUIRE_EQUAL(it_r->first, it_inOpts->first);
    ++it_r;
    ++it_inOpts;
  }
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(result["my_string"]), any_cast<std::string>(inOpts["my_string"]));
  BOOST_REQUIRE_EQUAL(any_cast<int>(result["my_int"]), any_cast<int>(inOpts["my_int"]));
}

BOOST_AUTO_TEST_CASE(generateOptionsForTask_hldRoot_after_hld)
{
  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld.root -t root -r 2 100  -i 231";
  auto inOpts  = getOptions(commandLine);
  std::map<std::string, boost::any> controlSettings = {{"outputFileType_std::string", std::string("hldRoot")}};
  auto resultsOpt = generateOptionsForTask(inOpts, controlSettings);
  BOOST_REQUIRE(isOptionSet(resultsOpt, "inputFileType_std::string"));
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(resultsOpt), FileTypeChecker::kHldRoot);
}

BOOST_AUTO_TEST_CASE(generateOptionsForTask_root_after_hldRoot)
{
  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.root -t root -r 2 100  -i 231";
  auto inOpts  = getOptions(commandLine);
  std::map<std::string, boost::any> controlSettings = {{"outputFileType_std::string", std::string("root")}};
  auto resultsOpt = generateOptionsForTask(inOpts, controlSettings);
  BOOST_REQUIRE(isOptionSet(resultsOpt, "inputFileType_std::string"));
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(resultsOpt), FileTypeChecker::kRoot);
  BOOST_REQUIRE(isOptionSet(resultsOpt, "firstEvent_int"));
  BOOST_REQUIRE(isOptionSet(resultsOpt, "lastEvent_int"));
  BOOST_REQUIRE_EQUAL(getOptionAsInt(resultsOpt, "firstEvent_int"), 2);
  BOOST_REQUIRE_EQUAL(getOptionAsInt(resultsOpt, "lastEvent_int"), 100);
}

BOOST_AUTO_TEST_CASE(generateOptionsForTask_root_after_Root)
{
  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.root -t root -r 2 100  -i 231";
  auto inOpts  = getOptions(commandLine);
  std::map<std::string, boost::any> controlSettings = {{"outputFileType_std::string", std::string("root")}};
  auto resultsOpt = generateOptionsForTask(inOpts, controlSettings);
  BOOST_REQUIRE(isOptionSet(resultsOpt, "inputFileType_std::string"));
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(resultsOpt), FileTypeChecker::kRoot);
  BOOST_REQUIRE(isOptionSet(resultsOpt, "firstEvent_int"));
  BOOST_REQUIRE(isOptionSet(resultsOpt, "lastEvent_int"));
  BOOST_REQUIRE_EQUAL(getOptionAsInt(resultsOpt, "firstEvent_int"), 2);
  BOOST_REQUIRE_EQUAL(getOptionAsInt(resultsOpt, "lastEvent_int"), 100);
}

BOOST_AUTO_TEST_CASE(generateOptionsForTask_resetEventRange)
{
  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.root -t root -r 2 100  -i 231";
  auto inOpts  = getOptions(commandLine);
  std::map<std::string, boost::any> controlSettings = {{"resetEventRange_bool", bool(true)}};
  auto resultsOpt = generateOptionsForTask(inOpts, controlSettings);
  BOOST_REQUIRE(isOptionSet(resultsOpt, "firstEvent_int"));
  BOOST_REQUIRE(isOptionSet(resultsOpt, "lastEvent_int"));
  BOOST_REQUIRE_EQUAL(getOptionAsInt(resultsOpt, "firstEvent_int"), -1);
  BOOST_REQUIRE_EQUAL(getOptionAsInt(resultsOpt, "lastEvent_int"), -1);
}

BOOST_AUTO_TEST_CASE(generateOptionsForTask_outputPath)
{
  auto commandLine = "main.x -f data.root -t root -r 2 100  -i 231 ";
  auto inOpts  = getOptions(commandLine);
  inOpts["inputFile_std::string"] = *(getInputFiles(inOpts).begin());
  std::map<std::string, boost::any> controlSettings = {{"outputPath_std::string", std::string("../../")}};
  auto resultsOpt = generateOptionsForTask(inOpts, controlSettings);
  BOOST_REQUIRE(isOptionSet(resultsOpt, "inputFile_std::string"));
  BOOST_REQUIRE_EQUAL(getOptionAsString(resultsOpt, "inputFile_std::string"), std::string("../../data.root"));
}

BOOST_AUTO_TEST_CASE(setResetEventRangeOption_test)
{
  std::map<std::string, boost::any> options;
  setResetEventRangeOption(options, true);
  BOOST_REQUIRE(isOptionSet(options, "resetEventRange_bool"));
  BOOST_REQUIRE(getOptionAsBool(options, "resetEventRange_bool"));
  setResetEventRangeOption(options, false);
  BOOST_REQUIRE(!getOptionAsBool(options, "resetEventRange_bool"));
}

BOOST_AUTO_TEST_CASE(setOutputFileType_test)
{
  std::map<std::string, boost::any> options;
  setOutputFileType(options, "root");
  BOOST_REQUIRE(isOptionSet(options, "outputFileType_std::string"));
  BOOST_REQUIRE_EQUAL(getOptionAsString(options, "outputFileType_std::string"), "root");
}

BOOST_AUTO_TEST_CASE(setOutputPath_test)
{
  std::map<std::string, boost::any> options;
  setOutputPath(options, "/here/and/there");
  BOOST_REQUIRE(isOptionSet(options, "outputPath_std::string"));
  BOOST_REQUIRE_EQUAL(getOptionAsString(options, "outputPath_std::string"), "/here/and/there");
}

BOOST_AUTO_TEST_SUITE_END()

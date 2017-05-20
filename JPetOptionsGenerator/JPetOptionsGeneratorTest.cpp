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
#define BOOST_TEST_MODULE JPetOptionsGeneratorTest
#include <boost/test/unit_test.hpp>
#include <cstdlib>
#include "../JPetCmdParser/JPetCmdParser.h"
#include "../JPetOptionsGenerator/JPetOptionsGenerator.h"
using boost::any_cast;
using namespace std;


char* convertStringToCharP(const std::string& s)
{
  char* pc = new char[s.size() + 1];
  std::strcpy(pc, s.c_str());
  return pc;
}

std::vector<char*> createArgs(const std::string& commandLine)
{
  std::istringstream iss(commandLine);
  std::vector<std::string> args {std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>{}
                                };
  std::vector<char*> args_char;
  std::transform(args.begin(), args.end(), std::back_inserter(args_char), convertStringToCharP);
  return args_char;
}

BOOST_AUTO_TEST_SUITE(FirstSuite)
BOOST_AUTO_TEST_CASE(runIdTest)
{
  JPetOptionsGenerator cmdParser;

  auto commandLine = "main.x -i 231";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  po::options_description description("Allowed options");
  description.add_options()
  ("runId_int,i", po::value<int>(), "Run id.")
  ;

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  std::map<std::string, boost::any> mapFromVariableMap = cmdParser.variablesMapToOption(variablesMap);

  BOOST_REQUIRE(cmdParser.isOptionSet(mapFromVariableMap, "runId_int"));
  BOOST_REQUIRE_EQUAL(any_cast<int>(cmdParser.getOptionValue(mapFromVariableMap, "runId_int")), 231);

  auto runId = any_cast<int>(cmdParser.getOptionValue(mapFromVariableMap, "runId_int"));
  BOOST_REQUIRE(variablesMap.size() == 1);
  BOOST_REQUIRE(variablesMap.count("runId_int") == 1);
  BOOST_REQUIRE(runId == 231);
}

BOOST_AUTO_TEST_CASE(localDBTest)
{
  auto commandLine = "main.x -l input.json -L output.json -i 8";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  po::options_description description("Allowed options");
  description.add_options()
  ("localDB_std::string,l", po::value<std::string>(), "The file to use as the parameter database.")
  ("localDBCreate_std::string,L", po::value<std::string>(), "Where to save the parameter database.")
  ("runId_int,i", po::value<int>(), "Run id.")
  ;

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  JPetOptionsGenerator cmdParser;
  std::map<std::string, boost::any> mapFromVariableMap = cmdParser.variablesMapToOption(variablesMap);
  BOOST_REQUIRE(cmdParser.isOptionSet(mapFromVariableMap, "localDB_std::string"));
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(cmdParser.getOptionValue(mapFromVariableMap, "localDB_std::string")), std::string("input.json"));
  BOOST_REQUIRE(cmdParser.isOptionSet(mapFromVariableMap, "localDBCreate_std::string"));
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(cmdParser.getOptionValue(mapFromVariableMap, "localDBCreate_std::string")), std::string("output.json"));

}


BOOST_AUTO_TEST_CASE(generateOptionsTest)
{
  JPetOptionsGenerator cmdParser;

  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -r 2 -r 4 -p unitTestData/JPetCmdParserTest/data.hld -i 231 -b 1 -l unitTestData/JPetCmdParserTest/input.json -L output.json";
  auto args_char = createArgs(commandLine);
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
  ;

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  std::map<std::string, boost::any> mapFromVariableMap = cmdParser.variablesMapToOption(variablesMap);

  std::vector<JPetOptions> options = cmdParser.generateOptions(variablesMap);
  JPetOptions firstOption = options.front();
  // for (auto & opt: firstOption.getOptions()){
  //   std::cout<<"Option name: "<<opt.first<<" Option value: "<<opt.second<<std::endl;
  // }
  BOOST_REQUIRE(strcmp(firstOption.getInputFile(), "unitTestData/JPetCmdParserTest/data.hld") == 0);
  BOOST_REQUIRE(firstOption.getInputFileType() == JPetOptions::kHld);
  //BOOST_REQUIRE(firstOption.getOutputFile() == "root");
  //BOOST_REQUIRE(firstOption.getOutputFileType() == "test.root");
  BOOST_REQUIRE(firstOption.getFirstEvent() == 2);
  BOOST_REQUIRE(firstOption.getLastEvent() == 4);
  BOOST_REQUIRE(firstOption.getRunNumber() == 231);
  BOOST_REQUIRE(firstOption.isProgressBar());
  BOOST_REQUIRE(firstOption.isLocalDB());
  BOOST_REQUIRE(firstOption.getLocalDB() == std::string("unitTestData/JPetCmdParserTest/input.json"));
  BOOST_REQUIRE(firstOption.isLocalDBCreate());
  BOOST_REQUIRE(firstOption.getLocalDBCreate() == std::string("output.json"));
}

BOOST_AUTO_TEST_CASE(checkWrongOutputPath)
{
  auto args_char = createArgs("main.x -o ./blebel/blaba33/bob -f unitTestData/JPetCmdParserTest/data.hld -t hld");
  auto argc = args_char.size();
  auto argv = args_char.data();

  po::options_description description("Allowed options");
  description.add_options()
  ("help,h", "Displays this help message.")
  ("type_std::string,t", po::value<std::string>()->required()->implicit_value(""), "Type of file: hld, zip, root or scope.")
  ("file_std::vector<std::string>,f", po::value< std::vector<std::string> >()->required()->multitoken(), "File(s) to open.")
  ("outputPath_std::string,o", po::value<std::string>(), "Location to which the outputFiles will be saved.")
  ("range_std::vector<int>,r", po::value< std::vector<int> >()->multitoken()->default_value({ -1, -1}, ""), "Range of events to process e.g. -r 1 1000 .")
  ("param_std::string,p", po::value<std::string>(), "xml file with TRB settings used by the unpacker program.")
  ("runId_int,i", po::value<int>(), "Run id.")
  ("progressBar_bool,b", po::bool_switch()->default_value(false), "Progress bar.")
  ("localDB_std::string,l", po::value<std::string>(), "The file to use as the parameter database.")
  ("localDBCreate_std::string,L", po::value<std::string>(), "File name to which the parameter database will be saved.")
  ("userCfg_std::string,u", po::value<std::string>(), "Json file with optional user parameters.");

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);
  JPetOptionsGenerator parser;
}

BOOST_AUTO_TEST_CASE(checkIfFunctionsToTransformOptionWork)
{
  std::vector<int> firstOption = {1, 2};

  BOOST_REQUIRE_EQUAL(any_cast<int>(JPetOptionsGenerator::getLowerEventBound(firstOption).second), 1);
  BOOST_REQUIRE_EQUAL(any_cast<int>(JPetOptionsGenerator::getHigherEventBound(firstOption).second), 2);

  std::vector<int> secondOption = { -1, -2};

  BOOST_REQUIRE_EQUAL(any_cast<int>(JPetOptionsGenerator::getLowerEventBound(secondOption).second), -1);
  BOOST_REQUIRE_EQUAL(any_cast<int>(JPetOptionsGenerator::getHigherEventBound(secondOption).second), -1);

  std::string inputFileType = "inputFileType";
  BOOST_REQUIRE_EQUAL(JPetOptionsGenerator::setInputFileType(inputFileType).first, "inputFileType_std::string");
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(JPetOptionsGenerator::setInputFileType(inputFileType).second), inputFileType);

  std::string emptyPath = "";
  BOOST_REQUIRE_EQUAL(JPetOptionsGenerator::appendSlash(emptyPath).first, "outputPath_std::string");
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(JPetOptionsGenerator::appendSlash(emptyPath).second), "");

  std::string correctPath = "a/b/c/d/";
  BOOST_REQUIRE_EQUAL(JPetOptionsGenerator::appendSlash(correctPath).first, "outputPath_std::string");
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(JPetOptionsGenerator::appendSlash(correctPath).second), correctPath);

  std::string pathForCorrection = "a/b/c/d";
  BOOST_REQUIRE_EQUAL(JPetOptionsGenerator::appendSlash(pathForCorrection).first, "outputPath_std::string");
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(JPetOptionsGenerator::appendSlash(pathForCorrection).second), correctPath);

}

BOOST_AUTO_TEST_CASE(checkIfFunctionToGenerateTransformationMapWork)
{
  JPetOptionsGenerator generator;
  auto transformationMap = generator.generateTransformationMap();
  BOOST_REQUIRE(transformationMap.count("outputPath_std::string"));
  BOOST_REQUIRE(transformationMap.count("range_std::vector<int>"));
  BOOST_REQUIRE(transformationMap.count("type_std::string"));
}

BOOST_AUTO_TEST_CASE(checkIfFunctionToTransformOptionsWork)
{
  JPetOptionsGenerator generator;

  std::map<std::string, boost::any> emptyOptions;
  BOOST_REQUIRE(generator.transformOptions(emptyOptions).empty());

  std::string pathForCorrection = "a/b/c/d";
  std::vector<int> range = {1, 2};
  std::string inputFileType = "inputFileType";

  std::map<std::string, boost::any> optionForTransformation;
  optionForTransformation["outputPath_std::string"] = pathForCorrection;
  optionForTransformation["range_std::vector<int>"] = range;
  optionForTransformation["type_std::string"] = inputFileType;

  auto mapAfterTransformation = generator.transformOptions(optionForTransformation);
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(mapAfterTransformation.at("outputPath_std::string")), (pathForCorrection + '/'));
  BOOST_REQUIRE_EQUAL(any_cast<int>(mapAfterTransformation.at("lastEvent_int")), 2);
  BOOST_REQUIRE_EQUAL(any_cast<int>(mapAfterTransformation.at("firstEvent_int")), 1);
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(mapAfterTransformation.at("inputFileType_std::string")), inputFileType);
}

BOOST_AUTO_TEST_CASE(checkIfFunctionGetConfigFileNameWork)
{
  JPetOptionsGenerator generator;

  auto commandLine = "main.x -u example.json";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  po::options_description description("Allowed options");
  description.add_options()
    ("userCfg_std::string,u", po::value<std::string>(), "Json file with optional user parameters.");
  ;

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  BOOST_REQUIRE_EQUAL(generator.getConfigFileName(variablesMap), "example.json");

  auto commandLine2 = "main.x ";
  auto args_char2 = createArgs(commandLine2);
  auto argc2 = args_char2.size();
  auto argv2 = args_char2.data();

  po::options_description description2("Allowed options");
  description2.add_options()
    ("userCfg_std::string,u", po::value<std::string>(), "Json file with optional user parameters.");
  ;

  po::variables_map variablesMap2;
  po::store(po::parse_command_line(argc2, argv2, description2), variablesMap2);
  po::notify(variablesMap2);

  BOOST_REQUIRE_EQUAL(generator.getConfigFileName(variablesMap2), "");
}

BOOST_AUTO_TEST_CASE(checkIfFumctionToAddOptionsFromCfgFileWork)
{
  JPetOptionsGenerator generator;

  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -r 2 -r 4 -p unitTestData/JPetCmdParserTest/data.hld -i 231 -b 1 -l unitTestData/JPetCmdParserTest/input.json -L output.json -u unitTestData/JPetOptionsToolsTest/newInputTestCfg.json";
  auto args_char = createArgs(commandLine);
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
  ("userCfg_std::string,u", po::value<std::string>(), "Json file with optional user parameters.")
  ;

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  auto options = generator.variablesMapToOption(variablesMap);
  auto cfgFileName = generator.getConfigFileName(variablesMap);
  if (!cfgFileName.empty()) {
    generator.addNewOptionsFromCfgFile(cfgFileName, options);
  }
  BOOST_REQUIRE(options.count("myOption_std::string"));
  BOOST_REQUIRE(options.count("myAnotherOption_std::string"));
}

// BOOST_AUTO_TEST_CASE(checkIfFumctionToAddMissingDefaultOptionsWork)
// {
//   JPetOptionsGenerator generator;

//   auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -r 2 -r 4 -p unitTestData/JPetCmdParserTest/data.hld -i 231 -b 1 -l unitTestData/JPetCmdParserTest/input.json -L output.json";
//   auto args_char = createArgs(commandLine);
//   auto argc = args_char.size();
//   auto argv = args_char.data();

//   po::options_description description("Allowed options");
//   description.add_options()
//   ("file_std::vector<std::string>,f", po::value<std::vector<std::string>>(), "File(s) to open")
//   ("type_std::string,t", po::value<std::string>(), "type of file: hld, zip, root or scope")
//   ("range_std::vector<int>,r", po::value<std::vector<int>>(), "Range of events to process.")
//   ("param_std::string,p", po::value<std::string>(), "File with TRB numbers.")
//   ("runId_int,i", po::value<int>(), "Run id.")
//   ("progressBar_bool,b", po::bool_switch()->default_value(false), "Progress bar.")
//   ("localDB_std::string,l", po::value<std::string>(), "The file to use as the parameter database.")
//   ("localDBCreate_std::string,L", po::value<std::string>(), "Where to save the parameter database.")
//   ;

//   po::variables_map variablesMap;
//   po::store(po::parse_command_line(argc, argv, description), variablesMap);
//   po::notify(variablesMap);

//   auto options = generator.variablesMapToOption(variablesMap);
//   generator.addMissingDefaultOptions(options);
//   BOOST_REQUIRE_EQUAL(any_cast<std::string>(mapAfterTransformation.at("outputPath_std::string")), (pathForCorrection + '/'));
//   BOOST_REQUIRE_EQUAL(any_cast<int>(mapAfterTransformation.at("lastEvent_int")), 2);
// }
BOOST_AUTO_TEST_CASE(checkIfGetOptionAndIsOptionWork)
{
  std::map<std::string, boost::any> options = {
  {"firstEvent_int", -1},
  {"lastEvent_int", -1},
  {"progressBar_bool", false},
  {"runId_int", -1},
  {"unpackerConfigFile_std::string", std::string("conf_trb3.xml")},
  {"unpackerCalibFile_std::string", std::string("")}
};

  JPetOptionsGenerator generator;
  BOOST_REQUIRE(generator.isOptionSet(options, "firstEvent_int"));
  BOOST_REQUIRE(generator.isOptionSet(options, "lastEvent_int"));
  
  BOOST_REQUIRE_EQUAL(any_cast<int>(generator.getOptionValue(options, "firstEvent_int")), -1);
  BOOST_REQUIRE_EQUAL(any_cast<int>(generator.getOptionValue(options, "lastEvent_int")), -1);

}
BOOST_AUTO_TEST_SUITE_END()

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
  ("runId,i", po::value<int>(), "Run id.")
  ;

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  BOOST_REQUIRE(cmdParser.isOptionSet(variablesMap, "runId") == true);
  BOOST_REQUIRE(cmdParser.getRunNumber(variablesMap) == 231);

  auto runId = variablesMap["runId"].as<int>();
  BOOST_REQUIRE(variablesMap.size() == 1);
  BOOST_REQUIRE(variablesMap.count("runId") == 1);
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
  ("localDB,l", po::value<std::string>(), "The file to use as the parameter database.")
  ("localDBCreate,L", po::value<std::string>(), "Where to save the parameter database.")
  ("runId,i", po::value<int>(), "Run id.")
  ;

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  JPetOptionsGenerator cmdParser;
  BOOST_REQUIRE(cmdParser.isOptionSet(variablesMap, "localDB") == true);
  BOOST_REQUIRE(cmdParser.getOptionValue(variablesMap, "localDB") == std::string("input.json"));
  BOOST_REQUIRE(cmdParser.isOptionSet(variablesMap, "localDBCreate") == true);
  BOOST_REQUIRE(cmdParser.getOptionValue(variablesMap, "localDBCreate") == std::string("output.json"));

//  BOOST_REQUIRE(JPetOptionsGenerator::isOptionSet(variablesMap, "localDB") == true);
//  BOOST_REQUIRE(JPetOptionsGenerator::getLocalDBName(variablesMap) == std::string("input.json"));
//  BOOST_REQUIRE(JPetOptionsGenerator::isOptionSet(variablesMap, "localDBCreate") == true);
//  BOOST_REQUIRE(JPetOptionsGenerator::getLocalDBCreateName(variablesMap) == std::string("output.json"));
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
  ("file,f", po::value<std::vector<std::string>>(), "File(s) to open")
  ("type,t", po::value<std::string>(), "type of file: hld, zip, root or scope")
  ("range,r", po::value<std::vector<int>>(), "Range of events to process.")
  ("param,p", po::value<std::string>(), "File with TRB numbers.")
  ("runId,i", po::value<int>(), "Run id.")
  ("progressBar,b", po::bool_switch()->default_value(false), "Progress bar.")
  ("localDB,l", po::value<std::string>(), "The file to use as the parameter database.")
  ("localDBCreate,L", po::value<std::string>(), "Where to save the parameter database.")
  ;

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  BOOST_REQUIRE(cmdParser.areCorrectOptions(variablesMap));

  std::vector<JPetOptions> options = cmdParser.generateOptions(variablesMap);
  JPetOptions firstOption = options.front();

  BOOST_REQUIRE(firstOption.areCorrect(firstOption.getOptions()));
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
  ("type,t", po::value<std::string>()->required()->implicit_value(""), "Type of file: hld, zip, root or scope.")
  ("file,f", po::value< std::vector<std::string> >()->required()->multitoken(), "File(s) to open.")
  ("outputPath,o", po::value<std::string>(), "Location to which the outputFiles will be saved.")
  ("range,r", po::value< std::vector<int> >()->multitoken()->default_value({ -1, -1}, ""), "Range of events to process e.g. -r 1 1000 .")
  ("param,p", po::value<std::string>(), "xml file with TRB settings used by the unpacker program.")
  ("runId,i", po::value<int>(), "Run id.")
  ("progressBar,b", po::bool_switch()->default_value(false), "Progress bar.")
  ("localDB,l", po::value<std::string>(), "The file to use as the parameter database.")
  ("localDBCreate,L", po::value<std::string>(), "File name to which the parameter database will be saved.")
  ("userCfg,u", po::value<std::string>(), "Json file with optional user parameters.");

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);
  JPetOptionsGenerator parser;
  BOOST_REQUIRE(!parser.areCorrectOptions(variablesMap));
}

BOOST_AUTO_TEST_SUITE_END()

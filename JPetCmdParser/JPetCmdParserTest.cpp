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
 *  @file JPetCmdParserTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetCmdParserTest
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

BOOST_AUTO_TEST_CASE( parsing_1 )
{
  auto commandLine = "main.x -t hld -f unitTestData/JPetCmdParserTest/testfile.hld -i 10";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE_EQUAL(options.size(), 1);
  auto option = options.at(0);
  BOOST_REQUIRE(std::string(option.getInputFile()) == "unitTestData/JPetCmdParserTest/testfile.hld");
  BOOST_REQUIRE_EQUAL(option.getFirstEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getLastEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getRunNumber(), 10);
  BOOST_REQUIRE(!option.isProgressBar());
  BOOST_REQUIRE_EQUAL(option.getOutputPath(), "");
  BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kHld);

}

BOOST_AUTO_TEST_CASE( parsing_2 )
{
  auto commandLine = "main.x -t scope -f unitTestData/JPetCmdParserTest/testfile.json ";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE_EQUAL(options.size(), 1);
  auto option = options.at(0);
  BOOST_REQUIRE_EQUAL(std::string(option.getInputFile()), "unitTestData/JPetCmdParserTest/testfile_config1_6");
  BOOST_REQUIRE_EQUAL(std::string(option.getScopeConfigFile()), "unitTestData/JPetCmdParserTest/testfile.json");
  BOOST_REQUIRE_EQUAL(std::string(option.getScopeInputDirectory()), "unitTestData/JPetCmdParserTest/data/6");
  BOOST_REQUIRE_EQUAL(option.getFirstEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getLastEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getRunNumber(), -1);
  BOOST_REQUIRE_EQUAL(option.getOutputPath(), "");
  BOOST_REQUIRE(!option.isProgressBar());
  BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kScope);
}

BOOST_AUTO_TEST_CASE( parsing_zip_file )
{
  auto commandLine = "main.x -t zip -f unitTestData/JPetCommonToolsTest/goodZip.gz";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE_EQUAL(options.size(), 1);
  auto option = options.at(0);
  BOOST_REQUIRE(std::string(option.getInputFile()) == "unitTestData/JPetCommonToolsTest/goodZip.gz");
  BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kZip);
}

////ToDo: remake unit tests without calling private methods

BOOST_AUTO_TEST_CASE(getOptionsDescriptionTest)
{
  JPetCmdParser cmdParser;
  auto optionDescription = cmdParser.getOptionsDescription();
  //optionDescription.add
  //optionDescription.find()
  auto helpOptionDescription = optionDescription.find("help", true);
  //cout << helpOptionDescription.description() << endl;
  BOOST_REQUIRE(std::string(helpOptionDescription.description()) == "Displays this help message.");
  //cout << helpOptionDescription.format_name() << endl;
  BOOST_REQUIRE(std::string(helpOptionDescription.format_name()) == "-h [ --help ]");

  auto typeOptionDescription = optionDescription.find("type", true);
  //cout << typeOptionDescription.description() << endl;
  BOOST_REQUIRE(std::string(typeOptionDescription.description()) == "Type of file: hld, zip, root or scope.");
  //cout << typeOptionDescription.format_name() << endl;
  BOOST_REQUIRE(std::string(typeOptionDescription.format_name()) == "-t [ --type ]");

  auto fileOptionDescription = optionDescription.find("file", true);
  //cout << fileOptionDescription.description() << endl;
  BOOST_REQUIRE(std::string(fileOptionDescription.description()) == "File(s) to open.");
  //cout << fileOptionDescription.format_name() << endl;
  BOOST_REQUIRE(std::string(fileOptionDescription.format_name()) == "-f [ --file ]");

  auto rangeOptionDescription = optionDescription.find("range", true);
  //cout << rangeOptionDescription.description() << endl;
  BOOST_REQUIRE(std::string(rangeOptionDescription.description()) == "Range of events to process e.g. -r 1 1000 .");
  //cout << rangeOptionDescription.format_name() << endl;
  BOOST_REQUIRE(std::string(rangeOptionDescription.format_name()) == "-r [ --range ]");

  auto paramOptionDescription = optionDescription.find("param", true);
  //cout << paramOptionDescription.description() << endl;
  BOOST_REQUIRE(std::string(paramOptionDescription.description()) == "xml file with TRB settings used by the unpacker program.");
  //cout << paramOptionDescription.format_name() << endl;
  BOOST_REQUIRE(std::string(paramOptionDescription.format_name()) == "-p [ --param ]");

  auto runIdOptionDescription = optionDescription.find("runId", true);
  //cout << runIdOptionDescription.description() << endl;
  BOOST_REQUIRE(std::string(runIdOptionDescription.description()) == "Run id.");
  //cout << runIdOptionDescription.format_name() << endl;
  BOOST_REQUIRE(std::string(runIdOptionDescription.format_name()) == "-i [ --runId ]");

  auto progressBarOptionDescription = optionDescription.find("progressBar", true);
  //cout << progressBarOptionDescription.description() << endl;
  BOOST_REQUIRE(std::string(progressBarOptionDescription.description()) == "Progress bar.");
  //cout << progressBarOptionDescription.format_name() << endl;
  BOOST_REQUIRE(std::string(progressBarOptionDescription.format_name()) == "-b [ --progressBar ]");
}


BOOST_AUTO_TEST_CASE(parseAndGenerateOptionsTest)
{
  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -r 2 4 -p data.hld -i 231 -L output.json";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  std::vector<JPetOptions> options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));

  BOOST_REQUIRE_EQUAL(options.size(), 1);
  JPetOptions firstOption = options.front();

  BOOST_REQUIRE(firstOption.areCorrect(firstOption.getOptions()));
  BOOST_REQUIRE(strcmp(firstOption.getInputFile(), "unitTestData/JPetCmdParserTest/data.hld") == 0);
  BOOST_REQUIRE(firstOption.getInputFileType() == JPetOptions::kHld);
  BOOST_REQUIRE(firstOption.getFirstEvent() == 2);
  BOOST_REQUIRE(firstOption.getLastEvent() == 4);
  BOOST_REQUIRE(firstOption.getRunNumber() == 231);
  BOOST_REQUIRE(firstOption.isProgressBar() == false);
  BOOST_REQUIRE(firstOption.isLocalDB() == false);
  BOOST_REQUIRE(firstOption.isLocalDBCreate());
  BOOST_REQUIRE(firstOption.getLocalDBCreate() == std::string("output.json"));
}

BOOST_AUTO_TEST_CASE(parseAndGenerateOptionsDefaultValuesTest)
{
  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -i 4";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  std::vector<JPetOptions> options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));

  BOOST_REQUIRE_EQUAL(options.size(), 1);
  JPetOptions firstOption = options.front();

  BOOST_REQUIRE(firstOption.areCorrect(firstOption.getOptions()));
  BOOST_REQUIRE(strcmp(firstOption.getInputFile(), "unitTestData/JPetCmdParserTest/data.hld") == 0);
  BOOST_REQUIRE(firstOption.getInputFileType() == JPetOptions::kHld);
  BOOST_REQUIRE(firstOption.getFirstEvent() == -1);
  BOOST_REQUIRE(firstOption.getLastEvent() == -1);
  BOOST_REQUIRE(firstOption.getRunNumber() == 4);
  BOOST_REQUIRE_EQUAL(firstOption.getOutputPath(), "");
  BOOST_REQUIRE(firstOption.isProgressBar() == false);
  BOOST_REQUIRE(firstOption.isLocalDB() == false);
  BOOST_REQUIRE(firstOption.isLocalDBCreate() == false);
}

BOOST_AUTO_TEST_CASE(runNumberNotObligatoryIfHldType)
{
  auto args_char = createArgs("main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld");
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  BOOST_REQUIRE_NO_THROW(parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv)));
}

BOOST_AUTO_TEST_CASE(runNumberNotObligatoryIfScopeType)
{
  auto args_char = createArgs("main.x -t scope -f unitTestData/JPetCmdParserTest/testfile.json");
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  BOOST_REQUIRE_NO_THROW(parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv)));

  args_char = createArgs("main.x -t scope -f unitTestData/JPetCmdParserTest/testfile.json -i 10");
  argc = args_char.size();
  argv = args_char.data();

  BOOST_REQUIRE_NO_THROW(parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv)));
}


BOOST_AUTO_TEST_CASE(checkOutputPath)
{
  auto args_char = createArgs("main.x -o ./ -f unitTestData/JPetCmdParserTest/data.hld -t hld");
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  auto option = options.at(0);
  BOOST_REQUIRE_EQUAL(option.getOutputPath(), "./");
}



BOOST_AUTO_TEST_CASE(checkOptionsWithAddedFromJson)
{
  auto args_char = createArgs("main.x -o ./ -f unitTestData/JPetCmdParserTest/data.hld -t hld -u unitTestData/JPetOptionsToolsTest/inputTestCfg.json");
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  auto option = options.at(0);
  auto allOptions = option.getOptions();
  BOOST_REQUIRE_EQUAL(allOptions.count("myOption"), 1);
  BOOST_REQUIRE_EQUAL(allOptions.at("myOption"), "great");
  BOOST_REQUIRE(allOptions.count("myAnotherOption"));
  BOOST_REQUIRE_EQUAL(allOptions.at("myAnotherOption"), "wat");
  BOOST_REQUIRE(allOptions.count("boolOption"));
  BOOST_REQUIRE_EQUAL(allOptions.at("boolOption"), "true");
  BOOST_REQUIRE(allOptions.count("NumberOption"));
  BOOST_REQUIRE_EQUAL(allOptions.at("NumberOption"), "12.2");
}
BOOST_AUTO_TEST_SUITE_END()

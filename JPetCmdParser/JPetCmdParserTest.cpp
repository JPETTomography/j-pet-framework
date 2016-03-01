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
#define private public
#define protected public
#include "../JPetCmdParser/JPetCmdParser.h"
#undef private 
#undef protected
//public method
//std::vector<JPetOptions> parseAndGenerateOptions(int argc, const char** argv);

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
  BOOST_REQUIRE(std::string(option.getInputFile()) == "unitTestData/JPetCmdParserTest/testfile.json");
  BOOST_REQUIRE_EQUAL(option.getFirstEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getLastEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getRunNumber(), -1);
  BOOST_REQUIRE(!option.isProgressBar());
  BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kScope);
}
/*
  ("help,h", "produce help message")
  ("type,t", po::value<std::string>()->required(), "type of file: hld, root or scope")
  ("file,f", po::value< std::vector<std::string> >()->required()->multitoken(), "File(s) to open")
  ("range,r", po::value< std::vector<int> >()->multitoken()->default_value(tmp, ""), "Range of events to process.")
  ("param,p", po::value<std::string>(), "File with TRB numbers.")
  ("runId,i", po::value<int>(), "Run id.")
  ("progressBar,b", "Progress bar.");
*/
BOOST_AUTO_TEST_CASE(getOptionsDescriptionTest)
{
    JPetCmdParser cmdParser;
    auto optionDescription = cmdParser.getOptionsDescription();
    //optionDescription.add
    //optionDescription.find()
    auto helpOptionDescription = optionDescription.find("help", true);
    //cout << helpOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(helpOptionDescription.description()) == "produce help message");
    //cout << helpOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(helpOptionDescription.format_name()) == "-h [ --help ]");

    auto typeOptionDescription = optionDescription.find("type", true);
    //cout << typeOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(typeOptionDescription.description()) == "type of file: hld, root or scope");
    //cout << typeOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(typeOptionDescription.format_name()) == "-t [ --type ]");

    auto fileOptionDescription = optionDescription.find("file", true);
    //cout << fileOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(fileOptionDescription.description()) == "File(s) to open");
    //cout << fileOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(fileOptionDescription.format_name()) == "-f [ --file ]");

    auto rangeOptionDescription = optionDescription.find("range", true);
    //cout << rangeOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(rangeOptionDescription.description()) == "Range of events to process.");
    //cout << rangeOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(rangeOptionDescription.format_name()) == "-r [ --range ]");

    auto paramOptionDescription = optionDescription.find("param", true);
    //cout << paramOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(paramOptionDescription.description()) == "File with TRB numbers.");
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

BOOST_AUTO_TEST_CASE(fileTest)
{
    JPetCmdParser cmdParser;

    auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld";
    auto args_char = createArgs(commandLine);
    auto argc = args_char.size();
    auto argv = args_char.data();

    po::options_description description("Allowed options");
    description.add_options()
            ("file,f", po::value<std::vector<std::string>>(), "File(s) to open")
    ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);
    po::notify(variablesMap);

    auto fileNames = cmdParser.getFileNames(variablesMap);
    BOOST_REQUIRE(fileNames.size() == 1);
    BOOST_REQUIRE(fileNames.front() == "unitTestData/JPetCmdParserTest/data.hld");

    auto file = variablesMap["file"].as<std::vector<std::string>>();
    BOOST_REQUIRE(variablesMap.size() == 1);
    BOOST_REQUIRE(variablesMap.count("file") == 1);
    BOOST_REQUIRE(file.front() == "unitTestData/JPetCmdParserTest/data.hld");
}

BOOST_AUTO_TEST_CASE(fileTypeTest)
{
    JPetCmdParser cmdParser;

    auto commandLine = "main.x -t hld";
    auto args_char = createArgs(commandLine);
    auto argc = args_char.size();
    auto argv = args_char.data();

    po::options_description description("Allowed options");
    description.add_options()
            ("type,t", po::value<std::string>(), "type of file: hld, root or scope")
    ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);
    po::notify(variablesMap);

    auto fileType = variablesMap["type"].as<std::string>();

    BOOST_REQUIRE(variablesMap.size() == 1);
    BOOST_REQUIRE(variablesMap.count("type") > 0);
    BOOST_REQUIRE(fileType == "hld");
    BOOST_REQUIRE(cmdParser.isCorrectFileType(fileType));
    BOOST_REQUIRE(cmdParser.getFileType(variablesMap) == "hld");
    BOOST_REQUIRE(cmdParser.IsFileTypeSet(variablesMap));
}

BOOST_AUTO_TEST_CASE(rangeTest)
{
    JPetCmdParser cmdParser;

    auto commandLine = "main.x -r 4";
    auto args_char = createArgs(commandLine);
    auto argc = args_char.size();
    auto argv = args_char.data();

    po::options_description description("Allowed options");
    description.add_options()
            ("range,r", po::value<std::vector<int>>(), "Range of events to process.")
    ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);
    po::notify(variablesMap);

    BOOST_REQUIRE(cmdParser.getLowerEventBound(variablesMap) == 4);

    auto range = variablesMap["range"].as<std::vector<int>>();
    BOOST_REQUIRE(variablesMap.size() == 1);
    BOOST_REQUIRE(variablesMap.count("range") == 1);
    BOOST_REQUIRE(range.front() == 4);
}

BOOST_AUTO_TEST_CASE(paramTest)
{
    JPetCmdParser cmdParser;

    auto commandLine = "main.x -p unitTestData/JPetCmdParserTest/data.hld";
    auto args_char = createArgs(commandLine);
    auto argc = args_char.size();
    auto argv = args_char.data();

    po::options_description description("Allowed options");
    description.add_options()
            ("param,p", po::value<std::string>(), "File with TRB numbers.")
    ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);
    po::notify(variablesMap);

    BOOST_REQUIRE(cmdParser.isParamSet(variablesMap) == true);
    BOOST_REQUIRE(cmdParser.getParam(variablesMap) == "unitTestData/JPetCmdParserTest/data.hld");

    auto param = variablesMap["param"].as<std::string>();
    BOOST_REQUIRE(variablesMap.size() == 1);
    BOOST_REQUIRE(variablesMap.count("param") == 1);
    BOOST_REQUIRE(param == "unitTestData/JPetCmdParserTest/data.hld");
}

BOOST_AUTO_TEST_CASE(runIdTest)
{
    JPetCmdParser cmdParser;

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

    BOOST_REQUIRE(cmdParser.isRunNumberSet(variablesMap) == true);
    BOOST_REQUIRE(cmdParser.getRunNumber(variablesMap) == 231);

    auto runId = variablesMap["runId"].as<int>();
    BOOST_REQUIRE(variablesMap.size() == 1);
    BOOST_REQUIRE(variablesMap.count("runId") == 1);
    BOOST_REQUIRE(runId == 231);
}

BOOST_AUTO_TEST_CASE(progressBarTest)
{
    JPetCmdParser cmdParser;

    auto commandLine = "main.x -b 1";
    auto args_char = createArgs(commandLine);
    auto argc = args_char.size();
    auto argv = args_char.data();

    po::options_description description("Allowed options");
    description.add_options()
            ("progressBar,b", po::value<int>(), "Progress bar.")
    ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);
    po::notify(variablesMap);

    BOOST_REQUIRE(cmdParser.isProgressBarSet(variablesMap) == true);
    BOOST_REQUIRE(variablesMap.size() == 1);
    BOOST_REQUIRE(variablesMap.count("progressBar") == 1);
}

BOOST_AUTO_TEST_CASE(generateOptionsTest)
{
    JPetCmdParser cmdParser;

    auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -r 2 -r 4 -p unitTestData/JPetCmdParserTest/data.hld -i 231 -b 1";
    auto args_char = createArgs(commandLine);
    auto argc = args_char.size();
    auto argv = args_char.data();

    po::options_description description("Allowed options");
    description.add_options()
            ("file,f", po::value<std::vector<std::string>>(), "File(s) to open")
            ("type,t", po::value<std::string>(), "type of file: hld, root or scope")
            ("range,r", po::value<std::vector<int>>(), "Range of events to process.")
            ("param,p", po::value<std::string>(), "File with TRB numbers.")
            ("runId,i", po::value<int>(), "Run id.")
            ("progressBar,b", po::value<int>(), "Progress bar.")
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
    //std::cout << "PROCES =" << firstOption.getOutputFileType() << std::endl;
    //BOOST_REQUIRE(firstOption.getOutputFile() == "root");
    //BOOST_REQUIRE(firstOption.getOutputFileType() == "test.root");
    BOOST_REQUIRE(firstOption.getFirstEvent() == 2);
    BOOST_REQUIRE(firstOption.getLastEvent() == 4);
    BOOST_REQUIRE(firstOption.getRunNumber() == 231);
    BOOST_REQUIRE(firstOption.isProgressBar() == true);
}

BOOST_AUTO_TEST_CASE(parseAndGenerateOptionsTest)
{
  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -r 2 4 -p data.hld -i 231";
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
}

BOOST_AUTO_TEST_CASE(parseAndGenerateOptionsDefaultValuesTest)
{
  auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld";
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
  BOOST_REQUIRE(firstOption.getRunNumber() == -1);
  BOOST_REQUIRE(firstOption.isProgressBar() == false);
}

BOOST_AUTO_TEST_SUITE_END()

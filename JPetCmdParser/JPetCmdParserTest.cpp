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
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetCmdParser/JPetCmdParser.h"
#include "../JPetOptionsGenerator/JPetOptionsGenerator.h"
#include <boost/any.hpp>

using boost::any_cast;
using namespace std;


std::vector<JPetOptions> getOptionsBasedOnCmdLineArgs(const std::string& cmdLine)
{
  auto args_char = JPetCommonTools::createArgs(cmdLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  JPetOptionsGenerator optGenerator;
  return optGenerator.generateOptions2(parser.parseCmdLineArgs(argc, const_cast<const char**>(argv)));
}

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

//BOOST_AUTO_TEST_CASE( parsing_1 )
//{
//auto commandLine = "main.x -t hld -f unitTestData/JPetCmdParserTest/testfile.hld -i 10";
//auto options = getOptionsBasedOnCmdLineArgs(commandLine);
//BOOST_REQUIRE_EQUAL(options.size(), 1);
//auto option = options.at(0);
//BOOST_REQUIRE(std::string(option.getInputFile()) == "unitTestData/JPetCmdParserTest/testfile.hld");
//BOOST_REQUIRE_EQUAL(option.getFirstEvent(), -1);
//BOOST_REQUIRE_EQUAL(option.getLastEvent(), -1);
//BOOST_REQUIRE_EQUAL(option.getRunNumber(), 10);
//BOOST_REQUIRE(!option.isProgressBar());
//BOOST_REQUIRE_EQUAL(option.getOutputPath(), "");
//BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kHld);

//}

//BOOST_AUTO_TEST_CASE( parsing_2 )
//{
//auto commandLine = "main.x -t scope -f unitTestData/JPetCmdParserTest/testfile.json ";
//auto options = getOptionsBasedOnCmdLineArgs(commandLine);
//BOOST_REQUIRE_EQUAL(options.size(), 1);
//auto option = options.at(0);
//BOOST_REQUIRE_EQUAL(std::string(option.getInputFile()), "unitTestData/JPetCmdParserTest/testfile_config1_6");
//BOOST_REQUIRE_EQUAL(std::string(option.getScopeConfigFile()), "unitTestData/JPetCmdParserTest/testfile.json");
//BOOST_REQUIRE_EQUAL(std::string(option.getScopeInputDirectory()), "unitTestData/JPetCmdParserTest/data/6");
//BOOST_REQUIRE_EQUAL(option.getFirstEvent(), -1);
//BOOST_REQUIRE_EQUAL(option.getLastEvent(), -1);
//BOOST_REQUIRE_EQUAL(option.getRunNumber(), -1);
//BOOST_REQUIRE_EQUAL(option.getOutputPath(), "");
//BOOST_REQUIRE(!option.isProgressBar());
//BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kScope);
//}

//BOOST_AUTO_TEST_CASE( parsing_zip_file )
//{
//auto commandLine = "main.x -t zip -f unitTestData/JPetCommonToolsTest/goodZip.gz";
//auto options = getOptionsBasedOnCmdLineArgs(commandLine);
//BOOST_REQUIRE_EQUAL(options.size(), 1);
//auto option = options.at(0);
//BOOST_REQUIRE(std::string(option.getInputFile()) == "unitTestData/JPetCommonToolsTest/goodZip.gz");
//BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kZip);
//}

//BOOST_AUTO_TEST_CASE(getOptionsDescriptionTest)
//{
//JPetCmdParser cmdParser;
//auto optionDescription = cmdParser.getOptionsDescription();

//auto helpOptionDescription = optionDescription.find("help", true);

//BOOST_REQUIRE(std::string(helpOptionDescription.description()) == "Displays this help message.");

//BOOST_REQUIRE(std::string(helpOptionDescription.format_name()) == "-h [ --help ]");

//auto typeOptionDescription = optionDescription.find("type", true);
//BOOST_REQUIRE(std::string(typeOptionDescription.description()) == "Type of file: hld, zip, root or scope.");
//BOOST_REQUIRE(std::string(typeOptionDescription.format_name()) == "-t [ --type ]");

//auto fileOptionDescription = optionDescription.find("file", true);
//BOOST_REQUIRE(std::string(fileOptionDescription.description()) == "File(s) to open.");
//BOOST_REQUIRE(std::string(fileOptionDescription.format_name()) == "-f [ --file ]");

//auto rangeOptionDescription = optionDescription.find("range", true);
//BOOST_REQUIRE(std::string(rangeOptionDescription.description()) == "Range of events to process e.g. -r 1 1000 .");
//BOOST_REQUIRE(std::string(rangeOptionDescription.format_name()) == "-r [ --range ]");

//auto unpackerConfigOptionDescription = optionDescription.find("unpackerConfigFile", true);
//BOOST_REQUIRE(std::string(unpackerConfigOptionDescription.description()) == "xml file with TRB settings used by the unpacker program.");
//BOOST_REQUIRE(std::string(unpackerConfigOptionDescription.format_name()) == "-p [ --unpackerConfigFile ]");

//auto unpackerCalibOptionDescription = optionDescription.find("unpackerCalibFile", true);
//BOOST_REQUIRE(std::string(unpackerCalibOptionDescription.description()) == "ROOT file with TRB calibration used by the unpacker program.");
//BOOST_REQUIRE(std::string(unpackerCalibOptionDescription.format_name()) == "-c [ --unpackerCalibFile ]");

//auto runIdOptionDescription = optionDescription.find("runId", true);
//BOOST_REQUIRE(std::string(runIdOptionDescription.description()) == "Run id.");
//BOOST_REQUIRE(std::string(runIdOptionDescription.format_name()) == "-i [ --runId ]");

//auto progressBarOptionDescription = optionDescription.find("progressBar", true);
//BOOST_REQUIRE(std::string(progressBarOptionDescription.description()) == "Progress bar.");
//BOOST_REQUIRE(std::string(progressBarOptionDescription.format_name()) == "-b [ --progressBar ]");
//}


//BOOST_AUTO_TEST_CASE(parseAndGenerateOptionsTest)
//{
//auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -r 2 4 -p unitTestData/JPetCmdParserTest/data.hld -c unitTestData/JPetUnpackerTest/calib.root -i 231 -L output.json";
//auto options = getOptionsBasedOnCmdLineArgs(commandLine);

//BOOST_REQUIRE_EQUAL(options.size(), 1);
//JPetOptions firstOption = options.front();

//BOOST_REQUIRE(strcmp(firstOption.getInputFile(), "unitTestData/JPetCmdParserTest/data.hld") == 0);
//BOOST_REQUIRE(strcmp(firstOption.getUnpackerConfigFile(), "unitTestData/JPetCmdParserTest/data.hld") == 0);
//BOOST_REQUIRE(strcmp(firstOption.getUnpackerCalibFile(), "unitTestData/JPetUnpackerTest/calib.root") == 0);
//BOOST_REQUIRE(firstOption.getInputFileType() == JPetOptions::kHld);
//BOOST_REQUIRE(firstOption.getFirstEvent() == 2);
//BOOST_REQUIRE(firstOption.getLastEvent() == 4);
//BOOST_REQUIRE(firstOption.getRunNumber() == 231);
//BOOST_REQUIRE(firstOption.isProgressBar() == false);
//BOOST_REQUIRE(firstOption.isLocalDB() == false);
//BOOST_REQUIRE(firstOption.isLocalDBCreate());
//BOOST_REQUIRE(firstOption.getLocalDBCreate() == std::string("output.json"));
//}

//BOOST_AUTO_TEST_CASE(parseAndGenerateOptionsDefaultValuesTest)
//{
//auto commandLine = "main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld -i 4";
//auto options = getOptionsBasedOnCmdLineArgs(commandLine);

//BOOST_REQUIRE_EQUAL(options.size(), 1);
//JPetOptions firstOption = options.front();

//BOOST_REQUIRE(strcmp(firstOption.getInputFile(), "unitTestData/JPetCmdParserTest/data.hld") == 0);
//BOOST_REQUIRE(firstOption.getInputFileType() == JPetOptions::kHld);
//BOOST_REQUIRE(firstOption.getFirstEvent() == -1);
//BOOST_REQUIRE(firstOption.getLastEvent() == -1);
//BOOST_REQUIRE(firstOption.getRunNumber() == 4);
//BOOST_REQUIRE_EQUAL(firstOption.getOutputPath(), "");
//BOOST_REQUIRE(firstOption.isProgressBar() == false);
//BOOST_REQUIRE(firstOption.isLocalDB() == false);
//BOOST_REQUIRE(firstOption.isLocalDBCreate() == false);
//}

//BOOST_AUTO_TEST_CASE(runNumberNotObligatoryIfHldType)
//{
//auto args_char = JPetCommonTools::createArgs("main.x -f unitTestData/JPetCmdParserTest/data.hld -t hld");
//auto argc = args_char.size();
//auto argv = args_char.data();
//JPetCmdParser parser;
//BOOST_REQUIRE_NO_THROW(parser.parseCmdLineArgs(argc, argv));
//}

//BOOST_AUTO_TEST_CASE(runNumberNotObligatoryIfScopeType)
//{
//auto args_char = JPetCommonTools::createArgs("main.x -t scope -f unitTestData/JPetCmdParserTest/testfile.json");
//auto argc = args_char.size();
//auto argv = args_char.data();
//JPetCmdParser parser;
//BOOST_REQUIRE_NO_THROW(parser.parseCmdLineArgs(argc, argv));

//args_char = JPetCommonTools::createArgs("main.x -t scope -f unitTestData/JPetCmdParserTest/testfile.json -i 10");
//argc = args_char.size();
//argv = args_char.data();

//BOOST_REQUIRE_NO_THROW(parser.parseCmdLineArgs(argc, argv));
//}


//BOOST_AUTO_TEST_CASE(checkOutputPath)
//{
//auto commandLine = "main.x -o ./ -f unitTestData/JPetCmdParserTest/data.hld -t hld";
//auto options = getOptionsBasedOnCmdLineArgs(commandLine);
//auto option = options.at(0);
//BOOST_REQUIRE_EQUAL(option.getOutputPath(), "./");
//}



//BOOST_AUTO_TEST_CASE(checkOptionsWithAddedFromJson)
//{
//auto commandLine = "main.x -o ./ -f unitTestData/JPetCmdParserTest/data.hld -t hld -u unitTestData/JPetOptionsToolsTest/newInputTestCfg.json";
//auto options = getOptionsBasedOnCmdLineArgs(commandLine);
//auto option = options.at(0);
//auto allOptions = option.getOptions();
//BOOST_REQUIRE_EQUAL(allOptions.count("myOption_std::string"), 1);
//BOOST_REQUIRE_EQUAL(any_cast<std::string>(allOptions.at("myOption_std::string")), "great");
//BOOST_REQUIRE(allOptions.count("myAnotherOption_std::string"));
//BOOST_REQUIRE_EQUAL(any_cast<std::string>(allOptions.at("myAnotherOption_std::string")), "wat");
//BOOST_REQUIRE(allOptions.count("boolOption_bool"));
//BOOST_REQUIRE_EQUAL(any_cast<bool>(allOptions.at("boolOption_bool")), true);
//BOOST_REQUIRE(allOptions.count("NumberOption_std::string"));
//BOOST_REQUIRE_EQUAL(any_cast<std::string>(allOptions.at("NumberOption_std::string")), "12.2");
//}

BOOST_AUTO_TEST_SUITE_END()

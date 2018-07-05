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
#define BOOST_TEST_MODULE JPetOptionsGeneratorTest

#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetCmdParser/JPetCmdParser.h"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cstdlib>

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

BOOST_AUTO_TEST_CASE(generateOptions_emptyOptions)
{
  JPetOptionsGenerator gener;
  po::variables_map inArgs;
  auto opt = gener.generateAndValidateOptions(inArgs);
  auto result = gener.generateOptionsForTasks(opt, 1);
  BOOST_REQUIRE(result.empty());
  result = gener.generateOptionsForTasks(opt, -2);
  BOOST_REQUIRE(result.empty());
  result = gener.generateOptionsForTasks(opt, 0);
  BOOST_REQUIRE(result.empty());
}

BOOST_AUTO_TEST_CASE(generateOptions_oneFileOneTask)
{
  JPetOptionsGenerator gener;
  auto inArgs =  getCmdLineArgs("main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root -t root");
  auto opt = gener.generateAndValidateOptions(inArgs);
  auto result = gener.generateOptionsForTasks(opt, -2);
  BOOST_REQUIRE(result.empty());
  result = gener.generateOptionsForTasks(opt, 0);
  BOOST_REQUIRE(result.empty());
  result = gener.generateOptionsForTasks(opt, 1);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 1);
  auto it = result.begin();
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetOptionsGeneratorTest/infile.root");
  auto opts = it->second;
  BOOST_REQUIRE_EQUAL(getRunNumber(opts),  231);
  BOOST_REQUIRE_EQUAL(getInputFile(opts), "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts), FileTypeChecker::kRoot);
}

BOOST_AUTO_TEST_CASE(generateOptions_oneFileTwoTasks)
{
  JPetOptionsGenerator gener;
  auto inArgs =  getCmdLineArgs("main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root -t root");
  auto opt = gener.generateAndValidateOptions(inArgs);
  auto result = gener.generateOptionsForTasks(opt, 2);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 1);
  BOOST_REQUIRE_EQUAL(result.begin()->first, "unitTestData/JPetOptionsGeneratorTest/infile.root");
}

BOOST_AUTO_TEST_CASE(generateOptions_TwoFilesOneTasks)
{
  JPetOptionsGenerator gener;
  auto inArgs =  getCmdLineArgs("main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root unitTestData/JPetOptionsGeneratorTest/infile2.root -t root");
  auto opt = gener.generateAndValidateOptions(inArgs);
  auto result = gener.generateOptionsForTasks(opt, 1);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 2u);
  auto it = result.begin();
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetOptionsGeneratorTest/infile.root");
  auto opts = it->second;
  BOOST_REQUIRE_EQUAL(getRunNumber(opts),  231);
  BOOST_REQUIRE_EQUAL(getInputFile(opts), "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts), FileTypeChecker::kRoot);
  BOOST_REQUIRE_EQUAL(getFirstEvent(opts),  -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(opts),   -1);
  BOOST_REQUIRE(!isProgressBar(opts));
  BOOST_REQUIRE(!isLocalDB(opts) );
  BOOST_REQUIRE(!isLocalDBCreate(opts));
  it++;
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetOptionsGeneratorTest/infile2.root");
  opts = it->second;
  BOOST_REQUIRE_EQUAL(getRunNumber(opts),  231);
  BOOST_REQUIRE_EQUAL(getInputFile(opts), "unitTestData/JPetOptionsGeneratorTest/infile2.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts), FileTypeChecker::kRoot);
  BOOST_REQUIRE_EQUAL(getFirstEvent(opts),  -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(opts),   -1);
  BOOST_REQUIRE(!isProgressBar(opts));
  BOOST_REQUIRE(!isLocalDB(opts) );
  BOOST_REQUIRE(!isLocalDBCreate(opts));
}

BOOST_AUTO_TEST_CASE(generateOptions_oneFileTwoTasksWithOutput)
{
  JPetOptionsGenerator gener;
  auto inArgs =  getCmdLineArgs("main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root -t root -o unitTestData/JPetCmdParserTest/ -r 2 100");
  auto opt = gener.generateAndValidateOptions(inArgs);
  auto result = gener.generateOptionsForTasks(opt, 2);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 1);
  auto it = result.begin();
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetOptionsGeneratorTest/infile.root");
  auto opts = it->second;
  BOOST_REQUIRE_EQUAL(getRunNumber(opts),  231);
  BOOST_REQUIRE_EQUAL(getInputFile(opts), "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts), FileTypeChecker::kRoot);
  BOOST_REQUIRE_EQUAL(getOutputPath(opts), "unitTestData/JPetCmdParserTest/");
  BOOST_REQUIRE_EQUAL(getFirstEvent(opts),  2);
  BOOST_REQUIRE_EQUAL(getLastEvent(opts),   100);
  BOOST_REQUIRE(!isProgressBar(opts));
  BOOST_REQUIRE(!isLocalDB(opts) );
  BOOST_REQUIRE(!isLocalDBCreate(opts));
}

BOOST_AUTO_TEST_CASE(generateOptions_TestWithUserOptions)
{
  JPetOptionsGenerator generator;
  auto commandLine = "main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root -t root -u unitTestData/JPetOptionsToolsTest/newInputTestCfg.json" ;
  auto inArgs =  getCmdLineArgs(commandLine);
  auto opt = generator.generateAndValidateOptions(inArgs);
  auto result = generator.generateOptionsForTasks(opt, 1);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 1);
  auto it = result.begin();
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetOptionsGeneratorTest/infile.root");
  auto opts = it->second;
  BOOST_REQUIRE(!opts.empty());
  BOOST_REQUIRE_EQUAL(getRunNumber(opts),  231);
  BOOST_REQUIRE_EQUAL(getInputFiles(opts).size(), 1);
  BOOST_REQUIRE_EQUAL(getInputFiles(opts).at(0), "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts), FileTypeChecker::kRoot);
  BOOST_REQUIRE_EQUAL(getFirstEvent(opts),  -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(opts),   -1);
  BOOST_REQUIRE(!isProgressBar(opts));
  BOOST_REQUIRE(!isLocalDB(opts) );
  BOOST_REQUIRE(!isLocalDBCreate(opts));
  BOOST_REQUIRE(isOptionSet(opts, "myOption_std::string"));
  BOOST_REQUIRE_EQUAL(getOptionAsString(opts, "myOption_std::string"), "great" );
  BOOST_REQUIRE(isOptionSet(opts, "myAnotherOption_std::string"));
  BOOST_REQUIRE_EQUAL(getOptionAsString(opts, "myAnotherOption_std::string"), "wat");
  BOOST_REQUIRE(isOptionSet(opts, "intOption_int"));
  BOOST_REQUIRE_EQUAL(getOptionAsInt(opts, "intOption_int"), 123);
  BOOST_REQUIRE(isOptionSet(opts, "boolOption_bool"));
}

BOOST_AUTO_TEST_CASE(ScopeOptions)
{
  JPetOptionsGenerator gener;
  auto inArgs =  getCmdLineArgs("main.exe  -t scope -f unitTestData/JPetScopeLoaderTest/test_file.json -l unitTestData/JPetScopeLoaderTest/test_params.json -i 1");
  auto opt = gener.generateAndValidateOptions(inArgs);
  auto result = gener.generateOptionsForTasks(opt, 1);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 1u);
  auto it = result.begin();
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetScopeLoaderTest/test_file_test_0");
  auto opts = it->second;
  BOOST_REQUIRE_EQUAL(getRunNumber(opts), 1);
  BOOST_REQUIRE_EQUAL(getInputFile(opts), "unitTestData/JPetScopeLoaderTest/test_file_test_0");
  BOOST_REQUIRE_EQUAL(getScopeConfigFile(opts), "unitTestData/JPetScopeLoaderTest/test_file.json");
  BOOST_REQUIRE_EQUAL(getScopeInputDirectory(opts), "unitTestData/JPetScopeLoaderTest/scope_files/0");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts), FileTypeChecker::kScope);
  BOOST_REQUIRE_EQUAL(getFirstEvent(opts), -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(opts), -1);
  BOOST_REQUIRE(!isProgressBar(opts));
  BOOST_REQUIRE(isLocalDB(opts));
  BOOST_REQUIRE(!isLocalDBCreate(opts));
}

BOOST_AUTO_TEST_CASE(generateAndValidateOptions_emptyOptions)
{
  JPetOptionsGenerator gener;
  po::variables_map inArgs;
  auto result = gener.generateAndValidateOptions(inArgs);
  BOOST_REQUIRE(result.empty());
}

BOOST_AUTO_TEST_CASE(generateAndValidateOptions_Test)
{
  JPetOptionsGenerator gener;
  auto inArgs =  getCmdLineArgs("main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root -t root");
  auto result = gener.generateAndValidateOptions(inArgs);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(getRunNumber(result),  231);
  BOOST_REQUIRE_EQUAL(getInputFiles(result).size(), 1);
  BOOST_REQUIRE_EQUAL(getInputFiles(result).at(0), "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(result), FileTypeChecker::kRoot);
  BOOST_REQUIRE_EQUAL(getFirstEvent(result), -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(result), -1);
  BOOST_REQUIRE(!isProgressBar(result));
  BOOST_REQUIRE(!isLocalDB(result) );
  BOOST_REQUIRE(!isLocalDBCreate(result));
}

BOOST_AUTO_TEST_CASE(generateAndValidateOptions_TestWithUserOptions)
{
  JPetOptionsGenerator generator;
  auto commandLine = "main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root -t root -u unitTestData/JPetOptionsToolsTest/newInputTestCfg.json" ;
  auto inArgs =  getCmdLineArgs(commandLine);
  auto result = generator.generateAndValidateOptions(inArgs);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(getRunNumber(result),  231);
  BOOST_REQUIRE_EQUAL(getInputFiles(result).size(), 1);
  BOOST_REQUIRE_EQUAL(getInputFiles(result).at(0), "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(result), FileTypeChecker::kRoot);
  BOOST_REQUIRE_EQUAL(getFirstEvent(result), -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(result), -1);
  BOOST_REQUIRE(!isProgressBar(result));
  BOOST_REQUIRE(!isLocalDB(result));
  BOOST_REQUIRE(!isLocalDBCreate(result));
  BOOST_REQUIRE(isOptionSet(result, "myOption_std::string"));
  BOOST_REQUIRE_EQUAL(getOptionAsString(result, "myOption_std::string"), "great");
  BOOST_REQUIRE(isOptionSet(result, "myAnotherOption_std::string"));
  BOOST_REQUIRE_EQUAL(getOptionAsString(result, "myAnotherOption_std::string"), "wat");
  BOOST_REQUIRE(isOptionSet(result, "intOption_int"));
  BOOST_REQUIRE_EQUAL(getOptionAsInt(result, "intOption_int"), 123);
  BOOST_REQUIRE(isOptionSet(result, "boolOption_bool"));
}

struct MyFixture {
  MyFixture()
  {
    fInputFile = "dabc_17025151847.hld.root";
    std::ofstream outfile (fInputFile);
    outfile.close();
  }
  ~MyFixture()
  {
    boost::filesystem::remove(fInputFile);
  }
  std::string fInputFile;
};

BOOST_FIXTURE_TEST_CASE(generateAndValidateOptions_roothld, MyFixture)
{
  JPetOptionsGenerator gener;
  auto inArgs =  getCmdLineArgs("./LargeBarrelAnalysisExtended.x -t root -f dabc_17025151847.hld.root");
  auto result = gener.generateAndValidateOptions(inArgs);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(getRunNumber(result), -1);
  BOOST_REQUIRE_EQUAL(getInputFiles(result).size(), 1);
  BOOST_REQUIRE_EQUAL(getInputFiles(result).at(0), "dabc_17025151847.hld.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(result), FileTypeChecker::kHldRoot);
  BOOST_REQUIRE_EQUAL(getFirstEvent(result), -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(result), -1);
  BOOST_REQUIRE(!isProgressBar(result));
  BOOST_REQUIRE(!isLocalDB(result));
  BOOST_REQUIRE(!isLocalDBCreate(result));
}

BOOST_AUTO_TEST_SUITE_END()

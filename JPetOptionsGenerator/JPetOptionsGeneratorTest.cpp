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
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "../JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include <iostream>
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

/// @todo add infile.root and infile2.root files to sphinx
BOOST_AUTO_TEST_CASE(generateOptions_oneFileOneTask)
{
  JPetOptionsGenerator gener;
  auto inArgs =  getCmdLineArgs("main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root -t root");
  auto opt = gener.generateAndValidateOptions(inArgs);

/// bad second arg
  auto result = gener.generateOptionsForTasks(opt, -2);
  BOOST_REQUIRE(result.empty());
  result = gener.generateOptionsForTasks(opt, 0);
  BOOST_REQUIRE(result.empty());

/// one in file one task
  result = gener.generateOptionsForTasks(opt, 1);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 1); //one file
  auto it = result.begin();
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(it->second.size(), 1u); // one task
  auto itTaskOpts = it->second.begin(); //get options for this one task
  auto opts = *itTaskOpts;
  BOOST_REQUIRE_EQUAL(getRunNumber(opts),  231);
  BOOST_REQUIRE_EQUAL(getInputFile(opts), "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts), FileTypeChecker::kRoot);
}

BOOST_AUTO_TEST_CASE(generateOptions_oneFileTwoTasks)
{
  JPetOptionsGenerator gener;
  auto inArgs =  getCmdLineArgs("main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root -t root");

/// one in file two task
  auto opt = gener.generateAndValidateOptions(inArgs);
  auto result = gener.generateOptionsForTasks(opt, 2);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 1); //one file
  BOOST_REQUIRE_EQUAL(result.begin()->first, "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(result.begin()->second.size(), 2u); // two tasks
}

BOOST_AUTO_TEST_CASE(generateOptions_TwoFilesOneTasks)
{
  JPetOptionsGenerator gener;
  auto inArgs =  getCmdLineArgs("main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root unitTestData/JPetOptionsGeneratorTest/infile2.root -t root");
/// one in file two tasks
  auto opt = gener.generateAndValidateOptions(inArgs);
  auto result = gener.generateOptionsForTasks(opt, 1);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 2u); //two files

  auto it = result.begin(); //first file
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(it->second.size(), 1u); // one tasks
  auto itTaskOpts = it->second.begin();
  auto opts = *itTaskOpts; //get option for first task
  BOOST_REQUIRE_EQUAL(getRunNumber(opts),  231);
  BOOST_REQUIRE_EQUAL(getInputFile(opts), "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts), FileTypeChecker::kRoot);
  BOOST_REQUIRE_EQUAL(getFirstEvent(opts),  -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(opts),   -1);
  BOOST_REQUIRE(!isProgressBar(opts));
  BOOST_REQUIRE(!isLocalDB(opts) );
  BOOST_REQUIRE(!isLocalDBCreate(opts));

  it++; //second file
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetOptionsGeneratorTest/infile2.root");
  BOOST_REQUIRE_EQUAL(it->second.size(), 1u);
  itTaskOpts = it->second.begin();
  opts = *itTaskOpts; //get option for first task of second file
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

/// one in file two task
  auto opt = gener.generateAndValidateOptions(inArgs);
  auto result = gener.generateOptionsForTasks(opt, 2);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 1); //one file
  auto it = result.begin();
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(it->second.size(), 2u); // two tasks
  auto itTaskOpts = it->second.begin();
  auto opts = *itTaskOpts; //get option for first task
  BOOST_REQUIRE_EQUAL(getRunNumber(opts),  231);
  BOOST_REQUIRE_EQUAL(getInputFile(opts), "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts), FileTypeChecker::kRoot);
  BOOST_REQUIRE_EQUAL(getOutputPath(opts), "unitTestData/JPetCmdParserTest/");
  BOOST_REQUIRE_EQUAL(getFirstEvent(opts),  2);
  BOOST_REQUIRE_EQUAL(getLastEvent(opts),   100);
  BOOST_REQUIRE(!isProgressBar(opts));
  BOOST_REQUIRE(!isLocalDB(opts) );
  BOOST_REQUIRE(!isLocalDBCreate(opts));
  itTaskOpts++;
  opts["resetEventRange_bool"] = true; ///to reset event number
  auto opts2 = *itTaskOpts; //get option for second task
  opts2 = generateOptionsForTask(opts2, opts);
  BOOST_REQUIRE_EQUAL(getRunNumber(opts2),  231);
  BOOST_REQUIRE_EQUAL(getInputFile(opts2), "unitTestData/JPetCmdParserTest/infile.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts2), FileTypeChecker::kRoot);
  BOOST_REQUIRE_EQUAL(getOutputPath(opts2), "unitTestData/JPetCmdParserTest/");
  BOOST_REQUIRE_EQUAL(getFirstEvent(opts2),  -1); /// second task has event numbers reset
  BOOST_REQUIRE_EQUAL(getLastEvent(opts2),   -1);
  BOOST_REQUIRE(!isProgressBar(opts2));
  BOOST_REQUIRE(!isLocalDB(opts2) );
  BOOST_REQUIRE(!isLocalDBCreate(opts2));
}

BOOST_AUTO_TEST_CASE(generateOptions_TestWithUserOptions)
{
  JPetOptionsGenerator generator;

  auto commandLine = "main.x -i 231 -f unitTestData/JPetOptionsGeneratorTest/infile.root -t root -u unitTestData/JPetOptionsToolsTest/newInputTestCfg.json" ;
  auto inArgs =  getCmdLineArgs(commandLine);
  auto opt = generator.generateAndValidateOptions(inArgs);
  auto result = generator.generateOptionsForTasks(opt, 1);
  BOOST_REQUIRE(!result.empty());
  BOOST_REQUIRE_EQUAL(result.size(), 1); //one file
  auto it = result.begin();
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetOptionsGeneratorTest/infile.root");
  BOOST_REQUIRE_EQUAL(it->second.size(), 1u); // one task
  auto itTaskOpts = it->second.begin();
  auto opts = *itTaskOpts; //get option for first task

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
  BOOST_REQUIRE_EQUAL(result.size(), 1u); //one file

  auto it = result.begin();
  BOOST_REQUIRE_EQUAL(it->first, "unitTestData/JPetScopeLoaderTest/test_file_test_0");  ///fake input file
  BOOST_REQUIRE_EQUAL(it->second.size(), 1u); // one tasks
  auto itTaskOpts = it->second.begin();
  auto opts = *itTaskOpts; //get option for first task
  BOOST_REQUIRE_EQUAL(getRunNumber(opts),  1);
  BOOST_REQUIRE_EQUAL(getInputFile(opts), "unitTestData/JPetScopeLoaderTest/test_file_test_0"); /// fake input file
  BOOST_REQUIRE_EQUAL(getScopeConfigFile(opts), "unitTestData/JPetScopeLoaderTest/test_file.json");
  BOOST_REQUIRE_EQUAL(getScopeInputDirectory(opts), "unitTestData/JPetScopeLoaderTest/scope_files/0");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(opts), FileTypeChecker::kScope);
  BOOST_REQUIRE_EQUAL(getFirstEvent(opts),  -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(opts),   -1);
  BOOST_REQUIRE(!isProgressBar(opts));
  BOOST_REQUIRE(isLocalDB(opts) );
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

  BOOST_REQUIRE_EQUAL(getFirstEvent(result),  -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(result),   -1);
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

  BOOST_REQUIRE_EQUAL(getFirstEvent(result),  -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(result),   -1);
  BOOST_REQUIRE(!isProgressBar(result));
  BOOST_REQUIRE(!isLocalDB(result) );
  BOOST_REQUIRE(!isLocalDBCreate(result));

  BOOST_REQUIRE(isOptionSet(result, "myOption_std::string"));
  BOOST_REQUIRE_EQUAL(getOptionAsString(result, "myOption_std::string"), "great" );

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
    /// create empty file for tests
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
  BOOST_REQUIRE_EQUAL(getRunNumber(result),  -1);
  BOOST_REQUIRE_EQUAL(getInputFiles(result).size(), 1);
  BOOST_REQUIRE_EQUAL(getInputFiles(result).at(0), "dabc_17025151847.hld.root");
  BOOST_REQUIRE_EQUAL(FileTypeChecker::getInputFileType(result), FileTypeChecker::kHldRoot);

  BOOST_REQUIRE_EQUAL(getFirstEvent(result),  -1);
  BOOST_REQUIRE_EQUAL(getLastEvent(result),   -1);
  BOOST_REQUIRE(!isProgressBar(result));
  BOOST_REQUIRE(!isLocalDB(result) );
  BOOST_REQUIRE(!isLocalDBCreate(result));
}

BOOST_AUTO_TEST_SUITE_END()

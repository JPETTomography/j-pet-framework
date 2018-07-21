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
 *  @file JPetParamBankHandlerTaskTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamBankHandlerTask

#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "./JPetParamBankHandlerTask.h"
#include "./JPetParams/JPetParams.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(goodRootFile)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["runId_int"] = -1;
  options["inputFileType_std::string"] = std::string("root");
  options["inputFile_std::string"] = std::string(
                                       "unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root"
                                     );
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>();
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(!bank2.isDummy());
}

BOOST_AUTO_TEST_CASE(badRootFile)
{
  gErrorIgnoreLevel = kFatal; /// To turn off ROOT error reporting.
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["runId_int"] = -1;
  options["inputFileType_std::string"] = std::string("root");
  options["inputFile_std::string"] = std::string("unitTestData/auxdata.root");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>();
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(!task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(bank2.isDummy());
  gErrorIgnoreLevel = kPrint; /// Turning back the ROOT error reporting.
}

BOOST_AUTO_TEST_CASE(badHldFile)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["inputFileType_std::string"] = std::string("hld");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>();
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(!task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(bank2.isDummy());
}

BOOST_AUTO_TEST_CASE(goodUnknownFileFromFile)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["inputFile_std::string"] = std::string("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root");
  options["inputFileType_std::string"] = std::string("unknown");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>();
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(!bank2.isDummy());
}

BOOST_AUTO_TEST_CASE(badUnknownFileFromFile)
{
  gErrorIgnoreLevel = kFatal; /// To turn off ROOT error reporting.
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["inputFile_std::string"] = std::string("unitTestData/auxdata.root");
  options["inputFileType_std::string"] = std::string("unknown");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>();
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(!task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(bank2.isDummy());
  gErrorIgnoreLevel = kPrint; /// Turning back the ROOT error reporting.
}

BOOST_AUTO_TEST_CASE(goodUnknownFileFromConfig)
{
  gErrorIgnoreLevel = kFatal; /// To turn off ROOT error reporting.
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["runId_int"] = 44;
  options["localDB_std::string"] = std::string("unitTestData/JPetParamBankHandlerTask/large_barrel.json");
  options["inputFile_std::string"] = std::string("unitTestData/auxdata.root");
  options["inputFileType_std::string"] = std::string("unknown");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>(new JPetParamGetterAscii("unitTestData/JPetParamBankHandlerTask/large_barrel.json"));
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(!bank2.isDummy());
  gErrorIgnoreLevel = kPrint; /// Turning back the ROOT error reporting.
}

BOOST_AUTO_TEST_CASE(badUnknownFileFromConfig)
{
  gErrorIgnoreLevel = kFatal; /// To turn off ROOT error reporting.
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["runId_int"] = 1;
  options["localDB_std::string"] = std::string(
                                     "unitTestData/JPetParamBankHandlerTask/large_barrel.json"
                                   );
  options["inputFile_std::string"] = std::string("unitTestData/auxdata.root");
  options["inputFileType_std::string"] = std::string("unknown");
  std::shared_ptr<JPetParamManager> manager =
    std::make_shared<JPetParamManager>(new JPetParamGetterAscii(
                                         "unitTestData/JPetParamBankHandlerTask/large_barrel.json")
                                      );
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(!bank2.isDummy());
  gErrorIgnoreLevel = kPrint; /// Turning back the ROOT error reporting.
}

BOOST_AUTO_TEST_CASE(goodHldFile)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["runId_int"] = 44;
  options["localDB_std::string"] = std::string(
                                     "unitTestData/JPetParamBankHandlerTask/large_barrel.json"
                                   );
  options["inputFileType_std::string"] = std::string("hld");
  std::shared_ptr<JPetParamManager> manager =
    std::make_shared<JPetParamManager>(new JPetParamGetterAscii(
                                         "unitTestData/JPetParamBankHandlerTask/large_barrel.json")
                                      );
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(!bank2.isDummy());
}

BOOST_AUTO_TEST_SUITE_END()

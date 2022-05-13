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
 *  @file JPetTaskIOLoopPerSubTaskTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskIOTest

#include "JPetTaskIOLoopPerSubTask/JPetTaskIOLoopPerSubTask.h"
#include "JPetCmdParser/JPetCmdParser.h"
#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetDataInterface/JPetDataInterface.h"
#include "JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "JPetUserTask/JPetUserTask.h"

#include <boost/test/unit_test.hpp>

class JPetTaskTest : public JPetUserTask
{
public:
  explicit JPetTaskTest(const char* name) : JPetUserTask(name) {}
  virtual ~JPetTaskTest() { ; }

protected:
  bool init() { return true; }
  bool exec() { return true; }
  bool terminate() { return true; }
};

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(progressBarTest)
{
  JPetTaskIOLoopPerSubTask taskIOLoopPerSubTask;
  taskIOLoopPerSubTask.displayProgressBar("Test task", 5, 100);
}

BOOST_AUTO_TEST_CASE(No_output_no_input)
{
  auto opts = jpet_options_generator_tools::getDefaultOptions();
  JPetParams params(opts, nullptr);
  JPetTaskIOLoopPerSubTask taskIOLoopPerSubTask("myTestIOLoopPerSubTask", "", "");
  taskIOLoopPerSubTask.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask"));
  BOOST_REQUIRE(taskIOLoopPerSubTask.init(params));
  JPetDataInterface pseudoData;
  BOOST_REQUIRE(taskIOLoopPerSubTask.run(pseudoData));
  BOOST_REQUIRE(taskIOLoopPerSubTask.terminate(params));
}

BOOST_AUTO_TEST_CASE(No_output_bad_input)
{
  gErrorIgnoreLevel = kFatal; /// To turn off ROOT error reporting.
  auto opts = jpet_options_generator_tools::getDefaultOptions();
  JPetParams params(opts, nullptr);
  JPetTaskIOLoopPerSubTask taskIOLoopPerSubTask("myTestIOLoopPerSubTask", "bla", "");
  taskIOLoopPerSubTask.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask"));
  BOOST_REQUIRE(!taskIOLoopPerSubTask.init(params));
  JPetDataInterface pseudoData;
  BOOST_REQUIRE(!taskIOLoopPerSubTask.run(pseudoData));
  BOOST_REQUIRE(taskIOLoopPerSubTask.terminate(params)); /// terminate returns true!
  gErrorIgnoreLevel = kPrint;                            /// Turning back the ROOT error reporting.
}

BOOST_AUTO_TEST_CASE(No_input_bad_output)
{
  gErrorIgnoreLevel = kFatal; /// To turn off ROOT error reporting.
  auto opts = jpet_options_generator_tools::getDefaultOptions();
  JPetParams params(opts, nullptr);
  JPetTaskIOLoopPerSubTask taskIOLoopPerSubTask("myTestIOLoopPerSubTask", "", "bla");
  taskIOLoopPerSubTask.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask"));
  BOOST_REQUIRE(!taskIOLoopPerSubTask.init(params));
  JPetDataInterface pseudoData;
  BOOST_REQUIRE(taskIOLoopPerSubTask.run(pseudoData)); /// run returns true!
  BOOST_REQUIRE(!taskIOLoopPerSubTask.terminate(params));
  gErrorIgnoreLevel = kPrint; /// Turning back the ROOT error reporting.
}

BOOST_AUTO_TEST_CASE(bad_input_bad_output)
{
  gErrorIgnoreLevel = kFatal; /// To turn off ROOT error reporting.
  auto opts = jpet_options_generator_tools::getDefaultOptions();
  JPetParams params(opts, nullptr);
  JPetTaskIOLoopPerSubTask taskIOLoopPerSubTask("myTestIOLoopPerSubTask", "", "bla");
  taskIOLoopPerSubTask.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask"));
  BOOST_REQUIRE(!taskIOLoopPerSubTask.init(params));
  JPetDataInterface pseudoData;
  BOOST_REQUIRE(taskIOLoopPerSubTask.run(pseudoData)); /// run returns true!
  BOOST_REQUIRE(!taskIOLoopPerSubTask.terminate(params));
  gErrorIgnoreLevel = kPrint; /// Turning back the ROOT error reporting.
}

BOOST_AUTO_TEST_SUITE_END()

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
 *  @file JPetTaskIOTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskIOTest

#include "./JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "./JPetCmdParser/JPetCmdParser.h"
#include "./JPetTaskIO/JPetTaskIO.h"
#include "./JPetUserTask/JPetUserTask.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetDataInterface/JPetDataInterface.h"
#include <boost/test/unit_test.hpp>

class JPetTaskTest: public JPetUserTask
{
public:
  explicit JPetTaskTest(const char* name): JPetUserTask(name) {}
  virtual ~JPetTaskTest()
  {
    ;
  }

protected:
  bool init()
  {
    return true;
  }
  bool exec()
  {
    return true;
  }
  bool terminate()
  {
    return true;
  }
};

BOOST_AUTO_TEST_SUITE( FirstSuite )

BOOST_AUTO_TEST_CASE(progressBarTest)
{
  JPetTaskIO taskIO;
  taskIO.displayProgressBar(5, 100);
}

BOOST_AUTO_TEST_CASE(No_output_no_input )
{
  auto opts = jpet_options_generator_tools::getDefaultOptions();
  JPetParams params(opts, nullptr);
  JPetTaskIO taskIO("myTestIO", "", "");
  taskIO.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask"));
  BOOST_REQUIRE(taskIO.init(params));
  JPetDataInterface pseudoData;
  BOOST_REQUIRE(taskIO.run(pseudoData));
  BOOST_REQUIRE(taskIO.terminate(params));
}

BOOST_AUTO_TEST_CASE(No_output_bad_input)
{
  gErrorIgnoreLevel = kFatal; /// To turn off ROOT error reporting.
  auto opts = jpet_options_generator_tools::getDefaultOptions();
  JPetParams params(opts, nullptr);
  JPetTaskIO taskIO("myTestIO", "bla", "");
  taskIO.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask"));
  BOOST_REQUIRE(!taskIO.init(params));
  JPetDataInterface pseudoData;
  BOOST_REQUIRE(!taskIO.run(pseudoData));
  BOOST_REQUIRE(taskIO.terminate(params)); /// terminate returns true!
  gErrorIgnoreLevel = kPrint; /// Turning back the ROOT error reporting.
}

BOOST_AUTO_TEST_CASE(No_input_bad_output)
{
  gErrorIgnoreLevel = kFatal; /// To turn off ROOT error reporting.
  auto opts = jpet_options_generator_tools::getDefaultOptions();
  JPetParams params(opts, nullptr);
  JPetTaskIO taskIO("myTestIO", "", "bla");
  taskIO.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask"));
  BOOST_REQUIRE(!taskIO.init(params));
  JPetDataInterface pseudoData;
  BOOST_REQUIRE(taskIO.run(pseudoData));  /// run returns true!
  BOOST_REQUIRE(!taskIO.terminate(params));
  gErrorIgnoreLevel = kPrint; /// Turning back the ROOT error reporting.
}

BOOST_AUTO_TEST_CASE(bad_input_bad_output)
{
  gErrorIgnoreLevel = kFatal; /// To turn off ROOT error reporting.
  auto opts = jpet_options_generator_tools::getDefaultOptions();
  JPetParams params(opts, nullptr);
  JPetTaskIO taskIO("myTestIO", "", "bla");
  taskIO.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask"));
  BOOST_REQUIRE(!taskIO.init(params));
  JPetDataInterface pseudoData;
  BOOST_REQUIRE(taskIO.run(pseudoData));  /// run returns true!
  BOOST_REQUIRE(!taskIO.terminate(params));
  gErrorIgnoreLevel = kPrint; /// Turning back the ROOT error reporting.
}

BOOST_AUTO_TEST_SUITE_END()

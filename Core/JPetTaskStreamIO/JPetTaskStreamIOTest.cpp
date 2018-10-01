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
 *  @file JPetTaskStreamIOTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskStreamIOTest

#include "./JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "./JPetCmdParser/JPetCmdParser.h"
#include "./JPetTaskStreamIO/JPetTaskStreamIO.h"
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
    fOutputEvents = new JPetTimeWindow("JPetSigCh");
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

class JPetTaskWrongInit: public JPetUserTask
{
public:
  explicit JPetTaskWrongInit(const char* name): JPetUserTask(name) {}
  virtual ~JPetTaskWrongInit()
  {
    ;
  }

protected:
  bool init()
  {
    fOutputEvents = new JPetTimeWindow("JPetSigCh");
    return false;
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

BOOST_AUTO_TEST_CASE(Run_ok)
{
  auto opts = jpet_options_generator_tools::getDefaultOptions();
  opts["inputFile_std::string"] = std::string("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root");
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager);
  JPetParams params(opts, mgr);
  JPetTaskStreamIO taskStreamIO("myTestIO", "unk.evt", "out");
  taskStreamIO.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask1"));
  taskStreamIO.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask2"));
  taskStreamIO.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask3"));
  BOOST_REQUIRE(taskStreamIO.init(params));
  JPetDataInterface pseudoData;
  BOOST_REQUIRE(taskStreamIO.run(pseudoData));
  BOOST_REQUIRE(taskStreamIO.terminate(params));
}

BOOST_AUTO_TEST_CASE(Any_subtask_init_failed)
{
  auto opts = jpet_options_generator_tools::getDefaultOptions();
  opts["inputFile_std::string"] = std::string("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root");
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager);
  JPetParams params(opts, mgr);
  JPetTaskStreamIO taskStreamIO("myTestIO", "unk.evt", "out");
  taskStreamIO.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask1"));
  taskStreamIO.addSubTask(jpet_common_tools::make_unique<JPetTaskWrongInit>("testTask2"));
  taskStreamIO.addSubTask(jpet_common_tools::make_unique<JPetTaskTest>("testTask3"));
  BOOST_REQUIRE(taskStreamIO.init(params));
  JPetDataInterface pseudoData;
  BOOST_REQUIRE(!taskStreamIO.run(pseudoData));
}

BOOST_AUTO_TEST_SUITE_END()

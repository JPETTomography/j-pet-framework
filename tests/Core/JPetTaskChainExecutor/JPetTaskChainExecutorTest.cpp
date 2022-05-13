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
 *  @file JPetTaskChainExecutorTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskChainExecutorTest

#include "JPetTaskChainExecutor/JPetTaskChainExecutor.h"
#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetLoggerInclude.h"
#include "JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "JPetTaskIO/JPetTaskIO.h"
#include "JPetTaskIOLoopPerSubTask/JPetTaskIOLoopPerSubTask.h"
#include "JPetUserTask/JPetUserTask.h"

#include <boost/test/unit_test.hpp>

class TestTask : public JPetUserTask
{
public:
  explicit TestTask(const char* name = "") : JPetUserTask(name) {}
  bool init() override
  {
    fOutputEvents = new JPetTimeWindow("JPetEvent");
    return true;
  }
  bool exec() override
  {
    fOutputEvents = dynamic_cast<JPetTimeWindow*>(fEvent);
    return true;
  }
  bool terminate() override { return true; }
};

BOOST_AUTO_TEST_SUITE(JPetTaskChainExecutorTestSuite)

BOOST_AUTO_TEST_CASE(test0)
{
  // TODO restore tests with files with new structures
}

BOOST_AUTO_TEST_CASE(test1)
{
  auto opt = jpet_options_generator_tools::getDefaultOptions();
  opt["inputFile_std::string"] = std::string("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root");
  opt["inputFileType_std::string"] = std::string("root");
  opt["outputFile_std::string"] = std::string("JPetTaskChainExecutorTest1.root");
  auto taskGenerator1 = []() { return jpet_common_tools::make_unique<JPetTaskIOLoopPerSubTask>("test1", "unk.evt", "test.file"); };
  TaskGeneratorChain chain;
  chain.push_back(taskGenerator1);
  JPetTaskChainExecutor taskExecutor(chain, 1, opt);
  BOOST_REQUIRE(!taskExecutor.process());
}

BOOST_AUTO_TEST_CASE(test2)
{
  auto opt = jpet_options_generator_tools::getDefaultOptions();
  opt["firstEvent_int"] = 0;
  opt["lastEvent_int"] = 10;
  opt["inputFile_std::string"] = std::string("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root");
  opt["inputFileType_std::string"] = std::string("root");
  opt["outputFile_std::string"] = std::string("JPetTaskChainExecutorTest2Chain2.root");
  auto taskGenerator1 = []() {
    auto taskIO = jpet_common_tools::make_unique<JPetTaskIOLoopPerSubTask>("TaskA", "unk.evt", "test.file");
    taskIO->addSubTask(std::unique_ptr<TestTask>(new TestTask("test2 TestTask1")));
    taskIO->addSubTask(std::unique_ptr<TestTask>(new TestTask("test2 TestTask2")));
    return taskIO;
  };
  auto taskGenerator2 = []() {
    auto taskIO = jpet_common_tools::make_unique<JPetTaskIOLoopPerSubTask>("TaskB", "test.file", "test2.file");
    taskIO->addSubTask(std::unique_ptr<TestTask>(new TestTask("test2 TestTask3")));
    return taskIO;
  };
  TaskGeneratorChain chain;
  chain.push_back(taskGenerator1);
  chain.push_back(taskGenerator2);
  BOOST_REQUIRE_EQUAL(chain.size(), 2u);
  JPetTaskChainExecutor taskExecutor(chain, 1, opt);
  BOOST_REQUIRE(taskExecutor.process());
}

BOOST_AUTO_TEST_SUITE_END()

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
 *  @file JPetTaskChainExecutorTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskChainExecutorTest
#include <boost/test/unit_test.hpp>
#include "../JPetTaskChainExecutor/JPetTaskChainExecutor.h"
#include "../JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "../JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "../JPetTaskIO/JPetTaskIO.h"
#include "../JPetUserTask/JPetUserTask.h"
#include "../JPetLoggerInclude.h"


class TestTask: public JPetUserTask
{
public:
  TestTask(const char* name = ""): JPetUserTask(name) {}
  bool init() override
  {
    return true;
  }
  bool exec() override
  {
    return true;
  }
  bool terminate() override
  {
    return true;
  }

};

BOOST_AUTO_TEST_SUITE(JPetTaskChainExecutorTestSuite)

BOOST_AUTO_TEST_CASE(test1)
{
  std::vector<jpet_options_tools::OptsStrAny> opts;
  auto opt = jpet_options_generator_tools::getDefaultOptions();
  opts.push_back(opt);
  auto taskGenerator1 = []() {
    return new JPetTaskIO;
  };
  TaskGeneratorChain* chain =  new TaskGeneratorChain;
  chain->push_back(taskGenerator1);

  JPetTaskChainExecutor taskExecutor(chain, 1, opts);
  BOOST_REQUIRE(!taskExecutor.process());
  delete chain;
}

BOOST_AUTO_TEST_CASE(test2)
{
  std::vector<jpet_options_tools::OptsStrAny> opts;
  auto opt = jpet_options_generator_tools::getDefaultOptions();
  opt["firstEvent_int"] = 0;
  opt["lastEvent_int"] = 10;
  opts.push_back(opt);
  opts.push_back(opt);

  auto taskGenerator1 = []() {
    auto taskIO =  new JPetTaskIO("TaskA");
    taskIO->setSubTask(std::unique_ptr<TestTask>(new TestTask));
    return taskIO;
  };
  auto taskGenerator2 = []() {
    auto taskIO =  new JPetTaskIO("TaskB");
    taskIO->setSubTask(std::unique_ptr<TestTask>(new TestTask));
    return taskIO;
  };
  TaskGeneratorChain* chain =  new TaskGeneratorChain;
  chain->push_back(taskGenerator1);
  chain->push_back(taskGenerator2);

  BOOST_REQUIRE_EQUAL(chain->size(), 2u);
  JPetTaskChainExecutor taskExecutor(chain, 1, opts);
  BOOST_REQUIRE(!taskExecutor.process());
  delete chain;
}

BOOST_AUTO_TEST_SUITE_END()

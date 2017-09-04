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
#include "../JPetTaskIO/JPetTaskIO.h"
#include "../JPetLoggerInclude.h"


BOOST_AUTO_TEST_SUITE(JPetTaskChainExecutorTestSuite)

BOOST_AUTO_TEST_CASE(test1)
{
  auto opts = JPetOptionsGenerator::getDefaultOptions();
  auto taskGenerator1 = []() {
    return new JPetTaskIO;
  };
  TaskGeneratorChain* chain =  new TaskGeneratorChain;
  chain->push_back(taskGenerator1);

  JPetTaskChainExecutor taskExecutor(chain, 1, JPetOptions(opts));
  delete chain;
}

BOOST_AUTO_TEST_SUITE_END()

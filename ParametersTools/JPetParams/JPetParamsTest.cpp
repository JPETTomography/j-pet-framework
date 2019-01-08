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
 *  @file JPetParamsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamsTest

#include "./JPetParams/JPetParams.h"
#include <boost/test/unit_test.hpp>
#include <boost/any.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(defaultConstr)
{
  JPetParams params;
  BOOST_REQUIRE(params.getParamManager() == nullptr);
  BOOST_REQUIRE(params.getOptions().empty());
}

BOOST_AUTO_TEST_CASE(nonDefaultConstr)
{
  jpet_options_tools::OptsStrAny opts;
  opts["blaOption"] = std::string("value");
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager);
  JPetParams params(opts, mgr);
  BOOST_REQUIRE_EQUAL(params.getParamManager(), mgr.get());
  BOOST_REQUIRE_EQUAL(params.getOptions().size(), 1u);
}

BOOST_AUTO_TEST_CASE(copyCtr)
{
  jpet_options_tools::OptsStrAny opts;
  opts["blaOption"] = std::string("value");
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager);
  JPetParams params(opts, mgr);
  auto params2 = params;
  BOOST_REQUIRE_EQUAL(params2.getParamManager(), mgr.get());
  BOOST_REQUIRE_EQUAL(params2.getOptions().size(), params.getOptions().size());
}

BOOST_AUTO_TEST_CASE(memoryLeaks)
{
  jpet_options_tools::OptsStrAny opts;
  opts["blaOption"] = std::string("value");
  JPetParams* params = new JPetParams(opts, std::make_shared<JPetParamManager>(new JPetParamManager));
  auto mgr = params->getParamManager();
  delete params;
  BOOST_REQUIRE(mgr != nullptr);
}

BOOST_AUTO_TEST_SUITE_END()

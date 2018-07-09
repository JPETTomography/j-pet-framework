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
 *  @file JPetParamsFactoryTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamsFactoryTest

#include "./JPetParamsFactory/JPetParamsFactory.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(JPetParamsFactoryTestSuite)

BOOST_AUTO_TEST_CASE(generateParams)
{
  std::map<std::string, boost::any> opts;
  auto params = jpet_params_factory::generateParams(opts);
  BOOST_REQUIRE(params.getOptions().empty());
  BOOST_REQUIRE(params.getParamManager());
}

BOOST_AUTO_TEST_SUITE_END()

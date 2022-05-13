/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetOptionsTransformatorsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTest
#include "JPetOptionsTools/JPetOptionsTools.h"

#include <boost/test/unit_test.hpp>
using boost::any_cast;
using namespace std;

using namespace jpet_options_tools;

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(checkIfFunctionsToTransformOptionWork)
{
  std::vector<int> firstOption = {1, 2};

  BOOST_REQUIRE_EQUAL(any_cast<int>(generateLowerEventBound(firstOption).second), 1);
  BOOST_REQUIRE_EQUAL(any_cast<int>(generateHigherEventBound(firstOption).second), 2);

  std::vector<int> secondOption = {-1, -2};

  BOOST_REQUIRE_EQUAL(any_cast<int>(generateLowerEventBound(secondOption).second), -1);
  BOOST_REQUIRE_EQUAL(any_cast<int>(generateHigherEventBound(secondOption).second), -1);

  std::string emptyPath = "";
  BOOST_REQUIRE_EQUAL(appendSlash(emptyPath).first, "outputPath_std::string");
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(appendSlash(emptyPath).second), "");

  std::string correctPath = "a/b/c/d/";
  BOOST_REQUIRE_EQUAL(appendSlash(correctPath).first, "outputPath_std::string");
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(appendSlash(correctPath).second), correctPath);

  std::string pathForCorrection = "a/b/c/d";
  BOOST_REQUIRE_EQUAL(appendSlash(pathForCorrection).first, "outputPath_std::string");
  BOOST_REQUIRE_EQUAL(any_cast<std::string>(appendSlash(pathForCorrection).second), correctPath);
}

BOOST_AUTO_TEST_SUITE_END()

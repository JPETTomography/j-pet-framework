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
 *  @file HelperMathFunctionsTest.h
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE HelperMathFunctionsTest

#include "./JPetSimplePhysSignalReco/HelperMathFunctions.h"
#include <boost/test/unit_test.hpp>

using namespace boost::numeric::ublas;

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(polynomialFitTest1)
{
  vector<float> time(4);
  vector<float> volt(4);
  int alfa = 1;
  float v0 = -0.10;
  time(0) = 1035.0;
  time(1) = 1542.0;
  time(2) = 2282.0;
  time(3) = 2900.0;
  volt(0) = -0.06;
  volt(1) = -0.20;
  volt(2) = -0.35;
  volt(3) = -0.50;
  float result = polynomialFit(time, volt,  alfa, v0);
  float epsilon = 0.1;
  BOOST_REQUIRE_CLOSE(result, 1171.98, epsilon);
}

BOOST_AUTO_TEST_CASE(polynomialFitTest2)
{
  vector<float> time(4);
  vector<float> volt(4);
  int alfa = 2;
  float v0 = -0.05;
  time(0) = 1035.0;
  time(1) = 1542.0;
  time(2) = 2282.0;
  time(3) = 2900.0;
  volt(0) = -0.06;
  volt(1) = -0.20;
  volt(2) = -0.35;
  volt(3) = -0.50;
  float result = polynomialFit(time, volt,  alfa, v0);
  float epsilon = 0.1;
  BOOST_REQUIRE_CLOSE(result, 793.1, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

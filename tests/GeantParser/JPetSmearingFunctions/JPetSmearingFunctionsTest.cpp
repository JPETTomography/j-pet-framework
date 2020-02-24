/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetSmearingFunctionsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSmearingFunctionsTest
#include <boost/test/unit_test.hpp>

#include "JPetSmearingFunctions/JPetSmearingFunctions.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(testOne)
{
  JPetHitExperimentalParametrizer parametrizer;
  parametrizer.addEnergySmearing(0,0,0);
  parametrizer.addZHitSmearing(0,0,0);
  parametrizer.addTimeSmearing(0,0,0,0);
}

BOOST_AUTO_TEST_SUITE_END()

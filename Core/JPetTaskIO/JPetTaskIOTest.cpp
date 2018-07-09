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
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(progressBarTest)
{
  JPetTaskIO taskIO;
  taskIO.displayProgressBar(5, 100);
}

/* TODO - add more tests! */

BOOST_AUTO_TEST_SUITE_END()

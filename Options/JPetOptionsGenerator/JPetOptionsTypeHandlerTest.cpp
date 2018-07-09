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
 *  @file JPetOptionsGeneratorTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTypeHandlerTest

#include "./JPetOptionsGenerator/JPetOptionsTypeHandler.h"
#include <boost/test/unit_test.hpp>
#include <cstdlib>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(getTypeOfOption)
{
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getTypeOfOption(""), "default");
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getTypeOfOption("blabla"), "default");
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getTypeOfOption("blabla_int"), "int");
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getTypeOfOption("blwblw_std::string"), "std::string");
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getTypeOfOption("bla_bla_int"), "int");
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getTypeOfOption("_int"), "int");
}

BOOST_AUTO_TEST_CASE(getNameOfOption)
{
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getNameOfOption(""), "");
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getNameOfOption("blabla"), "blabla");
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getNameOfOption("blabla_int"), "blabla");
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getNameOfOption("blwblw_std::string"), "blwblw");
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getNameOfOption("bla_bla_int"), "bla_bla");
  BOOST_REQUIRE_EQUAL(JPetOptionsTypeHandler::getNameOfOption("_int"), "");
}

BOOST_AUTO_TEST_SUITE_END()

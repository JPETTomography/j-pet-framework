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
 *  @file JPetGeantEventInformationTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGeantEventInformationTest

#include "JPetGeantEventInformation/JPetGeantEventInformation.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetGeantEventInformation info;

  BOOST_REQUIRE_EQUAL(info.getThreeGammaGen(), 0);
  BOOST_REQUIRE_EQUAL(info.getTwoGammaGen(), 0);
  BOOST_REQUIRE_EQUAL(info.getPromptGammaGen(), 0);
  BOOST_REQUIRE_EQUAL(info.getRunNr(), 0);

  double epsilon = 0.0001;

  BOOST_REQUIRE_CLOSE(info.getVtxPositionX(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(info.getVtxPositionY(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(info.getVtxPositionZ(), 0.0f, epsilon);

  BOOST_REQUIRE_CLOSE(info.getVtxPromptPositionX(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(info.getVtxPromptPositionY(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(info.getVtxPromptPositionZ(), 0.0f, epsilon);

  BOOST_REQUIRE_CLOSE(info.getLifetime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(info.getPromptLifetime(), 0.0f, epsilon);
}

BOOST_AUTO_TEST_CASE(check_setters)
{
  JPetGeantEventInformation info;

  bool gammaGen = true;

  info.setThreeGammaGen(gammaGen);
  info.setTwoGammaGen(gammaGen);
  info.setPromptGammaGen(gammaGen);

  int runNR = 45;
  info.setRunNr(runNR);

  BOOST_REQUIRE_EQUAL(info.getThreeGammaGen(), gammaGen);
  BOOST_REQUIRE_EQUAL(info.getTwoGammaGen(), gammaGen);
  BOOST_REQUIRE_EQUAL(info.getPromptGammaGen(), gammaGen);
  BOOST_REQUIRE_EQUAL(info.getRunNr(), runNR);

  double vtx_x = 35;
  double vtx_y = 25;
  double vtx_z = 33;
  double lifetime = 432;
  info.setVtxPosition(vtx_x, vtx_y, vtx_z);
  info.setLifetime(lifetime);

  double prompt_vtx_x = 335;
  double prompt_vtx_y = 325;
  double prompt_vtx_z = 333;
  double prompt_lifetime = 43.342;
  info.setVtxPromptPosition(prompt_vtx_x, prompt_vtx_y, prompt_vtx_z);
  info.setPromptLifetime(prompt_lifetime);

  BOOST_REQUIRE_EQUAL(info.getVtxPositionX(), vtx_x);
  BOOST_REQUIRE_EQUAL(info.getVtxPositionY(), vtx_y);
  BOOST_REQUIRE_EQUAL(info.getVtxPositionZ(), vtx_z);
  BOOST_REQUIRE_EQUAL(info.getLifetime(), lifetime);

  BOOST_REQUIRE_EQUAL(info.getVtxPromptPositionX(), prompt_vtx_x);
  BOOST_REQUIRE_EQUAL(info.getVtxPromptPositionY(), prompt_vtx_y);
  BOOST_REQUIRE_EQUAL(info.getVtxPromptPositionZ(), prompt_vtx_z);
  BOOST_REQUIRE_EQUAL(info.getPromptLifetime(), prompt_lifetime);
}

BOOST_AUTO_TEST_SUITE_END()

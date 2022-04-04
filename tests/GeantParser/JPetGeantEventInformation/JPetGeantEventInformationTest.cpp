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

  BOOST_REQUIRE_EQUAL(info.GetThreeGammaGen(), 0);
  BOOST_REQUIRE_EQUAL(info.GetTwoGammaGen(), 0);
  BOOST_REQUIRE_EQUAL(info.GetPromptGammaGen(), 0);
  BOOST_REQUIRE_EQUAL(info.GetRunNr(), 0);

  double epsilon = 0.0001;

  BOOST_REQUIRE_CLOSE(info.GetVtxPositionX(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(info.GetVtxPositionY(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(info.GetVtxPositionZ(), 0.0f, epsilon);

  BOOST_REQUIRE_CLOSE(info.GetVtxPromptPositionX(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(info.GetVtxPromptPositionY(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(info.GetVtxPromptPositionZ(), 0.0f, epsilon);

  BOOST_REQUIRE_CLOSE(info.GetLifetime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(info.GetPromptLifetime(), 0.0f, epsilon);
}

BOOST_AUTO_TEST_CASE(check_setters)
{
  JPetGeantEventInformation info;

  bool gammaGen = true;

  info.SetThreeGammaGen(gammaGen);
  info.SetTwoGammaGen(gammaGen);
  info.SetPromptGammaGen(gammaGen);

  int runNR = 45;
  info.SetRunNr(runNR);

  BOOST_REQUIRE_EQUAL(info.GetThreeGammaGen(), gammaGen);
  BOOST_REQUIRE_EQUAL(info.GetTwoGammaGen(), gammaGen);
  BOOST_REQUIRE_EQUAL(info.GetPromptGammaGen(), gammaGen);
  BOOST_REQUIRE_EQUAL(info.GetRunNr(), runNR);

  double vtx_x = 35;
  double vtx_y = 25;
  double vtx_z = 33;
  double lifetime = 432;
  info.SetVtxPosition(vtx_x, vtx_y, vtx_z);
  info.SetLifetime(lifetime);

  double prompt_vtx_x = 335;
  double prompt_vtx_y = 325;
  double prompt_vtx_z = 333;
  double prompt_lifetime = 43.342;
  info.SetVtxPromptPosition(prompt_vtx_x, prompt_vtx_y, prompt_vtx_z);
  info.SetPromptLifetime(prompt_lifetime);

  BOOST_REQUIRE_EQUAL(info.GetVtxPositionX(), vtx_x);
  BOOST_REQUIRE_EQUAL(info.GetVtxPositionY(), vtx_y);
  BOOST_REQUIRE_EQUAL(info.GetVtxPositionZ(), vtx_z);
  BOOST_REQUIRE_EQUAL(info.GetLifetime(), lifetime);

  BOOST_REQUIRE_EQUAL(info.GetVtxPromptPositionX(), prompt_vtx_x);
  BOOST_REQUIRE_EQUAL(info.GetVtxPromptPositionY(), prompt_vtx_y);
  BOOST_REQUIRE_EQUAL(info.GetVtxPromptPositionZ(), prompt_vtx_z);
  BOOST_REQUIRE_EQUAL(info.GetPromptLifetime(), prompt_lifetime);
}

BOOST_AUTO_TEST_SUITE_END()

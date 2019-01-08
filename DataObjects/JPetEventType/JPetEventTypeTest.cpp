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
 *  @file JPetEventTypeTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetEventTypeTest

#include <boost/test/unit_test.hpp>
#include "./JPetEventType/JPetEventType.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(JPetEventTest)
{
  auto eventType1 = JPetEventType::kUnknown;
  auto eventType2 = JPetEventType::k2Gamma;
  auto eventTypeRes = eventType1 | eventType2;
  BOOST_REQUIRE((eventTypeRes & JPetEventType::kUnknown) == JPetEventType::kUnknown);
  BOOST_REQUIRE((eventTypeRes & JPetEventType::k2Gamma) == JPetEventType::k2Gamma);
  BOOST_REQUIRE((eventTypeRes & JPetEventType::k2Gamma) != JPetEventType::k3Gamma);
}

BOOST_AUTO_TEST_CASE(JPetEventTest2)
{
  auto eventType1 = JPetEventType::kUnknown | JPetEventType::k2Gamma | JPetEventType::kPrompt;
  auto eventTypeRes = eventType1 & ~JPetEventType::k2Gamma; /// unset flag
  BOOST_REQUIRE((eventTypeRes & JPetEventType::kUnknown) == JPetEventType::kUnknown);
  BOOST_REQUIRE((eventTypeRes & JPetEventType::k2Gamma) != JPetEventType::k2Gamma);
  BOOST_REQUIRE((eventTypeRes & JPetEventType::kPrompt) == JPetEventType::kPrompt);
}

BOOST_AUTO_TEST_SUITE_END()

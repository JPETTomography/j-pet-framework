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
 *  @file JPetEventTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetEventTest

#include "JPetEvent/JPetEvent.h"
#include "Hits/JPetMCRecoHit/JPetMCRecoHit.h"
#include "Hits/JPetPhysRecoHit/JPetPhysRecoHit.h"
#include "Hits/JPetRecoHit/JPetRecoHit.h"
#include "JPetLoggerInclude.h"
#include "JPetRawMCHit/JPetRawMCHit.h"
#include "JPetWriter/JPetWriter.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

double epsilon = 0.00001;

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetEvent event;
  BOOST_REQUIRE_EQUAL(event.getRecoFlag(), JPetEvent::Unknown);
  BOOST_REQUIRE(event.getHits().empty());
}

BOOST_AUTO_TEST_CASE(recoFlagSetterTest)
{
  JPetEvent event;
  BOOST_REQUIRE_EQUAL(event.getRecoFlag(), JPetEvent::Unknown);
  event.setRecoFlag(JPetEvent::Good);
  BOOST_REQUIRE_EQUAL(event.getRecoFlag(), JPetEvent::Good);
  event.setRecoFlag(JPetEvent::Corrupted);
  BOOST_REQUIRE_EQUAL(event.getRecoFlag(), JPetEvent::Corrupted);
  event.setRecoFlag(JPetEvent::MC);
  BOOST_REQUIRE_EQUAL(event.getRecoFlag(), JPetEvent::MC);
}

BOOST_AUTO_TEST_CASE(constructor)
{
  JPetBaseHit firstHit;
  JPetBaseHit secondHit;
  JPetEvent event({&firstHit, &secondHit}, JPetEventType::kUnknown);
  BOOST_REQUIRE(!event.getHits().empty());
  BOOST_REQUIRE_EQUAL(event.getHits().size(), 2);
}

BOOST_AUTO_TEST_CASE(constructor_orderedHits)
{
  TVector3 position(1.0, 1.0, 1.0);
  std::vector<JPetBaseHit*> hits;
  JPetBaseHit hit1(2.2, 511.0, position);
  JPetBaseHit hit2(1.1, 511.0, position);
  JPetBaseHit hit3(4.4, 511.0, position);
  JPetBaseHit hit4(3.3, 511.0, position);
  hits.push_back(&hit1);
  hits.push_back(&hit2);
  hits.push_back(&hit3);
  hits.push_back(&hit4);
  JPetEvent event(hits, JPetEventType::kUnknown);
  auto results = event.getHits();
  double epsilon = 0.00001;
  BOOST_REQUIRE_CLOSE(results[0]->getTime(), 1.1, epsilon);
  BOOST_REQUIRE_CLOSE(results[1]->getTime(), 2.2, epsilon);
  BOOST_REQUIRE_CLOSE(results[2]->getTime(), 3.3, epsilon);
  BOOST_REQUIRE_CLOSE(results[3]->getTime(), 4.4, epsilon);
}

BOOST_AUTO_TEST_CASE(constructor_unorderedHits)
{
  TVector3 position(1.0, 1.0, 1.0);
  std::vector<JPetBaseHit*> hits;
  JPetBaseHit hit1(2.2, 511.0, position);
  JPetBaseHit hit2(1.1, 511.0, position);
  JPetBaseHit hit3(4.4, 511.0, position);
  JPetBaseHit hit4(3.3, 511.0, position);
  hits.push_back(&hit1);
  hits.push_back(&hit2);
  hits.push_back(&hit3);
  hits.push_back(&hit4);
  JPetEvent event(hits, JPetEventType::kUnknown, false);
  auto results = event.getHits();
  BOOST_REQUIRE_CLOSE(results[0]->getTime(), 2.2, epsilon);
  BOOST_REQUIRE_CLOSE(results[1]->getTime(), 1.1, epsilon);
  BOOST_REQUIRE_CLOSE(results[2]->getTime(), 4.4, epsilon);
  BOOST_REQUIRE_CLOSE(results[3]->getTime(), 3.3, epsilon);
}

BOOST_AUTO_TEST_CASE(set_unorderedHits)
{
  TVector3 position(1.0, 1.0, 1.0);
  std::vector<JPetBaseHit*> hits;
  JPetBaseHit hit1(2.2, 511.0, position);
  JPetBaseHit hit2(1.1, 511.0, position);
  JPetBaseHit hit3(4.4, 511.0, position);
  JPetBaseHit hit4(3.3, 511.0, position);
  hits.push_back(&hit1);
  hits.push_back(&hit2);
  hits.push_back(&hit3);
  hits.push_back(&hit4);

  JPetEvent event;
  event.setHits(hits, false);
  auto results = event.getHits();
  BOOST_REQUIRE_CLOSE(results[0]->getTime(), 2.2, epsilon);
  BOOST_REQUIRE_CLOSE(results[1]->getTime(), 1.1, epsilon);
  BOOST_REQUIRE_CLOSE(results[2]->getTime(), 4.4, epsilon);
  BOOST_REQUIRE_CLOSE(results[3]->getTime(), 3.3, epsilon);
}

BOOST_AUTO_TEST_CASE(set_orderedHits)
{
  TVector3 position(1.0, 1.0, 1.0);
  std::vector<JPetBaseHit*> hits;
  JPetBaseHit hit1(2.2, 511.0, position);
  JPetBaseHit hit2(1.1, 511.0, position);
  JPetBaseHit hit3(4.4, 511.0, position);
  JPetBaseHit hit4(3.3, 511.0, position);
  hits.push_back(&hit1);
  hits.push_back(&hit2);
  hits.push_back(&hit3);
  hits.push_back(&hit4);

  JPetEvent event;
  event.setHits(hits);
  auto results = event.getHits();
  BOOST_REQUIRE_CLOSE(results[0]->getTime(), 1.1, epsilon);
  BOOST_REQUIRE_CLOSE(results[1]->getTime(), 2.2, epsilon);
  BOOST_REQUIRE_CLOSE(results[2]->getTime(), 3.3, epsilon);
  BOOST_REQUIRE_CLOSE(results[3]->getTime(), 4.4, epsilon);
}

BOOST_AUTO_TEST_CASE(addHit)
{
  JPetEvent event;
  JPetBaseHit firstHit;
  JPetBaseHit secondHit;
  JPetBaseHit thirdHit;
  event.setHits({&firstHit, &secondHit});
  BOOST_REQUIRE(!event.getHits().empty());
  BOOST_REQUIRE_EQUAL(event.getHits().size(), 2);
  event.addHit(&thirdHit);
  BOOST_REQUIRE_EQUAL(event.getHits().size(), 3);
}

BOOST_AUTO_TEST_CASE(eventTypes)
{
  JPetEvent event;
  auto type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::kUnknown) == JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) != JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) != JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kPrompt) != JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);
  BOOST_REQUIRE((type & JPetEventType::kCosmic) != JPetEventType::kCosmic);
}

BOOST_AUTO_TEST_CASE(eventTypes2)
{
  JPetBaseHit firstHit;
  JPetEvent event({&firstHit}, JPetEventType::kPrompt);
  auto type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::kPrompt) == JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::kUnknown) != JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) != JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) != JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);
  BOOST_REQUIRE((type & JPetEventType::kCosmic) != JPetEventType::kCosmic);
}

BOOST_AUTO_TEST_CASE(eventTypes3)
{
  JPetBaseHit firstHit;
  JPetEvent event({&firstHit}, static_cast<JPetEventType>(JPetEventType::kPrompt | JPetEventType::k2Gamma));
  auto type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::kPrompt) == JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) == JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::kUnknown) != JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) != JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);
  BOOST_REQUIRE((type & JPetEventType::kCosmic) != JPetEventType::kCosmic);
}

BOOST_AUTO_TEST_CASE(isTypeOf)
{
  JPetBaseHit firstHit;
  JPetEvent event({&firstHit}, static_cast<JPetEventType>(JPetEventType::kPrompt | JPetEventType::kCosmic));
  BOOST_REQUIRE(!event.isTypeOf(JPetEventType::k2Gamma));
  BOOST_REQUIRE(!event.isTypeOf(JPetEventType::k3Gamma));
  BOOST_REQUIRE(event.isTypeOf(JPetEventType::kPrompt));
  BOOST_REQUIRE(!event.isTypeOf(JPetEventType::kUnknown));
  BOOST_REQUIRE(!event.isTypeOf(JPetEventType::kScattered));
  BOOST_REQUIRE(event.isTypeOf(JPetEventType::kCosmic));
}

BOOST_AUTO_TEST_CASE(isOnlyTypeOf)
{
  JPetBaseHit firstHit;
  JPetEvent event({&firstHit}, static_cast<JPetEventType>(JPetEventType::kPrompt | JPetEventType::k2Gamma));
  BOOST_REQUIRE(!event.isOnlyTypeOf(JPetEventType::k2Gamma));
  BOOST_REQUIRE(!event.isOnlyTypeOf(JPetEventType::k3Gamma));
  BOOST_REQUIRE(!event.isOnlyTypeOf(JPetEventType::kPrompt));
  BOOST_REQUIRE(!event.isOnlyTypeOf(JPetEventType::kUnknown));
  BOOST_REQUIRE(!event.isOnlyTypeOf(JPetEventType::kScattered));
  BOOST_REQUIRE(!event.isOnlyTypeOf(JPetEventType::kCosmic));
  BOOST_REQUIRE(event.isOnlyTypeOf(static_cast<JPetEventType>(JPetEventType::kPrompt | JPetEventType::k2Gamma)));

  JPetEvent event2;
  event2.addEventType(JPetEventType::kPrompt);
  BOOST_REQUIRE(event2.isOnlyTypeOf(JPetEventType::kPrompt));
  BOOST_REQUIRE(!event2.isOnlyTypeOf(JPetEventType::k2Gamma));
  BOOST_REQUIRE(!event2.isOnlyTypeOf(JPetEventType::k3Gamma));
  BOOST_REQUIRE(!event2.isOnlyTypeOf(JPetEventType::kUnknown));
  BOOST_REQUIRE(!event2.isOnlyTypeOf(JPetEventType::kScattered));
  BOOST_REQUIRE(!event2.isOnlyTypeOf(JPetEventType::kCosmic));
}

BOOST_AUTO_TEST_CASE(setGetType)
{
  JPetBaseHit firstHit;
  JPetEvent event({&firstHit}, JPetEventType::kPrompt);
  event.setEventType(static_cast<JPetEventType>(JPetEventType::kCosmic | JPetEventType::k3Gamma));
  auto type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::kPrompt) != JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::kUnknown) != JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) != JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::kCosmic) == JPetEventType::kCosmic);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) == JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);
}

BOOST_AUTO_TEST_CASE(addEventType)
{
  JPetBaseHit firstHit;
  JPetEvent event({&firstHit}, JPetEventType::kPrompt);
  event.addEventType(JPetEventType::k2Gamma);
  auto type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::kPrompt) == JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) == JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::kUnknown) != JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) != JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kCosmic) != JPetEventType::kCosmic);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);
}

BOOST_AUTO_TEST_CASE(addEventType2)
{
  JPetEvent event; // default is kUnknown
  event.addEventType(JPetEventType::k2Gamma);
  auto type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) == JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::kUnknown) != JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) != JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kPrompt) != JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);
  BOOST_REQUIRE((type & JPetEventType::kCosmic) != JPetEventType::kCosmic);
}

BOOST_AUTO_TEST_CASE(addEventType3)
{
  JPetEvent event; // default is kUnknown
  event.addEventType(JPetEventType::k2Gamma);
  auto type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) == JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::kUnknown) != JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) != JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kPrompt) != JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::kCosmic) != JPetEventType::kCosmic);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);

  event.addEventType(JPetEventType::k3Gamma);
  type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) == JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) == JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kUnknown) != JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::kPrompt) != JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::kCosmic) != JPetEventType::kCosmic);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);
}

BOOST_AUTO_TEST_CASE(test_cast_hit_types)
{
  JPetRecoHit recoHit(JPetRecoHit::Good);
  JPetMCRecoHit mcRecoHit(123);
  JPetPhysRecoHit physHit;
  JPetRawMCHit rawMCHit;

  recoHit.setTime(1.0);
  mcRecoHit.setTime(2.0);
  physHit.setTime(3.0);
  rawMCHit.setTime(4.0);

  JPetEvent event;
  event.addHit(&recoHit);
  event.addHit(&mcRecoHit);
  event.addHit(&physHit);
  event.addHit(&rawMCHit);

  BOOST_REQUIRE_CLOSE(event.getHits().at(0)->getTime(), 1.0, epsilon);
  BOOST_REQUIRE_CLOSE(event.getHits().at(1)->getTime(), 2.0, epsilon);
  BOOST_REQUIRE_CLOSE(event.getHits().at(2)->getTime(), 3.0, epsilon);
  BOOST_REQUIRE_CLOSE(event.getHits().at(3)->getTime(), 4.0, epsilon);

  // Testing casts
  BOOST_REQUIRE(dynamic_cast<JPetRecoHit*>(event.getHits().at(0)));
  BOOST_REQUIRE(dynamic_cast<JPetRecoHit*>(event.getHits().at(1)));
  BOOST_REQUIRE(dynamic_cast<JPetRecoHit*>(event.getHits().at(2)));
  BOOST_REQUIRE(!dynamic_cast<JPetRecoHit*>(event.getHits().at(3)));

  BOOST_REQUIRE(!dynamic_cast<JPetMCRecoHit*>(event.getHits().at(0)));
  BOOST_REQUIRE(dynamic_cast<JPetMCRecoHit*>(event.getHits().at(1)));
  BOOST_REQUIRE(!dynamic_cast<JPetMCRecoHit*>(event.getHits().at(2)));
  BOOST_REQUIRE(!dynamic_cast<JPetMCRecoHit*>(event.getHits().at(3)));

  BOOST_REQUIRE(!dynamic_cast<JPetPhysRecoHit*>(event.getHits().at(0)));
  BOOST_REQUIRE(!dynamic_cast<JPetPhysRecoHit*>(event.getHits().at(1)));
  BOOST_REQUIRE(dynamic_cast<JPetPhysRecoHit*>(event.getHits().at(2)));
  BOOST_REQUIRE(!dynamic_cast<JPetPhysRecoHit*>(event.getHits().at(3)));

  BOOST_REQUIRE(!dynamic_cast<JPetRawMCHit*>(event.getHits().at(0)));
  BOOST_REQUIRE(!dynamic_cast<JPetRawMCHit*>(event.getHits().at(1)));
  BOOST_REQUIRE(!dynamic_cast<JPetRawMCHit*>(event.getHits().at(2)));
  BOOST_REQUIRE(dynamic_cast<JPetRawMCHit*>(event.getHits().at(3)));
}

BOOST_AUTO_TEST_SUITE_END()

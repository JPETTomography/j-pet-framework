#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetEventTest
#include <boost/test/unit_test.hpp>

#include "../JPetEvent/JPetEvent.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)
BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetEvent event;
  BOOST_REQUIRE(event.getHits().empty());
}

BOOST_AUTO_TEST_CASE(constructor)
{

  JPetBarrelSlot slot1(43, true, "", 0, 43);
  JPetBarrelSlot slot2(44, true, "", 0, 44);
  JPetHit firstHit;
  JPetHit secondHit;
  firstHit.setBarrelSlot(slot1);
  secondHit.setBarrelSlot(slot2);
  JPetEvent event({firstHit, secondHit}, JPetEventType::kUnknown);

  BOOST_REQUIRE(!event.getHits().empty());
  BOOST_REQUIRE_EQUAL(event.getHits().size(), 2);
}

BOOST_AUTO_TEST_CASE(constructor_orderedHits)
{
  std::vector<JPetHit> hits(4);
  hits[0].setTime(2);
  hits[1].setTime(1);
  hits[2].setTime(4);
  hits[3].setTime(3);
  JPetEvent event(hits, JPetEventType::kUnknown);
  auto results = event.getHits();
  BOOST_REQUIRE_EQUAL(results[0].getTime(), 1);
  BOOST_REQUIRE_EQUAL(results[1].getTime(), 2);
  BOOST_REQUIRE_EQUAL(results[2].getTime(), 3);
  BOOST_REQUIRE_EQUAL(results[3].getTime(), 4);
}

BOOST_AUTO_TEST_CASE(constructor_unorderedHits)
{
  std::vector<JPetHit> hits(4);
  hits[0].setTime(2);
  hits[1].setTime(1);
  hits[2].setTime(4);
  hits[3].setTime(3);
  JPetEvent event(hits, JPetEventType::kUnknown, false);
  auto results = event.getHits();
  BOOST_REQUIRE_EQUAL(results[0].getTime(), 2);
  BOOST_REQUIRE_EQUAL(results[1].getTime(), 1);
  BOOST_REQUIRE_EQUAL(results[2].getTime(), 4);
  BOOST_REQUIRE_EQUAL(results[3].getTime(), 3);
}

BOOST_AUTO_TEST_CASE(set_unorderedHits)
{
  JPetEvent event;
  std::vector<JPetHit> hits(4);
  hits[0].setTime(2);
  hits[1].setTime(1);
  hits[2].setTime(4);
  hits[3].setTime(3);
  event.setHits(hits, false);
  auto results = event.getHits();
  BOOST_REQUIRE_EQUAL(results[0].getTime(), 2);
  BOOST_REQUIRE_EQUAL(results[1].getTime(), 1);
  BOOST_REQUIRE_EQUAL(results[2].getTime(), 4);
  BOOST_REQUIRE_EQUAL(results[3].getTime(), 3);
}

BOOST_AUTO_TEST_CASE(set_orderedHits)
{
  JPetEvent event;
  std::vector<JPetHit> hits(4);
  hits[0].setTime(2);
  hits[1].setTime(1);
  hits[2].setTime(4);
  hits[3].setTime(3);
  event.setHits(hits);
  auto results = event.getHits();
  BOOST_REQUIRE_EQUAL(results[0].getTime(), 1);
  BOOST_REQUIRE_EQUAL(results[1].getTime(), 2);
  BOOST_REQUIRE_EQUAL(results[2].getTime(), 3);
  BOOST_REQUIRE_EQUAL(results[3].getTime(), 4);
}

BOOST_AUTO_TEST_CASE(addHit)
{
  JPetEvent event;
  JPetHit firstHit;
  JPetHit secondHit;
  JPetHit thirdHit;
  event.setHits( {firstHit, secondHit});
  BOOST_REQUIRE(!event.getHits().empty());
  BOOST_REQUIRE_EQUAL(event.getHits().size(), 2);
  event.addHit(thirdHit);
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
}

BOOST_AUTO_TEST_CASE(eventTypes2)
{
  JPetHit firstHit;
  JPetEvent event( {firstHit}, JPetEventType::kPrompt);
  auto type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::kPrompt) == JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::kUnknown) != JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) != JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) != JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);
}

BOOST_AUTO_TEST_CASE(eventTypes3)
{
  JPetHit firstHit;
  JPetEvent event( {firstHit}, (JPetEventType::kPrompt | JPetEventType::k2Gamma));
  auto type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::kPrompt) == JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) == JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::kUnknown) != JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) != JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);
}

BOOST_AUTO_TEST_CASE(isTypeOf)
{
  JPetHit firstHit;
  JPetEvent event( {firstHit}, (JPetEventType::kPrompt | JPetEventType::k2Gamma));
  BOOST_REQUIRE(event.isTypeOf(JPetEventType::k2Gamma));
  BOOST_REQUIRE(!event.isTypeOf(JPetEventType::k3Gamma));
  BOOST_REQUIRE(event.isTypeOf(JPetEventType::kPrompt));
  BOOST_REQUIRE(!event.isTypeOf(JPetEventType::kUnknown));
  BOOST_REQUIRE(!event.isTypeOf(JPetEventType::kScattered));
}

BOOST_AUTO_TEST_CASE(setGetType)
{
  JPetHit firstHit;
  JPetEvent event( {firstHit}, JPetEventType::kPrompt);
  event.setEventType(JPetEventType::k2Gamma | JPetEventType::k3Gamma);
  auto type = event.getEventType();
  BOOST_REQUIRE((type & JPetEventType::kPrompt) != JPetEventType::kPrompt);
  BOOST_REQUIRE((type & JPetEventType::kUnknown) != JPetEventType::kUnknown);
  BOOST_REQUIRE((type & JPetEventType::k2Gamma) == JPetEventType::k2Gamma);
  BOOST_REQUIRE((type & JPetEventType::k3Gamma) == JPetEventType::k3Gamma);
  BOOST_REQUIRE((type & JPetEventType::kScattered) != JPetEventType::kScattered);
}

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOpsEventTest
#include <boost/test/unit_test.hpp>

#include "./JPetWriter/JPetWriter.h"
#include "./JPetEventTest/JPetEventTest.h"
#include "./JPetLoggerInclude.h"


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
  JPetOpsEvent event({firstHit, secondHit}, JPetEventType::kUnknown);

  BOOST_REQUIRE(!event.getHits().empty());
  BOOST_REQUIRE_EQUAL(event.getHits().size(), 2u);
}

BOOST_AUTO_TEST_CASE(constructor_orderedHits)
{
  std::vector<JPetHit> hits(4);
  hits[0].setTime(2);
  hits[1].setTime(1);
  hits[2].setTime(4);
  hits[3].setTime(3);
  JPetOpsEvent event(hits, JPetEventType::kUnknown);
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
  JPetOpsEvent event(hits, JPetEventType::kUnknown, false);
  auto results = event.getHits();
  BOOST_REQUIRE_EQUAL(results[0].getTime(), 2);
  BOOST_REQUIRE_EQUAL(results[1].getTime(), 1);
  BOOST_REQUIRE_EQUAL(results[2].getTime(), 4);
  BOOST_REQUIRE_EQUAL(results[3].getTime(), 3);
}

BOOST_AUTO_TEST_CASE(annihilation_position_setter1)
{
  double epsilon = 0.0001;
  JPetOpsEvent event;
  double x = 11.5;
  double y = -20.1;
  double z = 0.1;
  event.setAnninihationPoint(x, y, z);

  BOOST_REQUIRE_CLOSE(event.getAnnihilationPoint().X(), x, epsilon );
  BOOST_REQUIRE_CLOSE(event.getAnnihilationPoint().Y(), y, epsilon );
  BOOST_REQUIRE_CLOSE(event.getAnnihilationPoint().Z(), z, epsilon );

}

BOOST_AUTO_TEST_CASE(annihilation_position_setter2)
{
  double epsilon = 0.0001;
  JPetOpsEvent event;
  double x = 11.5;
  double y = -20.1;
  double z = 0.1;
  TVector3 vec(x, y, z);
  event.setAnninihationPoint(vec);

  BOOST_REQUIRE_CLOSE(event.getAnnihilationPoint().X(), x, epsilon );
  BOOST_REQUIRE_CLOSE(event.getAnnihilationPoint().Y(), y, epsilon );
  BOOST_REQUIRE_CLOSE(event.getAnnihilationPoint().Z(), z, epsilon );

}

BOOST_AUTO_TEST_CASE(annihilation_time)
{

  double epsilon = 0.0001;
  JPetOpsEvent event;
  double t = 43.21;
  event.setAnnihilationTime(t);

  BOOST_REQUIRE_CLOSE(event.getAnnihilationTime(), t, epsilon);

}


BOOST_AUTO_TEST_SUITE_END()

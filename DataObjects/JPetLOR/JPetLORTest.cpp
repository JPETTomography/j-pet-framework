#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetLORTest
#include <boost/test/unit_test.hpp>

#include "./JPetLOR/JPetLOR.h"


BOOST_AUTO_TEST_SUITE(FirstSuite)
BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetLOR event;
  BOOST_REQUIRE_EQUAL(event.getTime(), 0.0f);
  BOOST_REQUIRE_EQUAL(event.getQualityOfTime(), 0.0f);

  BOOST_REQUIRE_EQUAL(event.isFromSameBarrelSlot(), true);
}

BOOST_AUTO_TEST_CASE(constructor)
{
  JPetBarrelSlot slot1(43, true, "", 0, 43);
  JPetBarrelSlot slot2(44, true, "", 0, 44);
  JPetHit firstHit;
  JPetHit secondHit;
  firstHit.setBarrelSlot(slot1);
  secondHit.setBarrelSlot(slot2);
  JPetLOR event(8.5f, 4.5f, firstHit, secondHit);

  BOOST_REQUIRE_EQUAL(event.isFromSameBarrelSlot(), true);
  
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(event.getTime(), 8.5f, epsilon);
  BOOST_REQUIRE_CLOSE(event.getQualityOfTime(), 4.5f, epsilon);
  BOOST_REQUIRE_CLOSE(event.getTimeDiff(), 0.f, epsilon);
  BOOST_REQUIRE_EQUAL(event.getQualityOfTimeDiff(), 0.f);
  BOOST_REQUIRE_EQUAL(event.isHitSet(0), 1);
  BOOST_REQUIRE_EQUAL(event.isHitSet(1), 1);
}

BOOST_AUTO_TEST_CASE(hitTest)
{
  JPetHit firstHit;
  JPetHit secondHit;
  JPetLOR event(8.5f, 4.5f, firstHit, secondHit);
  
  BOOST_REQUIRE(event.getFirstHit().getEnergy() == firstHit.getEnergy());
  BOOST_REQUIRE(event.getSecondHit().getEnergy() == firstHit.getEnergy());
  
  JPetHit fh;
  JPetHit sh;
  JPetScin scin1(8);
  JPetScin scin2(16);
  fh.setScintillator(scin1);
  sh.setScintillator(scin2);
  event.setHits(fh, sh);
  BOOST_REQUIRE(event.getFirstHit().getScintillator().getID()
  				== fh.getScintillator().getID());
  BOOST_REQUIRE(event.getSecondHit().getScintillator().getID()
  				== sh.getScintillator().getID());
  
  JPetScin scin3(32);
  JPetScin scin4(64);
  fh.setScintillator(scin3);
  sh.setScintillator(scin4);
  event.setFirstHit(fh);
  event.setSecondHit(sh);
  BOOST_REQUIRE(event.getFirstHit().getScintillator().getID()
  				== fh.getScintillator().getID());
  BOOST_REQUIRE(event.getSecondHit().getScintillator().getID()
  				== sh.getScintillator().getID());
}

BOOST_AUTO_TEST_CASE(timeDiffTest)
{
  JPetLOR event;
  event.setTimeDiff(111.f);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(event.getTimeDiff(), 111.f, epsilon);
}

BOOST_AUTO_TEST_CASE(qualityOfTimeTest)
{
  JPetLOR event;
  event.setQualityOfTimeDiff(111.f);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(event.getQualityOfTime(), 111.f, epsilon);
}

BOOST_AUTO_TEST_CASE(timeTest)
{
  JPetLOR event;
  event.setTime(111.f);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_CLOSE(event.getTime(), 111.f, epsilon);
}

BOOST_AUTO_TEST_CASE(consistency_check_test)
{
  JPetBarrelSlot slot1(43, true, "", 0, 43);
  JPetBarrelSlot slot2(44, true, "", 0, 44);
  JPetHit firstHit;
  JPetHit secondHit;
  firstHit.setBarrelSlot(slot1);
  secondHit.setBarrelSlot(slot2);
  JPetLOR event(8.5f, 4.5f, firstHit, secondHit);

  BOOST_REQUIRE_EQUAL(event.isFromSameBarrelSlot(), true);

  secondHit.setBarrelSlot(slot1);
  event.setSecondHit(secondHit);
  BOOST_REQUIRE_EQUAL(event.isFromSameBarrelSlot(), false);

  secondHit.setBarrelSlot(slot2);
  event.setSecondHit(secondHit);
  BOOST_REQUIRE_EQUAL(event.isFromSameBarrelSlot(), true);

  firstHit.setTime(10.001);
  secondHit.setTime(10.002);
  event.setHits(firstHit, secondHit);
  BOOST_REQUIRE_EQUAL(event.isFromSameBarrelSlot(), true);

  event.setHits(secondHit, firstHit);
  BOOST_REQUIRE_EQUAL(event.isFromSameBarrelSlot(), false);
}
BOOST_AUTO_TEST_SUITE_END()

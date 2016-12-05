#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetEventTest
#include <boost/test/unit_test.hpp>

#include "../JPetAnalysisTools/JPetAnalysisTools.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)


BOOST_AUTO_TEST_CASE(constructor_getHitsOrderedByTime)
{
  std::vector<JPetHit> hits(4);
  hits[0].setTime(2);
  hits[1].setTime(1);
  hits[2].setTime(4);
  hits[3].setTime(3);
  auto results = JPetAnalysisTools::getHitsOrderedByTime(hits);
  BOOST_REQUIRE_EQUAL(results[0].getTime(), 1);
  BOOST_REQUIRE_EQUAL(results[1].getTime(), 2);
  BOOST_REQUIRE_EQUAL(results[2].getTime(), 3);
  BOOST_REQUIRE_EQUAL(results[3].getTime(), 4);
}

BOOST_AUTO_TEST_SUITE_END()

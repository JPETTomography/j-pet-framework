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
  double epsilon = 0.0001;
  BOOST_REQUIRE_CLOSE(results[0].getTime(), 1, epsilon );
  BOOST_REQUIRE_CLOSE(results[1].getTime(), 2, epsilon );
  BOOST_REQUIRE_CLOSE(results[2].getTime(), 3, epsilon );
  BOOST_REQUIRE_CLOSE(results[3].getTime(), 4, epsilon );
}

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetProgressBarManagerTest
#include <boost/test/unit_test.hpp>
#include "../JPetProgressBarManager/JPetProgressBarManager.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(progressBarTest)
{
  JPetProgressBarManager bar;
  BOOST_REQUIRE_EQUAL(bar.getCurrentValue(5, 100), 5);
  BOOST_REQUIRE_EQUAL(bar.getCurrentValue(5, 5), 100);
  BOOST_REQUIRE_EQUAL(bar.getCurrentValue(1, 5), 20);
  BOOST_REQUIRE_EQUAL(bar.getCurrentValue(0, 5), 0);
  BOOST_REQUIRE_EQUAL(bar.getCurrentValue(0, 2), 0);
}

BOOST_AUTO_TEST_SUITE_END()

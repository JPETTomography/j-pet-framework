#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionTest
#include <boost/test/unit_test.hpp>
#include "JPetOption.h"


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( constructor )
{
  JPetOption opt("test", 5);
  BOOST_REQUIRE(opt.isValid());
  auto res = opt.getNameVal();
  BOOST_REQUIRE_EQUAL(res.first, "test");
  BOOST_REQUIRE_EQUAL(boost::any_cast<int>(res.second), 5);
}

BOOST_AUTO_TEST_SUITE_END()

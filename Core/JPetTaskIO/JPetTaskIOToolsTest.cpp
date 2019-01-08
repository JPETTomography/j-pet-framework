#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskIOToolsTest
#include <boost/test/unit_test.hpp>
#include "./JPetTaskIO/JPetTaskIOTools.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(setUserLimits)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();
  auto total = 0ll;
  auto first = 0ll;
  auto last = 0ll;
  bool isOK = true;

  total = 10;
  opts["firstEvent_int"] = 0;
  opts["lastEvent_int"] = 0;
  std::tie(isOK, first, last) = JPetTaskIOTools::setUserLimits(opts, total);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(first, 0);
  BOOST_REQUIRE_EQUAL(last, 0);

  total = 10;
  opts["firstEvent_int"] = 1;
  opts["lastEvent_int"] = 7;
  std::tie(isOK, first, last) = JPetTaskIOTools::setUserLimits(opts, total);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(first, 1);
  BOOST_REQUIRE_EQUAL(last, 7);

  total = 10;
  opts["firstEvent_int"] = 2;
  opts["lastEvent_int"] = 10;
  std::tie(isOK, first, last) = JPetTaskIOTools::setUserLimits(opts, total);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(first, 2);
  BOOST_REQUIRE_EQUAL(last, 9);

  total = 10;
  opts["firstEvent_int"] = 1;
  opts["lastEvent_int"] = 11;
  std::tie(isOK, first, last) = JPetTaskIOTools::setUserLimits(opts, total);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(first, 1);
  BOOST_REQUIRE_EQUAL(last, 9);


}

BOOST_AUTO_TEST_CASE(setUserLimits_wrong)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();
  opts["firstEvent_int"] = 0;
  opts["lastEvent_int"] = 0;
  auto total = 0ll;
  auto first = 0ll;
  auto last = 0ll;
  bool isOK = true;
  std::tie(isOK, first, last) = JPetTaskIOTools::setUserLimits(opts, total);
  BOOST_REQUIRE(!isOK);
  BOOST_REQUIRE_EQUAL(first, -1);
  BOOST_REQUIRE_EQUAL(last, -1);

  total = -1;
  opts["firstEvent_int"] = 1;
  opts["lastEvent_int"] = 11;
  std::tie(isOK, first, last) = JPetTaskIOTools::setUserLimits(opts, total);
  BOOST_REQUIRE(!isOK);
  BOOST_REQUIRE_EQUAL(first, -1);
  BOOST_REQUIRE_EQUAL(last, -1);

  total = 10;
  opts["firstEvent_int"] = 9;
  opts["lastEvent_int"] = 6;
  std::tie(isOK, first, last) = JPetTaskIOTools::setUserLimits(opts, total);
  BOOST_REQUIRE(!isOK);
  BOOST_REQUIRE_EQUAL(first, -1);
  BOOST_REQUIRE_EQUAL(last, -1);
}

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetRecoImageToolsTests
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "./JPetMD5.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)
BOOST_AUTO_TEST_CASE(test_1)
{
  std::string result =
      JPetMD5::getMD5FromFile("unitTestData/JPetCmdParserTest/data.hld");
  BOOST_REQUIRE_EQUAL(result, std::string("d5d9e1c6112b106fabaef2a8ed1f972e"));
}

BOOST_AUTO_TEST_CASE(test_2)
{
  std::string result =
      JPetMD5::getMD5FromFile("unitTestData/JPetRecoImageToolsTest/phantom.pgm");
  BOOST_REQUIRE_EQUAL(result, std::string("37b9ef1add018cfff000d0c73bb9b465"));
}
BOOST_AUTO_TEST_SUITE_END()
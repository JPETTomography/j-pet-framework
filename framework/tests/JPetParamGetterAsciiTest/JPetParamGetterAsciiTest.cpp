#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamGetterAsciiTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetParamGetterAscii/JPetParamGetterAscii.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( noExisting_file )
{
  JPetParamGetterAscii getter;
  BOOST_REQUIRE(getter.generateParamBank("noExisting.txt", 1) == 0);
}

BOOST_AUTO_TEST_CASE( empty_file )
{
  JPetParamGetterAscii getter;
  BOOST_REQUIRE(getter.generateParamBank("empty.txt", 1) == 0);
}

BOOST_AUTO_TEST_CASE( nonempty_file )
{
  JPetParamGetterAscii getter;
  BOOST_REQUIRE(getter.generateParamBank("DB1.json", 1) != 0);
}

BOOST_AUTO_TEST_SUITE_END()

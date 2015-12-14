#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamGetterAsciiTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetParamGetterAscii/JPetParamGetterAscii.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( noExisting_file )
{
  JPetParamGetterAscii getter("noExisting.txt");
  BOOST_REQUIRE(getter.generateParamBank(1) == 0);
}

BOOST_AUTO_TEST_CASE( empty_file )
{
  JPetParamGetterAscii getter("empty.txt");
  BOOST_REQUIRE(getter.generateParamBank(1) == 0);
}

BOOST_AUTO_TEST_CASE( nonempty_file )
{
  JPetParamGetterAscii getter("DB1.json");
  BOOST_REQUIRE(getter.generateParamBank(1) != 0);
}

BOOST_AUTO_TEST_SUITE_END()

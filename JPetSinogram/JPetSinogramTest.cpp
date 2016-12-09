#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSinogramTest
#include <boost/test/unit_test.hpp>
#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;

#include "./JPetSinogram.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( emissionMatrix_projection )
{
  matrix<int> m (2, 2);
  m(0, 0) = 2;
  m(0, 1) = 3;
  m(1, 0) = 4;
  m(1, 1) = 1;

  JPetSinogram sin;
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(0, 0, m), 5ll);
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(1, 0, m), 5ll);
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(0, 90, m), 6ll);
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(1, 90, m), 4ll);
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(0, 45, m), 3ll);
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(1, 45, m), 3ll);
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(2, 45, m), 4ll);
}

BOOST_AUTO_TEST_CASE( emissionMatrix_45theta )
{
  matrix<int> m (3, 3);
  /*
    3 4 5
    1 2 7
    9 3 2
    s = 0 - 5
    s = 1 - 11
    s = 2 - 7
    s = 3 - 4
    s = 4 - 9
  */
  m(0, 0) = 3;
  m(0, 1) = 4;
  m(0, 2) = 5;

  m(1, 0) = 1;
  m(1, 1) = 2;
  m(1, 2) = 7;

  m(2, 0) = 9;
  m(2, 1) = 3;
  m(2, 2) = 2;

  JPetSinogram sin;
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(0, 45, m), 5ll);
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(1, 45, m), 11ll);
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(2, 45, m), 7ll);
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(3, 45, m), 4ll);
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(4, 45, m), 9ll);
}

BOOST_AUTO_TEST_SUITE_END()

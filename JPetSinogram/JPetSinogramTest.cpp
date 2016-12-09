#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSinogramTest
#include <boost/test/unit_test.hpp>
#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;

#include "./JPetSinogram.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( emissionMatrix_sinogram_0_degree )
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
}

BOOST_AUTO_TEST_SUITE_END()

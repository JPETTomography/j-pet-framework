#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSinogramTest
#include <boost/test/unit_test.hpp>
#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;

#include "./JPetSinogram.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( emissionMatrix_sinogram_0_degree )
{
  matrix<int> m (3, 3);
    for (unsigned i = 0; i < m.size1 (); ++ i)
        for (unsigned j = 0; j < m.size2 (); ++ j)
            m (i, j) = 1;

  JPetSinogram sin;
  BOOST_REQUIRE_EQUAL(sin.forwardProjection(0, 0, m), 3ll);
}

BOOST_AUTO_TEST_SUITE_END()

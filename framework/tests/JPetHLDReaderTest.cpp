#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetHLDTest
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetHLDReader/JPetHLDReader.h"

#include <cstddef>


BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE(tt )
{
//  JPetHit hit;
//  BOOST_CHECK_EQUAL(hit.GetEnergy(), 0.0f);
//  BOOST_CHECK_EQUAL(hit.GetQualityOfEnergy(), 0.0f);
//  BOOST_CHECK_EQUAL(hit.GetTime(), 0.0f);
//  BOOST_CHECK_EQUAL(hit.GetQualityOfTime(), 0.0f);
//  
//  BOOST_CHECK(hit.fPos != NULL);
}


BOOST_AUTO_TEST_SUITE_END()

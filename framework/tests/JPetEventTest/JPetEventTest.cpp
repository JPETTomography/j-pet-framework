#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetEventTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetEvent/JPetEvent.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetEvent event;
  BOOST_CHECK_EQUAL(event.GetTime(), 0.0f);
  BOOST_CHECK_EQUAL(event.GetQualityOfTime(), 0.0f);
  
  //BOOST_CHECK(event.fHits->first == NULL);
  //BOOST_CHECK(event.fHits->second == NULL);
}

BOOST_AUTO_TEST_SUITE_END()

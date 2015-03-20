#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamUtilsTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetParamUtils/JPetParamUtils.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_not_related_slots )
{
  /*JPetBarrelSlot slot1;
  JPetBarrelSlot slot2;
  double epsilon = 0.0001;
  BOOST_REQUIRE_CLOSE(JPetParamUtils::distance(slot1, slot2), -1, epsilon);*/
}

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DummyClassTest 
#include <boost/test/unit_test.hpp>



#define private public

#include "../../DummyClass/DummyClass.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( my_test1 )
{
  DummyClass obj;
  BOOST_REQUIRE_EQUAL(&obj, &obj);
  BOOST_REQUIRE_EQUAL(1, 1);
}

BOOST_AUTO_TEST_SUITE_END()

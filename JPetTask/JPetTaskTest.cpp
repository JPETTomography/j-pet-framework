#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../JPetTask/JPetTask.h"
#undef private

BOOST_AUTO_TEST_SUITE(JPetTaskTestSuite)

BOOST_AUTO_TEST_CASE( my_test1 )
{
  //BOOST_REQUIRE(1==0);
}

BOOST_AUTO_TEST_SUITE_END()

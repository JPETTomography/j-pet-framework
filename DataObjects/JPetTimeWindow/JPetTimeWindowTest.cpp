#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTSlotTest
#include <boost/test/unit_test.hpp>

#include "./JPetSigCh/JPetSigCh.h"
#include "./JPetHit/JPetHit.h"
#include "./JPetTimeWindow/JPetTimeWindow.h"


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetTimeWindow test;
  BOOST_REQUIRE(test.getNumberOfEvents() == 0);

}

BOOST_AUTO_TEST_CASE( some_channels )
{
  JPetTimeWindow test("JPetSigCh");
  JPetSigCh ch_test(JPetSigCh::Trailing, 1.2), ch_test2(JPetSigCh::Leading, 1.5), ch_test3(JPetSigCh::Leading, 98);
  test.add<JPetSigCh>(ch_test);
  test.add<JPetSigCh>(ch_test2);
  test.add<JPetSigCh>(ch_test3);

  BOOST_REQUIRE_EQUAL(test.getNumberOfEvents(), 3);
  double epsilon = 0.001;
  BOOST_REQUIRE_CLOSE((dynamic_cast<const JPetSigCh&>(test[0])).getValue(), 1.2, epsilon);
  BOOST_REQUIRE_CLOSE(test.getEvent<JPetSigCh>(1).getValue(), 1.5, epsilon);
  BOOST_REQUIRE_CLOSE(test.getEvent<JPetSigCh>(2).getValue(), 98, epsilon);

}

BOOST_AUTO_TEST_CASE( clearing )
{
  JPetTimeWindow test("JPetHit");
  JPetHit hit1;
  JPetHit hit2;
  test.add<JPetHit>(hit1);
  test.add<JPetHit>(hit2);
  BOOST_REQUIRE_EQUAL(test.getNumberOfEvents(), 2);

  test.Clear();
  BOOST_REQUIRE_EQUAL(test.getNumberOfEvents(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

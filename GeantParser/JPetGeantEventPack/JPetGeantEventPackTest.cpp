#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGeantScinHitsTest
#include <boost/test/unit_test.hpp>

#include "./JPetGeantEventPack/JPetGeantEventPack.h"


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
    JPetGeantEventPack pack;
    BOOST_REQUIRE_EQUAL( pack.GetNumberOfHits(), 0);
    BOOST_REQUIRE_EQUAL( pack.GetNumberOfDecayTrees(), 0);
    BOOST_REQUIRE_EQUAL( pack.GetEventNumber(), 0);
}


BOOST_AUTO_TEST_CASE( setter )
{
    JPetGeantEventPack pack;
    int evtNr = 944;

    pack.SetEventNumber(evtNr);
    BOOST_REQUIRE_EQUAL( pack.GetEventNumber(), evtNr);
}


BOOST_AUTO_TEST_CASE( fillingStructues )
{
    JPetGeantEventPack pack;
    pack.ConstructNextHit();
    BOOST_REQUIRE_EQUAL( pack.GetNumberOfHits(), 1);

    pack.ConstructNextDecayTree();
    BOOST_REQUIRE_EQUAL( pack.GetNumberOfDecayTrees(), 1);

    pack.Clear();

    BOOST_REQUIRE_EQUAL( pack.GetNumberOfHits(), 0);
    BOOST_REQUIRE_EQUAL( pack.GetNumberOfDecayTrees(), 0);
    BOOST_REQUIRE_EQUAL( pack.GetEventNumber(), 0);

}



BOOST_AUTO_TEST_SUITE_END()

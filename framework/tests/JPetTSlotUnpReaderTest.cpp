#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTSlotUnpReaderTest
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetTSlotUnpReader/JPetTSlotUnpReader.h"

#include <cstddef>

using namespace std;

BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( first )
{
    JPetTSlotUnpReader test;
    test.OpenFile("badname.root");
}

BOOST_AUTO_TEST_SUITE_END()

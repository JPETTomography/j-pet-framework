#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetTSlot/JPetTSlot.h"
#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetSignal/JPetSignal.h"
#include <vector>

/// @todo update methods tests are outdated
//#include <TError.h> /// gErrorIgnoreLevel
//  gErrorIgnoreLevel = 7000;
BOOST_AUTO_TEST_SUITE(FirstSuite)


//BOOST_AUTO_TEST_CASE( first )
//{
//  JPetTSlot test;
//  JPetSigCh ch_test(1.3, 1.2), ch_test2(1, 0), ch_test3(123, 98);
//  test.addCh(ch_test);
//  test.addCh(ch_test2);
//  test.addCh(ch_test3);
//
//
//  JPetTSlot test2(test.getSigChVect());
//
//  for (size_t i = 0; i < test.size() || i < test2.size() ; i++) {
//    BOOST_CHECK_EQUAL(test[i].getTime(JPetSigCh::Trailing), test2[i].getTime(JPetSigCh::Trailing));
//    BOOST_CHECK_EQUAL(test[i].getTime(JPetSigCh::Leading), test2[i].getTime(JPetSigCh::Leading));
//  }
//}
//
//BOOST_AUTO_TEST_CASE( second )
//{
//  JPetTSlot test;
//  JPetTSlot test2(test.getSigChVect());
//}

BOOST_AUTO_TEST_SUITE_END()

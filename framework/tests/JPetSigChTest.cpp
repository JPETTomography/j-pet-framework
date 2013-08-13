#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest 
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetSignal/JPetSignal.h"
#include <vector>

             
BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( first )
{
  JPetSigCh test;
  BOOST_CHECK_EQUAL(test.getAmpl(), 0);
  BOOST_CHECK_EQUAL(test.isSlow(), 0);
}

BOOST_AUTO_TEST_CASE( second )
{
	JPetSigCh test;
	JPetPM pm_test;
	JPetScin scin_test;
	JPetTRB trb_test;
	
	test.setPM(pm_test);
	test.setScin(scin_test);
	test.setTRB(trb_test);
	test.addCh(1.2345, 6.789);
	test.addCh(9.876, 5.4321);
	test.addCh(6.66, 6.66);
	
	JPetSigCh test2(test);
	
	BOOST_CHECK_EQUAL(test.getPM().getID(), test2.getPM().getID());
	BOOST_CHECK_EQUAL(test.getTRB().getID(), test2.getTRB().getID());
  
  for (unsigned int i = 0; i < test.size() || i < test2.size() ; i++){
  	BOOST_CHECK_EQUAL(test.getTime(JPetSigCh::kRising, i), test2.getTime(JPetSigCh::kRising, i));
  	BOOST_CHECK_EQUAL(test.getTime(JPetSigCh::kFalling, i), test2.getTime(JPetSigCh::kFalling, i));
  }
  BOOST_CHECK_EQUAL(test.getScin().getID(), test2.getScin().getID());
//  BOOST_CHECK_EQUAL(test.getBarrelSlot(), test2.getBarrelSlot());
//  BOOST_CHECK_EQUAL(test.getChSet(), test2.getChSet());
  
}

BOOST_AUTO_TEST_CASE( third )
{
	JPetSigCh test, test2;
	JPetPM pm_test;
	JPetScin scin_test;
	JPetTRB trb_test;
	
	test.setPM(pm_test);
	test.setScin(scin_test);
	test.setTRB(trb_test);
	test.addCh(1.2345, 6.789);
	test.addCh(9.876, 5.4321);
	test.addCh(6.66, 6.66);
	
	test2 = test;
	
	BOOST_CHECK_EQUAL(test.getPM().getID(), test2.getPM().getID());
	BOOST_CHECK_EQUAL(test.getTRB().getID(), test2.getTRB().getID());
  
  for (unsigned int i = 0; i < test.size() || i < test2.size() ; i++){
  	BOOST_CHECK_EQUAL(test.getTime(JPetSigCh::kRising, i), test2.getTime(JPetSigCh::kRising, i));
  	BOOST_CHECK_EQUAL(test.getTime(JPetSigCh::kFalling, i), test2.getTime(JPetSigCh::kFalling, i));
  }
  BOOST_CHECK_EQUAL(test.getScin().getID(), test2.getScin().getID());
//  BOOST_CHECK_EQUAL(test.getBarrelSlot(), test2.getBarrelSlot());
//  BOOST_CHECK_EQUAL(test.getChSet(), test2.getChSet());
  
}

BOOST_AUTO_TEST_SUITE_END()

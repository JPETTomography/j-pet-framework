#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest 
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetTSlotWriter/JPetTSlotWriter.h"
#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetSignal/JPetSignal.h"
#include <vector>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( first ) {
	JPetTSlotWriter writer;
	JPetTSlot tslot;
	
	writer.write(tslot, "test.root");
}

BOOST_AUTO_TEST_SUITE_END()

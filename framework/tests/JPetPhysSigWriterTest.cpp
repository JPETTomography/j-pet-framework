#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPhysSigWriterTest
#include <boost/test/unit_test.hpp>

#define protected public
#define private public

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include "../JPetPhysSigWriter/JPetPhysSigWriter.h"

#include <cstddef>
#include <vector>

BOOST_AUTO_TEST_SUITE (FirstSuite)

BOOST_AUTO_TEST_CASE (default_constructor)
{
	JPetPhysSigWriter writer;
	BOOST_CHECK(writer.fFile == NULL);
}

BOOST_AUTO_TEST_CASE (test3)
{
	JPetPhysSigWriter writer;
	JPetSignal* signal = new JPetSignal;

	BOOST_CHECK(writer.Write(*signal,"phys1.sig.root"));
}

BOOST_AUTO_TEST_CASE (test4)
{
	JPetPhysSigWriter writer;
	std::vector<JPetSignal> signal_vect;

	for (int i=0; i<5; i++) signal_vect.push_back(*(new JPetSignal));

	BOOST_CHECK(writer.Write(signal_vect,"phys2.sig.root"));
}

BOOST_AUTO_TEST_CASE (test5)
{
	//init SigCh
	
	std::vector<JPetSigCh> falling;
	std::vector<JPetSigCh> rising;

	for(int i=0; i<4; i++) {
	  falling.push_back(*(new JPetSigCh));
	  rising.push_back(*(new JPetSigCh));
	}

	//init Signal
	
	JPetSignal* signal = new JPetSignal (0.0, 0.0, true, falling, rising);
	
	//init and test writer
	
	JPetPhysSigWriter writer;
	
	BOOST_CHECK(writer.Write(*signal,"phys.sig.root"));
}

BOOST_AUTO_TEST_SUITE_END()

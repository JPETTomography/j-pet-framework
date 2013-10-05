#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPhysSigWriterTest
#include <boost/test/unit_test.hpp>

#define protected public
#define private public

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include "../JPetPhysSigWriter/JPetPhysSigWriter.h"

#include <cstddef>

BOOST_AUTO_TEST_SUITE (FirstSuite)

BOOST_AUTO_TEST_CASE (default_constructor)
{
	JPetPhysSigWriter writer;
	BOOST_CHECK(writer.fFile == NULL);
}

BOOST_AUTO_TEST_CASE (test3)
{
	JPetPhysSigWriter writer;
	vector<JPetSignal> signal_vect;

	for (int i=0; i<5; i++) signal_vect.push_back(*(new JPetSignal));
	BOOST_CHECK_EQUAL(writer.Write(signal_vect,"phys.sig.root"),true);
}


BOOST_AUTO_TEST_SUITE_END()

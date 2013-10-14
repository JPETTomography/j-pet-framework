#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPhysSigReaderTest
#include <boost/test/unit_test.hpp>

#define protected public
#define private public

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include "../JPetPhysSigReader/JPetPhysSigReader.h"

#include <cstddef>
#include <iostream>
#include <vector>

class JPetSignal;

BOOST_AUTO_TEST_SUITE (FirstSuite)

BOOST_AUTO_TEST_CASE (default_constructor)
{
	JPetPhysSigReader reader;
	BOOST_CHECK(reader.fFile == NULL);
	BOOST_CHECK(reader.fTree == NULL);
	BOOST_CHECK(reader.fBranch == NULL);
	BOOST_CHECK(reader.GetSignal() == NULL);
}

BOOST_AUTO_TEST_CASE (bad_file)
{
	JPetPhysSigReader reader;

	reader.OpenFile("bad_file.txt");

	BOOST_CHECK(reader.fFile == NULL);
	BOOST_CHECK(reader.GetSignal() == NULL);

	reader.CloseFile();
}

BOOST_AUTO_TEST_CASE (proper_file)
{
	JPetPhysSigReader reader;
	reader.OpenFile("phys2.sig.root");
	
	std::cout<<reader.GetEntries()<<std::endl;

	BOOST_CHECK(reader.GetEntries()>0);
	BOOST_CHECK(reader.GetEntry(1)>0);

	reader.CloseFile();

	BOOST_CHECK(reader.fFile == NULL);
	BOOST_CHECK(reader.fTree == NULL);
	BOOST_CHECK(reader.fBranch == NULL);
	BOOST_CHECK(reader.GetSignal() == NULL);

}

BOOST_AUTO_TEST_CASE (test5)
{
	JPetPhysSigReader reader;
	reader.OpenFile("phys.sig.root");

	BOOST_CHECK(reader.GetEntries()>0);
	BOOST_CHECK(reader.GetEntry(0)>0);
	BOOST_CHECK(reader.GetSignal() != NULL);

	JPetSignal* signal = reader.GetSignal();

	BOOST_CHECK_EQUAL(signal->GetT(),10.0);
	BOOST_CHECK_EQUAL(signal->GetQual(),10.0);
	BOOST_CHECK_EQUAL(signal->IsLeft(),true);
	BOOST_CHECK_EQUAL(signal->GetNTresholds(JPetSignal::kRising),4);
	BOOST_CHECK_EQUAL(signal->GetNTresholds(JPetSignal::kFalling),4);


}

//BOOST_AUTO_TEST_CASE (test5)
//{
//	//init SigCh
//	
//	std::vector<JPetSigCh> falling;
//	std::vector<JPetSigCh> rising;
//
//	for(int i=0; i<4; i++) {
//	  falling.push_back(*(new JPetSigCh));
//	  rising.push_back(*(new JPetSigCh));
//	}
//
//	//init Signal
//	
//	JPetSignal* signal = new JPetSignal (0.0, 0.0, true, falling, rising);
//	
//	//init and test writer
//	
//	JPetPhysSigWriter writer;
//	
//	BOOST_CHECK(writer.Write(*signal,"phys.sig.root"));
//}

BOOST_AUTO_TEST_SUITE_END()

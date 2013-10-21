#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTSlotRawReaderTest
#include <boost/test/unit_test.hpp>

#define protected public
#define private public

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetTSlot/JPetTSlot.h"
#include "../JPetTSlotRawReader/JPetTSlotRawReader.h"

#include <cstddef>
#include <iostream>
#include <vector>

class JPetTSlot;

BOOST_AUTO_TEST_SUITE (FirstSuite)

BOOST_AUTO_TEST_CASE (default_constructor)
{
	JPetTSlotRawReader reader;
	BOOST_CHECK(reader.fFile == NULL);
	BOOST_CHECK(reader.fTree == NULL);
	BOOST_CHECK(reader.fBranch == NULL);
	BOOST_CHECK(reader.GetTSlot() == NULL);
}

BOOST_AUTO_TEST_CASE (bad_file)
{
	JPetTSlotRawReader reader;

	reader.OpenFile("bad_file.txt");

	BOOST_CHECK(reader.fFile == NULL);
	BOOST_CHECK(reader.GetTSlot() == NULL);

	reader.CloseFile();
}

//BOOST_AUTO_TEST_CASE (proper_file)
//{
//	JPetTSlotRawReader reader;
//	reader.OpenFile("phys2.sig.root");
//	
//	std::cout<<reader.GetEntries()<<std::endl;
//
//	BOOST_CHECK(reader.GetEntries()>0);
//	BOOST_CHECK(reader.GetEntry(1)>0);
//
//	reader.CloseFile();
//
//	BOOST_CHECK(reader.fFile == NULL);
//	BOOST_CHECK(reader.fTree == NULL);
//	BOOST_CHECK(reader.fBranch == NULL);
//	BOOST_CHECK(reader.GetTSlot() == NULL);
//
//}

BOOST_AUTO_TEST_SUITE_END()

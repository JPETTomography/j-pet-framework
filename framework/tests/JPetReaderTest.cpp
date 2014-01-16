#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetReaderTest
#include <boost/test/unit_test.hpp>

#define protected public
#define private public

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include "../JPetReader/JPetReader.h"

#include <cstddef>
#include <iostream>
#include <vector>

class JPetReader;
class JPetSignal;

BOOST_AUTO_TEST_SUITE (FirstSuite)

BOOST_AUTO_TEST_CASE (default_constructor)
{
	JPetReader reader;
	BOOST_CHECK(reader.fBranch == NULL);
	BOOST_CHECK(reader.fFile == NULL);
	BOOST_CHECK(reader.fObject == NULL);
	BOOST_CHECK(reader.fTree == NULL);

}

BOOST_AUTO_TEST_CASE (bad_file)
{
	JPetReader reader;

	reader.OpenFile("bad_file.txt");

	BOOST_CHECK(reader.fBranch == NULL);
	BOOST_CHECK(reader.fFile == NULL);
	BOOST_CHECK(reader.fObject == NULL);
	BOOST_CHECK(reader.fTree == NULL);

	reader.CloseFile();
}

BOOST_AUTO_TEST_CASE (proper_file)
{

	JPetReader reader;
	
	reader.OpenFile("phys.sig.root");
	
	reader.ReadData("");

	BOOST_CHECK(reader.fBranch != NULL);
	BOOST_CHECK(reader.fFile != NULL);
	BOOST_CHECK(reader.fObject != NULL);
	BOOST_CHECK(reader.fTree != NULL);

	BOOST_CHECK(reader.GetEntries()>0);
	BOOST_CHECK(reader.GetEntry(1)>0);

	reader.CloseFile();

	BOOST_CHECK(reader.fBranch == NULL);
	BOOST_CHECK(reader.fFile == NULL);
	BOOST_CHECK(reader.fObject == NULL);
	BOOST_CHECK(reader.fTree == NULL);

}

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetReaderTest
#include <boost/test/unit_test.hpp>

#define protected public
#define private public

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include "../JPetWriter/JPetWriter.h"
#include "../JPetReader/JPetReader.h"

#include <cstddef>
#include <iostream>
#include <vector>

#include <TError.h> /// gErrorIgnoreLevel
#include <TObjString.h>


BOOST_AUTO_TEST_SUITE (FirstSuite)

BOOST_AUTO_TEST_CASE (default_constructor)
{
  JPetReader reader;
  BOOST_CHECK(reader.fBranch == 0);
  BOOST_CHECK(reader.fFile == NULL);
  BOOST_CHECK(reader.fObject == 0);
  BOOST_CHECK(reader.fTree == 0);

}

BOOST_AUTO_TEST_CASE (bad_file)
{
  gErrorIgnoreLevel = 6000; /// we turn off the ROOT error messages
  JPetReader reader;
  /// not a ROOT file
  BOOST_CHECK(!reader.OpenFile("bad_file.txt"));
  BOOST_CHECK(reader.fBranch == 0);
  BOOST_CHECK(reader.fFile == NULL);
  BOOST_CHECK(reader.fObject == 0);
  BOOST_CHECK(reader.fTree == 0);

  reader.CloseFile();
}

BOOST_AUTO_TEST_CASE (open_file)
{
    //std::cout << "test if open constructor works" << std::endl;
    JPetReader constructor_open("test.root");
    constructor_open.ReadData("");
    constructor_open.CloseFile();
    
    //std::cout << "test if OpenFile works" << std::endl;
    JPetReader reader;
    BOOST_CHECK( reader.OpenFile("test.root") );
    reader.ReadData("");
    reader.CloseFile();
}

BOOST_AUTO_TEST_CASE (read_and_write_header )
{
    TObjString input_string("Ala ma kota");
    JPetWriter writer("test_file.root");
    writer.WriteHeader(&input_string);
    JPetSigCh signal;
    writer.Write(signal);
    writer.CloseFile();
    
    JPetReader reader("test_file.root");
    TObjString* output_string = static_cast<TObjString *>(reader.GetHeader());
    BOOST_CHECK(input_string.Compare(output_string) == 0);
}

/// @todo add a proper file example !!
//BOOST_AUTO_TEST_CASE (proper_file)
//{
//  JPetReader reader;
//  bool openedPropery = reader.OpenFile("phys.sig.root");
//  BOOST_CHECK(openedPropery );
//  if (openedPropery) {
//    reader.ReadData("");
//    BOOST_CHECK(reader.fBranch != 0);
//    BOOST_CHECK(reader.fFile.IsOpen());
//    BOOST_CHECK(reader.fObject != 0);
//    BOOST_CHECK(reader.fTree != 0);
//
//    BOOST_CHECK(reader.GetEntries() > 0);
//    BOOST_CHECK(reader.GetEntry(1) > 0);
//
//    reader.CloseFile();
//
//    BOOST_CHECK(reader.fBranch == 0);
//    BOOST_CHECK(reader.fFile.IsOpen());
//    BOOST_CHECK(reader.fObject == 0);
//    BOOST_CHECK(reader.fTree == 0);
//  }
//}

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetReaderTest
#include <boost/test/unit_test.hpp>

#define private public
#define protected public

#include "../../JPetReader/JPetReader.h"
#include "../../JPetWriter/JPetWriter.h"
#include "../../JPetSignal/JPetSignal.h"

#include <cstddef>
#include <iostream>
#include <vector>

#include <TError.h> /// gErrorIgnoreLevel
#include <TObjString.h>

// method list
/*
  JPetReader(void);
  explicit JPetReader(const char* p_filename);
  virtual ~JPetReader(void);
  virtual void closeFile();
  virtual long long GetEntries () const { return fTree->GetEntries(); }
  virtual int GetEntry (int entryNo);
  virtual bool OpenFile(const char* filename);
  virtual void readData(const char* objname = "");
  virtual TNamed& GetData () {return *fObject;}
  JPetTreeHeader * GetHeaderClone()const;
  void fillContainer(std::vector<T> &p_container, const std::string &p_objectName);
  virtual void closeTFile(void){};
*/

BOOST_AUTO_TEST_SUITE (FirstSuite)


BOOST_AUTO_TEST_CASE (default_constructor)
{
  JPetReader reader;
  BOOST_REQUIRE(reader.fBranch == 0);
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(reader.fObject == 0);
  BOOST_REQUIRE(reader.fTree == 0);
}

BOOST_AUTO_TEST_CASE (bad_file)
{
  gErrorIgnoreLevel = 6000; /// we turn off the ROOT error messages
  JPetReader reader;
  /// not a ROOT file
  BOOST_REQUIRE(!reader.openFile("bad_file.txt"));
  BOOST_REQUIRE(reader.fBranch == 0);
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(reader.fObject == 0);
  BOOST_REQUIRE(reader.fTree == 0);
}

BOOST_AUTO_TEST_CASE (open_file)
{
  TFile file("test.root", "RECREATE");
  TTree tree("tree", "tree");
  JPetSignal* filler = 0;
  tree.Branch("JPetSignal", "JPetSignal", &filler);

  JPetSignal signal;
  signal.setTime(101.43);
  filler = &signal;
  tree.Fill();
  file.Write();
  file.Close("R");

  JPetReader constructor_open("test.root");
  std::cout <<"open?:"<< constructor_open.fFile->IsOpen()<<std::endl;
  BOOST_REQUIRE(constructor_open.readData("tree"));
  constructor_open.closeFile();

  JPetReader reader;
  BOOST_REQUIRE(reader.openFile("test.root") );
  BOOST_REQUIRE(reader.readData("tree"));
}

BOOST_AUTO_TEST_CASE (read_and_write_objects )
{
  TFile file("test2.root", "RECREATE");
  TTree tree("tree", "tree");
  JPetSignal* filler = 0;
  tree.Branch("JPetSignal", "JPetSignal", &filler);

  JPetSignal signal;
  signal.setTime(101.43);
  filler = &signal;
  tree.Fill();
  file.Write();
  file.Close("R");
  
  JPetReader reader("test2.root");
  BOOST_REQUIRE_EQUAL(reader.getEntries(), 1);
  reader.getEntry(0);
  JPetSignal & signal2 = (JPetSignal&)reader.getData();
  BOOST_REQUIRE_EQUAL(signal.getTime(), signal2.getTime());
}

BOOST_AUTO_TEST_CASE (proper_file)
{
  JPetReader reader;
  bool openedPropery = reader.openFile("test2.root");
  BOOST_REQUIRE(openedPropery );
  if (openedPropery) {
    reader.readData("tree");
    BOOST_REQUIRE(reader.fBranch != 0);
    BOOST_REQUIRE(reader.isOpen());
    BOOST_REQUIRE(reader.fObject != 0);
    BOOST_REQUIRE(reader.fTree != 0);

    BOOST_REQUIRE(reader.getEntries() > 0);
    BOOST_REQUIRE(reader.getEntry(0) > 0);
  }
}

BOOST_AUTO_TEST_CASE (read_and_write_header )
{
  JPetTreeHeader input_header(1);
  JPetWriter writer("test3.root");
  writer.writeHeader(&input_header);
  JPetTSlot tslot;
  writer.write(tslot);
  writer.closeFile();
  
  JPetReader reader("test3.root");
  JPetTreeHeader* output_header = reader.getHeaderClone();
  BOOST_REQUIRE_EQUAL(input_header.getRunNumber(), output_header->getRunNumber());
}

BOOST_AUTO_TEST_SUITE_END()

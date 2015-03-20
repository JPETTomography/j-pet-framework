#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetReaderTest
#include <boost/test/unit_test.hpp>

#define private public
#define protected public

#include "../../JPetReader/JPetReader.h"
#include "../../JPetWriter/JPetWriter.h"

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

BOOST_AUTO_TEST_SUITE_END()

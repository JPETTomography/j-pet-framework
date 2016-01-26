#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetReaderTest
#include <boost/test/unit_test.hpp>

#define private public
#define protected public

#include "../JPetReader/JPetReader.h"
#include "../JPetWriter/JPetWriter.h"

#include <cstddef>
#include <iostream>
#include <vector>

#include <TError.h> /// gErrorIgnoreLevel
#include <TObjString.h>

// method list
  //JPetReader(void); //maybe remove this one
  //explicit JPetReader(const char* p_filename);

  //virtual Event& getCurrentEvent();
  //virtual bool nextEvent();
  //virtual bool firstEvent();
  //virtual bool lastEvent();
  //virtual bool nthEvent(int n);
  //virtual long long getCurrentEventNumber();
  //virtual long long getNbOfAllEvents();

  //virtual bool openFileAndLoadData(const char* filename, const char* treename = "tree");
  //virtual void closeFile();
  //JPetTreeHeader* getHeaderClone() const;

  //virtual TObject* getObject(const char* name);
  //virtual bool isOpen() const;

BOOST_AUTO_TEST_SUITE (JPetReaderTestSuite)


BOOST_AUTO_TEST_CASE (default_constructor)
{
  JPetReader reader;
  BOOST_REQUIRE(std::string(reader.getCurrentEvent().GetName())==std::string("Empty event"));
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(!reader.nextEvent());
  BOOST_REQUIRE(!reader.firstEvent());
  BOOST_REQUIRE(!reader.lastEvent());
  BOOST_REQUIRE(!reader.nthEvent(0));
  BOOST_REQUIRE(!reader.nthEvent(1));
  BOOST_REQUIRE(!reader.nthEvent(-1));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEventNumber(), -1);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 0);
  BOOST_REQUIRE(!reader.getHeaderClone());
  BOOST_REQUIRE(!reader.getObject("testObj"));
}

BOOST_AUTO_TEST_CASE (bad_file)
{
  gErrorIgnoreLevel = 6000; /// we turn off the ROOT error messages
  JPetReader reader;
  /// not a ROOT file
  BOOST_REQUIRE(!reader.openFileAndLoadData("bad_file.txt", "tree"));
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(std::string(reader.getCurrentEvent().GetName())==std::string("Empty event"));
  BOOST_REQUIRE(!reader.nextEvent());
  BOOST_REQUIRE(!reader.firstEvent());
  BOOST_REQUIRE(!reader.lastEvent());
  BOOST_REQUIRE(!reader.nthEvent(0));
  BOOST_REQUIRE(!reader.nthEvent(1));
  BOOST_REQUIRE(!reader.nthEvent(-1));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEventNumber(), -1);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 0);
  BOOST_REQUIRE(!reader.getHeaderClone());
  BOOST_REQUIRE(!reader.getObject("testObj"));
}

BOOST_AUTO_TEST_CASE (good_file_with_constructor)
{
  JPetReader reader("small.root");
  BOOST_REQUIRE(reader.isOpen());
  BOOST_REQUIRE(std::string(reader.getCurrentEvent().GetName())==std::string("JPetTSlot"));
  BOOST_REQUIRE(reader.nextEvent());
  BOOST_REQUIRE(reader.firstEvent());
  BOOST_REQUIRE(reader.lastEvent());
  BOOST_REQUIRE(reader.nthEvent(0));
  BOOST_REQUIRE(reader.nthEvent(5));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEventNumber(), 5);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 10);
  BOOST_REQUIRE(reader.getHeaderClone());
}
BOOST_AUTO_TEST_CASE (good_file_getObject)
{
  JPetReader reader("small.root");
  BOOST_REQUIRE(!reader.getObject("nonExistentObj"));
  BOOST_REQUIRE(reader.getObject("tree"));
}

BOOST_AUTO_TEST_CASE (good_file_openFileAndLoadData)
{
  JPetReader reader;
  BOOST_REQUIRE(reader.openFileAndLoadData("small.root","tree"));
  BOOST_REQUIRE(reader.isOpen());
  BOOST_REQUIRE(std::string(reader.getCurrentEvent().GetName())==std::string("JPetTSlot"));
  BOOST_REQUIRE(reader.firstEvent());
  BOOST_REQUIRE(reader.nextEvent());
  BOOST_REQUIRE(reader.lastEvent());
  BOOST_REQUIRE(reader.nthEvent(0));
  BOOST_REQUIRE(reader.nthEvent(5));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEventNumber(), 5);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 10);
  BOOST_REQUIRE(reader.getHeaderClone());
  
}

BOOST_AUTO_TEST_CASE (good_file_closeFile)
{
  JPetReader reader;
  BOOST_REQUIRE(reader.openFileAndLoadData("small.root","tree"));
  BOOST_REQUIRE(reader.isOpen());
  reader.closeFile();
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(std::string(reader.getCurrentEvent().GetName())==std::string("Empty event"));
  BOOST_REQUIRE(!reader.nextEvent());
  BOOST_REQUIRE(!reader.firstEvent());
  BOOST_REQUIRE(!reader.lastEvent());
  BOOST_REQUIRE(!reader.nthEvent(0));
  BOOST_REQUIRE(!reader.nthEvent(1));
  BOOST_REQUIRE(!reader.nthEvent(-1));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEventNumber(), -1);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 0);
  BOOST_REQUIRE(!reader.getHeaderClone());
  BOOST_REQUIRE(!reader.getObject("testObj"));
}

BOOST_AUTO_TEST_SUITE_END()

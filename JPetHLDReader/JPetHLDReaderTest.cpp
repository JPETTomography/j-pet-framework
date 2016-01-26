#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetHLDReaderTest
#include <boost/test/unit_test.hpp>

#define private public
#define protected public

#include "../JPetHLDReader/JPetHLDReader.h"

#include <cstddef>
#include <iostream>
#include <vector>

#include <TError.h> /// gErrorIgnoreLevel
#include <TObjString.h>

// method list

BOOST_AUTO_TEST_SUITE (FirstSuite)


BOOST_AUTO_TEST_CASE (default_constructor)
{
  JPetHLDReader reader;
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(!reader.nextEvent());
  BOOST_REQUIRE(!reader.firstEvent());
  BOOST_REQUIRE(!reader.lastEvent());
  BOOST_REQUIRE(!reader.nthEvent(0));
  BOOST_REQUIRE(!reader.nthEvent(1));
  BOOST_REQUIRE(!reader.nthEvent(-1));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEventNumber(), -1);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 0);
}

BOOST_AUTO_TEST_CASE (bad_file)
{
  gErrorIgnoreLevel = 6000; /// we turn off the ROOT error messages
  JPetHLDReader reader;
  /// not a ROOT file
  BOOST_REQUIRE(!reader.openFileAndLoadData("bad_file.txt", "tree"));
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(!reader.nextEvent());
  BOOST_REQUIRE(!reader.firstEvent());
  BOOST_REQUIRE(!reader.lastEvent());
  BOOST_REQUIRE(!reader.nthEvent(0));
  BOOST_REQUIRE(!reader.nthEvent(1));
  BOOST_REQUIRE(!reader.nthEvent(-1));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEventNumber(), -1);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 0);
}

BOOST_AUTO_TEST_CASE (good_file_with_constructor)
{
  JPetHLDReader reader("unitTestData/JPetHLDReaderTest/small_hld.root");
  BOOST_REQUIRE(reader.isOpen());
  BOOST_REQUIRE(reader.nextEvent());
  BOOST_REQUIRE(reader.firstEvent());
  BOOST_REQUIRE(reader.lastEvent());
  BOOST_REQUIRE(reader.nthEvent(0));
  BOOST_REQUIRE(reader.nthEvent(5));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEventNumber(), 5);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 10);
}

BOOST_AUTO_TEST_CASE (good_file_openFileAndLoadData)
{
  JPetHLDReader reader;
  BOOST_REQUIRE(reader.openFileAndLoadData("unitTestData/JPetHLDReaderTest/small_hld.root","T"));
  BOOST_REQUIRE(reader.isOpen());
  BOOST_REQUIRE(reader.firstEvent());
  BOOST_REQUIRE(reader.nextEvent());
  BOOST_REQUIRE(reader.lastEvent());
  BOOST_REQUIRE(reader.nthEvent(0));
  BOOST_REQUIRE(reader.nthEvent(5));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEventNumber(), 5);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 10);
  
}

BOOST_AUTO_TEST_CASE (good_file_closeFile)
{
  JPetHLDReader reader;
  BOOST_REQUIRE(reader.openFileAndLoadData("unitTestData/JPetHLDReaderTest/small_hld.root","T"));
  BOOST_REQUIRE(reader.isOpen());
  reader.closeFile();
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(!reader.nextEvent());
  BOOST_REQUIRE(!reader.firstEvent());
  BOOST_REQUIRE(!reader.lastEvent());
  BOOST_REQUIRE(!reader.nthEvent(0));
  BOOST_REQUIRE(!reader.nthEvent(1));
  BOOST_REQUIRE(!reader.nthEvent(-1));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEventNumber(), -1);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEvents(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

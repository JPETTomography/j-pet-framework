#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetReaderTest
#include <cstddef>
#include <iostream>
#include <vector>
#include <boost/test/unit_test.hpp>
#include <TError.h> /// gErrorIgnoreLevel
#include <TObjString.h>

#include "./JPetReader/JPetReader.h"
#include "./JPetWriter/JPetWriter.h"


BOOST_AUTO_TEST_SUITE (JPetReaderTestSuite)

BOOST_AUTO_TEST_CASE (default_constructor)
{
  JPetReader reader;
  BOOST_REQUIRE_EQUAL(std::string(reader.getCurrentEntry().GetName()),  std::string("Empty event"));
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(!reader.nextEntry());
  BOOST_REQUIRE(!reader.firstEntry());
  BOOST_REQUIRE(!reader.lastEntry());
  BOOST_REQUIRE(!reader.nthEntry(0));
  BOOST_REQUIRE(!reader.nthEntry(1));
  BOOST_REQUIRE(!reader.nthEntry(-1));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEntryNumber(), -1);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), 0);
  BOOST_REQUIRE(!reader.getHeaderClone());
  BOOST_REQUIRE(!reader.getObjectFromFile("testObj"));
}

BOOST_AUTO_TEST_CASE (bad_file)
{
  gErrorIgnoreLevel = 6000; /// we turn off the ROOT error messages
  JPetReader reader;
  /// not a ROOT file
  BOOST_REQUIRE(!reader.openFileAndLoadData("bad_file.txt", "tree"));
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE_EQUAL(std::string(reader.getCurrentEntry().GetName()), std::string("Empty event"));
  BOOST_REQUIRE(!reader.nextEntry());
  BOOST_REQUIRE(!reader.firstEntry());
  BOOST_REQUIRE(!reader.lastEntry());
  BOOST_REQUIRE(!reader.nthEntry(0));
  BOOST_REQUIRE(!reader.nthEntry(1));
  BOOST_REQUIRE(!reader.nthEntry(-1));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEntryNumber(), -1);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), 0);
  BOOST_REQUIRE(!reader.getHeaderClone());
  BOOST_REQUIRE(!reader.getObjectFromFile("testObj"));
}

BOOST_AUTO_TEST_CASE (good_file_with_constructor)
{
  JPetReader reader("unitTestData/JPetReaderTest/timewindows_v2.root", "tree");
  BOOST_REQUIRE(reader.isOpen());
  BOOST_REQUIRE_EQUAL(std::string(reader.getCurrentEntry().GetName()), std::string("JPetTimeWindow"));
  BOOST_REQUIRE(reader.nextEntry());
  BOOST_REQUIRE(reader.firstEntry());
  BOOST_REQUIRE(reader.lastEntry());
  BOOST_REQUIRE(reader.nthEntry(0));
  BOOST_REQUIRE(reader.nthEntry(5));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEntryNumber(), 5);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), 10);
  BOOST_REQUIRE(reader.getHeaderClone());
}

BOOST_AUTO_TEST_CASE (good_file_getObject)
{
  JPetReader reader("unitTestData/JPetReaderTest/timewindows_v2.root", "tree");
  BOOST_REQUIRE(!reader.getObjectFromFile("nonExistentObj"));
  BOOST_REQUIRE(reader.getObjectFromFile("tree"));
}

BOOST_AUTO_TEST_CASE (good_file_openFileAndLoadData)
{
  JPetReader reader;
  BOOST_REQUIRE(reader.openFileAndLoadData("unitTestData/JPetReaderTest/timewindows_v2.root", "tree"));
  BOOST_REQUIRE(reader.isOpen());
  BOOST_REQUIRE_EQUAL(std::string(reader.getCurrentEntry().GetName()), std::string("JPetTimeWindow"));
  BOOST_REQUIRE(reader.firstEntry());
  BOOST_REQUIRE(reader.nextEntry());
  BOOST_REQUIRE(reader.lastEntry());
  BOOST_REQUIRE(reader.nthEntry(0));
  BOOST_REQUIRE(reader.nthEntry(5));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEntryNumber(), 5);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), 10);
  BOOST_REQUIRE(reader.getHeaderClone());
}

BOOST_AUTO_TEST_CASE (good_file_closeFile)
{
  JPetReader reader;
  BOOST_REQUIRE(reader.openFileAndLoadData("unitTestData/JPetReaderTest/timewindows_v2.root", "tree"));
  BOOST_REQUIRE(reader.isOpen());
  reader.closeFile();
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(std::string(reader.getCurrentEntry().GetName()) == std::string("Empty event"));
  BOOST_REQUIRE(!reader.nextEntry());
  BOOST_REQUIRE(!reader.firstEntry());
  BOOST_REQUIRE(!reader.lastEntry());
  BOOST_REQUIRE(!reader.nthEntry(0));
  BOOST_REQUIRE(!reader.nthEntry(1));
  BOOST_REQUIRE(!reader.nthEntry(-1));
  BOOST_REQUIRE_EQUAL(reader.getCurrentEntryNumber(), -1);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), 0);
  BOOST_REQUIRE(!reader.getHeaderClone());
  BOOST_REQUIRE(!reader.getObjectFromFile("testObj"));
}

/// @todo The correct file should be added
//BOOST_AUTO_TEST_CASE (file_with_no_jpettreeheader)
//{
//JPetReader reader;
//BOOST_REQUIRE(reader.openFileAndLoadData("unitTestData/JPetReaderTest/testWithNoJPetTreeHeader.root", "tree"));
//BOOST_REQUIRE(!reader.getHeaderClone());
//}

BOOST_AUTO_TEST_SUITE_END()

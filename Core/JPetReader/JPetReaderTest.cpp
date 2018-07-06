/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetReaderTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetReaderTest

#include "./JPetReader/JPetReader.h"
#include "./JPetWriter/JPetWriter.h"
#include <boost/test/unit_test.hpp>
#include <TObjString.h>
#include <TError.h>
#include <iostream>
#include <cstddef>
#include <vector>

BOOST_AUTO_TEST_SUITE (JPetReaderTestSuite)

BOOST_AUTO_TEST_CASE (default_constructor)
{
  JPetReader reader;
  BOOST_REQUIRE_EQUAL(
    std::string(reader.getCurrentEntry().GetName()),
    std::string("Empty event")
  );
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
  gErrorIgnoreLevel = 6000;
  JPetReader reader;
  BOOST_REQUIRE(!reader.openFileAndLoadData("bad_file.txt", "tree"));
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE_EQUAL(
    std::string(reader.getCurrentEntry().GetName()),
    std::string("Empty event")
  );
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
  BOOST_REQUIRE_EQUAL(
    std::string(reader.getCurrentEntry().GetName()),
    std::string("JPetTimeWindow")
  );
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
  BOOST_REQUIRE(
    reader.openFileAndLoadData(
      "unitTestData/JPetReaderTest/timewindows_v2.root",
      "tree"
    )
  );
  BOOST_REQUIRE(reader.isOpen());
  BOOST_REQUIRE_EQUAL(
    std::string(reader.getCurrentEntry().GetName()),
    std::string("JPetTimeWindow")
  );
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
  BOOST_REQUIRE(
    reader.openFileAndLoadData(
      "unitTestData/JPetReaderTest/timewindows_v2.root",
      "tree"
    )
  );
  BOOST_REQUIRE(reader.isOpen());
  reader.closeFile();
  BOOST_REQUIRE(!reader.isOpen());
  BOOST_REQUIRE(
    std::string(reader.getCurrentEntry().GetName()) == std::string("Empty event")
  );
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

BOOST_AUTO_TEST_SUITE_END()

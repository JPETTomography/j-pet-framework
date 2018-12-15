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
 *  @file JPetHaddTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetHaddTest
#include "JPetBarrelSlot/JPetBarrelSlot.h"
#include "JPetEvent/JPetEvent.h"
#include "JPetReader/JPetReader.h"
#include "JPetScin/JPetScin.h"
#include "JPetTimeWindow/JPetTimeWindow.h"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

BOOST_AUTO_TEST_SUITE(JPetHaddTestSuite)

std::string exec(std::string cmd)
{
  char buffer[128];
  std::string result = "";
  FILE* pipe = popen(cmd.c_str(), "r");
  if (!pipe)
    throw std::runtime_error("popen() failed!");
  try {
    while (!feof(pipe)) {
      if (fgets(buffer, 128, pipe) != NULL)
        result += buffer;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  return result;
}

BOOST_AUTO_TEST_CASE(hadd_test)
{
  std::string resultFileName = "";
  std::string firstFileName = "unitTestData/JPetHaddTest/single_link_def/dabc_17237091818.hadd.test.root";
  std::string secondFileName = "unitTestData/JPetHaddTest/single_link_def/dabc_17237093844.hadd.test.root";
#if ROOT_VERSION_CODE < ROOT_VERSION(6, 0, 0)
  resultFileName = "unitTestData/JPetHaddTest/result_root5.hadd.test.root";
#else
  resultFileName = "unitTestData/JPetHaddTest/result_root6.hadd.test.root";
#endif
  exec("hadd -f " + resultFileName + " " + firstFileName + " " + secondFileName);
  JPetReader readerFirstFile(firstFileName.c_str());
  JPetReader readerSecondFile(secondFileName.c_str());
  JPetReader readerResultFile(resultFileName.c_str());
  BOOST_REQUIRE(readerFirstFile.isOpen());
  BOOST_REQUIRE(readerSecondFile.isOpen());
  BOOST_REQUIRE(readerResultFile.isOpen());
  BOOST_REQUIRE_EQUAL(std::string(readerFirstFile.getCurrentEntry().GetName()), std::string("JPetTimeWindow"));
  BOOST_REQUIRE_EQUAL(std::string(readerSecondFile.getCurrentEntry().GetName()), std::string("JPetTimeWindow"));
  BOOST_REQUIRE_EQUAL(std::string(readerResultFile.getCurrentEntry().GetName()), std::string("JPetTimeWindow"));
  long long firstFileNumberOfEntries = readerFirstFile.getNbOfAllEntries();
  long long secondFileNumberOfEntries = readerSecondFile.getNbOfAllEntries();
  long long resultFileNumberOfEntires = readerResultFile.getNbOfAllEntries();
  BOOST_REQUIRE_EQUAL(resultFileNumberOfEntires, firstFileNumberOfEntries + secondFileNumberOfEntries);
  for (long long i = 0; i < resultFileNumberOfEntires; i++) {
    const auto& timeWindow = static_cast<const JPetTimeWindow&>(readerResultFile.getCurrentEntry());
    const auto& secondTimeWindow = i < firstFileNumberOfEntries ? static_cast<const JPetTimeWindow&>(readerFirstFile.getCurrentEntry())
                                   : static_cast<const JPetTimeWindow&>(readerSecondFile.getCurrentEntry());
    BOOST_REQUIRE_EQUAL(timeWindow.getNumberOfEvents(), secondTimeWindow.getNumberOfEvents());
    BOOST_CHECK_PREDICATE(std::not_equal_to<size_t>(), (timeWindow.getNumberOfEvents())(0));
    for (size_t i = 0; i < timeWindow.getNumberOfEvents(); i++) {
      const auto& event = static_cast<const JPetEvent&>(timeWindow[i]);
      const auto& secondEvent = static_cast<const JPetEvent&>(secondTimeWindow[i]);
      const auto& hits = event.getHits();
      const auto& secondHits = secondEvent.getHits();
      BOOST_REQUIRE_EQUAL(hits.size(), secondHits.size());
      for (unsigned int i = 0; i < hits.size(); i++) {
        BOOST_REQUIRE_EQUAL(hits[i].getPosX(), secondHits[i].getPosX());
        BOOST_REQUIRE_EQUAL(hits[i].getPosY(), secondHits[i].getPosY());
        BOOST_REQUIRE_EQUAL(hits[i].getPosZ(), secondHits[i].getPosZ());
        BOOST_REQUIRE_EQUAL(hits[i].getEnergy(), secondHits[i].getEnergy());
        BOOST_REQUIRE_EQUAL(hits[i].getQualityOfEnergy(), secondHits[i].getQualityOfEnergy());
        BOOST_REQUIRE_EQUAL(hits[i].getTime(), secondHits[i].getTime());
        BOOST_REQUIRE_EQUAL(hits[i].getTimeDiff(), secondHits[i].getTimeDiff());
        BOOST_REQUIRE_EQUAL(hits[i].getQualityOfTime(), secondHits[i].getQualityOfTime());
        BOOST_REQUIRE_EQUAL(hits[i].getQualityOfTimeDiff(), secondHits[i].getQualityOfTimeDiff());
        BOOST_REQUIRE(hits[i].getScintillator() == secondHits[i].getScintillator());
        BOOST_REQUIRE(hits[i].getBarrelSlot() == secondHits[i].getBarrelSlot());
      }
    }
    readerResultFile.nextEntry();
    if (i < firstFileNumberOfEntries)
      readerFirstFile.nextEntry();
    else
      readerSecondFile.nextEntry();
  }
}

BOOST_AUTO_TEST_SUITE_END()

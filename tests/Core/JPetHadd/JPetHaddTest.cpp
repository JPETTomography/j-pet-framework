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
  try
  {
    while (!feof(pipe))
    {
      if (fgets(buffer, 128, pipe) != NULL)
        result += buffer;
    }
  }
  catch (...)
  {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  return result;
}

BOOST_AUTO_TEST_CASE(check_same_data)
{
  std::string haddedFileName;
  std::string firstFileName = "unitTestData/JPetHaddTest/single_link_def/dabc_17237091818.hadd.test.root";
  std::string secondFileName = "unitTestData/JPetHaddTest/single_link_def/dabc_17237093844.hadd.test.root";
#if ROOT_VERSION_CODE < ROOT_VERSION(6, 0, 0)
  haddedFileName = "unitTestData/JPetHaddTest/hadded_root5.hadd.test.root";
#else
  haddedFileName = "unitTestData/JPetHaddTest/hadded_root6.hadd.test.root";
#endif
  exec("hadd -f " + haddedFileName + " " + firstFileName + " " + secondFileName);
  JPetReader readerFirstFile(firstFileName.c_str());
  JPetReader readerSecondFile(secondFileName.c_str());
  JPetReader readerHaddedFile(haddedFileName.c_str());
  BOOST_REQUIRE(readerFirstFile.isOpen());
  BOOST_REQUIRE(readerSecondFile.isOpen());
  BOOST_REQUIRE(readerHaddedFile.isOpen());
  BOOST_REQUIRE_EQUAL(std::string(readerFirstFile.getCurrentEntry().GetName()), std::string("JPetTimeWindow"));
  BOOST_REQUIRE_EQUAL(std::string(readerSecondFile.getCurrentEntry().GetName()), std::string("JPetTimeWindow"));
  BOOST_REQUIRE_EQUAL(std::string(readerHaddedFile.getCurrentEntry().GetName()), std::string("JPetTimeWindow"));
  const auto firstParamBank = readerFirstFile.getObjectFromFile("ParamBank;1");
  const auto secondParamBank = readerSecondFile.getObjectFromFile("ParamBank;1");
  const auto haddedParamBank = readerHaddedFile.getObjectFromFile("ParamBank;1");
  BOOST_CHECK(firstParamBank);
  BOOST_CHECK(secondParamBank);
  BOOST_CHECK(haddedParamBank);

  long long firstFileNumberOfEntries = readerFirstFile.getNbOfAllEntries();
  long long secondFileNumberOfEntries = readerSecondFile.getNbOfAllEntries();
  long long haddedFileNumberOfEntries = readerHaddedFile.getNbOfAllEntries();
  BOOST_REQUIRE_EQUAL(haddedFileNumberOfEntries, firstFileNumberOfEntries + secondFileNumberOfEntries);
  for (long long i = 0; i < haddedFileNumberOfEntries; i++)
  {
    const auto& haddedTimeWindow = static_cast<const JPetTimeWindow&>(readerHaddedFile.getCurrentEntry());
    const auto& compareTimeWindow = i < firstFileNumberOfEntries ? static_cast<const JPetTimeWindow&>(readerFirstFile.getCurrentEntry())
                                                                 : static_cast<const JPetTimeWindow&>(readerSecondFile.getCurrentEntry());
    BOOST_REQUIRE_EQUAL(haddedTimeWindow.getNumberOfEvents(), compareTimeWindow.getNumberOfEvents());
    BOOST_CHECK_PREDICATE(std::not_equal_to<size_t>(), (haddedTimeWindow.getNumberOfEvents())(0));
    for (size_t i = 0; i < haddedTimeWindow.getNumberOfEvents(); i++)
    {
      const auto& haddedEvent = static_cast<const JPetEvent&>(haddedTimeWindow[i]);
      const auto& compareEvent = static_cast<const JPetEvent&>(compareTimeWindow[i]);
      const auto& haddedHits = haddedEvent.getHits();
      const auto& compareHits = compareEvent.getHits();
      BOOST_REQUIRE_EQUAL(haddedHits.size(), compareHits.size());
      for (unsigned int i = 0; i < haddedHits.size(); i++)
      {
        BOOST_REQUIRE_EQUAL(haddedHits[i].getPosX(), compareHits[i].getPosX());
        BOOST_REQUIRE_EQUAL(haddedHits[i].getPosY(), compareHits[i].getPosY());
        BOOST_REQUIRE_EQUAL(haddedHits[i].getPosZ(), compareHits[i].getPosZ());
        BOOST_REQUIRE_EQUAL(haddedHits[i].getEnergy(), compareHits[i].getEnergy());
        BOOST_REQUIRE_EQUAL(haddedHits[i].getQualityOfEnergy(), compareHits[i].getQualityOfEnergy());
        BOOST_REQUIRE_EQUAL(haddedHits[i].getTime(), compareHits[i].getTime());
        BOOST_REQUIRE_EQUAL(haddedHits[i].getTimeDiff(), compareHits[i].getTimeDiff());
        BOOST_REQUIRE_EQUAL(haddedHits[i].getQualityOfTime(), compareHits[i].getQualityOfTime());
        BOOST_REQUIRE_EQUAL(haddedHits[i].getQualityOfTimeDiff(), compareHits[i].getQualityOfTimeDiff());
        BOOST_REQUIRE(haddedHits[i].getScintillator() == compareHits[i].getScintillator());
        BOOST_REQUIRE(haddedHits[i].getBarrelSlot() == compareHits[i].getBarrelSlot());
      }
    }
    readerHaddedFile.nextEntry();
    if (i < firstFileNumberOfEntries)
      readerFirstFile.nextEntry();
    else
      readerSecondFile.nextEntry();
  }
  delete firstParamBank;
  delete secondParamBank;
  delete haddedParamBank;
}

BOOST_AUTO_TEST_CASE(check_param_bank)
{
  std::string haddedFileName;
  std::string firstFileName = "unitTestData/JPetHaddTest/single_link_def/dabc_17237091818.hadd.test.root";
  std::string secondFileName = "unitTestData/JPetHaddTest/single_link_def/dabc_17237093844.hadd.test.root";
#if ROOT_VERSION_CODE < ROOT_VERSION(6, 0, 0)
  haddedFileName = "unitTestData/JPetHaddTest/hadded_parambank_root5.hadd.test.root";
#else
  haddedFileName = "unitTestData/JPetHaddTest/hadded_parambank_root6.hadd.test.root";
#endif
  exec("hadd -f " + haddedFileName + " " + firstFileName + " " + secondFileName);
  JPetReader readerHaddedFile(haddedFileName.c_str());
  BOOST_REQUIRE(readerHaddedFile.isOpen());
  BOOST_REQUIRE_EQUAL(std::string(readerHaddedFile.getCurrentEntry().GetName()), std::string("JPetTimeWindow"));
  const auto haddedParamBank = readerHaddedFile.getObjectFromFile("ParamBank;1");
  BOOST_CHECK(haddedParamBank);

  long long haddedFileNumberOfEntries = readerHaddedFile.getNbOfAllEntries();
  for (long long i = 0; i < haddedFileNumberOfEntries; i++)
  {
    const auto& haddedTimeWindow = static_cast<const JPetTimeWindow&>(readerHaddedFile.getCurrentEntry());

    BOOST_CHECK_PREDICATE(std::not_equal_to<size_t>(), (haddedTimeWindow.getNumberOfEvents())(0));
    for (size_t i = 0; i < haddedTimeWindow.getNumberOfEvents(); i++)
    {
      const auto& haddedEvent = static_cast<const JPetEvent&>(haddedTimeWindow[i]);
      const auto& haddedHits = haddedEvent.getHits();
      for (unsigned int i = 0; i < haddedHits.size(); i++)
      {
        BOOST_CHECK_PREDICATE(std::not_equal_to<size_t>(), (haddedHits[i].getScintillator().getID())(0));
      }
    }
    readerHaddedFile.nextEntry();
  }
  delete haddedParamBank;
}

BOOST_AUTO_TEST_SUITE_END()

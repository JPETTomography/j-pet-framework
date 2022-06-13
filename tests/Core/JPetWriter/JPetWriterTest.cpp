/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetWriterTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetWriterTest

#include "JPetWriter/JPetWriter.h"
#include "Hits/JPetBaseHit/JPetBaseHit.h"
#include "JPetEvent/JPetEvent.h"
#include "JPetLOR/JPetLOR.h"
#include "JPetReader/JPetReader.h"
#include "JPetTimeWindow/JPetTimeWindow.h"
#include "Signals/JPetBaseSignal/JPetBaseSignal.h"
#include "Signals/JPetChannelSignal/JPetChannelSignal.h"
#include "Signals/JPetMatrixSignal/JPetMatrixSignal.h"
#include "Signals/JPetPMSignal/JPetPMSignal.h"
#include "Signals/JPetPhysSignal/JPetPhysSignal.h"
#include "Signals/JPetRecoSignal/JPetRecoSignal.h"
#include <TFile.h>
#include <TList.h>
#include <THashTable.h>
#include <TNamed.h>
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(FirstSuite)

const auto kHugeNumberOfObjects = 10000;

BOOST_AUTO_TEST_CASE(my_test1)
{
  JPetWriter writer("test.root");
  BOOST_REQUIRE(writer.isOpen());
  writer.closeFile();
  BOOST_REQUIRE(!writer.isOpen());
}

BOOST_AUTO_TEST_CASE(my_test2)
{
  std::string fileName = "test2.root";
  JPetWriter writer(fileName.c_str());
  TNamed obj("TNamed", "Title of this testObj");
  writer.write(obj);
  writer.closeFile();
  JPetReader reader(fileName.c_str());
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), 1);
  TNamed& objOut = (TNamed&)reader.getCurrentEntry();
  BOOST_REQUIRE(std::string(objOut.GetName()) == "TNamed");
  BOOST_REQUIRE(std::string(objOut.GetTitle()) == "Title of this testObj");
}

BOOST_AUTO_TEST_CASE(my_helperTest_for_test3)
{
  std::string fileName = "test3_bis.root";
  TFile file(fileName.c_str(), "RECREATE");
  TTree tree("tree", "tree");
  tree.SetAutoSave(1000);
  TNamed* filler = 0;
  tree.Branch("TNamed", "TNamed", &filler);
  std::cout << "Write Tree " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    TNamed obj("TNamed", Form("Title of this testObj%d", i));
    filler = &obj;
    tree.Fill();
    tree.FlushBaskets();
  }
  std::cout << std::endl;
  file.Close();
}

BOOST_AUTO_TEST_CASE(my_test3)
{
  std::string fileName = "test3.root";
  JPetWriter writer(fileName.c_str());
  std::cout << "Write TNamed " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    TNamed obj("TNamed", Form("Title of this testObj%d", i));
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    writer.write(obj);
  }
  std::cout << std::endl;
  writer.closeFile();

  JPetReader reader(fileName.c_str());
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    reader.nthEntry(i);
    TNamed& objOut = (TNamed&)reader.getCurrentEntry();
    BOOST_REQUIRE(std::string(objOut.GetName()) == "TNamed");
    BOOST_REQUIRE(std::string(objOut.GetTitle()) == Form("Title of this testObj%d", i));
  }
}

BOOST_AUTO_TEST_CASE(saving_different_objects1)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  std::cout << "Write JPetChannelSignal " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    JPetChannelSignal testChannelSignal;
    writer.write(testChannelSignal);
  }
  std::cout << std::endl;
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  JPetReader reader(fileTest);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  reader.closeFile();
  if (boost::filesystem::exists(fileTest))
  {
    boost::filesystem::remove(fileTest);
  }
}

BOOST_AUTO_TEST_CASE(saving_different_objects2)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  std::cout << "Write JPetTimeWindow " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    JPetTimeWindow testJPetTimeWindow("JPetChannelSignal");
    writer.write(testJPetTimeWindow);
  }
  std::cout << std::endl;
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  JPetReader reader(fileTest);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  reader.closeFile();
  if (boost::filesystem::exists(fileTest))
  {
    boost::filesystem::remove(fileTest);
  }
}

BOOST_AUTO_TEST_CASE(saving_different_objects3)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  std::cout << "Write JPetBaseSignal " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    JPetBaseSignal testJPetBaseSignal;
    writer.write(testJPetBaseSignal);
  }
  std::cout << std::endl;
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  JPetReader reader(fileTest);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  reader.closeFile();
  if (boost::filesystem::exists(fileTest))
  {
    boost::filesystem::remove(fileTest);
  }
}

BOOST_AUTO_TEST_CASE(saving_different_objects4)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  std::cout << "Write JPetPMSignal " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    JPetPMSignal testPMSignal;
    writer.write(testPMSignal);
  }
  std::cout << std::endl;
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  JPetReader reader(fileTest);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  reader.closeFile();
  if (boost::filesystem::exists(fileTest))
  {
    boost::filesystem::remove(fileTest);
  }
}

BOOST_AUTO_TEST_CASE(saving_different_objects5)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  std::cout << "Write JPetRecoSignal " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    JPetRecoSignal testJPetRecoSignal;
    writer.write(testJPetRecoSignal);
  }
  std::cout << std::endl;
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  JPetReader reader(fileTest);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  reader.closeFile();
  if (boost::filesystem::exists(fileTest))
  {
    boost::filesystem::remove(fileTest);
  }
}

BOOST_AUTO_TEST_CASE(saving_different_objects6)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  std::cout << "Write JPetPhysSignal " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    JPetPhysSignal testJPetPhysSignal;
    writer.write(testJPetPhysSignal);
  }
  std::cout << std::endl;
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  JPetReader reader(fileTest);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  reader.closeFile();
  if (boost::filesystem::exists(fileTest))
  {
    boost::filesystem::remove(fileTest);
  }
}

BOOST_AUTO_TEST_CASE(saving_different_objects7)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  std::cout << "Write JPetMatrixSignal " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    JPetMatrixSignal testMatrixSignal;
    writer.write(testMatrixSignal);
  }
  std::cout << std::endl;
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  JPetReader reader(fileTest);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  reader.closeFile();
  if (boost::filesystem::exists(fileTest))
  {
    boost::filesystem::remove(fileTest);
  }
}

BOOST_AUTO_TEST_CASE(saving_different_objects8)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  std::cout << "Write JPetBaseHit " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    JPetBaseHit testBaseHit;
    writer.write(testBaseHit);
  }
  std::cout << std::endl;
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  JPetReader reader(fileTest);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  reader.closeFile();
  if (boost::filesystem::exists(fileTest))
  {
    boost::filesystem::remove(fileTest);
  }
}

BOOST_AUTO_TEST_CASE(saving_different_objects9)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  std::cout << "Write JPetLOR " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    JPetLOR testLOR;
    writer.write(testLOR);
  }
  std::cout << std::endl;
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  JPetReader reader(fileTest);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  reader.closeFile();
  if (boost::filesystem::exists(fileTest))
  {
    boost::filesystem::remove(fileTest);
  }
}

BOOST_AUTO_TEST_CASE(saving_different_objects10)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  std::cout << "Write JPetEvent " << std::flush;
  for (int i = 0; i < kHugeNumberOfObjects; i++)
  {
    if (i % 1000 == 0)
    {
      std::cout << "*" << std::flush;
    }
    JPetEvent testEvent;
    writer.write(testEvent);
  }
  std::cout << std::endl;
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  JPetReader reader(fileTest);
  BOOST_REQUIRE_EQUAL(reader.getNbOfAllEntries(), kHugeNumberOfObjects);
  reader.closeFile();
  if (boost::filesystem::exists(fileTest))
  {
    boost::filesystem::remove(fileTest);
  }
}

BOOST_AUTO_TEST_CASE(saving_ROOT_container)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  TList list;
  list.Add(new TNamed("test1", "test object 1"));
  list.Add(new TNamed("test2", "test object 2"));
  list.Add(new TNamed("test3", "test object 3"));
  writer.writeCollection(&list, "testdir");
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  TFile fread(fileTest, "READ");
  TNamed* retrieved1 = dynamic_cast<TNamed*>(fread.Get("testdir/test1"));
  TNamed* retrieved2 = dynamic_cast<TNamed*>(fread.Get("testdir/test2"));
  TNamed* retrieved3 = dynamic_cast<TNamed*>(fread.Get("testdir/test3"));
  BOOST_CHECK(retrieved1);
  BOOST_CHECK(retrieved2);
  BOOST_CHECK(retrieved3);
  BOOST_REQUIRE(std::string(retrieved1->GetName()) == "test1");
  BOOST_REQUIRE(std::string(retrieved2->GetName()) == "test2");
  BOOST_REQUIRE(std::string(retrieved3->GetName()) == "test3");
  BOOST_REQUIRE(std::string(retrieved1->GetTitle()) == "test object 1");
  fread.Close();
}

BOOST_AUTO_TEST_CASE(saving_ROOT_container_subdir)
{
  auto fileTest = "saving_different_objectsTest.root";
  JPetWriter writer(fileTest);
  TList list;
  list.Add(new TNamed("test1", "test object 1"));
  THashTable hash;
  hash.Add(new TNamed("test2", "test object 2"));
  hash.Add(new TNamed("test3", "test object 3"));
  writer.writeCollection(&list, "testdir", "listcontents");
  writer.writeCollection(&hash, "testdir", "hashcontents");
  writer.closeFile();
  BOOST_REQUIRE(boost::filesystem::exists(fileTest));
  TFile fread(fileTest, "READ");
  TNamed* retrieved1 = dynamic_cast<TNamed*>(fread.Get("testdir/listcontents/test1"));
  TNamed* retrieved2 = dynamic_cast<TNamed*>(fread.Get("testdir/hashcontents/test2"));
  TNamed* retrieved3 = dynamic_cast<TNamed*>(fread.Get("testdir/hashcontents/test3"));
  BOOST_CHECK(retrieved1);
  BOOST_CHECK(retrieved2);
  BOOST_CHECK(retrieved3);
  BOOST_REQUIRE(std::string(retrieved1->GetName()) == "test1");
  BOOST_REQUIRE(std::string(retrieved2->GetName()) == "test2");
  BOOST_REQUIRE(std::string(retrieved3->GetName()) == "test3");
  BOOST_REQUIRE(std::string(retrieved1->GetTitle()) == "test object 1");
  fread.Close();
}

BOOST_AUTO_TEST_SUITE_END()

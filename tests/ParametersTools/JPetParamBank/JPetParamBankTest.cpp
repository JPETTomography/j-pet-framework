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
 *  @file JPetParamBankTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamBankTest

#include "JPetParamBank/JPetParamBank.h"

#include <TFile.h>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(JPetParamBankTestSuite)

double epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(DefaultConstructorTest)
{
  JPetParamBank bank;
  BOOST_REQUIRE_EQUAL(bank.getDataModulesSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getDataSourcesSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getChannelsSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getMatricesSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getScinsSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getSlotsSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getLayersSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getSetupsSize(), 0);

  BOOST_REQUIRE_EQUAL(bank.getDataModules().size(), 0);
  BOOST_REQUIRE_EQUAL(bank.getDataSources().size(), 0);
  BOOST_REQUIRE_EQUAL(bank.getChannels().size(), 0);
  BOOST_REQUIRE_EQUAL(bank.getPMs().size(), 0);
  BOOST_REQUIRE_EQUAL(bank.getMatrices().size(), 0);
  BOOST_REQUIRE_EQUAL(bank.getScins().size(), 0);
  BOOST_REQUIRE_EQUAL(bank.getLayers().size(), 0);
  BOOST_REQUIRE_EQUAL(bank.getSlots().size(), 0);
  BOOST_REQUIRE_EQUAL(bank.getSetups().size(), 0);
}

BOOST_AUTO_TEST_CASE(AddingDummyElementsTest)
{
  JPetParamBank bank;
  JPetDataModule dataModule(1, "test_type", 57425, 65, 130);
  JPetDataSource dataSource(1, "test_type", 32832, 32832);
  JPetChannel channel(1, 2, 30.0);
  JPetPM pm(1, "blah", 3);
  JPetMatrix mtx(1, JPetMatrix::SideB);
  JPetScin scin(1, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9);
  JPetSlot slot(1, 45.0, JPetSlot::Module);
  JPetLayer layer(1, "blah", 44.4);
  JPetSetup setup(1, "jpet");

  bank.addDataModule(dataModule);
  bank.addDataSource(dataSource);
  bank.addChannel(channel);
  bank.addPM(pm);
  bank.addMatrix(mtx);
  bank.addScin(scin);
  bank.addSlot(slot);
  bank.addLayer(layer);
  bank.addSetup(setup);

  BOOST_REQUIRE_EQUAL(bank.getDataModulesSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getDataSourcesSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getChannelsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getMatricesSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getScinsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getSlotsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getLayersSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getSetupsSize(), 1);

  BOOST_REQUIRE_EQUAL(bank.getDataModules().size(), 1);
  BOOST_REQUIRE_EQUAL(bank.getDataSources().size(), 1);
  BOOST_REQUIRE_EQUAL(bank.getChannels().size(), 1);
  BOOST_REQUIRE_EQUAL(bank.getPMs().size(), 1);
  BOOST_REQUIRE_EQUAL(bank.getMatrices().size(), 1);
  BOOST_REQUIRE_EQUAL(bank.getScins().size(), 1);
  BOOST_REQUIRE_EQUAL(bank.getSlots().size(), 1);
  BOOST_REQUIRE_EQUAL(bank.getLayers().size(), 1);
  BOOST_REQUIRE_EQUAL(bank.getSetups().size(), 1);

  // Check Data Module
  BOOST_REQUIRE_EQUAL(bank.getDataModule(1).getID(), 1);
  BOOST_REQUIRE_EQUAL(bank.getDataModule(1).getType(), "test_type");
  BOOST_REQUIRE_EQUAL(bank.getDataModule(1).getTBRNetAddress(), 57425);
  BOOST_REQUIRE_EQUAL(bank.getDataModule(1).getChannelsNumber(), 65);
  BOOST_REQUIRE_EQUAL(bank.getDataModule(1).getChannelsOffset(), 130);

  // Check Data Source
  BOOST_REQUIRE_EQUAL(bank.getDataSource(1).getID(), 1);
  BOOST_REQUIRE_EQUAL(bank.getDataSource(1).getType(), "test_type");
  BOOST_REQUIRE_EQUAL(bank.getDataSource(1).getTBRNetAddress(), 32832);
  BOOST_REQUIRE_EQUAL(bank.getDataSource(1).getHubAddress(), 32832);

  // Check Channel
  BOOST_REQUIRE_EQUAL(bank.getChannel(1).getID(), 1);
  BOOST_REQUIRE_EQUAL(bank.getChannel(1).getThresholdNumber(), 2);
  BOOST_REQUIRE_CLOSE(bank.getChannel(1).getThresholdValue(), 30.0, epsilon);

  // Check PM
  BOOST_REQUIRE_EQUAL(bank.getPM(1).getID(), 1);
  BOOST_REQUIRE_EQUAL(bank.getPM(1).getDesc(), "blah");
  BOOST_REQUIRE_EQUAL(bank.getPM(1).getMatrixPosition(), 3);

  // Check Matrix
  BOOST_REQUIRE_EQUAL(bank.getMatrix(1).getID(), 1);
  BOOST_REQUIRE_EQUAL(bank.getMatrix(1).getSide(), JPetMatrix::SideB);

  // Check Scin
  BOOST_REQUIRE_EQUAL(bank.getScin(1).getID(), 1);
  BOOST_REQUIRE_CLOSE(bank.getScin(1).getLength(), 1.1, epsilon);
  BOOST_REQUIRE_CLOSE(bank.getScin(1).getHeight(), 2.2, epsilon);
  BOOST_REQUIRE_CLOSE(bank.getScin(1).getWidth(), 3.3, epsilon);
  BOOST_REQUIRE_CLOSE(bank.getScin(1).getCenterX(), 4.4, epsilon);
  BOOST_REQUIRE_CLOSE(bank.getScin(1).getCenterY(), 5.5, epsilon);
  BOOST_REQUIRE_CLOSE(bank.getScin(1).getCenterZ(), 6.6, epsilon);
  BOOST_REQUIRE_CLOSE(bank.getScin(1).getRotationX(), 7.7, epsilon);
  BOOST_REQUIRE_CLOSE(bank.getScin(1).getRotationY(), 8.8, epsilon);
  BOOST_REQUIRE_CLOSE(bank.getScin(1).getRotationZ(), 9.9, epsilon);

  // Check Slot
  BOOST_REQUIRE_EQUAL(bank.getSlot(1).getID(), 1);
  BOOST_REQUIRE_CLOSE(bank.getSlot(1).getTheta(), 45.0, epsilon);
  BOOST_REQUIRE_EQUAL(bank.getSlot(1).getType(), JPetSlot::Module);

  // // Check Layer
  BOOST_REQUIRE_EQUAL(bank.getLayer(1).getID(), 1);
  BOOST_REQUIRE_EQUAL(bank.getLayer(1).getName(), "blah");
  BOOST_REQUIRE_CLOSE(bank.getLayer(1).getRadius(), 44.4, epsilon);

  // Check Setup
  BOOST_REQUIRE_EQUAL(bank.getSetup(1).getID(), 1);
  BOOST_REQUIRE_EQUAL(bank.getSetup(1).getDescription(), "jpet");
}

BOOST_AUTO_TEST_CASE(clearAllContainersTest)
{
  JPetParamBank bank;
  JPetDataModule dataModule(1, "test_type", 57425, 65, 130);
  JPetDataSource dataSource(1, "test_type", 32832, 32832);
  JPetChannel channel(1, 2, 30.0);
  JPetPM pm(1, "blah", 3);
  JPetMatrix mtx(1, JPetMatrix::SideB);
  JPetScin scin(1, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9);
  JPetSlot slot(1, 45.0, JPetSlot::Module);
  JPetLayer layer(1, "blah", 44.4);
  JPetSetup setup(1, "jpet");

  bank.addDataModule(dataModule);
  bank.addDataSource(dataSource);
  bank.addChannel(channel);
  bank.addPM(pm);
  bank.addMatrix(mtx);
  bank.addScin(scin);
  bank.addSlot(slot);
  bank.addLayer(layer);
  bank.addSetup(setup);

  BOOST_REQUIRE_EQUAL(bank.getDataModulesSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getDataSourcesSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getChannelsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getMatricesSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getScinsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getSlotsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getLayersSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getSetupsSize(), 1);

  bank.clear();
  BOOST_REQUIRE_EQUAL(bank.getDataModulesSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getDataSourcesSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getChannelsSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getMatricesSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getScinsSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getSlotsSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getLayersSize(), 0);
  BOOST_REQUIRE_EQUAL(bank.getSetupsSize(), 0);
}

BOOST_AUTO_TEST_CASE(saving_reading_file)
{
  JPetParamBank bank1;
  for (int i = 0; i < 100; i++)
  {
    JPetDataModule dataModule(i, "test_type", 57425, 65, 130);
    bank1.addDataModule(dataModule);
    JPetDataSource dataSource(i, "test_type", 32832, 32832);
    bank1.addDataSource(dataSource);
    JPetChannel channel(i, 2, 30.0);
    bank1.addChannel(channel);
    JPetPM pm(i, "blah", 3);
    bank1.addPM(pm);
    JPetMatrix mtx(i, JPetMatrix::SideB);
    bank1.addMatrix(mtx);
    JPetScin scin(i, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9);
    bank1.addScin(scin);
    JPetSlot slot(i, 45.0, JPetSlot::Module);
    bank1.addSlot(slot);
    JPetLayer layer(i, "blah", 44.4);
    bank1.addLayer(layer);
    JPetSetup setup(i, "jpet");
    bank1.addSetup(setup);
  }

  TFile file("test.root", "UPDATE");
  file.cd();
  file.WriteObject(&bank1, "ParamBank");
  file.Close();

  TFile file2("test.root", "READ");
  JPetParamBank* pBank = static_cast<JPetParamBank*>(file2.Get("ParamBank;1"));
  JPetParamBank& bank2 = *pBank;

  BOOST_REQUIRE_EQUAL(bank1.getDataModulesSize(), bank2.getDataModulesSize());
  BOOST_REQUIRE_EQUAL(bank1.getDataSourcesSize(), bank2.getDataSourcesSize());
  BOOST_REQUIRE_EQUAL(bank1.getChannelsSize(), bank2.getChannelsSize());
  BOOST_REQUIRE_EQUAL(bank1.getPMsSize(), bank2.getPMsSize());
  BOOST_REQUIRE_EQUAL(bank1.getMatricesSize(), bank2.getMatricesSize());
  BOOST_REQUIRE_EQUAL(bank1.getScinsSize(), bank2.getScinsSize());
  BOOST_REQUIRE_EQUAL(bank1.getSlotsSize(), bank2.getSlotsSize());
  BOOST_REQUIRE_EQUAL(bank1.getLayersSize(), bank2.getLayersSize());
  BOOST_REQUIRE_EQUAL(bank1.getSetupsSize(), bank2.getSetupsSize());
}

BOOST_AUTO_TEST_SUITE_END()

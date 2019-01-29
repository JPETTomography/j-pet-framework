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
 *  @file JPetParamGetterAsciiTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamGetterAsciiTest

#include "./JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "./JPetParamGetterAscii/JPetParamSaverAscii.h"
#include "./JPetParamManager/JPetParamManager.h"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

const std::string dataDir = "unitTestData/JPetParamGetterAsciiTest/";

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(noExisting_file_read)
{
  JPetParamGetterAscii getter(dataDir + "noExisting.json");
  BOOST_REQUIRE_EQUAL(getter.getAllBasicData(ParamObjectType::kPM, 1).size(), 0u);
}

BOOST_AUTO_TEST_CASE(empty_file_read)
{
  JPetParamGetterAscii getter(dataDir + "empty.json");
  BOOST_REQUIRE_EQUAL(getter.getAllBasicData(ParamObjectType::kPM, 1).size(), 0u);
}

BOOST_AUTO_TEST_CASE(minimal_basic_data_read)
{
  JPetParamGetterAscii getter(dataDir + "DB1.json");
  ParamObjectsDescriptions descriptions = getter.getAllBasicData(ParamObjectType::kPM, 1);
  BOOST_REQUIRE_EQUAL(descriptions.size(), 1u);
  ParamObjectDescription& description = descriptions[1];
  BOOST_REQUIRE_EQUAL(description["id"], "1");
  BOOST_REQUIRE_EQUAL(description["is_right_side"], "1");
  BOOST_REQUIRE_EQUAL(description["description"], "no writing");
}

BOOST_AUTO_TEST_CASE(minimal_relational_data_read)
{
  JPetParamGetterAscii getter(dataDir + "DB1.json");
  ParamRelationalData relations = getter.getAllRelationalData(
    ParamObjectType::kPM, ParamObjectType::kBarrelSlot, 1);
  BOOST_REQUIRE_EQUAL(relations.size(), 1u);
  BOOST_REQUIRE_EQUAL(relations[1], 1);
}

BOOST_AUTO_TEST_CASE(minimal_example_write)
{
  JPetParamManager paramManager(new JPetParamGetterAscii(dataDir + "DB1.json"));
  paramManager.fillParameterBank(1);
  const JPetParamBank& paramBank = paramManager.getParamBank();
  JPetParamSaverAscii saver;
  std::string writtenFileName(dataDir + "writtenDB1.json");
  saver.saveParamBank(paramBank, 1, writtenFileName);
  JPetParamManager reparamManager(new JPetParamGetterAscii(writtenFileName.c_str()));
  reparamManager.fillParameterBank(1);
  const JPetParamBank& reparamBank = reparamManager.getParamBank();
  BOOST_REQUIRE(paramBank.getScintillatorsSize() == reparamBank.getScintillatorsSize());
  BOOST_REQUIRE(paramBank.getBarrelSlotsSize() == reparamBank.getBarrelSlotsSize());
  BOOST_REQUIRE(paramBank.getPMsSize() == reparamBank.getPMsSize());
  BOOST_REQUIRE(paramBank.getFEBsSize() == reparamBank.getFEBsSize());
  BOOST_REQUIRE(paramBank.getLayersSize() == reparamBank.getLayersSize());
  BOOST_REQUIRE(paramBank.getFramesSize() == reparamBank.getFramesSize());
  BOOST_REQUIRE(paramBank.getTOMBChannelsSize() == reparamBank.getTOMBChannelsSize());
  BOOST_REQUIRE(paramBank.getTRBsSize() == reparamBank.getTRBsSize());
  JPetScin& scintillator = paramBank.getScintillator(1);
  JPetScin& rescintillator = reparamBank.getScintillator(1);
  BOOST_REQUIRE(scintillator.getID() == rescintillator.getID());
  BOOST_REQUIRE(scintillator.getAttenLen() == rescintillator.getAttenLen());
  BOOST_REQUIRE(scintillator.getScinSize().fLength == rescintillator.getScinSize().fLength);
  BOOST_REQUIRE(scintillator.getScinSize().fHeight == rescintillator.getScinSize().fHeight);
  BOOST_REQUIRE(scintillator.getScinSize().fWidth == rescintillator.getScinSize().fWidth);
  JPetBarrelSlot& barrelSlot = paramBank.getBarrelSlot(1);
  JPetBarrelSlot& rebarrelSlot = reparamBank.getBarrelSlot(1);
  BOOST_REQUIRE(barrelSlot.getID() == rebarrelSlot.getID());
  BOOST_REQUIRE(barrelSlot.isActive() == rebarrelSlot.isActive());
  BOOST_REQUIRE(barrelSlot.getName() == rebarrelSlot.getName());
  BOOST_REQUIRE(barrelSlot.getTheta() == rebarrelSlot.getTheta());
  BOOST_REQUIRE(barrelSlot.getInFrameID() == rebarrelSlot.getInFrameID());
  JPetPM& pm = paramBank.getPM(1);
  JPetPM& repm = reparamBank.getPM(1);
  BOOST_REQUIRE(pm.getID() == repm.getID());
  BOOST_REQUIRE(pm.getSide() == repm.getSide());
  BOOST_REQUIRE(pm.getDescription() == repm.getDescription());
  JPetFEB& feb = paramBank.getFEB(1);
  JPetFEB& refeb = reparamBank.getFEB(1);
  BOOST_REQUIRE(feb.getID() == refeb.getID());
  BOOST_REQUIRE(feb.isActive() == refeb.isActive());
  BOOST_REQUIRE(feb.status() == refeb.status());
  BOOST_REQUIRE(feb.description() == refeb.description());
  BOOST_REQUIRE(feb.version() == refeb.version());
  BOOST_REQUIRE(feb.getNtimeOutsPerInput() == refeb.getNtimeOutsPerInput());
  BOOST_REQUIRE(feb.getNnotimeOutsPerInput() == refeb.getNnotimeOutsPerInput());
  JPetLayer& layer = paramBank.getLayer(1);
  JPetLayer& relayer = reparamBank.getLayer(1);
  BOOST_REQUIRE(layer.getID() == relayer.getID());
  BOOST_REQUIRE(layer.getIsActive() == relayer.getIsActive());
  BOOST_REQUIRE(layer.getName() == relayer.getName());
  BOOST_REQUIRE(layer.getRadius() == relayer.getRadius());
  JPetFrame& frame = paramBank.getFrame(1);
  JPetFrame& reframe = reparamBank.getFrame(1);
  BOOST_REQUIRE(frame.getID() == reframe.getID());
  BOOST_REQUIRE(frame.getIsActive() == reframe.getIsActive());
  BOOST_REQUIRE(frame.getStatus() == reframe.getStatus());
  BOOST_REQUIRE(frame.getDescription() == reframe.getDescription());
  BOOST_REQUIRE(frame.getVersion() == reframe.getVersion());
  BOOST_REQUIRE(frame.getCreator() == reframe.getCreator());
  JPetTOMBChannel& tomb = paramBank.getTOMBChannel(1);
  JPetTOMBChannel& retomb = reparamBank.getTOMBChannel(1);
  BOOST_REQUIRE(tomb.getThreshold() == retomb.getThreshold());
  JPetTRB& trb = paramBank.getTRB(1);
  JPetTRB& retrb = reparamBank.getTRB(1);
  BOOST_REQUIRE(trb.getID() == retrb.getID());
  BOOST_REQUIRE(trb.getType() == retrb.getType());
  BOOST_REQUIRE(trb.getChannel() == retrb.getChannel());
  BOOST_REQUIRE(barrelSlot == scintillator.getBarrelSlot());
  BOOST_REQUIRE(barrelSlot == pm.getBarrelSlot());
  BOOST_REQUIRE(scintillator == pm.getScin());
  BOOST_REQUIRE(feb == pm.getFEB());
  BOOST_REQUIRE(layer == barrelSlot.getLayer());
  BOOST_REQUIRE(frame == layer.getFrame());
  BOOST_REQUIRE(trb == feb.getTRB());
  BOOST_REQUIRE(trb == tomb.getTRB());
  BOOST_REQUIRE(feb == tomb.getFEB());
  BOOST_REQUIRE(pm == tomb.getPM());
  BOOST_REQUIRE(rebarrelSlot == rescintillator.getBarrelSlot());
  BOOST_REQUIRE(rebarrelSlot == repm.getBarrelSlot());
  BOOST_REQUIRE(rescintillator == repm.getScin());
  BOOST_REQUIRE(refeb == repm.getFEB());
  BOOST_REQUIRE(relayer == rebarrelSlot.getLayer());
  BOOST_REQUIRE(reframe == relayer.getFrame());
  BOOST_REQUIRE(retrb == refeb.getTRB());
  BOOST_REQUIRE(retrb == retomb.getTRB());
  BOOST_REQUIRE(refeb == retomb.getFEB());
  BOOST_REQUIRE(repm == retomb.getPM());
  boost::filesystem::remove(writtenFileName);
}

BOOST_AUTO_TEST_SUITE_END()

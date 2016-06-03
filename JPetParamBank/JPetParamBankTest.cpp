#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamBankTest
#include <boost/test/unit_test.hpp>
#include <TFile.h>

#include "../JPetParamBank/JPetParamBank.h"
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

BOOST_AUTO_TEST_SUITE(JPetParamBankTestSuite)

BOOST_AUTO_TEST_CASE(DefaultConstructorTest)
{
  JPetParamBank bank;
  BOOST_REQUIRE(bank.getScintillatorsSize() == 0);
  BOOST_REQUIRE(bank.getPMsSize() == 0);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
  BOOST_REQUIRE(bank.getBarrelSlotsSize() == 0);
  BOOST_REQUIRE(bank.getLayersSize() == 0);
  BOOST_REQUIRE(bank.getFramesSize() == 0);
  BOOST_REQUIRE(bank.getFEBsSize() == 0);
  BOOST_REQUIRE(bank.getTRBsSize() == 0);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 0);

  BOOST_REQUIRE(bank.getScintillators().size() == 0);
  BOOST_REQUIRE(bank.getPMs().size() == 0);
  BOOST_REQUIRE(bank.getPMCalibs().size() == 0);
  BOOST_REQUIRE(bank.getBarrelSlots().size() == 0);
  BOOST_REQUIRE(bank.getFrames().size() == 0);
  BOOST_REQUIRE(bank.getFEBs().size() == 0);
  BOOST_REQUIRE(bank.getTRBs().size() == 0);
  BOOST_REQUIRE(bank.getTOMBChannels().size() == 0);
}

BOOST_AUTO_TEST_CASE(AddingDummyElementsTest)
{
  JPetParamBank bank;
  JPetScin scint(111, 8.f, 2.f, 4.f, 8.f);
  JPetPM pm(JPetPM::SideB, 222, 32, 64, std::make_pair(16.f, 32.f));
  JPetPMCalib pmCalib(256, "JPetPMCalibTest", 2.f, 4.f, 8.f, 16.f, 32.f, 128, 512);
  JPetBarrelSlot barrelSlot(1, true, "barrelSlotTest", 35.f, 6);
  JPetLayer layer(1, true, "layerTest", 35.f);
  JPetFrame frame(1, true, "OKTEST", "FrameTest", 5, 2);
  JPetFEB feb(1, true, "testStatus", "descr", 1, 1, 8, 1);
  JPetTRB trb(333, 64, 128);
  JPetTOMBChannel TOMBChannel(32u);
  float epsilon = 0.0001f;
  
  bank.addScintillator(scint);
  bank.addPM(pm);
  bank.addPMCalib(pmCalib);
  bank.addBarrelSlot(barrelSlot);
  bank.addLayer(layer);
  bank.addFrame(frame);
  bank.addFEB(feb);
  bank.addTRB(trb);
  bank.addTOMBChannel(TOMBChannel);

  BOOST_REQUIRE(bank.getScintillatorsSize() == 1);
  BOOST_REQUIRE(bank.getPMsSize() == 1);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 1);
  BOOST_REQUIRE(bank.getBarrelSlotsSize() == 1);
  BOOST_REQUIRE(bank.getLayersSize() == 1);
  BOOST_REQUIRE(bank.getFramesSize() == 1);
  BOOST_REQUIRE(bank.getFEBsSize() == 1);
  BOOST_REQUIRE(bank.getTRBsSize() == 1);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 1);

  BOOST_REQUIRE(bank.getScintillators().size() == 1);
  BOOST_REQUIRE(bank.getPMs().size() == 1);
  BOOST_REQUIRE(bank.getPMCalibs().size() == 1);
  BOOST_REQUIRE(bank.getBarrelSlots().size() == 1);
  BOOST_REQUIRE(bank.getLayers().size() == 1);
  BOOST_REQUIRE(bank.getFrames().size() == 1);
  BOOST_REQUIRE(bank.getFEBs().size() == 1);
  BOOST_REQUIRE(bank.getTRBs().size() == 1);
  BOOST_REQUIRE(bank.getTOMBChannels().size() == 1);

  BOOST_REQUIRE(bank.getScintillator(111).getID() == 111);
  BOOST_CHECK_CLOSE(bank.getScintillator(111).getAttenLen(), 8.f, epsilon);
  struct JPetScin::ScinDimensions scin_dimensions(2.f, 4.f, 8.f);
  scin_dimensions = bank.getScintillator(111).getScinSize();
  BOOST_CHECK_CLOSE(scin_dimensions.fLength, 2.f, epsilon);
  BOOST_CHECK_CLOSE(scin_dimensions.fHeight, 4.f, epsilon);
  BOOST_CHECK_CLOSE(scin_dimensions.fWidth, 8.f, epsilon);
  
  BOOST_REQUIRE(bank.getPM(222).getSide() == JPetPM::SideB);
  BOOST_REQUIRE(bank.getPM(222).getID() == 222);
  BOOST_REQUIRE(bank.getPM(222).getHVset() == 32);
  BOOST_REQUIRE(bank.getPM(222).getHVopt() == 64);
  BOOST_CHECK_CLOSE(bank.getPM(222).getHVgain(JPetPM::kFirst), 16.f, epsilon);
  BOOST_CHECK_CLOSE(bank.getPM(222).getHVgain(JPetPM::kSecond), 32.f, epsilon);
  std::pair<float, float> HVgain = bank.getPM(222).getHVgain();
  BOOST_CHECK_CLOSE(HVgain.first, 16.f, epsilon);
  BOOST_CHECK_CLOSE(HVgain.second, 32.f, epsilon);

  BOOST_REQUIRE(bank.getPMCalib(256).GetId() == 256);
  BOOST_REQUIRE(bank.getPMCalib(256).GetNamePM() == "JPetPMCalibTest");
  BOOST_CHECK_CLOSE(bank.getPMCalib(256).GetOpthv(), 2.f, epsilon);
  BOOST_CHECK_CLOSE(bank.getPMCalib(256).GetECalConst1(), 4.f, epsilon);
  BOOST_CHECK_CLOSE(bank.getPMCalib(256).GetECalConst2(), 8.f, epsilon);
  BOOST_CHECK_CLOSE(bank.getPMCalib(256).GetGainalpha(), 16.f, epsilon);
  BOOST_CHECK_CLOSE(bank.getPMCalib(256).GetGainbeta(), 32.f, epsilon);
  BOOST_REQUIRE(bank.getPMCalib(256).GetPMCalibAssignment().id == 128);
  BOOST_REQUIRE(bank.getPMCalib(256).GetPMCalibAssignment().photomultiplier_id == 512);

  BOOST_REQUIRE(bank.getBarrelSlot(1).getID() == 1);
  BOOST_REQUIRE(bank.getBarrelSlot(1).isActive() == true);
  BOOST_REQUIRE(bank.getBarrelSlot(1).getName() == "barrelSlotTest");
  BOOST_CHECK_CLOSE(bank.getBarrelSlot(1).getTheta(), 35.f, epsilon);
  BOOST_REQUIRE(bank.getBarrelSlot(1).getInFrameID()==6);
  
  BOOST_REQUIRE(bank.getLayer(1).getId() == 1);
  BOOST_REQUIRE(bank.getLayer(1).getIsActive() == true);
  BOOST_REQUIRE(bank.getLayer(1).getName() == "layerTest");
  BOOST_CHECK_CLOSE(bank.getLayer(1).getRadius(), 35.f, epsilon);
  
  BOOST_REQUIRE(bank.getFrame(1).getId() == 1);
  BOOST_REQUIRE(bank.getFrame(1).getIsActive() == true);
  BOOST_REQUIRE(bank.getFrame(1).getStatus() == "OKTEST");
  BOOST_REQUIRE(bank.getFrame(1).getDescription() == "FrameTest");
  BOOST_REQUIRE(bank.getFrame(1).getVersion() == 5);
  BOOST_REQUIRE(bank.getFrame(1).getCreator() == 2);
  
  BOOST_REQUIRE(bank.getFEB(1).getID() == 1);
  BOOST_REQUIRE(bank.getFEB(1).isActive() == true);
  BOOST_REQUIRE(bank.getFEB(1).status() == "testStatus");
  BOOST_REQUIRE(bank.getFEB(1).description() == "descr");
  BOOST_REQUIRE(bank.getFEB(1).version() == 1);
  
  BOOST_REQUIRE(bank.getTRB(333).getID() == 333);
  BOOST_REQUIRE(bank.getTRB(333).getType() == 64);
  BOOST_REQUIRE(bank.getTRB(333).getChannel() == 128);
  
  BOOST_REQUIRE(bank.getTOMBChannel(32).getChannel() == 32u);
}

BOOST_AUTO_TEST_CASE(clearAllContainersTest)
{
  JPetParamBank bank;
  JPetScin scint(111, 8.f, 2.f, 4.f, 8.f);
  JPetPM pm(JPetPM::SideB, 222, 32, 64, std::make_pair(16.f, 32.f));
  JPetPMCalib pmCalib(256, "JPetPMCalibTest", 2.f, 4.f, 8.f, 16.f, 32.f, 128, 512);
  JPetBarrelSlot barrelSlot(1, true, "barrelSlotTest", 35.f, 6);
  JPetLayer layer(1, true, "layerTest", 35.f);
  JPetFrame frame(1, true, "OKTEST", "FrameTest", 5, 2);
  JPetFEB feb(1, true, "testStatus", "descr", 1, 1, 8, 1);
  JPetTRB trb(333, 64, 128);
  JPetTOMBChannel TOMBChannel(32u);
  
  bank.addScintillator(scint);
  bank.addPM(pm);
  bank.addPMCalib(pmCalib);
  bank.addBarrelSlot(barrelSlot);
  bank.addLayer(layer);
  bank.addFrame(frame);
  bank.addFEB(feb);
  bank.addTRB(trb);
  bank.addTOMBChannel(TOMBChannel);

  BOOST_REQUIRE(bank.getScintillatorsSize() == 1);
  BOOST_REQUIRE(bank.getPMsSize() == 1);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 1);
  BOOST_REQUIRE(bank.getBarrelSlotsSize() == 1);
  BOOST_REQUIRE(bank.getLayersSize() == 1);
  BOOST_REQUIRE(bank.getFramesSize() == 1);
  BOOST_REQUIRE(bank.getFEBsSize() == 1);
  BOOST_REQUIRE(bank.getTRBsSize() == 1);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 1);
  
  bank.clear();
  
  BOOST_REQUIRE(bank.getScintillatorsSize() == 0);
  BOOST_REQUIRE(bank.getPMsSize() == 0);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
  BOOST_REQUIRE(bank.getBarrelSlotsSize() == 0);
  BOOST_REQUIRE(bank.getLayersSize() == 0);
  BOOST_REQUIRE(bank.getFramesSize() == 0);
  BOOST_REQUIRE(bank.getFEBsSize() == 0);
  BOOST_REQUIRE(bank.getTRBsSize() == 0);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 0);
}

BOOST_AUTO_TEST_CASE(getSizeTest)
{
  JPetParamBank bank;
  JPetScin scint(111, 8.f, 2.f, 4.f, 8.f);
  JPetPM pm(JPetPM::SideB, 222, 32, 64, std::make_pair(16.f, 32.f));
  JPetPMCalib pmCalib(256, "JPetPMCalibTest", 2.f, 4.f, 8.f, 16.f, 32.f, 128, 512);
  JPetBarrelSlot barrelSlot(1, true, "barrelSlotTest", 35.f, 6);
  JPetLayer layer(1, true, "layerTest", 35.f);
  JPetFrame frame(1, true, "OKTEST", "FrameTest", 5, 2);
  JPetFEB feb(1, true, "testStatus", "descr", 1, 1, 8, 1);
  JPetTRB trb(333, 64, 128);
  JPetTOMBChannel TOMBChannel(32u);
  
  bank.addScintillator(scint);
  bank.addPM(pm);
  bank.addPMCalib(pmCalib);
  bank.addBarrelSlot(barrelSlot);
  bank.addLayer(layer);
  bank.addFrame(frame);
  bank.addFEB(feb);
  bank.addTRB(trb);
  bank.addTOMBChannel(TOMBChannel);
  
  BOOST_REQUIRE(bank.getSize(JPetParamBank::kScintillator) == 1);
  BOOST_REQUIRE(bank.getSize(JPetParamBank::kPM) == 1);
  BOOST_REQUIRE(bank.getSize(JPetParamBank::kPMCalib) == 1);
  BOOST_REQUIRE(bank.getSize(JPetParamBank::kBarrelSlot) == 1);
  BOOST_REQUIRE(bank.getSize(JPetParamBank::kLayer) == 1);
  BOOST_REQUIRE(bank.getSize(JPetParamBank::kFrame) == 1);
  BOOST_REQUIRE(bank.getSize(JPetParamBank::kFEB) == 1);
  BOOST_REQUIRE(bank.getSize(JPetParamBank::kTRB) == 1);
  BOOST_REQUIRE(bank.getSize(JPetParamBank::kTOMBChannel) == 1);
}

BOOST_AUTO_TEST_CASE( saving_reading_file )
{
  JPetParamBank bank;
  JPetScin scint1(1, 0, 0, 0, 0);
  JPetScin scint2(2, 0, 0, 0, 0);
  JPetPM pm1(1);
  JPetPM pm2(2);
  JPetPM pm3(3);
  JPetPM pm4(4);
  JPetPMCalib pmCalib(256, "JPetPMCalibTest", 2.f, 4.f, 8.f, 16.f, 32.f, 128, 512);
  JPetBarrelSlot barrelSlot(1, true, "barrelSlotTest", 35.f, 6);
  JPetLayer layer(1, true, "layerTest", 35.f);
  JPetFrame frame(1, true, "OKTEST", "FrameTest", 5, 2);
  pm1.setScin(scint1);
  pm2.setScin(scint1);
  pm3.setScin(scint2);
  pm4.setScin(scint2);

  JPetFEB feb(1, true, "testStatus", "descr", 1, 1, 8, 1);
  JPetTRB trb;
  bank.addPM(pm1);
  bank.addPM(pm2);
  bank.addPM(pm3);
  bank.addPM(pm4);
  bank.addPMCalib(pmCalib);
  bank.addBarrelSlot(barrelSlot);
  bank.addLayer(layer);
  bank.addFrame(frame);
  bank.addScintillator(scint1);
  bank.addScintillator(scint2);
  bank.addTRB(trb);
  bank.addFEB(feb);
  for (int i = 0; i < 100; i++) {
    JPetTOMBChannel channel(i);
    bank.addTOMBChannel(channel);
  }

  BOOST_REQUIRE(bank.getPMCalibsSize() == 1);
  BOOST_REQUIRE(bank.getBarrelSlotsSize() == 1);
  BOOST_REQUIRE(bank.getLayersSize() == 1);
  BOOST_REQUIRE(bank.getFramesSize() == 1);
  
  TFile file("test.root", "UPDATE");
  file.cd();
  file.WriteObject(&bank, "ParamBank");
  file.Close();
  bank.clear();

  TFile file2("test.root", "READ");
  JPetParamBank* pBank = static_cast<JPetParamBank*>(file2.Get("ParamBank"));
  JPetParamBank& bank2 = *pBank;

  BOOST_REQUIRE(bank2.getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank2.getPMsSize() == 4);
  
  BOOST_REQUIRE(bank2.getPMCalibsSize() == 1);
  BOOST_REQUIRE(bank2.getBarrelSlotsSize() == 1);
  BOOST_REQUIRE(bank2.getLayersSize() == 1);
  BOOST_REQUIRE(bank2.getFramesSize() == 1);
  BOOST_REQUIRE(bank2.getFEBsSize() == 1);
  BOOST_REQUIRE(bank2.getTRBsSize() == 1);

  BOOST_REQUIRE(bank2.getScintillators().size() == 2);
  BOOST_REQUIRE(bank2.getPMs().size() == 4);
  BOOST_REQUIRE(bank2.getPMCalibs().size() == 1);
  BOOST_REQUIRE(bank2.getBarrelSlots().size() == 1);
  BOOST_REQUIRE(bank2.getLayers().size() == 1);
  BOOST_REQUIRE(bank2.getFrames().size() == 1);
  BOOST_REQUIRE(bank2.getFEBs().size() == 1);
  BOOST_REQUIRE(bank2.getTRBs().size() == 1);

  BOOST_REQUIRE(bank2.getPMCalib(256).GetId() == 256);
  BOOST_REQUIRE(bank2.getBarrelSlot(1).getID() == 1);
  BOOST_REQUIRE(bank2.getLayer(1).getId() == 1);
  BOOST_REQUIRE(bank2.getFrame(1).getId() == 1);
  
  BOOST_REQUIRE(bank2.getFEB(1).getID() == 1);
  BOOST_REQUIRE(bank2.getFEB(1).isActive());
  BOOST_REQUIRE(bank2.getFEB(1).status() == "testStatus");
  BOOST_REQUIRE(bank2.getFEB(1).description() == "descr");
  BOOST_REQUIRE(bank2.getFEB(1).version() == 1);

  BOOST_REQUIRE(bank2.getPM(1).getScin().getID() == 1);
  BOOST_REQUIRE(bank2.getPM(2).getScin().getID() == 1);
  BOOST_REQUIRE(bank2.getPM(3).getScin().getID() == 2);
  BOOST_REQUIRE(bank2.getPM(4).getScin().getID() == 2);
  BOOST_REQUIRE(bank2.getScintillator(1).getID() == 1);
  BOOST_REQUIRE(bank2.getScintillator(2).getID() == 2);

  file2.Close();
}


BOOST_AUTO_TEST_SUITE_END()


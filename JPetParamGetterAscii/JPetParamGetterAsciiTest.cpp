#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamGetterAsciiTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "../JPetParamGetterAscii/JPetParamSaverAscii.h"
#include <boost/filesystem.hpp>

const std::string dataDir = "unitTestData/JPetParamGetterAsciiTest/";

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( noExisting_file_read )
{
  JPetParamGetterAscii getter(dataDir+"noExisting.json");
  BOOST_REQUIRE(getter.generateParamBank(1) == 0);
}

BOOST_AUTO_TEST_CASE( empty_file_read )
{
  JPetParamGetterAscii getter(dataDir+"empty.json");
  BOOST_REQUIRE(getter.generateParamBank(1) == 0);
}

BOOST_AUTO_TEST_CASE( minimal_example_read )
{
  JPetParamGetterAscii getter(dataDir+"DB1.json");
		JPetParamBank * bank = getter.generateParamBank(1);
		BOOST_REQUIRE(bank != 0);
		JPetParamBank & paramBank = *bank;
		BOOST_REQUIRE(paramBank.getScintillatorsSize() == 1);
		BOOST_REQUIRE(paramBank.getBarrelSlotsSize() == 1);
		BOOST_REQUIRE(paramBank.getPMsSize() == 1);
		BOOST_REQUIRE(paramBank.getFEBsSize() == 1);
		BOOST_REQUIRE(paramBank.getPMCalibsSize() == 1);
		BOOST_REQUIRE(paramBank.getLayersSize() == 1);
		BOOST_REQUIRE(paramBank.getFramesSize() == 1);
		BOOST_REQUIRE(paramBank.getTOMBChannelsSize() == 1);
		BOOST_REQUIRE(paramBank.getTRBsSize() == 1);

		JPetScin & scintillator = paramBank.getScintillator(1);
		BOOST_REQUIRE(scintillator.getID() == 1);
		BOOST_REQUIRE(scintillator.getAttenLen() == 1.0);
		BOOST_REQUIRE(scintillator.getScinSize().fLength == 1.0);
		BOOST_REQUIRE(scintillator.getScinSize().fHeight == 1.0);
		BOOST_REQUIRE(scintillator.getScinSize().fWidth == 1.0);

		JPetBarrelSlot & barrelSlot = paramBank.getBarrelSlot(1);
		BOOST_REQUIRE(barrelSlot.getID() == 1);
		BOOST_REQUIRE(barrelSlot.isActive());
		BOOST_REQUIRE(barrelSlot.getName() == "Azathoth");
		BOOST_REQUIRE(barrelSlot.getTheta() == 1.0);
		BOOST_REQUIRE(barrelSlot.getInFrameID() == 1);

		JPetPM & pm = paramBank.getPM(1);
		BOOST_REQUIRE(pm.getID() == 1);
		BOOST_REQUIRE(pm.getSide() == JPetPM::Side::SideB);

		JPetFEB & feb = paramBank.getFEB(1);
		BOOST_REQUIRE(feb.getID() == 1);
		BOOST_REQUIRE(feb.isActive());
		BOOST_REQUIRE(feb.status() == std::string("fine"));
		BOOST_REQUIRE(feb.description() == std::string("tall and dark-haired"));
		BOOST_REQUIRE(feb.version() == 1);
		BOOST_REQUIRE(feb.getNtimeOutsPerInput() == 1);
		BOOST_REQUIRE(feb.getNnotimeOutsPerInput() == 1);

		JPetPMCalib & pmCalib = paramBank.getPMCalib(1);
		BOOST_REQUIRE(pmCalib.GetId() == 1);
		BOOST_REQUIRE(pmCalib.GetNamePM() == std::string("Eris"));
		BOOST_REQUIRE(pmCalib.GetOpthv() == 1.0);
		BOOST_REQUIRE(pmCalib.GetECalConst1() == 1.0);
		BOOST_REQUIRE(pmCalib.GetECalConst2() == 1.0);
		BOOST_REQUIRE(pmCalib.GetGainalpha() == 1.0);
		BOOST_REQUIRE(pmCalib.GetGainbeta() == 1.0);

		JPetLayer & layer = paramBank.getLayer(1);
		BOOST_REQUIRE(layer.getId() == 1);
		BOOST_REQUIRE(layer.getIsActive());
		BOOST_REQUIRE(layer.getName() == std::string("Krzesimir"));
		BOOST_REQUIRE(layer.getRadius() == 1.0);

		JPetFrame & frame = paramBank.getFrame(1);
		BOOST_REQUIRE(frame.getId() == 1);
		BOOST_REQUIRE(frame.getIsActive());
		BOOST_REQUIRE(frame.getStatus() == std::string("fine"));
		BOOST_REQUIRE(frame.getDescription() == std::string("tall and dark-haired"));
		BOOST_REQUIRE(frame.getVersion() == 1);
		BOOST_REQUIRE(frame.getCreator() == 1);

		JPetTOMBChannel & tomb = paramBank.getTOMBChannel(1);
		BOOST_REQUIRE(tomb.getThreshold() == 1.0);

		JPetTRB & trb = paramBank.getTRB(1);
		BOOST_REQUIRE(trb.getID() == 1);
		BOOST_REQUIRE(trb.getType() == 1);
		BOOST_REQUIRE(trb.getChannel() == 1);

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
}

BOOST_AUTO_TEST_CASE( minimal_example_write )
{
  JPetParamGetterAscii getter(dataDir+"DB1.json");
		JPetParamBank * bank = getter.generateParamBank(1);
		BOOST_REQUIRE(bank != 0);
		JPetParamSaverAscii saver;
		std::string writtenFileName(dataDir+"writtenDB1.json");
		saver.saveParamBank(*bank, 1, writtenFileName);
  JPetParamGetterAscii regetter(writtenFileName.c_str());
		JPetParamBank * rebank = regetter.generateParamBank(1);
		BOOST_REQUIRE(rebank != 0);
		JPetParamBank & paramBank = *bank;
		JPetParamBank & reparamBank = *rebank;
		BOOST_REQUIRE(paramBank.getScintillatorsSize() == reparamBank.getScintillatorsSize());
		BOOST_REQUIRE(paramBank.getBarrelSlotsSize() == reparamBank.getBarrelSlotsSize());
		BOOST_REQUIRE(paramBank.getPMsSize() == reparamBank.getPMsSize());
		BOOST_REQUIRE(paramBank.getFEBsSize() == reparamBank.getFEBsSize());
		BOOST_REQUIRE(paramBank.getPMCalibsSize() == reparamBank.getPMCalibsSize());
		BOOST_REQUIRE(paramBank.getLayersSize() == reparamBank.getLayersSize());
		BOOST_REQUIRE(paramBank.getFramesSize() == reparamBank.getFramesSize());
		BOOST_REQUIRE(paramBank.getTOMBChannelsSize() == reparamBank.getTOMBChannelsSize());
		BOOST_REQUIRE(paramBank.getTRBsSize() == reparamBank.getTRBsSize());

		JPetScin & scintillator = paramBank.getScintillator(1);
		JPetScin & rescintillator = reparamBank.getScintillator(1);
		BOOST_REQUIRE(scintillator.getID() == rescintillator.getID());
		BOOST_REQUIRE(scintillator.getAttenLen() == rescintillator.getAttenLen());
		BOOST_REQUIRE(scintillator.getScinSize().fLength == rescintillator.getScinSize().fLength);
		BOOST_REQUIRE(scintillator.getScinSize().fHeight == rescintillator.getScinSize().fHeight);
		BOOST_REQUIRE(scintillator.getScinSize().fWidth == rescintillator.getScinSize().fWidth);

		JPetBarrelSlot & barrelSlot = paramBank.getBarrelSlot(1);
		JPetBarrelSlot & rebarrelSlot = reparamBank.getBarrelSlot(1);
		BOOST_REQUIRE(barrelSlot.getID() == rebarrelSlot.getID());
		BOOST_REQUIRE(barrelSlot.isActive() == rebarrelSlot.isActive());
		BOOST_REQUIRE(barrelSlot.getName() == rebarrelSlot.getName());
		BOOST_REQUIRE(barrelSlot.getTheta() == rebarrelSlot.getTheta());
		BOOST_REQUIRE(barrelSlot.getInFrameID() == rebarrelSlot.getInFrameID());

		JPetPM & pm = paramBank.getPM(1);
		JPetPM & repm = reparamBank.getPM(1);
		BOOST_REQUIRE(pm.getID() == repm.getID());
		BOOST_REQUIRE(pm.getSide() == repm.getSide());

		JPetFEB & feb = paramBank.getFEB(1);
		JPetFEB & refeb = reparamBank.getFEB(1);
		BOOST_REQUIRE(feb.getID() == refeb.getID());
		BOOST_REQUIRE(feb.isActive() == refeb.isActive());
		BOOST_REQUIRE(feb.status() == refeb.status());
		BOOST_REQUIRE(feb.description() == refeb.description());
		BOOST_REQUIRE(feb.version() == refeb.version());
		BOOST_REQUIRE(feb.getNtimeOutsPerInput() == refeb.getNtimeOutsPerInput());
		BOOST_REQUIRE(feb.getNnotimeOutsPerInput() == refeb.getNnotimeOutsPerInput());

		JPetPMCalib & pmCalib = paramBank.getPMCalib(1);
		JPetPMCalib & repmCalib = reparamBank.getPMCalib(1);
		BOOST_REQUIRE(pmCalib.GetId() == repmCalib.GetId());
		BOOST_REQUIRE(pmCalib.GetNamePM() == repmCalib.GetNamePM());
		BOOST_REQUIRE(pmCalib.GetOpthv() == repmCalib.GetOpthv());
		BOOST_REQUIRE(pmCalib.GetECalConst1() == repmCalib.GetECalConst1());
		BOOST_REQUIRE(pmCalib.GetECalConst2() == repmCalib.GetECalConst2());
		BOOST_REQUIRE(pmCalib.GetGainalpha() == repmCalib.GetGainalpha());
		BOOST_REQUIRE(pmCalib.GetGainbeta() == repmCalib.GetGainbeta());

		JPetLayer & layer = paramBank.getLayer(1);
		JPetLayer & relayer = reparamBank.getLayer(1);
		BOOST_REQUIRE(layer.getId() == relayer.getId());
		BOOST_REQUIRE(layer.getIsActive() == relayer.getIsActive());
		BOOST_REQUIRE(layer.getName() == relayer.getName());
		BOOST_REQUIRE(layer.getRadius() == relayer.getRadius());

		JPetFrame & frame = paramBank.getFrame(1);
		JPetFrame & reframe = reparamBank.getFrame(1);
		BOOST_REQUIRE(frame.getId() == reframe.getId());
		BOOST_REQUIRE(frame.getIsActive() == reframe.getIsActive());
		BOOST_REQUIRE(frame.getStatus() == reframe.getStatus());
		BOOST_REQUIRE(frame.getDescription() == reframe.getDescription());
		BOOST_REQUIRE(frame.getVersion() == reframe.getVersion());
		BOOST_REQUIRE(frame.getCreator() == reframe.getCreator());

		JPetTOMBChannel & tomb = paramBank.getTOMBChannel(1);
		JPetTOMBChannel & retomb = reparamBank.getTOMBChannel(1);
		BOOST_REQUIRE(tomb.getThreshold() == retomb.getThreshold());

		JPetTRB & trb = paramBank.getTRB(1);
		JPetTRB & retrb = reparamBank.getTRB(1);
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

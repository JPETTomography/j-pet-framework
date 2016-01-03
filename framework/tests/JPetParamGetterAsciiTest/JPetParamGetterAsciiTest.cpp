#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamGetterAsciiTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetParamGetterAscii/JPetParamGetterAscii.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( noExisting_file )
{
  JPetParamGetterAscii getter("noExisting.json");
  BOOST_REQUIRE(getter.generateParamBank(1) == 0);
}

BOOST_AUTO_TEST_CASE( empty_file )
{
  JPetParamGetterAscii getter("empty.json");
  BOOST_REQUIRE(getter.generateParamBank(1) == 0);
}

BOOST_AUTO_TEST_CASE( minimal_example )
{
  JPetParamGetterAscii getter("DB1.json");
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

		JPetScin & scintillator = paramBank.getScintillator(0);
		BOOST_REQUIRE(scintillator.getID() == 1);
		BOOST_REQUIRE(scintillator.getAttenLen() == 1.0);
		BOOST_REQUIRE(scintillator.getScinSize().fLength == 1.0);
		BOOST_REQUIRE(scintillator.getScinSize().fHeight == 1.0);
		BOOST_REQUIRE(scintillator.getScinSize().fWidth == 1.0);

		JPetBarrelSlot & barrelSlot = paramBank.getBarrelSlot(0);
		BOOST_REQUIRE(barrelSlot.getID() == 1);
		BOOST_REQUIRE(barrelSlot.isActive());
		BOOST_REQUIRE(barrelSlot.getName() == "Azathoth");
		BOOST_REQUIRE(barrelSlot.getTheta() == 1.0);
		BOOST_REQUIRE(barrelSlot.getInFrameID() == 1);

		JPetPM & pm = paramBank.getPM(0);
		BOOST_REQUIRE(pm.getID() == 1);
		BOOST_REQUIRE(pm.getSide() == JPetPM::Side::SideB);

		JPetFEB & feb = paramBank.getFEB(0);
		BOOST_REQUIRE(feb.getID() == 1);
		BOOST_REQUIRE(feb.isActive());
		BOOST_REQUIRE(feb.status() == std::string("fine"));
		BOOST_REQUIRE(feb.description() == std::string("tall and dark-haired"));
		BOOST_REQUIRE(feb.version() == 1);
		BOOST_REQUIRE(feb.getNtimeOutsPerInput() == 1);
		BOOST_REQUIRE(feb.getNnotimeOutsPerInput() == 1);

		JPetPMCalib & pmCalib = paramBank.getPMCalib(0);
		BOOST_REQUIRE(pmCalib.GetId() == 1);
		BOOST_REQUIRE(pmCalib.GetNamePM() == std::string("Eris"));
		BOOST_REQUIRE(pmCalib.GetOpthv() == 1.0);
		BOOST_REQUIRE(pmCalib.GetECalConst1() == 1.0);
		BOOST_REQUIRE(pmCalib.GetECalConst2() == 1.0);
		BOOST_REQUIRE(pmCalib.GetGainalpha() == 1.0);
		BOOST_REQUIRE(pmCalib.GetGainbeta() == 1.0);

		JPetLayer & layer = paramBank.getLayer(0);
		BOOST_REQUIRE(layer.getId() == 1);
		BOOST_REQUIRE(layer.getIsActive());
		BOOST_REQUIRE(layer.getName() == std::string("Krzesimir"));
		BOOST_REQUIRE(layer.getRadius() == 1.0);

		JPetFrame & frame = paramBank.getFrame(0);
		BOOST_REQUIRE(frame.getId() == 1);
		BOOST_REQUIRE(frame.getIsActive());
		BOOST_REQUIRE(frame.getStatus() == std::string("fine"));
		BOOST_REQUIRE(frame.getDescription() == std::string("tall and dark-haired"));
		BOOST_REQUIRE(frame.getVersion() == 1);
		BOOST_REQUIRE(frame.getCreator() == 1);

		JPetTOMBChannel & tomb = paramBank.getTOMBChannel(0);
		BOOST_REQUIRE(tomb.getThreshold() == 1.0);

		JPetTRB & trb = paramBank.getTRB(0);
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

BOOST_AUTO_TEST_SUITE_END()

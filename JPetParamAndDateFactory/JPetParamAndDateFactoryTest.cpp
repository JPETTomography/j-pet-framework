#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamAndDateFactoryTest
#include <boost/test/unit_test.hpp>
#include "JPetParamAndDateFactory.h"
#include <boost/filesystem.hpp>


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( scin )
{
  JPetScin scin = factory::makeScin(1, 2.0, 3.0, 4.0, 5.0, p_barrelSlot );
}

BOOST_AUTO_TEST_CASE( feb )
{}
BOOST_AUTO_TEST_CASE( layer )
{}
BOOST_AUTO_TEST_CASE( hit )
{}
BOOST_AUTO_TEST_CASE( sigCh )
{}
BOOST_AUTO_TEST_CASE( barrelSlot )
{}
BOOST_AUTO_TEST_CASE( timeWindow )
{}
BOOST_AUTO_TEST_CASE( pm )
{}
BOOST_AUTO_TEST_CASE( baseSignal )
{}
BOOST_AUTO_TEST_CASE( physSignal )
{}
BOOST_AUTO_TEST_CASE( rawSignal )
{}
BOOST_AUTO_TEST_CASE( tombChannel )
{}

/*
BOOST_AUTO_TEST_CASE( scin )
{
  JPetBarrelSlot p_barrelSlot;
  JPetScin::Dimension dim = JPetScin::kLength;
  JPetScin scin = factory::makeScin(1, 2.0, 3.0, 4.0, 5.0, p_barrelSlot );
  BOOST_REQUIRE_EQUAL(scin.getID(), 1);
  BOOST_REQUIRE_EQUAL(scin.getAttenLen(), 2.0);
  BOOST_REQUIRE_EQUAL(scin.getScinSize(dim), 3.0);
  dim = JPetScin::kHeight;
  BOOST_REQUIRE_EQUAL(scin.getScinSize(dim), 4.0);
  dim = JPetScin::kWidth;
  BOOST_REQUIRE_EQUAL(scin.getScinSize(dim), 5.0);
  BOOST_REQUIRE(scin.getBarrelSlot() == p_barrelSlot);
}

BOOST_AUTO_TEST_CASE( feb )
{
  JPetTRB p_TRB;
  JPetFEB feb = factory::makeFEB( 1, true, "status", "description", 2, 7, 1, 0, p_TRB);
  BOOST_REQUIRE_EQUAL(feb.getID(), 1);
  BOOST_REQUIRE_EQUAL(feb.isActive(), true);
  BOOST_REQUIRE_EQUAL(feb.status(), "status");
  BOOST_REQUIRE_EQUAL(feb.description(), "description");
  BOOST_REQUIRE_EQUAL(feb.version(), 2);
  BOOST_REQUIRE_EQUAL(feb.getCreator(), 7);
  BOOST_REQUIRE_EQUAL(feb.getNtimeOutsPerInput(), 1);
  BOOST_REQUIRE_EQUAL(feb.getNnotimeOutsPerInput(), 0);
  BOOST_REQUIRE(feb.getTRB() ==p_TRB);

}

BOOST_AUTO_TEST_CASE( layer )
{
  JPetFrame frame;
  JPetLayer layer = factory::makeLayer(1, true, "name", 3, frame);
  BOOST_REQUIRE_EQUAL(layer.getID(), 1);
  BOOST_REQUIRE_EQUAL(layer.getIsActive(), true);
  BOOST_REQUIRE_EQUAL(layer.getName(), "name");
  BOOST_REQUIRE_EQUAL(layer.getRadius(), 3);
  BOOST_REQUIRE(const_cast<JPetFrame&>(layer.getFrame()) == frame);

}

BOOST_AUTO_TEST_CASE( hit )
{
   JPetBarrelSlot bs;
   JPetScin sc;
   JPetPhysSignal p_sigA;
   JPetPhysSignal p_sigB;
   TVector3 position(6.0, 7.0, 8.0);
   JPetHit hit = factory::makeHit(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, position, bs, sc, p_sigA, p_sigB );
   BOOST_REQUIRE_EQUAL(hit.getEnergy(), 0.0f);
   BOOST_REQUIRE_EQUAL(hit.getQualityOfEnergy(), 1.0f);
   BOOST_REQUIRE_EQUAL(hit.getTime(), 2.0f);
   BOOST_REQUIRE_EQUAL(hit.getQualityOfTime(), 3.0f);
   BOOST_REQUIRE_EQUAL(hit.getTimeDiff(), 4.0f);
   BOOST_REQUIRE_EQUAL(hit.getQualityOfTimeDiff(), 5.0f); 
   BOOST_REQUIRE_EQUAL(hit.getPosX(), 6.0 );
   BOOST_REQUIRE_EQUAL(hit.getPosY(), 7.0 );
   BOOST_REQUIRE_EQUAL(hit.getPosZ(), 8.0 );

   BOOST_REQUIRE(hit.isSignalASet());
   BOOST_REQUIRE(hit.isSignalBSet());
  
   BOOST_REQUIRE(hit.getBarrelSlot() == bs );
   BOOST_REQUIRE(hit.getScintillator() == sc );
   //BOOST_REQUIRE(hit.getSignalA() == p_sigA );
   //BOOST_REQUIRE(hit.getSignalB() == p_sigB );

}

BOOST_AUTO_TEST_CASE( sigCh )
{
  const JPetPM pm;
  const JPetTRB trb;
  const JPetFEB feb;
  const JPetTOMBChannel channel;
  JPetSigCh::EdgeType type;
  Int_t daqch;
  JPetSigCh sigCh = factory::makeSigCh(pm, trb, feb, channel, 4.0, type, 3.0, daqch, 0.0);
  BOOST_REQUIRE_EQUAL(sigCh.getValue(), 4.0);
  BOOST_REQUIRE_EQUAL(sigCh.getType(), type);
  BOOST_REQUIRE(sigCh.getPM() == pm);
  BOOST_REQUIRE(sigCh.getTRB() == trb);
  BOOST_REQUIRE(const_cast<JPetFEB&>(sigCh.getFEB()) == feb);
  BOOST_REQUIRE(const_cast<JPetTOMBChannel&>(sigCh.getTOMBChannel()) == channel);
  BOOST_REQUIRE(sigCh.getDAQch() == daqch);
  BOOST_REQUIRE(sigCh.getThresholdNumber() == 0.0);
  BOOST_REQUIRE(sigCh.getThreshold() == 3.0);
}

BOOST_AUTO_TEST_CASE( barrelSlot )
{
  JPetLayer p_layer;
  JPetBarrelSlot barrelSlot = factory::makeBarrelSlot(p_layer, 1 , true, "name", 0, 2);
  BOOST_REQUIRE(barrelSlot.getLayer() == p_layer);
  BOOST_REQUIRE_EQUAL(barrelSlot.getID(), 1);
  BOOST_REQUIRE(barrelSlot.isActive());
  BOOST_REQUIRE_EQUAL(barrelSlot.getName(), "name");
  BOOST_REQUIRE_EQUAL(barrelSlot.getTheta(), 0);
  BOOST_REQUIRE_EQUAL(barrelSlot.getInFrameID(), 2);
}

BOOST_AUTO_TEST_CASE( timeWindow )
{
  JPetSigCh new_ch;
  JPetTimeWindow timeWindow = factory::makeTimeWindow(new_ch, 1);
  BOOST_REQUIRE_EQUAL(timeWindow.getNumberOfSigCh(), 1);
  BOOST_REQUIRE_EQUAL(timeWindow.getIndex(), 1);
}

BOOST_AUTO_TEST_CASE( pm )
{
  JPetPM::Side side;
  JPetBarrelSlot p_barrelSlot;
  JPetScin p_scin;
  JPetFEB p_FEB;
  std::pair<float, float> gain(3.0, 4.0);
  JPetPM pm = factory::makePM(side, 1, 1, 2, gain, p_FEB, p_scin, p_barrelSlot);
  BOOST_REQUIRE(pm.getSide() == side);
  BOOST_REQUIRE_EQUAL(pm.getHVset(), 1);
  BOOST_REQUIRE_EQUAL(pm.getHVopt(), 2);
  BOOST_REQUIRE_EQUAL(pm.getHVgain().first, 3.0);
  BOOST_REQUIRE_EQUAL(pm.getHVgain().second, 4.0);
  BOOST_REQUIRE(const_cast<JPetFEB&>(pm.getFEB()) == p_FEB);
  BOOST_REQUIRE(pm.getScin() == p_scin);
  BOOST_REQUIRE(pm.getBarrelSlot() == p_barrelSlot);
}
*/
BOOST_AUTO_TEST_SUITE_END()

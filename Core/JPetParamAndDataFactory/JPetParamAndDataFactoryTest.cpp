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
 *  @file JPetParamAndDataFactoryTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamAndDataFactoryTest

#include "JPetParamAndDataFactory.h"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(scin)
{
  JPetBarrelSlot p_barrelSlot(1, true, "name", 1, 1);
  JPetScin scin = param_and_data_factory::makeScin(1, 2.0, 3.0, 4.0, 5.0, p_barrelSlot );
  BOOST_REQUIRE_EQUAL(scin.getID(), 1);
  BOOST_REQUIRE_EQUAL(scin.getAttenLen(), 2.0);
  JPetScin::Dimension dim = JPetScin::kLength;
  BOOST_REQUIRE_EQUAL(scin.getScinSize(dim), 3.0);
  dim = JPetScin::kHeight;
  BOOST_REQUIRE_EQUAL(scin.getScinSize(dim), 4.0);
  dim = JPetScin::kWidth;
  BOOST_REQUIRE_EQUAL(scin.getScinSize(dim), 5.0);
  BOOST_REQUIRE_EQUAL(scin.getBarrelSlot().getID(), p_barrelSlot.getID());
  BOOST_REQUIRE_EQUAL(scin.getBarrelSlot().isActive(), p_barrelSlot.isActive());
  BOOST_REQUIRE_EQUAL(scin.getBarrelSlot().getName(), p_barrelSlot.getName());
  BOOST_REQUIRE_EQUAL(scin.getBarrelSlot().getTheta(), p_barrelSlot.getTheta());
  BOOST_REQUIRE_EQUAL(scin.getBarrelSlot().getInFrameID(), p_barrelSlot.getInFrameID());
}

BOOST_AUTO_TEST_CASE(feb)
{
  JPetTRB p_TRB(1, 2, 2);
  const std::string status = "status";
  const std::string description = "description";
  JPetFEB feb = param_and_data_factory::makeFEB( 1, true, status, description, 2, 7, 1, 0, p_TRB);
  BOOST_REQUIRE_EQUAL(feb.getID(), 1);
  BOOST_REQUIRE_EQUAL(feb.isActive(), true);
  BOOST_REQUIRE_EQUAL(feb.status(), "status");
  BOOST_REQUIRE_EQUAL(feb.description(), "description");
  BOOST_REQUIRE_EQUAL(feb.version(), 2);
  BOOST_REQUIRE_EQUAL(feb.getCreator(), 7);
  BOOST_REQUIRE_EQUAL(feb.getNtimeOutsPerInput(), 1);
  BOOST_REQUIRE_EQUAL(feb.getNnotimeOutsPerInput(), 0);
  BOOST_REQUIRE_EQUAL(feb.getTRB().getID(), p_TRB.getID());
  BOOST_REQUIRE_EQUAL(feb.getTRB().getType(), p_TRB.getType());
  BOOST_REQUIRE_EQUAL(feb.getTRB().getChannel(), p_TRB.getChannel());
}

BOOST_AUTO_TEST_CASE(layer)
{
  const std::string name = "name";
  JPetFrame frame(1, true, "status", "description", 2, 3);
  JPetLayer layer = param_and_data_factory::makeLayer(1, true, name, 3, frame);
  BOOST_REQUIRE_EQUAL(layer.getID(), 1);
  BOOST_REQUIRE_EQUAL(layer.getIsActive(), true);
  BOOST_REQUIRE_EQUAL(layer.getName(), "name");
  BOOST_REQUIRE_EQUAL(layer.getRadius(), 3);
  BOOST_REQUIRE_EQUAL(layer.getFrame().getID(), frame.getID());
  BOOST_REQUIRE_EQUAL(layer.getFrame().getIsActive(), frame.getIsActive());
  BOOST_REQUIRE_EQUAL(layer.getFrame().getStatus(), frame.getStatus());
  BOOST_REQUIRE_EQUAL(layer.getFrame().getCreator(), frame.getCreator());
}

BOOST_AUTO_TEST_CASE(hit)
{
  JPetBarrelSlot bs(1, true, "name", 2, 3);
  JPetScin sc(1, 2, 3, 4, 5);
  JPetPhysSignal p_sigA(true);
  JPetPhysSignal p_sigB(true);
  p_sigA.setTime(1);
  p_sigA.setPhe(2);
  p_sigB.setTime(3);
  p_sigB.setPhe(4);
  TVector3 position(6.0, 7.0, 8.0);
  JPetHit hit = param_and_data_factory::makeHit(0.0f, 1.0f, 2.0f, 3.0f,
    position, p_sigA, p_sigB, bs, sc, 4.0f, 5.0f);
  BOOST_REQUIRE_EQUAL(hit.getEnergy(), 0.0f);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfEnergy(), 1.0f);
  BOOST_REQUIRE_EQUAL(hit.getTime(), 2.0f);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfTime(), 3.0f);
  BOOST_REQUIRE_EQUAL(hit.getTimeDiff(), 5.0f);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfTimeDiff(), 4.0f);
  BOOST_REQUIRE_EQUAL(hit.getPosX(), 6.0);
  BOOST_REQUIRE_EQUAL(hit.getPosY(), 7.0);
  BOOST_REQUIRE_EQUAL(hit.getPosZ(), 8.0);
  BOOST_REQUIRE(hit.isSignalASet());
  BOOST_REQUIRE(hit.isSignalBSet());
  BOOST_REQUIRE_EQUAL(hit.getBarrelSlot().getID(), bs.getID());
  BOOST_REQUIRE_EQUAL(hit.getBarrelSlot().isActive(), bs.isActive());
  BOOST_REQUIRE_EQUAL(hit.getBarrelSlot().getName(), bs.getName());
  BOOST_REQUIRE_EQUAL(hit.getBarrelSlot().getTheta(), bs.getTheta());
  BOOST_REQUIRE_EQUAL(hit.getScintillator().getID(), sc.getID());
  BOOST_REQUIRE_EQUAL(hit.getScintillator().getAttenLen(), sc.getAttenLen());
  BOOST_REQUIRE_EQUAL(hit.getSignalA().getTime(), p_sigA.getTime());
  BOOST_REQUIRE_EQUAL(hit.getSignalA().getPhe(), p_sigA.getPhe());
  BOOST_REQUIRE_EQUAL(hit.getSignalB().getTime(), p_sigB.getTime());
  BOOST_REQUIRE_EQUAL(hit.getSignalB().getPhe(), p_sigB.getPhe());
}

BOOST_AUTO_TEST_CASE(sigCh)
{
  JPetPM pm(1, "");
  pm.setHVopt(2);
  pm.setHVset(3);
  JPetTRB trb(1, 2, 3);
  JPetFEB feb(1);
  feb.setTRB(trb);
  JPetTOMBChannel channel(1);
  channel.setTRB(trb);
  JPetSigCh::EdgeType type = JPetSigCh::Trailing;
  Int_t daqch;
  JPetSigCh sigCh = param_and_data_factory::makeSigCh(
    pm, trb, feb, channel, 4.0, type, 3.0, daqch, 0.0
  );
  BOOST_REQUIRE_EQUAL(sigCh.getPM().getHVopt(), pm.getHVopt());
  BOOST_REQUIRE_EQUAL(sigCh.getPM().getHVset(), pm.getHVset());
  BOOST_REQUIRE_EQUAL(sigCh.getTRB().getID(), trb.getID());
  BOOST_REQUIRE_EQUAL(sigCh.getTRB().getType(), trb.getType());
  BOOST_REQUIRE_EQUAL(sigCh.getTRB().getChannel(), trb.getChannel());
  BOOST_REQUIRE_EQUAL(sigCh.getFEB().getID(), feb.getID());
  BOOST_REQUIRE_EQUAL(sigCh.getFEB().getTRB().getID(), feb.getTRB().getID());
  BOOST_REQUIRE_EQUAL(sigCh.getTOMBChannel().getChannel(), channel.getChannel());
  BOOST_REQUIRE_EQUAL(sigCh.getTOMBChannel().getTRB().getID(), channel.getTRB().getID());
  BOOST_REQUIRE_EQUAL(sigCh.getValue(), 4.0);
  BOOST_REQUIRE_EQUAL(sigCh.getThresholdNumber(), 0.0);
  BOOST_REQUIRE_EQUAL(sigCh.getThreshold(), 3.0);
  BOOST_REQUIRE_EQUAL(sigCh.getType(), type);
  BOOST_REQUIRE_EQUAL(sigCh.getDAQch(), daqch);
}

BOOST_AUTO_TEST_CASE(barrelSlot)
{
  const std::string name = "name";
  JPetLayer p_layer(1, true, "name", 3);
  JPetBarrelSlot barrelSlot = param_and_data_factory::makeBarrelSlot(
    p_layer, 1 , true, name, 0, 2
  );
  BOOST_REQUIRE_EQUAL(barrelSlot.getID(), 1);
  BOOST_REQUIRE(barrelSlot.isActive());
  BOOST_REQUIRE_EQUAL(barrelSlot.getName(), "name");
  BOOST_REQUIRE_EQUAL(barrelSlot.getTheta(), 0);
  BOOST_REQUIRE_EQUAL(barrelSlot.getInFrameID(), 2);
  BOOST_REQUIRE_EQUAL(barrelSlot.getLayer().getID(), p_layer.getID());
  BOOST_REQUIRE_EQUAL(barrelSlot.getLayer().getRadius(), p_layer.getRadius());
}

BOOST_AUTO_TEST_CASE(pm)
{
  JPetPM::Side side = JPetPM::SideA;
  JPetBarrelSlot p_barrelSlot;
  JPetScin p_scin(1, 2, 3, 4, 5);
  JPetFEB p_FEB(1, true, "p_status", "p_description", 2, 3, 4, 5);
  std::pair<float, float> gain(3.0, 4.0);
  JPetPM makePM(JPetPM::Side side, int id, int set, int opt,
    std::pair<float, float>& gain, JPetFEB & p_FEB, JPetScin & p_scin,
    JPetBarrelSlot & p_barrelSlot);
  JPetPM pm = param_and_data_factory::makePM(side, 1, 1, 2, gain, "no writing",
    p_FEB, p_scin, p_barrelSlot
  );
  BOOST_REQUIRE_EQUAL(pm.getID(), 1);
  BOOST_REQUIRE_EQUAL(pm.getHVset(), 1);
  BOOST_REQUIRE_EQUAL(pm.getHVopt(), 2);
  BOOST_REQUIRE_EQUAL(pm.getSide(), JPetPM::SideA);
  BOOST_REQUIRE_EQUAL(pm.getHVgain().first, 3.0);
  BOOST_REQUIRE_EQUAL(pm.getHVgain().second, 4.0);
  BOOST_REQUIRE_EQUAL(pm.getDescription(), "no writing");
  BOOST_REQUIRE_EQUAL(pm.getScin().getID(), p_scin.getID() );
  BOOST_REQUIRE_EQUAL(pm.getScin().getAttenLen(), p_scin.getAttenLen() );
  BOOST_REQUIRE_EQUAL(pm.getBarrelSlot().getID(), p_barrelSlot.getID());
  BOOST_REQUIRE_EQUAL(pm.getBarrelSlot().getName(), p_barrelSlot.getName());
  BOOST_REQUIRE_EQUAL(pm.getFEB().getID(), p_FEB.getID());
  BOOST_REQUIRE_EQUAL(pm.getFEB().isActive(), p_FEB.isActive());
}

BOOST_AUTO_TEST_CASE(baseSignal)
{
  JPetPM pm(1, "");
  pm.setHVopt(2);
  pm.setHVset(3);
  JPetBarrelSlot p_barrelSlot(1, true, "name", 2, 3);
  JPetBaseSignal bs = param_and_data_factory::makeBaseSignal(pm, p_barrelSlot);
  BOOST_REQUIRE_EQUAL(bs.getPM().getHVopt(), pm.getHVopt() );
  BOOST_REQUIRE_EQUAL(bs.getPM().getHVset(), pm.getHVset() );
  BOOST_REQUIRE_EQUAL(bs.getBarrelSlot().getID(), p_barrelSlot.getID());
  BOOST_REQUIRE_EQUAL(bs.getBarrelSlot().getName(), p_barrelSlot.getName());
}

BOOST_AUTO_TEST_CASE(physSignal)
{
  JPetRecoSignal recoSignal(2);
  JPetPhysSignal ps = param_and_data_factory::makePhysSignal(1, 2, 3, 4, recoSignal);
  BOOST_REQUIRE_EQUAL(ps.getTime(), 1);
  BOOST_REQUIRE_EQUAL(ps.getQualityOfTime(), 2);
  BOOST_REQUIRE_EQUAL(ps.getPhe(), 3);
  BOOST_REQUIRE_EQUAL(ps.getQualityOfPhe(), 4);
  BOOST_REQUIRE_EQUAL(ps.getRecoSignal().getAmplitude(), recoSignal.getAmplitude());
  BOOST_REQUIRE_EQUAL(ps.getRecoSignal().getCharge(), recoSignal.getCharge());
  BOOST_REQUIRE_EQUAL(ps.getRecoSignal().getOffset(), recoSignal.getOffset());
}

BOOST_AUTO_TEST_CASE(rawSignal)
{
  JPetSigCh::EdgeType type = JPetSigCh::Trailing;
  std::vector<JPetSigCh> vec = {JPetSigCh(type, 1), JPetSigCh(type, 1)};
  JPetRawSignal rs = param_and_data_factory::makeRawSignal(vec);
  BOOST_REQUIRE_EQUAL(rs.getNumberOfPoints(type), 2);
}

BOOST_AUTO_TEST_CASE(tombChannel)
{
  JPetPM pm(1, "");
  pm.setHVopt(2);
  pm.setHVset(3);
  JPetTRB trb(1, 2, 3);
  JPetFEB feb(1, true, "p_status", "p_description", 2, 3, 4, 5);
  JPetTOMBChannel tombChannel = param_and_data_factory::makeTOMBChannel(3, feb, trb, pm, 4, 5, 6);
  BOOST_REQUIRE_EQUAL(tombChannel.getChannel(), 3);
  BOOST_REQUIRE_EQUAL(tombChannel.getThreshold(), 4);
  BOOST_REQUIRE_EQUAL(tombChannel.getLocalChannelNumber(), 5);
  BOOST_REQUIRE_EQUAL(tombChannel.getFEBInputNumber(), 6);
  BOOST_REQUIRE_EQUAL(tombChannel.getTRB().getID(), trb.getID());
  BOOST_REQUIRE_EQUAL(tombChannel.getTRB().getType(), trb.getType());
  BOOST_REQUIRE_EQUAL(tombChannel.getTRB().getChannel(), trb.getChannel());
  BOOST_REQUIRE_EQUAL(tombChannel.getFEB().getID() , feb.getID());
  BOOST_REQUIRE_EQUAL(tombChannel.getFEB().isActive() , feb.isActive());
  BOOST_REQUIRE_EQUAL(tombChannel.getPM().getHVopt(), pm.getHVopt());
  BOOST_REQUIRE_EQUAL(tombChannel.getPM().getHVset(), pm.getHVset());
}

BOOST_AUTO_TEST_SUITE_END()

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
 *  @file JPetParamAndDataFactory.cpp
 */

#include "./JPetParamAndDataFactory.h"

namespace param_and_data_factory
{
JPetScin makeScin(int id, float attenLen, float length,
  float height, float width, JPetBarrelSlot& p_barrelSlot)
{
  JPetScin scinObject(id, attenLen, length, height, width);
  scinObject.setBarrelSlot(p_barrelSlot);
  return scinObject;
}

JPetFEB makeFEB(int p_id, bool p_isActive, const std::string& p_status,
  const std::string& p_description, int p_version, int p_userId,
  int p_n_time_outputs_per_input, int p_n_notime_outputs_per_input,
  JPetTRB& p_TRB)
{
  JPetFEB objectFEB(p_id, p_isActive, p_status, p_description, p_version,
    p_userId, p_n_time_outputs_per_input, p_n_notime_outputs_per_input);
  objectFEB.setTRB(p_TRB);
  return objectFEB;
}

JPetLayer makeLayer(int id, bool isActive, const std::string& name,
  float radius, JPetFrame& frame)
{
  JPetLayer objectLayer(id, isActive, name, radius);
  objectLayer.setFrame(frame);
  return objectLayer;
}

JPetHit makeHit(float e, float qe, float t, float qt, TVector3& pos,
  JPetPhysSignal& siga, JPetPhysSignal& sigb, JPetBarrelSlot& bslot,
  JPetScin& scin, float qtd, float td)
{
  JPetHit hitObject(e, qe, t, qt, pos, siga, sigb, bslot, scin);
  hitObject.setQualityOfTimeDiff(qtd);
  hitObject.setTimeDiff(td);
  return hitObject;
}

JPetSigCh makeSigCh(JPetPM& pm, JPetTRB& trb, JPetFEB& feb,
  JPetTOMBChannel& channel, float val, JPetSigCh::EdgeType type, float thr,
  Int_t daqch, unsigned int threshold_number)
{
  JPetSigCh sigChObject(type, val);
  sigChObject.setPM(pm);
  sigChObject.setTRB(trb);
  sigChObject.setFEB(feb);
  sigChObject.setTOMBChannel(channel);
  sigChObject.setThreshold(thr);
  sigChObject.setDAQch(daqch);
  sigChObject.setThresholdNumber(threshold_number);
  return sigChObject;
}

JPetBarrelSlot makeBarrelSlot(JPetLayer& p_layer, int id, bool isActive,
  const std::string& name, float theta, int inFrameID)
{
  JPetBarrelSlot barrelSlotObject(id, isActive, name, theta, inFrameID);
  barrelSlotObject.setLayer(p_layer);
  return barrelSlotObject;
}

JPetTimeWindow makeTimeWindow(const std::vector<JPetSigCh>& vec)
{
  JPetTimeWindow timeWindowObject;
  for (auto sigch : vec) {
    timeWindowObject.add<JPetSigCh>(sigch);
  }
  return timeWindowObject;
}

JPetPM makePM(JPetPM::Side side, int id, int set, int opt,
  std::pair<float, float>& gain, std::string description, JPetFEB& p_FEB,
  JPetScin& p_scin, JPetBarrelSlot& p_barrelSlot)
{
  JPetPM pmObject(side, id, set, opt, gain, description);
  pmObject.setFEB(p_FEB);
  pmObject.setScin(p_scin);
  pmObject.setBarrelSlot(p_barrelSlot);
  return pmObject;
}

JPetBaseSignal makeBaseSignal(JPetPM& pm, JPetBarrelSlot& bs)
{
  JPetBaseSignal baseSignalObject;
  baseSignalObject.setPM(pm);
  baseSignalObject.setBarrelSlot(bs);
  return baseSignalObject;
}

JPetPhysSignal makePhysSignal(float time, float qualityOfTime, double phe,
  double qualityOfPhe, JPetRecoSignal& recoSignal)
{
  JPetPhysSignal physSignalObject;
  physSignalObject.setTime(time);
  physSignalObject.setQualityOfTime(qualityOfTime);
  physSignalObject.setPhe(phe);
  physSignalObject.setQualityOfPhe(qualityOfPhe);
  physSignalObject.setRecoSignal(recoSignal);
  return physSignalObject;
}

JPetRawSignal makeRawSignal(const std::vector<JPetSigCh>& vec)
{
  JPetRawSignal rawSignalObject(vec.size());
  for (const auto& sigch : vec) {
    rawSignalObject.addPoint(sigch);
  }
  return rawSignalObject;
}

JPetTOMBChannel makeTOMBChannel(int p_channel, JPetFEB& p_FEB, JPetTRB& p_TRB,
  JPetPM& p_PM, float p_threshold, unsigned int lcn, unsigned int fin)
{
  JPetTOMBChannel tombChannelObject(p_channel);
  tombChannelObject.setFEB(p_FEB);
  tombChannelObject.setTRB(p_TRB);
  tombChannelObject.setPM(p_PM);
  tombChannelObject.setThreshold(p_threshold);
  tombChannelObject.setLocalChannelNumber(lcn);
  tombChannelObject.setFEBInputNumber(fin);
  return tombChannelObject;
}
}

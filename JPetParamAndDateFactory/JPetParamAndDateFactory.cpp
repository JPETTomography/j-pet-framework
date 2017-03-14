/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetParamAndDateFactory.cpp
 */

#include "./JPetParamAndDateFactory.h"

namespace factory
{
JPetScin makeScin(int id, float attenLen, float length, float height, float width, JPetBarrelSlot& p_barrelSlot )
{
  JPetScin scinObject(id, attenLen, length, height, width);
  scinObject.setBarrelSlot(p_barrelSlot);
  return scinObject;
}

JPetFEB makeFEB(int p_id, bool p_isActive, std::string p_status, std::string p_description, int p_version, int p_userId, int p_n_time_outputs_per_input, int p_n_notime_outputs_per_input, JPetTRB& p_TRB)
{
  JPetFEB objectFEB(p_id, p_isActive, p_status, p_description, p_version, p_userId, p_n_time_outputs_per_input, p_n_notime_outputs_per_input);
  objectFEB.setTRB(p_TRB);
  return objectFEB;
}

JPetLayer makeLayer(int id, bool isActive, std::string name, float radius, JPetFrame& frame)
{
  JPetLayer objectLayer(id, isActive, name, radius);
  objectLayer.setFrame(frame);
  return objectLayer;
}

JPetHit makeHit(float energy, float qualityOfEnergy, float time, float qualityOfTime, float td, float qtd, TVector3& pos , JPetBarrelSlot& bs, JPetScin& sc, JPetPhysSignal& p_sigA, JPetPhysSignal& p_sigB )
{
  JPetHit hitObject(energy, qualityOfEnergy, time, qualityOfTime, pos, p_sigA, p_sigB, bs, sc); 
  hitObject.setTimeDiff(td);
  hitObject.setQualityOfTimeDiff(qtd); 
  return hitObject;
}

JPetSigCh makeSigCh(const JPetPM & pm, const JPetTRB & trb, const JPetFEB & feb, const JPetTOMBChannel & channel, float val, JPetSigCh::EdgeType type, float thr, Int_t daqch, unsigned int threshold_number){
   JPetSigCh sigChObject(type, val );
   sigChObject.setPM(pm);
   sigChObject.setTRB(trb);
   sigChObject.setFEB(feb);
   sigChObject.setTOMBChannel(channel);
   sigChObject.setThreshold(thr);
   sigChObject.setDAQch(daqch);
   sigChObject.setThresholdNumber(threshold_number);
   return sigChObject;
  }

JPetBarrelSlot makeBarrelSlot(JPetLayer& p_layer, int id, bool isActive, std::string name, float theta, int inFrameID)
{
  JPetBarrelSlot barrelSlotObject(id, isActive, name, theta, inFrameID);
  barrelSlotObject.setLayer(p_layer);
  return barrelSlotObject;
}

JPetTimeWindow makeTimeWindow(JPetSigCh& new_ch, unsigned int index)
{
  JPetTimeWindow timeWindowObject;
  timeWindowObject.addCh(new_ch);
  timeWindowObject.setIndex(index);
  return timeWindowObject;
}

JPetPM makePM(JPetPM::Side side, int id, int set, int opt, std::pair<float, float>& gain, JPetFEB& p_FEB, JPetScin& p_scin, JPetBarrelSlot& p_barrelSlot)
{
  JPetPM pmObject(side, id, set, opt, gain);
  pmObject.setFEB(p_FEB);
  pmObject.setScin(p_scin);
  pmObject.setBarrelSlot(p_barrelSlot);
  return pmObject;
}

}
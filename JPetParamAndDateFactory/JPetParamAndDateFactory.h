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
 *  @file JPetParamAndDateFactory.h
 */

#ifndef JPETPARAM_AND_DATE_FACTORY_H
#define JPETPARAM_AND_DATE_FACTORY_H

#include "../JPetScin/JPetScin.h"
#include "../JPetFEB/JPetFEB.h"
#include "../JPetLayer/JPetLayer.h"
#include "../JPetHit/JPetHit.h"
#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetTimeWindow/JPetTimeWindow.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetFrame/JPetFrame.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetBaseSignal/JPetBaseSignal.h"
#include "../JPetRawSignal/JPetRawSignal.h"
#include  "TVector3.h"
#include "../JPetTOMBChannel/JPetTOMBChannel.h"

namespace factory
{
JPetScin makeScin(int id, float attenLen, float length, float height, float width, JPetBarrelSlot& p_barrelSlot ); 
JPetFEB makeFEB(int p_id, bool p_isActive, std::string p_status, std::string p_description, int p_version, int p_userId, int p_n_time_outputs_per_input, int p_n_notime_outputs_per_input, JPetTRB& p_TRB);
JPetLayer makeLayer(int id, bool isActive, std::string name, float radius,JPetFrame& frame); 
JPetHit makeHit(float energy, float qualityOfEnergy, float time, float qualityOfTime, float td, float qtd, TVector3& pos ,JPetBarrelSlot& bs, JPetScin& sc, JPetPhysSignal& p_sigA, JPetPhysSignal& p_sigB );
JPetSigCh makeSigCh(const JPetPM & pm, const JPetTRB & trb, const JPetFEB & feb, const JPetTOMBChannel & channel, float val, JPetSigCh::EdgeType type, float thr, Int_t daqch, unsigned int threshold_number); 
JPetBarrelSlot makeBarrelSlot(JPetLayer& p_layer, int id, bool isActive, std::string name, float theta, int inFrameID); 
JPetTimeWindow makeTimeWindow(JPetSigCh& new_ch, unsigned int index); 
JPetPM makePM(JPetPM::Side side, int id, int set, int opt, std::pair<float, float>& gain, JPetFEB& p_FEB, JPetScin& p_scin, JPetBarrelSlot& p_barrelSlot); 
JPetBaseSignal makeBaseSignal(unsigned int index, const JPetPM & pm, const JPetBarrelSlot & bs);
JPetPhysSignal makePhysSignal(float time, float qualityOfTime, double phe, double qualityOfPhe, const JPetRecoSignal& recoSignal);
JPetRawSignal makeRawSignal(const int points, const JPetSigCh& sigch);
JPetTOMBChannel makeTOMBChannel(int p_channel, JPetFEB& p_FEB, JPetTRB& p_TRB, JPetPM& p_PM, float p_threshold, unsigned int lcn, unsigned int fin);
}
#endif /*  !Factory_H */

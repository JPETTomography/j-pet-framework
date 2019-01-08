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
 *  @file JPetParamAndDataFactory.h
 */

#ifndef JPETPARAM_AND_DATA_FACTORY_H
#define JPETPARAM_AND_DATA_FACTORY_H

#include "./JPetTOMBChannel/JPetTOMBChannel.h"
#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetTimeWindow/JPetTimeWindow.h"
#include "./JPetPhysSignal/JPetPhysSignal.h"
#include "./JPetBaseSignal/JPetBaseSignal.h"
#include "./JPetRawSignal/JPetRawSignal.h"
#include "./JPetLayer/JPetLayer.h"
#include "./JPetSigCh/JPetSigCh.h"
#include "./JPetFrame/JPetFrame.h"
#include "./JPetScin/JPetScin.h"
#include "./JPetFEB/JPetFEB.h"
#include "./JPetHit/JPetHit.h"
#include "./JPetTRB/JPetTRB.h"
#include "./JPetPM/JPetPM.h"
#include  "TVector3.h"

/**
 * @brief Set of facotry methods for params
 *
 * A namespace contains set of factory methods to create
 * fully operational parameter and data objects.
 *
 * @todo There is no test for Time Window
 */
namespace param_and_data_factory
{
JPetScin makeScin(int id, float attenLen, float length,
  float height, float width, JPetBarrelSlot& p_barrelSlot);

JPetFEB makeFEB(int p_id, bool p_isActive, const std::string& p_status,
  const std::string& p_description, int p_version, int p_userId,
  int p_n_time_outputs_per_input, int p_n_notime_outputs_per_input,
  JPetTRB& p_TRB);

JPetLayer makeLayer(int id, bool isActive, const std::string& name,
  float radius, JPetFrame& frame);

JPetHit makeHit(float e, float qe, float t, float qt, TVector3& pos,
  JPetPhysSignal& siga, JPetPhysSignal& sigb, JPetBarrelSlot& bslot,
  JPetScin& scin, float qtd, float td);

JPetSigCh makeSigCh(JPetPM& pm, JPetTRB& trb, JPetFEB& feb,
  JPetTOMBChannel& channel, float val, JPetSigCh::EdgeType type,
  float thr, Int_t daqch, unsigned int threshold_number);

JPetBarrelSlot makeBarrelSlot(JPetLayer& p_layer, int id, bool isActive,
  const std::string& name, float theta, int inFrameID);

JPetTimeWindow makeTimeWindow(const std::vector<JPetSigCh>& vec);

JPetPM makePM(JPetPM::Side side, int id, int set, int opt,
  std::pair<float, float>& gain, std::string description,
  JPetFEB& p_FEB, JPetScin& p_scin, JPetBarrelSlot& p_barrelSlot);

JPetBarrelSlot makeBarrelSlot(JPetLayer& p_layer, int id, bool isActive,
  const std::string& name, float theta, int inFrameID);

JPetBaseSignal makeBaseSignal(JPetPM& pm, JPetBarrelSlot& bs);

JPetPhysSignal makePhysSignal(float time, float qualityOfTime, double phe,
  double qualityOfPhe, JPetRecoSignal& recoSignal);

JPetRawSignal makeRawSignal(const std::vector<JPetSigCh>& vec);

JPetTOMBChannel makeTOMBChannel(int p_channel, JPetFEB& p_FEB, JPetTRB& p_TRB,
  JPetPM& p_PM, float p_threshold, unsigned int lcn, unsigned int fin);
}

#endif /* !JPETPARAM_AND_DATA_FACTORY_H */

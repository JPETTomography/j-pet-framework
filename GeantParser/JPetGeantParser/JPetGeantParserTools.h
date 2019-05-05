/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetGeantParserTools.h
 */

#ifndef JPETGEANTPARSERTOOLS_H
#define JPETGEANTPARSERTOOLS_H

#include <map>
#include <vector>
#include <array>
#include <TRandom3.h>
#include <JPetMCHit/JPetMCHit.h>
#include <JPetHit/JPetHit.h>
#include <JPetMCDecayTree/JPetMCDecayTree.h>
#include <JPetGeantScinHits/JPetGeantScinHits.h>
#include <JPetGeantEventPack/JPetGeantEventPack.h>
#include <JPetGeomMapping/JPetGeomMapping.h>
#include "JPetParamBank/JPetParamBank.h"
#include <JPetRandom/JPetRandom.h>

#ifdef __CINT__
//when cint is used instead of compiler, override word is not recognized
//nevertheless it's needed for checking if the structure of project is correct
#   define override
#endif

class JPetGeantParserTools
{
public:
  static JPetMCHit createJPetMCHit(JPetGeantScinHits* geantHit, const JPetParamBank& paramBank );

  static JPetHit reconstructHit(JPetMCHit& hit, const JPetParamBank& paramBank, const float timeShift, const float z_resolution );

  static bool isHitReconstructed(JPetHit& hit, const float th);

  static void identifyRecoHits(JPetGeantScinHits* geantHit, const JPetHit& hit,
                               bool& isRecPrompt, std::array<bool, 2>& isSaved2g,
                               std::array<bool, 3>& isSaved3g,
                               float& enePrompt, std::array<float, 2>& ene2g,
                               std::array<float, 3>& ene3g );

  static float estimateNextDecayTimeExp(float activityMBq);
  static void fillTimeDistoOfDecays(float activityMBq, float timeWindowMin, float timeWindowMax);
  static float getNextTimeShift();
  static unsigned int getNumberOfDecaysInWindow();
  static bool isTimeWindowFull();
  static void clearTimeDistoOfDecays();
  static std::vector<float> getTimeDistoOfDecays();
  static std::vector<float> getTimeDiffDistoOfDecays();
  static std::pair<float, float> calculateEfficiency(ulong, ulong);

private:
  static TRandom3* fRandomGenerator;
  static std::vector<float> fTimeDistroOfDecays;
  static std::vector<float> fTimeDiffDistro;
  static unsigned int fCurrentIndexTimeShift;

};

#endif

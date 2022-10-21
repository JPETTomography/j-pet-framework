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

#include "JPetParamBank/JPetParamBank.h"
#include "JPetSmearingFunctions/JPetSmearingFunctions.h"
#include <JPetGeantEventPack/JPetGeantEventPack.h>
#include <JPetGeantScinHits/JPetGeantScinHits.h>
#include <JPetGeomMapping/JPetGeomMapping.h>
#include <JPetHit/JPetHit.h>
#include <JPetMCDecayTree/JPetMCDecayTree.h>
#include <JPetMCHit/JPetMCHit.h>
#include <TRandom3.h>
#include <array>
#include <functional>
#include <map>
#include <tuple>
#include <vector>

#ifdef __CINT__
// when cint is used instead of compiler, override word is not recognized
// nevertheless it's needed for checking if the structure of project is correct
#define override
#endif

class JPetGeantParserTools
{
public:
  static JPetMCHit createJPetMCHit(JPetGeantScinHits* geantHit, const JPetParamBank& paramBank);

  static JPetHit reconstructHit(JPetMCHit& hit, const JPetParamBank& paramBank, const float timeShift, JPetHitExperimentalParametrizer& parametrizer);

  static bool isHitReconstructed(JPetHit& hit, const float th);

  static void identifyRecoHits(JPetGeantScinHits* geantHit, const JPetHit& hit, bool& isRecPrompt, std::array<bool, 2>& isSaved2g,
                               std::array<bool, 3>& isSaved3g, float& enePrompt, std::array<float, 2>& ene2g, std::array<float, 3>& ene3g);

  static float estimateNextDecayTimeExp(float activityMBq);
  static std::tuple<std::vector<float>, std::vector<float>> getTimeDistoOfDecays(float activityMBq, float timeWindowMin, float timeWindowMax);
  static std::pair<float, float> calculateEfficiency(ulong, ulong);

  static void setSeedTogRandom(unsigned long seed);
};

#endif

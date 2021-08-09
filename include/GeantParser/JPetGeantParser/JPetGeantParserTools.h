/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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

#include "Hits/JPetMCRecoHit/JPetMCRecoHit.h"
#include "JPetGeantEventPack/JPetGeantEventPack.h"
#include "JPetGeantScinHits/JPetGeantScinHits.h"
#include "JPetMCDecayTree/JPetMCDecayTree.h"
#include "JPetParamBank/JPetParamBank.h"
#include "JPetRawMCHit/JPetRawMCHit.h"
#include "JPetSmearingFunctions/JPetSmearingFunctions.h"
#include <TRandom3.h>
#include <array>
#include <functional>
#include <map>
#include <tuple>
#include <vector>

class JPetGeantParserTools
{
public:
  static JPetRawMCHit createJPetRawMCHit(JPetGeantScinHits* geantHit, const JPetParamBank& paramBank);

  static JPetMCRecoHit reconstructHit(JPetRawMCHit& hit, const double timeShift, JPetHitExperimentalParametrizer& parametrizer);

  static bool isHitReconstructed(JPetMCRecoHit& hit, const double th);

  static void identifyRecoHits(JPetGeantScinHits* geantHit, const JPetMCRecoHit& recoHit, bool isRecPrompt, std::array<bool, 2>& isSaved2g,
                               std::array<bool, 3>& isSaved3g, double& enePrompt, std::array<double, 2>& ene2g, std::array<double, 3>& ene3g);
  static double estimateNextDecayTimeExp(double activityMBq);
  static std::tuple<std::vector<double>, std::vector<double>> getTimeDistoOfDecays(double activityMBq, double timeWindowMin, double timeWindowMax);
  static std::pair<double, double> calculateEfficiency(ulong, ulong);
  static void setSeedTogRandom(unsigned long seed);
};

#endif /* !JPETGEANTPARSERTOOLS_H */

/**
 *  @copyright Copyright 2022 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetGeantParserTools.cpp
 */

#include "JPetSmearingFunctions/JPetSmearingFunctions.h"
#include "JPetGeantParser/JPetGeantParserTools.h"

#include <TMath.h>

JPetMCHit JPetGeantParserTools::createJPetMCHit(JPetGeantScinHits* geantHit, const JPetParamBank& paramBank)
{
  JPetMCHit mcHit = JPetMCHit(0,          // UInt_t MCDecayTreeIndex,
                              geantHit->GetEvtID(),    // UInt_t MCVtxIndex,
                              geantHit->GetEneDepos(), //  keV
                              geantHit->GetTime(),     //  ps
                              geantHit->GetHitPosition(), geantHit->GetPolarizationIn(), geantHit->GetMomentumIn());

  JPetScin& scin = paramBank.getScintillator(geantHit->GetScinID());
  mcHit.setScintillator(scin);
  mcHit.setBarrelSlot(scin.getBarrelSlot());
  mcHit.setGenGammaMultiplicity(geantHit->GetGenGammaMultiplicity());
  return mcHit;
}

JPetHit JPetGeantParserTools::reconstructHit(JPetMCHit& mcHit, const JPetParamBank& paramBank, const float timeShift,
                                             JPetHitExperimentalParametrizer& parametrizer)
{
  JPetHit hit = dynamic_cast<JPetHit&>(mcHit);
  /// Nonsmeared values
  auto scinID = mcHit.getScintillator().getID();
  auto posZ = mcHit.getPosZ();
  auto energy = mcHit.getEnergy();
  auto time = mcHit.getTime() + timeShift;

  hit.setEnergy(parametrizer.addEnergySmearing(scinID, posZ, energy, time));
  // adjust to time window and smear
  hit.setTime(parametrizer.addTimeSmearing(scinID, posZ, energy, time));
  auto radius = paramBank.getScintillator(scinID).getBarrelSlot().getLayer().getRadius();
  auto theta = TMath::DegToRad() * paramBank.getScintillator(mcHit.getScintillator().getID()).getBarrelSlot().getTheta();
  hit.setPosX(radius * std::cos(theta));
  hit.setPosY(radius * std::sin(theta));
  hit.setPosZ(parametrizer.addZHitSmearing(scinID, posZ, energy, time));

  return hit;
}

bool JPetGeantParserTools::isHitReconstructed(JPetHit& hit, const float th) { return hit.getEnergy() >= th; }

void JPetGeantParserTools::identifyRecoHits(JPetGeantScinHits* geantHit, const JPetHit& recHit, bool& isRecPrompt, std::array<bool, 2>& isSaved2g,
                                            std::array<bool, 3>& isSaved3g, float& enePrompt, std::array<float, 2>& ene2g,
                                            std::array<float, 3>& ene3g)
{

  // identify generated hits
  if (geantHit->GetGenGammaMultiplicity() == 1)
  {
    isRecPrompt = true;
    enePrompt = recHit.getEnergy();
  }

  if (geantHit->GetGenGammaMultiplicity() == 2)
  {
    isSaved2g[geantHit->GetGenGammaIndex() - 1] = true;
    ene2g[geantHit->GetGenGammaIndex() - 1] = recHit.getEnergy();
  }

  if (geantHit->GetGenGammaMultiplicity() == 3)
  {
    isSaved3g[geantHit->GetGenGammaIndex() - 1] = true;
    ene3g[geantHit->GetGenGammaIndex() - 1] = recHit.getEnergy();
  }
}

float JPetGeantParserTools::estimateNextDecayTimeExp(float activityMBq) { return gRandom->Exp((pow(10, 6) / activityMBq)); }

std::tuple<std::vector<float>, std::vector<float>> JPetGeantParserTools::getTimeDistoOfDecays(float activityMBq, float timeWindowMin,
                                                                                              float timeWindowMax)
{
  std::vector<float> fTimeDistroOfDecays;
  std::vector<float> fTimeDiffOfDecays;

  float timeShift = estimateNextDecayTimeExp(activityMBq);
  float nextTime = timeWindowMin + timeShift;

  // checking if the draw time is not outside the timewindow -> Fix to the low activity issue
  if (nextTime > timeWindowMax) {
    float timeWindowSize = timeWindowMax - timeWindowMin;
    nextTime = timeWindowMin + fmod(nextTime, timeWindowSize);
  }
  
  while (nextTime < timeWindowMax)
  {
    fTimeDistroOfDecays.push_back(nextTime);
    fTimeDiffOfDecays.push_back(timeShift);
    timeShift = estimateNextDecayTimeExp(activityMBq);
    nextTime = nextTime + timeShift;
  }
  return std::make_tuple(fTimeDistroOfDecays, fTimeDiffOfDecays);
}

std::pair<float, float> JPetGeantParserTools::calculateEfficiency(ulong n, ulong k)
{
  if (n != 0)
  {
    float effi = float(k) / float(n);
    float err_effi = sqrt(float(k) * (1. - effi)) / float(n);
    return std::make_pair(effi, err_effi);
  }
  else
  {
    return std::make_pair(0, 0);
  }
}

void JPetGeantParserTools::setSeedTogRandom(unsigned long seed)
{
  if (!gRandom)
  {
    ERROR("gRandom is not set and we cannot set the seed");
  }
  else
  {
    gRandom->SetSeed(seed);
  }
}

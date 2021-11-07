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
 *  @file JPetGeantParserTools.cpp
 */

#include "JPetGeantParser/JPetGeantParserTools.h"
#include "JPetSmearingFunctions/JPetSmearingFunctions.h"
#include <TMath.h>

using namespace std;

JPetRawMCHit JPetGeantParserTools::createJPetRawMCHit(JPetGeantScinHits* geantHit, const JPetParamBank& paramBank)
{
  JPetRawMCHit mcHit;
  mcHit.setMCDecayTreeIndex(0);
  mcHit.setMCVtxIndex(geantHit->GetEvtID());
  mcHit.setTime(geantHit->GetTime());
  mcHit.setEnergy(geantHit->GetEneDepos());
  mcHit.setPos(geantHit->GetHitPosition());
  mcHit.setPolarization(geantHit->GetPolarizationIn());
  mcHit.setMomentum(geantHit->GetMomentumIn());
  mcHit.setGammaTag(geantHit->GetGenGammaMultiplicity());
  mcHit.setScin(paramBank.getScin(geantHit->GetScinID()));
  return mcHit;
}

JPetMCRecoHit JPetGeantParserTools::reconstructHit(JPetRawMCHit& mcHit, const double timeShift, JPetHitExperimentalParametrizer& parametrizer)
{
  auto time = mcHit.getTime() + timeShift;

  JPetMCRecoHit recoHit;
  recoHit.setRecoFlag(JPetRecoHit::MC);
  recoHit.setPosX(mcHit.getScin().getCenterX());
  recoHit.setPosY(mcHit.getScin().getCenterY());
  recoHit.setPosZ(parametrizer.addZHitSmearing(mcHit.getScin().getID(), mcHit.getPosZ(), mcHit.getEnergy(), time));
  recoHit.setTime(parametrizer.addTimeSmearing(mcHit.getScin().getID(), mcHit.getPosZ(), mcHit.getEnergy(), time));
  recoHit.setEnergy(parametrizer.addEnergySmearing(mcHit.getScin().getID(), mcHit.getPosZ(), mcHit.getEnergy(), time));
  return recoHit;
}

bool JPetGeantParserTools::isHitReconstructed(JPetMCRecoHit& recoHit, const double energyThreshold) { return recoHit.getEnergy() >= energyThreshold; }

void JPetGeantParserTools::identifyRecoHits(JPetGeantScinHits* geantHit, const JPetMCRecoHit& recoHit, bool& isRecPrompt, array<bool, 2>& isSaved2g,
                                            array<bool, 3>& isSaved3g, double& enePrompt, array<double, 2>& ene2g, array<double, 3>& ene3g)
{
  if (geantHit->GetGenGammaMultiplicity() == 1)
  {
    isRecPrompt = true;
    enePrompt = recoHit.getEnergy();
  }

  if (geantHit->GetGenGammaMultiplicity() == 2)
  {
    isSaved2g[geantHit->GetGenGammaIndex() - 1] = true;
    ene2g[geantHit->GetGenGammaIndex() - 1] = recoHit.getEnergy();
  }

  if (geantHit->GetGenGammaMultiplicity() == 3)
  {
    isSaved3g[geantHit->GetGenGammaIndex() - 1] = true;
    ene3g[geantHit->GetGenGammaIndex() - 1] = recoHit.getEnergy();
  }
}

double JPetGeantParserTools::estimateNextDecayTimeExp(double activityMBq) { return gRandom->Exp((pow(10, 6) / activityMBq)); }

tuple<vector<double>, vector<double>> JPetGeantParserTools::getTimeDistoOfDecays(double activityMBq, double timeWindowMin, double timeWindowMax)
{
  vector<double> fTimeDistroOfDecays;
  vector<double> fTimeDiffOfDecays;

  double timeShift = estimateNextDecayTimeExp(activityMBq);
  double nextTime = timeWindowMin + timeShift;

  while (nextTime < timeWindowMax)
  {
    fTimeDistroOfDecays.push_back(nextTime);
    fTimeDiffOfDecays.push_back(timeShift);
    timeShift = estimateNextDecayTimeExp(activityMBq);
    nextTime = nextTime + timeShift;
  }
  return make_tuple(fTimeDistroOfDecays, fTimeDiffOfDecays);
}

pair<double, double> JPetGeantParserTools::calculateEfficiency(ulong n, ulong k)
{
  if (n != 0)
  {
    double effi = double(k) / double(n);
    double err_effi = sqrt(double(k) * (1. - effi)) / double(n);
    return make_pair(effi, err_effi);
  }
  else
  {
    return make_pair(0, 0);
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

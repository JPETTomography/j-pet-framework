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
 *  @file JPetGeantParserTools.cpp
 */

#include <JPetGeantParser/JPetGeantParserTools.h>
#include <TMath.h>

const float JPetGeantParserTools::kEnergyThreshold = 200.;
const float JPetGeantParserTools::kReferenceEnergy = 270.;
const float JPetGeantParserTools::kTimeResolutionConstant = 80.;

TRandom3 JPetGeantParserTools::fRandomGenerator = TRandom3();

/**
 * @brief Set the seed of a single pseudorandom number generator used for smearing of generated values in JPetGeantParserTools methods
 *
 * This method can be optionally used to have the pseudorandom number generator
 * start with a particular seed. If this method is not used, the generator will
 * be initialized with seed=4357, see:
 * https://root.cern.ch/doc/master/classTRandom3.html
 *
 */
void JPetGeantParserTools::setGeneratorSeed(unsigned long seed)
{
  fRandomGenerator.SetSeed(seed);
}

JPetMCHit JPetGeantParserTools::createJPetMCHit(JPetGeantScinHits* geantHit, const JPetParamBank& paramBank  )
{
  JPetMCHit mcHit = JPetMCHit(
                      0,//UInt_t MCDecayTreeIndex,
                      0,//UInt_t MCVtxIndex,
                      geantHit->GetEneDepos(), //  keV
                      geantHit->GetTime(),   //  ps
                      geantHit->GetHitPosition(),
                      geantHit->GetPolarizationIn(),
                      geantHit->GetMomentumIn()
                    );

  JPetScin& scin =  paramBank.getScintillator(geantHit->GetScinID());
  mcHit.setScintillator(scin);
  mcHit.setBarrelSlot(scin.getBarrelSlot());
  return mcHit;
}

JPetHit JPetGeantParserTools::reconstructHit(JPetMCHit& mcHit, const JPetParamBank& paramBank, const float timeShift, const float z_resolution )
{
  JPetHit hit = dynamic_cast<JPetHit&>(mcHit);
  hit.setEnergy( addEnergySmearing(mcHit.getEnergy()) );
  // adjust to time window and smear
  hit.setTime( addTimeSmearing( -(mcHit.getTime() - timeShift), mcHit.getEnergy()) );

  auto radius = paramBank.getScintillator(mcHit.getScintillator().getID()).getBarrelSlot().getLayer().getRadius();
  auto theta = TMath::DegToRad() * paramBank.getScintillator(mcHit.getScintillator().getID()).getBarrelSlot().getTheta();
  hit.setPosX(radius * std::cos(theta));
  hit.setPosY(radius * std::sin(theta));
  hit.setPosZ( addZHitSmearing(hit.getPosZ(), z_resolution) );

  return hit;
}

float JPetGeantParserTools::addZHitSmearing(float zIn, float z_res)
{
  return fRandomGenerator.Gaus(zIn, z_res);
}

float JPetGeantParserTools::addEnergySmearing(float eneIn)
{
  // eneIn in keV
  float alpha = 0.044 / sqrt(eneIn / 1000.);
  return eneIn + alpha * eneIn * fRandomGenerator.Gaus(0., 1.);
}

float JPetGeantParserTools::addTimeSmearing(float timeIn, float eneIn)
{
  // eneIn in keV, timeIn in ps
  float time;

  if ( eneIn > kEnergyThreshold ) {
    time = timeIn + kTimeResolutionConstant * fRandomGenerator.Gaus(0., 1.);
  } else {
    time = timeIn + kTimeResolutionConstant * fRandomGenerator.Gaus(0., 1.) / sqrt(eneIn / kReferenceEnergy);
  }

  return time;
}

bool JPetGeantParserTools::isHitReconstructed(JPetHit& hit, const float th)
{
  return hit.getEnergy() >= th;
}

void JPetGeantParserTools::identifyRecoHits(JPetGeantScinHits* geantHit, const JPetHit& recHit,
    bool& isRecPrompt, std::array<bool, 2>& isSaved2g, std::array<bool, 3>& isSaved3g,
    float& enePrompt, std::array<float, 2>& ene2g, std::array<float, 3>& ene3g )
{

  // identify generated hits
  if ( geantHit->GetGenGammaMultiplicity() == 1) {
    isRecPrompt = true;
    enePrompt = recHit.getEnergy();
  }

  if ( geantHit->GetGenGammaMultiplicity() == 2) {
    isSaved2g[ geantHit->GetGenGammaIndex() - 1] = true;
    ene2g[ geantHit->GetGenGammaIndex() - 1] = recHit.getEnergy();
  }

  if ( geantHit->GetGenGammaMultiplicity() == 3) {
    isSaved3g[ geantHit->GetGenGammaIndex() - 1] = true;
    ene3g[ geantHit->GetGenGammaIndex() - 1] = recHit.getEnergy();
  }

}

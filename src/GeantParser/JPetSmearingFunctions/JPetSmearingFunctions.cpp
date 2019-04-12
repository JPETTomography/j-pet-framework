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
 *  @file JPetSmearingFunctions.cpp
 */

#include "JPetSmearingFunctions/JPetSmearingFunctions.h"

#include <TMath.h>

const float JPetSmearingFunctions::kEnergyThreshold = 200.;       ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5
const float JPetSmearingFunctions::kReferenceEnergy = 270.;       ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5
const float JPetSmearingFunctions::kTimeResolutionConstant = 80.; ///< see Eur. Phys. J. C (2016) 76:445  equation 3

TRandom3* JPetSmearingFunctions::fRandomGenerator = JPetRandom::GetRandomGenerator();

float JPetSmearingFunctions::addZHitSmearing(float zIn, float z_res) { return fRandomGenerator->Gaus(zIn, z_res); }

float JPetSmearingFunctions::addEnergySmearing(float eneIn)
{
  /// @param eneIn in keV
  float alpha = 0.044 / sqrt(eneIn / 1000.);
  return eneIn + alpha * eneIn * fRandomGenerator->Gaus(0., 1.);
}

float JPetSmearingFunctions::addTimeSmearing(float timeIn, float eneIn)
{
  /// @param eneIn in keV
  /// @param timeIn in ps
  float time;

  if (eneIn > kEnergyThreshold)
  {
    time = timeIn + kTimeResolutionConstant * fRandomGenerator->Gaus(0., 1.);
  }
  else
  {
    time = timeIn + kTimeResolutionConstant * fRandomGenerator->Gaus(0., 1.) / sqrt(eneIn / kReferenceEnergy);
  }

  return time;
}

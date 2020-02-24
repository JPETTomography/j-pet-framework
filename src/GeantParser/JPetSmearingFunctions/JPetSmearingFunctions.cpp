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

#include <JPetSmearingFunctions/JPetSmearingFunctions.h>
#define _USE_MATH_DEFINES
#include <math.h>

JPetHitExperimentalParametrizer::JPetHitExperimentalParametrizer()
{

  auto timeSmearingF = [&](double* x, double* p) -> double {
    // p[0] = scinID
    // p[1] = zIn
    // p[2] = eneIn
    // p[3] = timeIn
    const double kEnergyThreshold = 200.;       ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5
    const double kReferenceEnergy = 270.;       ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5
    const double kTimeResolutionConstant = 80.; ///< see Eur. Phys. J. C (2016) 76:445  equation 3

    double eneIn = p[2];
    double timeIn = p[3];
    double sigma = kTimeResolutionConstant;
    if (eneIn < kEnergyThreshold)
    {
      sigma = sigma / sqrt(eneIn / kReferenceEnergy);
    }
    return exp(-0.5 * pow((x[0] - timeIn) / sigma, 2)) / (sqrt(2 * M_PI) * sigma);
  };

  fSmearingFunctions[kTime] = TF1("funTimeHitSmearing", timeSmearingF, -200., 200., 4);

  auto energySmearingF = [&](double* x, double* p) -> double {
    // p[0] = scinID
    // p[1] = zIn
    // p[2] = eneIn
    double eneIn = p[2];
    double sigma = eneIn * 0.044 / sqrt(eneIn / 1000.);

    return exp(-0.5 * pow((x[0] - eneIn) / sigma, 2)) / (sqrt(2 * M_PI) * sigma);
  };

  fSmearingFunctions[kEnergy] = TF1("funEnergySmearing", energySmearingF, -200., 200., 3);

  auto zPositionSmearingF = [&](double* x, double* p) -> double {
    // p[0] = scinID
    // p[1] = zIn
    // p[2] = eneIn
    double zIn = p[1];
    double sigma = 0.976;

    return exp(-0.5 * pow((x[0] - zIn) / sigma, 2)) / (sqrt(2 * M_PI) * sigma);
  };
  fSmearingFunctions[kZPosition] = TF1("funZHitSmearing", zPositionSmearingF, -200., 200., 3);
}

void JPetHitExperimentalParametrizer::setSmearingFunctions(const std::vector<FuncAndParam>& params)
{
  assert(params.size() >= 3);
  auto timeParams = params[0];
  auto energyParams = params[1];
  auto zPositionParams = params[2];
}

double JPetHitExperimentalParametrizer::addZHitSmearing(int scinID, double zIn, double eneIn)
{
  fSmearingFunctions[kZPosition].SetParameters(double(scinID), zIn, eneIn);
  fSmearingFunctions[kZPosition].SetRange(zIn - 5., zIn + 5.);
  return fSmearingFunctions[kZPosition].GetRandom();
}

double JPetHitExperimentalParametrizer::addEnergySmearing(int scinID, double zIn, double eneIn)
{
  fSmearingFunctions[kEnergy].SetParameters(double(scinID), zIn, eneIn);
  fSmearingFunctions[kEnergy].SetRange(eneIn - 100., eneIn + 100.);
  return fSmearingFunctions[kEnergy].GetRandom();
}

double JPetHitExperimentalParametrizer::addTimeSmearing(int scinID, double zIn, double eneIn, double timeIn)
{
  fSmearingFunctions[kTime].SetParameters(double(scinID), zIn, eneIn, timeIn);
  fSmearingFunctions[kTime].SetRange(timeIn - 300., timeIn + 300.);
  return fSmearingFunctions[kTime].GetRandom();
}

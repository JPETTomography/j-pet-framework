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

#include "JPetLoggerInclude.h"
#include <JPetSmearingFunctions/JPetSmearingFunctions.h>

#include <TMath.h>

using SmearingType = JPetHitExperimentalParametrizer::SmearingType;
using SmearingFunctionLimits = JPetHitExperimentalParametrizer::SmearingFunctionLimits;

JPetHitExperimentalParametrizer::JPetHitExperimentalParametrizer()
{

  auto timeSmearingF = [&](double* x, double* p) -> double {
    // p[0] = scinID
    // p[1] = zIn
    // p[2] = eneIn
    // p[3] = timeIn

    // p[4] = timeResolution (sigma)
    // p[5] = energyThreshold
    // p[6] = referenceEnergy

    double eneIn = p[2];
    double timeIn = p[3];
    double sigma = p[4];
    double energyTreshold = p[5];
    double referenceEnergy = p[6];
    double time = x[0];

    if (eneIn < energyTreshold)
    {
      sigma = sigma / sqrt(eneIn / referenceEnergy);
    }

    return TMath::Gaus(time, timeIn, sigma, true);
  };

  const double kTimeResolutionConstant = 80.; ///< see Eur. Phys. J. C (2016) 76:445  equation 3
  const double kEnergyThreshold = 200.;       ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5
  const double kReferenceEnergy = 270.;       ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5
  fSmearingFunctions.emplace(kTime, std::make_unique<TF1>("funTimeHitSmearing", timeSmearingF, -200., 200., 7));
  fSmearingFunctions[kTime]->SetParameter(4, kTimeResolutionConstant);
  fSmearingFunctions[kTime]->SetParameter(5, kEnergyThreshold);
  fSmearingFunctions[kTime]->SetParameter(6, kReferenceEnergy);

  auto energySmearingF = [&](double* x, double* p) -> double {
    // p[0] = scinID
    // p[1] = zIn
    // p[2] = eneIn
    double eneIn = p[2];
    double sigma = eneIn * 0.044 / sqrt(eneIn / 1000.);
    double energy = x[0];

    return TMath::Gaus(energy, eneIn, sigma, true);
  };

  fSmearingFunctions.emplace(kEnergy, std::make_unique<TF1>("funEnergySmearing", energySmearingF, -200., 200., 3));

  auto zPositionSmearingF = [&](double* x, double* p) -> double {
    // p[0] = scinID
    // p[1] = zIn
    // p[2] = eneIn
    // p[3] = zResolution (sigma)
    double zIn = p[1];
    double sigma = p[3];
    double z = x[0];

    return TMath::Gaus(z, zIn, sigma, true);
  };

  fSmearingFunctions.emplace(kZPosition, std::make_unique<TF1>("funZHitSmearing", zPositionSmearingF, -200., 200., 4));
  double kZresolution = 0.976;
  fSmearingFunctions[kZPosition]->SetParameter(3, kZresolution);
}

void JPetHitExperimentalParametrizer::setSmearingFunctions(const std::vector<FuncAndParam>& params)
{
  assert(params.size() >= 3);
  auto timeFuncAndParams = params[0];
  auto energyFuncAndParams = params[1];
  auto zPositionFuncAndParams = params[2];

  auto timeFunc = timeFuncAndParams.first;
  auto timeParams = timeFuncAndParams.second;
  int nDefaultParams = 4;
  int nCustomParams = timeParams.size();
  int nTotalParams = nCustomParams + nDefaultParams;
  if (!timeFunc.empty())
  {
    fSmearingFunctions[kTime] = std::make_unique<TF1>("funTimeHitSmearing", timeFunc.c_str(), -200., 200., nTotalParams);
  }
  for (int i = 0; i < nCustomParams; i++)
  {
    fSmearingFunctions[kTime]->SetParameter(nDefaultParams + i, timeParams[i]);
  }

  auto energyFunc = energyFuncAndParams.first;
  auto energyParams = energyFuncAndParams.second;
  nDefaultParams = 3;
  nCustomParams = energyParams.size();
  nTotalParams = nCustomParams + nDefaultParams;
  if (!energyFunc.empty())
  {
    fSmearingFunctions[kEnergy] = std::make_unique<TF1>("funEnergySmearing", energyFunc.c_str(), -200., 200., nTotalParams);
  }
  for (int i = 0; i < nCustomParams; i++)
  {
    fSmearingFunctions[kEnergy]->SetParameter(nDefaultParams + i, energyParams[i]);
  }

  auto zPositionFunc = zPositionFuncAndParams.first;
  auto zPositionParams = zPositionFuncAndParams.second;
  nDefaultParams = 3;
  nCustomParams = zPositionParams.size();
  nTotalParams = nCustomParams + nDefaultParams;
  if (!zPositionFunc.empty())
  {
    fSmearingFunctions[kZPosition] = std::make_unique<TF1>("funzHitSmearing", zPositionFunc.c_str(), -200., 200., nTotalParams);
  }
  for (int i = 0; i < nCustomParams; i++)
  {
    fSmearingFunctions[kZPosition]->SetParameter(nDefaultParams + i, zPositionParams[i]);
  }
}

/// Only those limits are modified for which first value is smaller than the second one.
/// The limits vector is suppose to have 3 elements in the order time, energy and z Position.
void JPetHitExperimentalParametrizer::setSmearingFunctionLimits(const std::vector<std::pair<double, double>>& limits)
{
  assert(limits.size() == 3);
  auto timeLim = limits[0];
  auto energyLim = limits[1];
  ;
  auto zPositionLim = limits[2];
  if (timeLim.first < timeLim.second)
  {
    fFunctionLimits[kTime] = timeLim;
  }
  if (energyLim.first < energyLim.second)
  {
    fFunctionLimits[kEnergy] = energyLim;
  }
  if (zPositionLim.first < zPositionLim.second)
  {
    fFunctionLimits[kZPosition] = zPositionLim;
  }
}

void JPetHitExperimentalParametrizer::writeAllParametersToLog() const
{
  auto limits = getSmearingFunctionLimits();

  std::vector<SmearingType> types{kTime, kEnergy, kZPosition};
  for (auto type : types)
  {
    INFO(fSmearingFunctions.at(type)->GetName());
    INFO(std::string("limits: low = ") + limits[type].first + " , high = " + limits[type].second);
    auto nPar = fSmearingFunctions.at(type)->GetNpar();
    INFO(std::string("number of parameters:") + std::to_string(nPar));
    for (int i = 0; i < nPar; i++)
    {
      INFO(std::string("parameter ") + std::to_string(i) + " = " + std::to_string(fSmearingFunctions.at(type)->GetParameter(i)));
    }
  }
}

void JPetHitExperimentalParametrizer::printAllParameters() const
{
  auto limits = getSmearingFunctionLimits();

  std::cout << "***************" << std::endl;
  std::cout << "Time smearing function" << std::endl;
  std::cout << fSmearingFunctions.at(kTime)->GetName() << std::endl;
  std::cout << "limits: low = " << limits[kTime].first << " , high = " << limits[kTime].second << std::endl;
  auto nPar = fSmearingFunctions.at(kTime)->GetNpar();
  std::cout << "number of parameters:" << nPar << std::endl;
  for (int i = 0; i < nPar; i++)
  {
    std::cout << "parameter " << i << " = " << fSmearingFunctions.at(kTime)->GetParameter(i) << std::endl;
  }

  std::cout << "***************" << std::endl;
  std::cout << "Energy smearing function" << std::endl;
  std::cout << fSmearingFunctions.at(kEnergy)->GetName() << std::endl;
  std::cout << "limits: low = " << limits[kEnergy].first << " , high = " << limits[kEnergy].second << std::endl;
  nPar = fSmearingFunctions.at(kEnergy)->GetNpar();
  for (int i = 0; i < nPar; i++)
  {
    std::cout << "parameter " << i << " = " << fSmearingFunctions.at(kEnergy)->GetParameter(i) << std::endl;
  }
  std::cout << "***************" << std::endl;
  std::cout << fSmearingFunctions.at(kZPosition)->GetName() << std::endl;
  std::cout << "Z position smearing function" << std::endl;
  std::cout << "limits: low = " << limits[kZPosition].first << " , high = " << limits[kZPosition].second << std::endl;
  nPar = fSmearingFunctions.at(kZPosition)->GetNpar();
  for (int i = 0; i < nPar; i++)
  {
    std::cout << "parameter " << i << " = " << fSmearingFunctions.at(kZPosition)->GetParameter(i) << std::endl;
  }
}

std::map<SmearingType, SmearingFunctionLimits> JPetHitExperimentalParametrizer::getSmearingFunctionLimits() const 
{ 
  return fFunctionLimits; 
}

/// function is randomize in the range [lowLim + timeIn, highLim + timeIn]
double JPetHitExperimentalParametrizer::addTimeSmearing(int scinID, double zIn, double eneIn, double timeIn)
{
  /// We cannot use setParameters(...) cause if there are more then 4 parameters
  /// It would set it all to 0.
  fSmearingFunctions[kTime]->SetParameter(0, double(scinID));
  fSmearingFunctions[kTime]->SetParameter(1, zIn);
  fSmearingFunctions[kTime]->SetParameter(2, eneIn);
  fSmearingFunctions[kTime]->SetParameter(3, timeIn);
  fSmearingFunctions[kTime]->SetRange(timeIn + fFunctionLimits[kTime].first, timeIn + fFunctionLimits[kTime].second);
  return fSmearingFunctions[kTime]->GetRandom();
}

/// function is randomize in the range [lowLim + eneIn, highLim + eneIn]
double JPetHitExperimentalParametrizer::addEnergySmearing(int scinID, double zIn, double eneIn)
{
  fSmearingFunctions[kEnergy]->SetParameter(0, double(scinID));
  fSmearingFunctions[kEnergy]->SetParameter(1, zIn);
  fSmearingFunctions[kEnergy]->SetParameter(2, eneIn);
  fSmearingFunctions[kEnergy]->SetRange(eneIn + fFunctionLimits[kEnergy].first, eneIn + fFunctionLimits[kEnergy].second);
  return fSmearingFunctions[kEnergy]->GetRandom();
}

/// function is randomize in the range [lowLim + zIn, highLim + zIn]
double JPetHitExperimentalParametrizer::addZHitSmearing(int scinID, double zIn, double eneIn)
{
  /// We cannot use setParameters(...) cause if there are more then 4 parameters
  /// It would set it all to 0.
  fSmearingFunctions[kZPosition]->SetParameter(0, double(scinID));
  fSmearingFunctions[kZPosition]->SetParameter(1, zIn);
  fSmearingFunctions[kZPosition]->SetParameter(2, eneIn);
  fSmearingFunctions[kZPosition]->SetRange(zIn + fFunctionLimits[kZPosition].first, zIn + fFunctionLimits[kZPosition].second);
  return fSmearingFunctions[kZPosition]->GetRandom();
}

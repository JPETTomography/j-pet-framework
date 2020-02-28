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
 *  @file JPetSmearingFunctions.h
 */

#ifndef JPETSMEARINGFUNCTIONS_H
#define JPETSMEARINGFUNCTIONS_H

#include <TF1.h>

using SmearingFunctionLimits = std::pair<double, double>;

/**
 * @brief Helper class to store and handle functions to smear Hit properties from MC simulations.
 *
 * Class API consists of three methods addEnergySmearing(), addZHitSmearing(), addTimeSmearing()
 * ,which can be used to apply on MC hits the parametrizations of experimental uncertanities of 
 * energy,position along the z strip and time. There are three default parameterization functions 
 * that can be used from the beginnng. In addition, it is possible to redefine the parametrization
 * functions using the setSmearingFunctions() and their limits. The limit corresponds to the range
 * for  which the smearing function will be used (effectively it is the range of pdf integral over
 * which the smearing is done).
 * e.g. for gaussian smearing with parameters (mean, sigma)  the limit [low,up] would correspond to  
 * randomizing in the range [low + mean, high +mean].
 */
class JPetHitExperimentalParametrizer
{
  using FuncAndParam = std::pair<std::string, std::vector<double>>;

public:
  enum SmearingType
  {
    kTime,
    kEnergy,
    kZPosition
  };

  JPetHitExperimentalParametrizer();
  JPetHitExperimentalParametrizer(JPetHitExperimentalParametrizer const&) = delete;
  JPetHitExperimentalParametrizer& operator=(JPetHitExperimentalParametrizer const&) = delete;

  /// The limit is callculated with respect to the mean value
  /// e.g. [mean + low , mean + up]
  double addTimeSmearing(int scinID, double zIn, double eneIn, double timeIn);
  double addEnergySmearing(int scinID, double zIn, double eneIn);
  double addZHitSmearing(int scinID, double zIn, double eneIn);

  std::map<SmearingType, SmearingFunctionLimits> getSmearingFunctionLimits() const;

  /// If any of the arguments in params is empty, then the previous value is preserved. 
  /// e.g.
  /// std::string zSmearing = "[&](double* x, double* p)->double{ return TMath::Landau(x[0],p[1],p[3], false);};";
  /// parametrizer.setSmearingFunctions({{"", {}}, {"", {}}, {zSmearing, {sigma}}});
  /// The functions for time and energy smearing will not be changed. The zSmearing will be used
  /// and the sigma parameter will be applied.
  /// Please note that since we have 3 default paramteres: scinId, zIn, eneIn, the sigma is assigned to the 
  /// fourth one p[3].
  void setSmearingFunctions(const std::vector<FuncAndParam>& params);
 
  /// If the higher limit is equal or smaller than lower one, then it is ignored
  /// and old values will be preserved.
  /// e.g.  parametrizer.setSmearingFunctionLimits({{0, 0}, {0, 0}, {-4, 4}});
  /// The limits for time and energy functions will not be changed, since low == high.
  /// The limits for the zSmearing function will be changed.

  void setSmearingFunctionLimits(const std::vector<std::pair<double, double>>& limits);

private:
  std::map<SmearingType, TF1> fSmearingFunctions;
  std::map<SmearingType, SmearingFunctionLimits> fFunctionLimits{{kTime, {-300, 300}}, {kEnergy, {-100, 100}}, {kZPosition, {-5, 5}}};
};

#endif

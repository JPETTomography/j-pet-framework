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

/// The limit is callculated with respect to the mean value
/// e.g. [mean + low , mean + up]
using SmearingFunctionLimits = std::pair<double, double>;

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

  double addEnergySmearing(int scinID, double zIn, double eneIn);
  double addZHitSmearing(int scinID, double zIn, double eneIn);
  double addTimeSmearing(int scinID, double zIn, double eneIn, double timeIn);

  std::map<SmearingType, SmearingFunctionLimits> getSmearingFunctionLimits() const;
  void setSmearingFunctions(const std::vector<FuncAndParam>& params);
  void setSmearingFunctionLimits(const std::vector<std::pair<double, double>>& limits);

private:
  std::map<SmearingType, TF1> fSmearingFunctions;
  std::map<SmearingType, SmearingFunctionLimits> fFunctionLimits{{kTime, {-300, 300}}, {kEnergy, {-100, 100}}, {kZPosition, {-5, 5}}};
};

#endif

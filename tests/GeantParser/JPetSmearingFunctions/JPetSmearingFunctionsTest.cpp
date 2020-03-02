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
 *  @file JPetSmearingFunctionsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSmearingFunctionsTest
#include <boost/test/unit_test.hpp>

#include "JPetSmearingFunctions/JPetSmearingFunctions.h"

#include <TFile.h>
#include <TH1F.h>

using SmearingType = JPetHitExperimentalParametrizer::SmearingType;

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(testDefaultLimits)
{
  double epsilon = 0.001;
  JPetHitExperimentalParametrizer parametrizer;
  auto limits = parametrizer.getSmearingFunctionLimits();
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].first, -300, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].second, 300, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].first, -100, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].second, 100, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].first, -5, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].second, 5, epsilon);
}

BOOST_AUTO_TEST_CASE(testCustomLimits)
{
  double epsilon = 0.001;
  JPetHitExperimentalParametrizer parametrizer;
  parametrizer.setSmearingFunctionLimits({{-1, 1}, {-2, 2}, {-3, 3}});
  auto limits = parametrizer.getSmearingFunctionLimits();
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].first, -1, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].second, 1, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].first, -2, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].second, 2, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].first, -3, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].second, 3, epsilon);
}

BOOST_AUTO_TEST_CASE(testCustomLimits2)
{
  double epsilon = 0.001;
  JPetHitExperimentalParametrizer parametrizer;
  /// The second argument has the same upper and lower limit.
  ///  and so the energy smearing function should preserve original values.
  parametrizer.setSmearingFunctionLimits({{-1, 1}, {-2, -2}, {-3, 3}});
  auto limits = parametrizer.getSmearingFunctionLimits();
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].first, -1, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].second, 1, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].first, -100, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].second, 100, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].first, -3, epsilon);
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].second, 3, epsilon);
}

BOOST_AUTO_TEST_CASE(testDefaultZFunction)
{
  JPetHitExperimentalParametrizer parametrizer;
  double mean = 1;
  double sigma = 0.976; /// predefined sigma.
  TF1 refFunc("refFunc", "TMath::Gaus(x,[0],[1],1)", -4, 6);
  refFunc.SetParameter(0, mean);
  refFunc.SetParameter(1, sigma);

  const int nTrials = 10000;
  std::vector<double> vals;
  std::vector<double> valsRef;
  vals.reserve(nTrials);
  valsRef.reserve(nTrials);
  for (int i = 0; i < nTrials; i++)
  {
    vals.push_back(parametrizer.addZHitSmearing(0, mean, 0));
    valsRef.push_back(refFunc.GetRandom());
  }
  std::sort(vals.begin(), vals.end());
  std::sort(valsRef.begin(), valsRef.end());
  auto prob = TMath::KolmogorovTest(vals.size(), &vals[0], valsRef.size(), &valsRef[0], "");
  double alpha = 0.05;
  BOOST_REQUIRE(prob > alpha);
}

BOOST_AUTO_TEST_CASE(testDefaultZFunctionWithCustomSigma)
{
  JPetHitExperimentalParametrizer parametrizer;
  double mean = 1;
  double sigma = 3;

  TF1 refFunc("refFunc2", "TMath::Gaus(x,[0],[1],1)", -4, 6);
  refFunc.SetParameter(0, mean);
  refFunc.SetParameter(1, sigma);

  parametrizer.setSmearingFunctions({{"", {}}, {"", {}}, {"", {sigma}}});

  const int nTrials = 10000;
  std::vector<double> vals;
  std::vector<double> valsRef;
  vals.reserve(nTrials);
  valsRef.reserve(nTrials);
  for (int i = 0; i < nTrials; i++)
  {
    vals.push_back(parametrizer.addZHitSmearing(0, mean, 0));
    valsRef.push_back(refFunc.GetRandom());
  }
  std::sort(vals.begin(), vals.end());
  std::sort(valsRef.begin(), valsRef.end());
  auto prob = TMath::KolmogorovTest(vals.size(), &vals[0], valsRef.size(), &valsRef[0], "");
  double alpha = 0.05;
  BOOST_REQUIRE(prob > alpha);
}

BOOST_AUTO_TEST_CASE(testCustomZFunction)
{
  JPetHitExperimentalParametrizer parametrizer;

  /// default params are [0] scinId, [1] zIn, [2] eneIn
  /// we add here p[3] sigma of Landau
  std::string zSmearing = "[&](double* x, double* p)->double{ return TMath::Landau(x[0],p[1],p[3], 0);};";

  double mpv = 0; /// most probable value of Landau ~~ "mean"
  double sigma = 2;
  /// we pass only the additional parameters
  parametrizer.setSmearingFunctions({{"", {}}, {"", {}}, {zSmearing, {sigma}}});
  parametrizer.setSmearingFunctionLimits({{0, 0}, {0, 0}, {-4, 4}});

  TF1 refFunc("refFunc3", "TMath::Landau(x,[0],[1],0)", -4, 4);
  refFunc.SetParameter(0, mpv);
  refFunc.SetParameter(1, sigma);

  const int nTrials = 100000;
  std::vector<double> vals;
  std::vector<double> valsRef;
  vals.reserve(nTrials);
  valsRef.reserve(nTrials);
  for (int i = 0; i < nTrials; i++)
  {
    double res = parametrizer.addZHitSmearing(0, mpv, 0);
    double res2 = refFunc.GetRandom();
    vals.push_back(res);
    valsRef.push_back(res2);
  }
  std::sort(vals.begin(), vals.end());
  std::sort(valsRef.begin(), valsRef.end());
  auto prob = TMath::KolmogorovTest(vals.size(), &vals[0], valsRef.size(), &valsRef[0], "");
  double alpha = 0.05;
  BOOST_REQUIRE(prob > alpha);
}

BOOST_AUTO_TEST_SUITE_END()

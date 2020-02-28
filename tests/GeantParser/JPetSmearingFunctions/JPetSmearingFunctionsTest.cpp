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

using SmearingType = JPetHitExperimentalParametrizer::SmearingType;

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(testDefaultLimits)
{
  double epsilon = 0.001;
  JPetHitExperimentalParametrizer parametrizer;
  auto limits = parametrizer.getSmearingFunctionLimits();
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].first,-300, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].second,300, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].first,-100, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].second,100, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].first,-5, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].second,5, epsilon); 
}

BOOST_AUTO_TEST_CASE(testCustomLimits)
{
  double epsilon = 0.001;
  JPetHitExperimentalParametrizer parametrizer;
  parametrizer.setSmearingFunctionLimits({{-1,1}, {-2,2},{-3,3}});
  auto limits = parametrizer.getSmearingFunctionLimits();
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].first,-1, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].second,1, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].first,-2, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].second,2, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].first,-3, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].second,3, epsilon); 
}

BOOST_AUTO_TEST_CASE(testCustomLimits2)
{
  double epsilon = 0.001;
  JPetHitExperimentalParametrizer parametrizer;
  /// The second argument has the same upper and lower limit.
  ///  and so the energy smearing function should preserve original values.
  parametrizer.setSmearingFunctionLimits({{-1,1}, {-2,-2},{-3,3}});
  auto limits = parametrizer.getSmearingFunctionLimits();
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].first,-1, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kTime].second,1, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].first,-100, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kEnergy].second,100, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].first,-3, epsilon); 
  BOOST_REQUIRE_CLOSE(limits[SmearingType::kZPosition].second,3, epsilon); 
}

//BOOST_AUTO_TEST_CASE(testDefaultZFunction)
//{
  //JPetHitExperimentalParametrizer parametrizer;
  //TH1F hist("testHist","testHist",120,-6,6);  
  //for (int i = 0; i < 10000; i++) {
    //hist->Fill(sparametrizer.addZHitSmearing(0,1,0));
    
  //}
//}

BOOST_AUTO_TEST_CASE(testSettingFunction)
{
  JPetHitExperimentalParametrizer parametrizer;
  
  std::string timeSmearing= "[&](double* x, double* p)->double{ return 7;};";
  parametrizer.setSmearingFunctions({{timeSmearing,{}},{"",{}},{"",{}}});
  parametrizer.addTimeSmearing(1,1,1,1);
}

BOOST_AUTO_TEST_CASE(testSettingFunction2)
{
  JPetHitExperimentalParametrizer parametrizer;
  
  std::string timeSmearing= "[&](double* x, double* p)->double{ return x[0] + p[4]*x[0];};";
  parametrizer.setSmearingFunctions({{timeSmearing,{2}},{"",{}},{"",{}}});
  parametrizer.addTimeSmearing(1,1,1,1);
}

BOOST_AUTO_TEST_CASE(testSettingFunction3)
{
  JPetHitExperimentalParametrizer parametrizer;
  
  std::string timeSmearing= "[&](double* x, double* p)->double{ return TMath::Gaus(x[0],p[0],p[1]);};";
  parametrizer.setSmearingFunctions({{timeSmearing,{}},{"",{}},{"",{}}});
  parametrizer.addTimeSmearing(1,1,1,1);
}
BOOST_AUTO_TEST_SUITE_END()

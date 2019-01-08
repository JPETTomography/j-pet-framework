/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetSimplePhysSignalReco.cpp
 */

#include <boost/property_tree/json_parser.hpp>
#include "JPetSimplePhysSignalReco.h"
#include "./JPetWriter/JPetWriter.h"
#include "HelperMathFunctions.h"
#include <cassert>
#include <math.h>

using namespace boost::numeric::ublas;

JPetSimplePhysSignalReco::JPetSimplePhysSignalReco(): fAlpha(1), fThresholdSel(-1)
{
  readConfigFileAndSetAlphaAndThreshParams("configParams.json");
}

JPetSimplePhysSignalReco::~JPetSimplePhysSignalReco(){}

bool JPetSimplePhysSignalReco::exec()
{
  return true;
}

void JPetSimplePhysSignalReco::savePhysSignal(JPetPhysSignal){}

/**
 * Simple example of creating JPetPhysSignal from JPetRecoSignal
 */
JPetPhysSignal JPetSimplePhysSignalReco::createPhysSignal(JPetRecoSignal& recoSignal)
{
  JPetPhysSignal physSignal;
  physSignal.setPhe(recoSignal.getCharge() * 1.0 + 0.0);
  physSignal.setQualityOfPhe(1.0);
  double time = recoSignal.getRecoTimesAtThreshold().begin()->second;
  JPetRawSignal rawSignal = recoSignal.getRawSignal();

  if (rawSignal.getNumberOfPoints(JPetSigCh::Leading) >= 2
    && rawSignal.getNumberOfPoints(JPetSigCh::Trailing) >= 2) {
    int iNumPoints = rawSignal.getNumberOfPoints(JPetSigCh::Leading);
    std::vector<JPetSigCh> leadingPoints = rawSignal.getPoints(
      JPetSigCh::Leading, JPetRawSignal::ByThrValue);
    vector<float> vecTime(iNumPoints);
    vector<float> vecVolt(iNumPoints);
    for (int j = 0; j < iNumPoints; j++) {
      vecTime(j) = leadingPoints.at(j).getValue();
      vecVolt(j) = leadingPoints.at(j).getThreshold();
    }
    int alfa = getAlpha();
    float thr_sel = getThresholdSel();
    assert(thr_sel < 0);
    assert(alfa > 0);
    time = static_cast<double>(polynomialFit(vecTime, vecVolt, alfa, thr_sel));
  }
  physSignal.setTime(time);
  physSignal.setQualityOfTime(1.0);
  physSignal.setRecoSignal(recoSignal);
  return physSignal;
}

void JPetSimplePhysSignalReco::readConfigFileAndSetAlphaAndThreshParams(const char* filename)
{
  boost::property_tree::ptree content;
  try {
    read_json(filename, content);
    int alpha = content.get<int>("alpha");
    float thresholdSel = content.get<float>("thresholdSel");
    setAlpha(alpha);
    setThresholdSel(thresholdSel);
  } catch (const std::runtime_error& error) {
    std::string message = "Error opening config file. Error = " + std::string(error.what());
    std::cerr << message << std::endl;
  }
}

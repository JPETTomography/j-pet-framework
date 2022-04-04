/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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

#include "JPetSimplePhysSignalReco/JPetSimplePhysSignalReco.h"
#include "JPetSimplePhysSignalReco/HelperMathFunctions.h"
#include "JPetWriter/JPetWriter.h"
#include <boost/property_tree/json_parser.hpp>
#include <cassert>
#include <math.h>

using namespace boost::numeric::ublas;

JPetSimplePhysSignalReco::JPetSimplePhysSignalReco() : fAlpha(1), fThresholdSel(-1) { readConfigFileAndSetAlphaAndThreshParams("configParams.json"); }

JPetSimplePhysSignalReco::~JPetSimplePhysSignalReco() {}

bool JPetSimplePhysSignalReco::exec() { return true; }

void JPetSimplePhysSignalReco::savePhysSignal(JPetPhysSignal) {}

/**
 * Simple example of creating JPetPhysSignal from JPetPMSignal
 */
JPetPhysSignal JPetSimplePhysSignalReco::createPhysSignal(const JPetPMSignal& pmSignal)
{
  JPetPhysSignal physSignal;
  physSignal.setPhe(1.0);
  physSignal.setQualityOfPhe(1.0);

  auto points = pmSignal.getLeadTrailPairs(JPetPMSignal::ByThrValue);
  if (points.size() >= 2)
  {
    vector<double> vecTime(points.size());
    vector<double> vecVolt(points.size());
    for (unsigned int j = 0; j < points.size(); j++)
    {
      vecTime(j) = points.at(j).first.getTime();
      vecVolt(j) = points.at(j).first.getChannel().getThresholdValue();
    }
    int alfa = getAlpha();
    double thr_sel = getThresholdSel();
    assert(thr_sel < 0);
    assert(alfa > 0);
    double time = static_cast<double>(polynomialFit(vecTime, vecVolt, alfa, thr_sel));
    physSignal.setTime(time);
    physSignal.setQualityOfTime(1.0);
  }
  else
  {
    physSignal.setTime(0.0);
    physSignal.setQualityOfTime(1.0);
  }
  return physSignal;
}

void JPetSimplePhysSignalReco::readConfigFileAndSetAlphaAndThreshParams(const char* filename)
{
  boost::property_tree::ptree content;
  try
  {
    read_json(filename, content);
    int alpha = content.get<int>("alpha");
    double thresholdSel = content.get<double>("thresholdSel");
    setAlpha(alpha);
    setThresholdSel(thresholdSel);
  }
  catch (const std::runtime_error& error)
  {
    std::string message = "Error opening config file. Error = " + std::string(error.what());
    std::cerr << message << std::endl;
  }
}

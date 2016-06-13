/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetPMCalibFactory.cpp
 */

#include "JPetPMCalibFactory.h"

#include <exception>
#include <string>
#include <tuple>
#include <boost/lexical_cast.hpp>

std::map<int, JPetPMCalib *> & JPetPMCalibFactory::getPMCalibs()
{
  if (!fInitialized) {
    initialize();
  }
  return fPMCalibs;
}

void JPetPMCalibFactory::initialize()
{
  ParamObjectsDescriptions descriptions = paramGetter.getAllBasicData(ParamObjectType::kPMCalib, runId);
  if (descriptions.size() == 0) {
    ERROR(std::string("No pmCalibs in run ") + boost::lexical_cast<std::string>(runId));
  }
  for (auto description : descriptions) {
    fPMCalibs[description.first] = build(description.second);
  }
  fInitialized = true;
}

JPetPMCalib * JPetPMCalibFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    std::string name = data.at("name");
    double opthv = boost::lexical_cast<double>(data.at("opthv"));
    double c2e1 = boost::lexical_cast<double>(data.at("c2e1"));
    double c2e2 = boost::lexical_cast<double>(data.at("c2e2"));
    double gainAlpha = boost::lexical_cast<double>(data.at("gain_alpha"));
    double gainBeta = boost::lexical_cast<double>(data.at("gain_beta"));
    int assignmentId = boost::lexical_cast<int>(data.at("assignment_id"));
    int assignmentPMId = boost::lexical_cast<int>(data.at("assignment_photomultiplier_id"));
    return new JPetPMCalib(id, name, opthv, c2e1, c2e2, gainAlpha, gainBeta, assignmentId, assignmentPMId);
  } catch (const std::exception & e) {
    ERROR(std::string("Failed to build pmCalib with error: ") + e.what());
    throw;
  }
}

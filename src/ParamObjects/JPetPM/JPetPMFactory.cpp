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
 *  @file JPetPMFactory.cpp
 */

#include <boost/lexical_cast.hpp>
#include "JPetPM/JPetPMFactory.h"
#include <exception>
#include <string>

std::map<int, JPetPM*>& JPetPMFactory::getPMs()
{
  if (!fInitialized) { initialize(); }
  return fPMs;
}

void JPetPMFactory::initialize()
{
  ParamObjectsDescriptions descriptions = fParamGetter.getAllBasicData(
    ParamObjectType::kPM, fRunID
  );
  if (descriptions.size() == 0) {
    ERROR(Form("No PMs in run %i", fRunID));
    return;
  }
  for (auto description : descriptions) {
    fPMs[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = fParamGetter.getAllRelationalData(
    ParamObjectType::kPM, ParamObjectType::kScin, fRunID
  );
  for (auto relation : relations) {
    fPMs[relation.first]->setScin(*fScinFactory.getScins().at(relation.second));
  }
}

JPetPM* JPetPMFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    std::string side = boost::lexical_cast<std::string>(data.at("side"));
    std::string desc = boost::lexical_cast<std::string>(data.at("description"));
    int mtxPos = boost::lexical_cast<int>(data.at("pos_in_matrix"));
    if(side == "A"){
      return new JPetPM(id, JPetPM::SideA, desc, mtxPos);
    } else if(side == "B"){
      return new JPetPM(id, JPetPM::SideB, desc, mtxPos);
    }
  } catch (const std::exception& e) {
    ERROR(Form("Failed to build PM with error: %s", e.what()));
    throw;
  }
  return new JPetPM(true);
}

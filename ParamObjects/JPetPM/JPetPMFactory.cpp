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
 *  @file JPetPMFactory.cpp
 */

#include <boost/lexical_cast.hpp>
#include "JPetPMFactory.h"
#include <exception>
#include <string>
#include <tuple>

std::map<int, JPetPM*>& JPetPMFactory::getPMs()
{
  if (!fInitialized) { initialize(); }
  return fPMs;
}

void JPetPMFactory::initialize()
{
  ParamObjectsDescriptions descriptions = paramGetter.getAllBasicData(ParamObjectType::kPM, runId);
  if (descriptions.size() == 0) {
    ERROR(std::string("No PMs in run ") + boost::lexical_cast<std::string>(runId));
  }
  for (auto description : descriptions) {
    fPMs[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = paramGetter.getAllRelationalData(
    ParamObjectType::kPM, ParamObjectType::kFEB, runId);
  for (auto relation : relations) {
    fPMs[relation.first]->setFEB(*febFactory.getFEBs().at(relation.second));
  }
  relations = paramGetter.getAllRelationalData(ParamObjectType::kPM, ParamObjectType::kScintillator, runId);
  for (auto relation : relations) {
    fPMs[relation.first]->setScin(*scinFactory.getScins().at(relation.second));
  }
  relations = paramGetter.getAllRelationalData(ParamObjectType::kPM, ParamObjectType::kBarrelSlot, runId);
  for (auto relation : relations) {
    fPMs[relation.first]->setBarrelSlot(*barrelSlotFactory.getBarrelSlots().at(relation.second));
  }
}

JPetPM* JPetPMFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    JPetPM::Side side = boost::lexical_cast<bool>(data.at("is_right_side")) ? JPetPM::Side::SideB : JPetPM::Side::SideA;
    std::string description;
    try{
      description = boost::lexical_cast<std::string>(data.at("description"));
    } catch (const std::exception& e) {
      description = "";
    }
    JPetPM* result = new JPetPM(id, description);
    result->setSide(side);
    return result;
  } catch (const std::exception& e) {
    ERROR(std::string("Failed to build PM with error: ") + e.what());
    throw;
  }
}

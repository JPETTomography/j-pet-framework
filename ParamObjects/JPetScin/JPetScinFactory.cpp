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
 *  @file JPetScinFactory.cpp
 */

#include <boost/lexical_cast.hpp>
#include "JPetScinFactory.h"
#include <exception>
#include <string>
#include <tuple>

std::map<int, JPetScin *> & JPetScinFactory::getScins()
{
  if (!fInitialized) { initialize(); }
  return fScins;
}

void JPetScinFactory::initialize()
{
  ParamObjectsDescriptions descriptions = paramGetter.getAllBasicData(ParamObjectType::kScintillator, runId);
  if (descriptions.size() == 0) {
    ERROR(std::string("No scintillators in run ") + boost::lexical_cast<std::string>(runId));
  }
  for (auto description : descriptions) {
    fScins[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = paramGetter.getAllRelationalData(ParamObjectType::kScintillator, ParamObjectType::kBarrelSlot, runId);
  for (auto relation : relations) {
    fScins[relation.first]->setBarrelSlot(*barrelSlotFactory.getBarrelSlots().at(relation.second));
  }
}

JPetScin * JPetScinFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    double attenuationLength = boost::lexical_cast<double>(data.at("attenuation_length"));
    double length = boost::lexical_cast<double>(data.at("length"));
    double width = boost::lexical_cast<double>(data.at("width"));
    double height = boost::lexical_cast<double>(data.at("height"));
    return new JPetScin(id, attenuationLength, length, width, height);
  } catch (const std::exception & e) {
    ERROR(std::string("Failed to build scintillator with error: ") + e.what());
    throw;
  }
}

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
 *  @file JPetScinFactory.cpp
 */

#include "JPetScin/JPetScinFactory.h"
#include <boost/lexical_cast.hpp>
#include <exception>
#include <tuple>

std::map<int, JPetScin*>& JPetScinFactory::getScins()
{
  if (!fInitialized) { initialize(); }
  return fScins;
}

void JPetScinFactory::initialize()
{
  ParamObjectsDescriptions descriptions = fParamGetter.getAllBasicData(
    ParamObjectType::kScin, fRunID
  );
  if (descriptions.size() == 0) {
    ERROR(Form("No scintillators in run %i", fRunID));
    return;
  }
  for (auto description : descriptions) {
    fScins[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = fParamGetter.getAllRelationalData(
    ParamObjectType::kScin, ParamObjectType::kSlot, fRunID
  );
  for (auto relation : relations) {
    fScins[relation.first]->setSlot(*fSlotFactory.getSlots().at(relation.second));
  }
}

JPetScin* JPetScinFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    float length = boost::lexical_cast<float>(data.at("length"));
    float height = boost::lexical_cast<float>(data.at("height"));
    float width = boost::lexical_cast<float>(data.at("width"));
    float centerX = boost::lexical_cast<float>(data.at("xcenter"));
    float centerY = boost::lexical_cast<float>(data.at("ycenter"));
    float centerZ = boost::lexical_cast<float>(data.at("zcenter"));
    return new JPetScin(id, length, height, width, centerX, centerY, centerZ);
  } catch (const std::exception & e) {
    ERROR(Form("Failed to build scintillator with error: %s", e.what()));
    throw;
  }
}

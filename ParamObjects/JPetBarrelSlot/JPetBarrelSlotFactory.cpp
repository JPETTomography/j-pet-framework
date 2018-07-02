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
 *  @file JPetBarrelSlotFactory.cpp
 */

#include "JPetBarrelSlotFactory.h"
#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>
#include <tuple>

std::map<int, JPetBarrelSlot *> & JPetBarrelSlotFactory::getBarrelSlots()
{
  if (!fInitialized) {
    initialize();
  }
  return fBarrelSlots;
}

void JPetBarrelSlotFactory::initialize()
{
  ParamObjectsDescriptions descriptions = paramGetter.getAllBasicData(ParamObjectType::kBarrelSlot, runId);
  if (descriptions.size() == 0) {
    ERROR(std::string("No barrel slots in run ") + boost::lexical_cast<std::string>(runId));
  }
  for (auto description : descriptions) {
    fBarrelSlots[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = paramGetter.getAllRelationalData(ParamObjectType::kBarrelSlot, ParamObjectType::kLayer, runId);
  for (auto relation : relations) {
    fBarrelSlots[relation.first]->setLayer(*layerFactory.getLayers().at(relation.second));
  }
}

JPetBarrelSlot* JPetBarrelSlotFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    bool active = boost::lexical_cast<bool>(data.at("active"));
    std::string name = data.at("name");
    float theta = boost::lexical_cast<float>(data.at("theta1"));
    int inFrameId = boost::lexical_cast<int>(data.at("frame_id"));
    return new JPetBarrelSlot(id, active, name, theta, inFrameId);
  } catch (const std::exception & e) {
    ERROR(std::string("Failed to build barrelSlot with error: ") + e.what());
    throw;
  }
}

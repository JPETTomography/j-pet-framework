/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetSlotFactory.cpp
 */

#include "JPetSlot/JPetSlotFactory.h"
#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>
#include <tuple>

std::map<int, JPetSlot*>& JPetSlotFactory::getSlots()
{
  if (!fInitialized)
  {
    initialize();
  }
  return fSlots;
}

void JPetSlotFactory::initialize()
{
  ParamObjectsDescriptions descriptions = fParamGetter.getAllBasicData(ParamObjectType::kSlot, fRunID);
  if (descriptions.size() == 0)
  {
    ERROR(Form("No barrel slots in run %i", fRunID));
    return;
  }
  for (auto description : descriptions)
  {
    fSlots[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = fParamGetter.getAllRelationalData(ParamObjectType::kSlot, ParamObjectType::kLayer, fRunID);
  for (auto relation : relations)
  {
    fSlots[relation.first]->setLayer(*fLayerFactory.getLayers().at(relation.second));
  }
}

JPetSlot* JPetSlotFactory::build(ParamObjectDescription data)
{
  try
  {
    int id = boost::lexical_cast<int>(data.at("id"));
    float theta = boost::lexical_cast<float>(data.at("theta"));
    std::string typeStr = boost::lexical_cast<std::string>(data.at("type"));
    JPetSlot::Type type = JPetSlot::Barrel;
    if (typeStr == "module")
    {
      type = JPetSlot::Module;
    }
    return new JPetSlot(id, theta, type);
  }
  catch (const std::exception& e)
  {
    ERROR(Form("Failed to build Slot with error: %s", e.what()));
    throw;
  }
  return new JPetSlot(true);
}

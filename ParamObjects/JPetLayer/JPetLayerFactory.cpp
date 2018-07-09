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
 *  @file JPetLayerFactory.cpp
 */

#include <boost/lexical_cast.hpp>
#include "JPetLayerFactory.h"
#include <exception>
#include <string>
#include <tuple>

std::map<int, JPetLayer *> & JPetLayerFactory::getLayers()
{
  if (!fInitialized) { initialize(); }
  return fLayers;
}

void JPetLayerFactory::initialize()
{
  ParamObjectsDescriptions descriptions = paramGetter.getAllBasicData(ParamObjectType::kLayer, runId);
  if (descriptions.size() == 0) {
    ERROR(std::string("No layers in run ") + boost::lexical_cast<std::string>(runId));
  }
  for (auto description : descriptions) {
    fLayers[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = paramGetter.getAllRelationalData(
    ParamObjectType::kLayer, ParamObjectType::kFrame, runId
  );
  for (auto relation : relations) {
    fLayers[relation.first]->setFrame(*frameFactory.getFrames().at(relation.second));
  }
}

JPetLayer* JPetLayerFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    bool active = boost::lexical_cast<bool>(data.at("active"));
    std::string name = data.at("name");
    float radius = boost::lexical_cast<float>(data.at("radius"));
    return new JPetLayer(id, active, name, radius);
  } catch (const std::exception & e) {
    ERROR(std::string("Failed to build layer with error: ") + e.what());
    throw;
  }
}

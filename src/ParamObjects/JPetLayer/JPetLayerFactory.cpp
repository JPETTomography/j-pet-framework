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
 *  @file JPetLayerFactory.cpp
 */

#include "JPetLayer/JPetLayerFactory.h"
#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>
#include <tuple>

std::map<int, JPetLayer*>& JPetLayerFactory::getLayers()
{
  if (!fInitialized)
  {
    initialize();
  }
  return fLayers;
}

void JPetLayerFactory::initialize()
{
  ParamObjectsDescriptions descriptions = fParamGetter.getAllBasicData(ParamObjectType::kLayer, fRunID);
  if (descriptions.size() == 0)
  {
    ERROR(Form("No layers in run %i", fRunID));
    return;
  }
  for (auto description : descriptions)
  {
    fLayers[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = fParamGetter.getAllRelationalData(ParamObjectType::kLayer, ParamObjectType::kSetup, fRunID);
  for (auto relation : relations)
  {
    fLayers[relation.first]->setSetup(*fSetupFactory.getSetups().at(relation.second));
  }
}

JPetLayer* JPetLayerFactory::build(ParamObjectDescription data)
{
  try
  {
    int id = boost::lexical_cast<int>(data.at("id"));
    std::string name = data.at("name");
    double radius = boost::lexical_cast<double>(data.at("radius"));
    return new JPetLayer(id, name, radius);
  }
  catch (const std::exception& e)
  {
    ERROR(Form("Failed to build layer with error: %s", e.what()));
    throw;
  }
}

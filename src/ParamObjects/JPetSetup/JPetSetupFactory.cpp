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
 *  @file JPetSetupFactory.cpp
 */

#include "JPetSetup/JPetSetupFactory.h"
#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>

std::map<int, JPetSetup*>& JPetSetupFactory::getSetups()
{
  if (!fInitialized)
  {
    initialize();
  }
  return fSetups;
}

void JPetSetupFactory::initialize()
{
  ParamObjectsDescriptions descriptions = fParamGetter.getAllBasicData(ParamObjectType::kSetup, fRunID);
  if (descriptions.size() == 0)
  {
    ERROR(Form("No Setups in run %i", fRunID));
    return;
  }
  for (auto description : descriptions)
  {
    fSetups[description.first] = build(description.second);
  }
  fInitialized = true;
}

JPetSetup* JPetSetupFactory::build(ParamObjectDescription data)
{
  try
  {
    int id = boost::lexical_cast<int>(data.at("id"));
    std::string description = data.at("description");
    return new JPetSetup(id, description);
  }
  catch (const std::exception& e)
  {
    ERROR(Form("Failed to build setup with error: %s", e.what()));
    throw;
  }
}

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
 *  @file JPetChannelFactory.cpp
 */

#include "JPetChannel/JPetChannelFactory.h"
#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>

std::map<int, JPetChannel*>& JPetChannelFactory::getChannels()
{
  if (!fInitialized)
  {
    initialize();
  }
  return fChannels;
}

void JPetChannelFactory::initialize()
{
  ParamObjectsDescriptions descriptions = fParamGetter.getAllBasicData(ParamObjectType::kChannel, fRunID);
  if (descriptions.size() == 0)
  {
    ERROR(Form("No Channels in run %i", fRunID));
    return;
  }
  for (auto description : descriptions)
  {
    fChannels[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = fParamGetter.getAllRelationalData(ParamObjectType::kChannel, ParamObjectType::kPM, fRunID);
  for (auto relation : relations)
  {
    fChannels[relation.first]->setPM(*fPMFactory.getPMs().at(relation.second));
  }
  relations = fParamGetter.getAllRelationalData(ParamObjectType::kChannel, ParamObjectType::kDataModule, fRunID);
  for (auto relation : relations)
  {
    fChannels[relation.first]->setDataModule(*fDataModuleFactory.getDataModules().at(relation.second));
  }
}

JPetChannel* JPetChannelFactory::build(ParamObjectDescription data)
{
  try
  {
    int id = boost::lexical_cast<int>(data.at("id"));
    int thrNum = boost::lexical_cast<int>(data.at("thr_num"));
    double thrVal = boost::lexical_cast<double>(data.at("thr_val"));
    return new JPetChannel(id, thrNum, thrVal);
  }
  catch (const std::exception& e)
  {
    ERROR(Form("Failed to build Channel with error: %s", e.what()));
    throw;
  }
}

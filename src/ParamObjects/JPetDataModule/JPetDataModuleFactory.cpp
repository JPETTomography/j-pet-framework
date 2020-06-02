/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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

#include "JPetDataModule/JPetDataModuleFactory.h"

#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>

std::map<int, JPetDataModule*>& JPetDataModuleFactory::getDataModules()
{
  if (!fInitialized) { initialize(); }
  return fDataModules;
}

void JPetDataModuleFactory::initialize()
{
  ParamObjectsDescriptions descriptions = fParamGetter.getAllBasicData(
    ParamObjectType::kDataModule, fRunID
  );
  if (descriptions.size() == 0) {
    ERROR(Form("No Data Modules in run %i", fRunID));
    return;
  }
  for (auto description : descriptions) {
    fDataModules[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = fParamGetter.getAllRelationalData(
    ParamObjectType::kDataModule, ParamObjectType::kDataSource, fRunID
  );
  for (auto relation : relations) {
    fDataModules[relation.first]->setDataSource(
      *fDataSourceFactory.getDataSources().at(relation.second)
    );
  }
}

JPetDataModule* JPetDataModuleFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    std::string type = boost::lexical_cast<std::string>(data.at("type"));
    std::string trb = boost::lexical_cast<std::string>(data.at("trbnet_address"));
    int channelsNumber = boost::lexical_cast<int>(data.at("channels_number"));
    int channelsOffset = boost::lexical_cast<int>(data.at("channels_offset"));
    return new JPetDataModule(id, type, trb, channelsNumber, channelsOffset);
  } catch (const std::exception& e) {
    ERROR(Form("Failed to build Data Module with error: %s", e.what()));
    throw;
  }
  return new JPetDataModule(true);
}

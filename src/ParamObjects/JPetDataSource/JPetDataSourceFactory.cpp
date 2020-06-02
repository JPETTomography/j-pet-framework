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
 *  @file JPetDataSourceFactory.cpp
 */

#include "JPetDataSource/JPetDataSourceFactory.h"

#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>

std::map<int, JPetDataSource*>& JPetDataSourceFactory::getDataSources()
{
  if (!fInitialized) {
    initialize();
  }
  return fDataSources;
}

void JPetDataSourceFactory::initialize()
{
  ParamObjectsDescriptions descriptions = fParamGetter.getAllBasicData(
    ParamObjectType::kDataSource, fRunID
  );
  if (descriptions.size() == 0) {
    ERROR(Form("No DataSources in run %i", fRunID));
  }
  for (auto description : descriptions) {
    fDataSources[description.first] = build(description.second);
  }
  fInitialized = true;
}

JPetDataSource* JPetDataSourceFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    std::string type = boost::lexical_cast<std::string>(data.at("type"));
    std::string trb = boost::lexical_cast<std::string>(data.at("trbnet_address"));
    std::string hub = boost::lexical_cast<std::string>(data.at("hub_address"));
    return new JPetDataSource(id, type, trb, hub);
  } catch (const std::exception& e) {
    ERROR(Form("Failed to build Data Source with error: %s", e.what()));
    throw;
  }
  return new JPetDataSource(true);
}

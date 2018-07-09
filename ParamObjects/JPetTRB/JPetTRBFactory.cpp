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
 *  @file JPetTRBFactory.cpp
 */

#include <boost/lexical_cast.hpp>
#include "JPetTRBFactory.h"
#include <exception>
#include <string>
#include <tuple>

std::map<int, JPetTRB *> & JPetTRBFactory::getTRBs()
{
  if (!fInitialized) { initialize(); }
  return fTRBs;
}

void JPetTRBFactory::initialize()
{
  ParamObjectsDescriptions descriptions = paramGetter.getAllBasicData(ParamObjectType::kTRB, runId);
  if (descriptions.size() == 0) {
    ERROR(std::string("No TRBs in run ") + boost::lexical_cast<std::string>(runId));
  }
  for (auto description : descriptions) {
    fTRBs[description.first] = build(description.second);
  }
  fInitialized = true;
}

JPetTRB* JPetTRBFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    int type = boost::lexical_cast<int>(data.at("type"));
    int channel = boost::lexical_cast<int>(data.at("channel"));
    return new JPetTRB(id, type, channel);
  } catch (const std::exception & e) {
    ERROR(std::string("Failed to build TRB with error: ") + e.what());
    throw;
  }
}

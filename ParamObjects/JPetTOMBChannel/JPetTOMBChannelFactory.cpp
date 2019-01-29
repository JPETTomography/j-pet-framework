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
 *  @file JPetTOMBChannelFactory.cpp
 */

#include "JPetTOMBChannelFactory.h"
#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>
#include <tuple>

std::map<int, JPetTOMBChannel *> & JPetTOMBChannelFactory::getTOMBChannels()
{
  if (!fInitialized) { initialize(); }
  return fTOMBChannels;
}

void JPetTOMBChannelFactory::initialize()
{
  ParamObjectsDescriptions descriptions = paramGetter.getAllBasicData(ParamObjectType::kTOMBChannel, runId);
  if (descriptions.size() == 0) {
    ERROR(std::string("No TOMBChannels in run ") + boost::lexical_cast<std::string>(runId));
  }
  for (auto description : descriptions) {
    fTOMBChannels[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = paramGetter.getAllRelationalData(ParamObjectType::kTOMBChannel, ParamObjectType::kFEB, runId);
  for (auto relation : relations) {
    fTOMBChannels[relation.first]->setFEB(*febFactory.getFEBs().at(relation.second));
  }
  relations = paramGetter.getAllRelationalData(ParamObjectType::kTOMBChannel, ParamObjectType::kTRB, runId);
  for (auto relation : relations) {
    fTOMBChannels[relation.first]->setTRB(*TRBFactory.getTRBs().at(relation.second));
  }
  relations = paramGetter.getAllRelationalData(ParamObjectType::kTOMBChannel, ParamObjectType::kPM, runId);
  for (auto relation : relations) {
    fTOMBChannels[relation.first]->setPM(*PMFactory.getPMs().at(relation.second));
  }
}

JPetTOMBChannel * JPetTOMBChannelFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("channel"));
    int channel = boost::lexical_cast<int>(data.at("local_number"));
    int FEB = boost::lexical_cast<int>(data.at("FEB"));
    float threshold = boost::lexical_cast<float>(data.at("threshold"));
    JPetTOMBChannel * result = new JPetTOMBChannel(id);
    result->setLocalChannelNumber(channel);
    result->setFEBInputNumber(FEB);
    result->setThreshold(threshold);
    return result;
  } catch (const std::exception & e) {
    ERROR(std::string("Failed to build TOMBChannel with error: ") + e.what());
    throw;
  }
}

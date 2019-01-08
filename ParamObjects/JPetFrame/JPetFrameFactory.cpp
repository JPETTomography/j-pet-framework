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
 *  @file JPetFrameFactory.cpp
 */

#include <boost/lexical_cast.hpp>
#include "JPetFrameFactory.h"
#include <exception>
#include <string>
#include <tuple>

std::map<int, JPetFrame*> & JPetFrameFactory::getFrames()
{
  if (!fInitialized) { initialize(); }
  return fFrames;
}

void JPetFrameFactory::initialize()
{
  ParamObjectsDescriptions descriptions = paramGetter.getAllBasicData(ParamObjectType::kFrame, runId);
  if (descriptions.size() == 0) {
    ERROR(std::string("No frames in run ") + boost::lexical_cast<std::string>(runId));
  }
  for (auto description : descriptions) {
    fFrames[description.first] = build(description.second);
  }
  fInitialized = true;
}

JPetFrame* JPetFrameFactory::build(ParamObjectDescription data)
{
  try {
    int id = boost::lexical_cast<int>(data.at("id"));
    bool active = boost::lexical_cast<bool>(data.at("active"));
    std::string status = data.at("status");
    std::string description = data.at("description");
    int version = boost::lexical_cast<int>(data.at("version"));
    int creatorId = boost::lexical_cast<int>(data.at("creator_id"));
    return new JPetFrame(id, active, status, description, version, creatorId);
  } catch (const std::exception & e) {
    ERROR(std::string("Failed to build frame with error: ") + e.what());
    throw;
  }
}

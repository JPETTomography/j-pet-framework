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
 *  @file JPetParamSaverAscii.cpp
 */

#include <boost/property_tree/json_parser.hpp>
#include "./JPetParamBank/JPetParamBank.h"
#include "./JPetParamAsciiConstants.h"
#include "./JPetParamSaverAscii.h"
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

void JPetParamSaverAscii::saveParamBank(const JPetParamBank& bank,
  const int runNumber, const std::string& filename)
{
  std::string runNumberS = boost::lexical_cast<std::string>(runNumber);
  auto fileTree = getTreeFromFile(filename);
  addToTree(fileTree, bank, runNumberS);
  write_json(filename, fileTree);
}

boost::property_tree::ptree JPetParamSaverAscii::getTreeFromFile(const std::string& filename)
{
  boost::property_tree::ptree result;
  if (boost::filesystem::exists(filename)) {
    boost::property_tree::read_json(filename, result);
  }
  return result;
}

void JPetParamSaverAscii::addToTree(boost::property_tree::ptree& tree,
  const JPetParamBank& bank, const std::string& runNumber)
{
  if (tree.count(runNumber) != 0) {
    WARNING("Overwriting parameters in run number " + runNumber + ". I hope you wanted to do that.");
    tree.erase(runNumber);
  }
  boost::property_tree::ptree runContents;
  fillScintillators(runContents, bank);
  fillPMs(runContents, bank);
  fillBarrelSlots(runContents, bank);
  fillLayers(runContents, bank);
  fillFrames(runContents, bank);
  fillFEBs(runContents, bank);
  fillTRBs(runContents, bank);
  fillTOMBChannels(runContents, bank);
  tree.add_child(runNumber, runContents);
}

void JPetParamSaverAscii::fillScintillators(boost::property_tree::ptree& runContents,
  const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto scin : bank.getScintillators()) {
    infos.push_back(std::make_pair("", scintillatorToInfo(*scin.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kScintillator), infos);
}

boost::property_tree::ptree JPetParamSaverAscii::scintillatorToInfo(const JPetScin& scin)
{
  boost::property_tree::ptree info;
  info.put("id", scin.getID());
  info.put("attenuation_length", scin.getAttenLen());
  auto dimensions = scin.getScinSize();
  info.put("length", dimensions.fLength);
  info.put("width", dimensions.fWidth);
  info.put("height", dimensions.fHeight);
  info.put(objectsNames.at(ParamObjectType::kBarrelSlot) + "_id", scin.getBarrelSlot().getID());
  return info;
}

void JPetParamSaverAscii::fillPMs(boost::property_tree::ptree& runContents,
  const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto pm : bank.getPMs()) {
    infos.push_back(std::make_pair("", PMToInfo(*pm.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kPM), infos);
}

boost::property_tree::ptree JPetParamSaverAscii::PMToInfo(const JPetPM& pm)
{
  boost::property_tree::ptree info;
  info.put("id", pm.getID());
  info.put("is_right_side", (pm.getSide() == JPetPM::Side::SideB));
  info.put("description", pm.getDescription());
  info.put(objectsNames.at(ParamObjectType::kBarrelSlot) + "_id", pm.getBarrelSlot().getID());
  if (pm.hasFEB()) {
    info.put(objectsNames.at(ParamObjectType::kFEB) + "_id", pm.getFEB().getID());
  }
  info.put(objectsNames.at(ParamObjectType::kScintillator) + "_id", pm.getScin().getID());
  return info;
}

void JPetParamSaverAscii::fillBarrelSlots(boost::property_tree::ptree& runContents,
  const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto bs : bank.getBarrelSlots()) {
    infos.push_back(std::make_pair("", barrelSlotToInfo(*bs.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kBarrelSlot), infos);
}

boost::property_tree::ptree JPetParamSaverAscii::barrelSlotToInfo(const JPetBarrelSlot& bs)
{
  boost::property_tree::ptree info;
  info.put("id", bs.getID());
  info.put("active", bs.isActive());
  info.put("name", bs.getName());
  info.put("theta1", bs.getTheta());
  info.put("frame_id", bs.getInFrameID());
  if (bs.hasLayer()) {
    info.put(objectsNames.at(ParamObjectType::kLayer) + "_id", bs.getLayer().getID());
  }
  return info;
}

void JPetParamSaverAscii::fillLayers(boost::property_tree::ptree& runContents,
  const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto layer : bank.getLayers()) {
    infos.push_back(std::make_pair("", layerToInfo(*layer.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kLayer), infos);
}

boost::property_tree::ptree JPetParamSaverAscii::layerToInfo(const JPetLayer& layer)
{
  boost::property_tree::ptree info;
  info.put("id", layer.getID());
  info.put("active", layer.getIsActive());
  info.put("name", layer.getName());
  info.put("radius", layer.getRadius());
  info.put(objectsNames.at(ParamObjectType::kFrame) + "_id", layer.getFrame().getID());
  return info;
}

void JPetParamSaverAscii::fillFrames(boost::property_tree::ptree& runContents,
  const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto frame : bank.getFrames()) {
    infos.push_back(std::make_pair("", frameToInfo(*frame.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kFrame), infos);
}

boost::property_tree::ptree JPetParamSaverAscii::frameToInfo(const JPetFrame& frame)
{
  boost::property_tree::ptree info;
  info.put("id", frame.getID());
  info.put("active", frame.getIsActive());
  info.put("status", frame.getStatus());
  info.put("description", frame.getDescription());
  info.put("version", frame.getVersion());
  info.put("creator_id", frame.getCreator());
  return info;
}

void JPetParamSaverAscii::fillFEBs(boost::property_tree::ptree& runContents,
  const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto feb : bank.getFEBs()) {
    infos.push_back(std::make_pair("", FEBToInfo(*feb.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kFEB), infos);
}

boost::property_tree::ptree JPetParamSaverAscii::FEBToInfo(const JPetFEB& feb)
{
  boost::property_tree::ptree info;
  info.put("id", feb.getID());
  info.put("active", feb.isActive());
  info.put("status", feb.status());
  info.put("description", feb.description());
  info.put("version", feb.version());
  info.put("creator_id", feb.getCreator());
  info.put("time_outputs_per_input", feb.getNtimeOutsPerInput());
  info.put("no_time_outputs_per_input", feb.getNnotimeOutsPerInput());
  info.put(objectsNames.at(ParamObjectType::kTRB) + "_id", feb.getTRB().getID());
  return info;
}

void JPetParamSaverAscii::fillTRBs(boost::property_tree::ptree& runContents,
  const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto trb : bank.getTRBs()) {
    infos.push_back(std::make_pair("", TRBToInfo(*trb.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kTRB), infos);
}

boost::property_tree::ptree JPetParamSaverAscii::TRBToInfo(const JPetTRB& trb)
{
  boost::property_tree::ptree info;
  info.put("id", trb.getID());
  info.put("type", trb.getType());
  info.put("channel", trb.getChannel());
  return info;
}

void JPetParamSaverAscii::fillTOMBChannels(boost::property_tree::ptree& runContents,
  const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto tomb : bank.getTOMBChannels()) {
    infos.push_back(std::make_pair("", TOMBChannelToInfo(*tomb.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kTOMBChannel), infos);
}

boost::property_tree::ptree JPetParamSaverAscii::TOMBChannelToInfo(const JPetTOMBChannel& tomb)
{
  boost::property_tree::ptree info;
  info.put("local_number", tomb.getLocalChannelNumber());
  info.put("channel", tomb.getChannel());
  info.put("FEB", tomb.getFEBInputNumber());
  info.put("threshold", tomb.getThreshold());
  info.put(objectsNames.at(ParamObjectType::kTRB) + "_id", tomb.getTRB().getID());
  info.put(objectsNames.at(ParamObjectType::kFEB) + "_id", tomb.getFEB().getID());
  info.put(objectsNames.at(ParamObjectType::kPM) + "_id", tomb.getPM().getID());
  return info;
}

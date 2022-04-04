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
 *  @file JPetParamSaverAscii.cpp
 */

#include "JPetParamGetterAscii/JPetParamSaverAscii.h"
#include "JPetParamBank/JPetParamBank.h"
#include "JPetParamGetterAscii/JPetParamAsciiConstants.h"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>

void JPetParamSaverAscii::saveParamBank(const JPetParamBank& bank, const int runNumber, const std::string& filename)
{
  std::string runNumberS = boost::lexical_cast<std::string>(runNumber);
  auto fileTree = getTreeFromFile(filename);
  addToTree(fileTree, bank, runNumberS);
  write_json(filename, fileTree);
}

boost::property_tree::ptree JPetParamSaverAscii::getTreeFromFile(const std::string& filename)
{
  boost::property_tree::ptree result;
  if (boost::filesystem::exists(filename))
  {
    boost::property_tree::read_json(filename, result);
  }
  return result;
}

void JPetParamSaverAscii::addToTree(boost::property_tree::ptree& tree, const JPetParamBank& bank, const std::string& runNumber)
{
  if (tree.count(runNumber) != 0)
  {
    WARNING("Overwriting parameters in run number " + runNumber + ". I hope you wanted to do that.");
    tree.erase(runNumber);
  }
  boost::property_tree::ptree runContents;
  fillSetups(runContents, bank);
  fillLayers(runContents, bank);
  fillSlots(runContents, bank);
  fillScins(runContents, bank);
  fillMatrices(runContents, bank);
  fillPMs(runContents, bank);
  fillChannels(runContents, bank);
  fillDataSources(runContents, bank);
  fillDataModules(runContents, bank);
  tree.add_child(runNumber, runContents);
}

void JPetParamSaverAscii::fillSetups(boost::property_tree::ptree& runContents, const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto setup : bank.getSetups())
  {
    infos.push_back(std::make_pair("", setupToInfo(*setup.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kSetup), infos);
}

void JPetParamSaverAscii::fillLayers(boost::property_tree::ptree& runContents, const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto layer : bank.getLayers())
  {
    infos.push_back(std::make_pair("", layerToInfo(*layer.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kLayer), infos);
}

void JPetParamSaverAscii::fillSlots(boost::property_tree::ptree& runContents, const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto slot : bank.getSlots())
  {
    infos.push_back(std::make_pair("", slotToInfo(*slot.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kSlot), infos);
}

void JPetParamSaverAscii::fillScins(boost::property_tree::ptree& runContents, const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto scin : bank.getScins())
  {
    infos.push_back(std::make_pair("", scinToInfo(*scin.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kScin), infos);
}

void JPetParamSaverAscii::fillMatrices(boost::property_tree::ptree& runContents, const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto mtx : bank.getMatrices())
  {
    infos.push_back(std::make_pair("", matrixToInfo(*mtx.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kMatrix), infos);
}

void JPetParamSaverAscii::fillPMs(boost::property_tree::ptree& runContents, const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto pm : bank.getPMs())
  {
    infos.push_back(std::make_pair("", pmToInfo(*pm.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kPM), infos);
}

void JPetParamSaverAscii::fillChannels(boost::property_tree::ptree& runContents, const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto channel : bank.getChannels())
  {
    infos.push_back(std::make_pair("", channelToInfo(*channel.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kChannel), infos);
}

void JPetParamSaverAscii::fillDataSources(boost::property_tree::ptree& runContents, const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto dataSource : bank.getDataSources())
  {
    infos.push_back(std::make_pair("", dataSourceToInfo(*dataSource.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kDataSource), infos);
}

void JPetParamSaverAscii::fillDataModules(boost::property_tree::ptree& runContents, const JPetParamBank& bank)
{
  boost::property_tree::ptree infos;
  for (auto dataModule : bank.getDataModules())
  {
    infos.push_back(std::make_pair("", dataModuleToInfo(*dataModule.second)));
  }
  runContents.add_child(objectsNames.at(ParamObjectType::kDataModule), infos);
}

boost::property_tree::ptree JPetParamSaverAscii::setupToInfo(const JPetSetup& setup)
{
  boost::property_tree::ptree info;
  info.put("id", setup.getID());
  info.put("description", setup.getDescription());
  return info;
}

boost::property_tree::ptree JPetParamSaverAscii::layerToInfo(const JPetLayer& layer)
{
  boost::property_tree::ptree info;
  info.put("id", layer.getID());
  info.put("name", layer.getName());
  info.put("radius", layer.getRadius());
  info.put(objectsNames.at(ParamObjectType::kSetup) + "_id", layer.getSetup().getID());
  return info;
}

boost::property_tree::ptree JPetParamSaverAscii::slotToInfo(const JPetSlot& slot)
{
  boost::property_tree::ptree info;
  info.put("id", slot.getID());
  info.put("theta", slot.getTheta());
  if (slot.getType() == JPetSlot::Barrel)
  {
    info.put("type", "barrel");
  }
  else if (slot.getType() == JPetSlot::Module)
  {
    info.put("type", "module");
  }
  info.put(objectsNames.at(ParamObjectType::kLayer) + "_id", slot.getLayer().getID());
  return info;
}

boost::property_tree::ptree JPetParamSaverAscii::scinToInfo(const JPetScin& scin)
{
  boost::property_tree::ptree info;
  info.put("id", scin.getID());
  info.put("length", scin.getLength());
  info.put("width", scin.getWidth());
  info.put("height", scin.getHeight());
  info.put("xcenter", scin.getCenterX());
  info.put("ycenter", scin.getCenterY());
  info.put("zcenter", scin.getCenterZ());
  info.put("rot_x", scin.getRotationX());
  info.put("rot_y", scin.getRotationY());
  info.put("rot_z", scin.getRotationZ());
  info.put(objectsNames.at(ParamObjectType::kSlot) + "_id", scin.getSlot().getID());
  return info;
}

boost::property_tree::ptree JPetParamSaverAscii::matrixToInfo(const JPetMatrix& mtx)
{
  boost::property_tree::ptree info;
  info.put("id", mtx.getID());
  if (mtx.getSide() == JPetMatrix::SideA)
  {
    info.put("side", "A");
  }
  else if (mtx.getSide() == JPetMatrix::SideB)
  {
    info.put("side", "B");
  }
  info.put(objectsNames.at(ParamObjectType::kScin) + "_id", mtx.getScin().getID());
  return info;
}

boost::property_tree::ptree JPetParamSaverAscii::pmToInfo(const JPetPM& pm)
{
  boost::property_tree::ptree info;
  info.put("id", pm.getID());
  info.put("description", pm.getDesc());
  info.put("pos_in_matrix", pm.getMatrixPosition());
  info.put(objectsNames.at(ParamObjectType::kMatrix) + "_id", pm.getMatrix().getID());
  return info;
}

boost::property_tree::ptree JPetParamSaverAscii::channelToInfo(const JPetChannel& channel)
{
  boost::property_tree::ptree info;
  info.put("id", channel.getID());
  info.put("thr_num", channel.getThresholdNumber());
  info.put("thr_val", channel.getThresholdValue());
  info.put(objectsNames.at(ParamObjectType::kPM) + "_id", channel.getPM().getID());
  return info;
}

boost::property_tree::ptree JPetParamSaverAscii::dataSourceToInfo(const JPetDataSource& dataSource)
{
  // Converting TRB and HUB addresses from decimal to hex and to string
  std::stringstream trb2stringStream;
  std::stringstream hub2stringStream;
  trb2stringStream << std::hex << dataSource.getTBRNetAddress();
  hub2stringStream << std::hex << dataSource.getHubAddress();

  boost::property_tree::ptree info;
  info.put("id", dataSource.getID());
  info.put("type", dataSource.getType());
  info.put("trbnet_address", trb2stringStream.str());
  info.put("hub_address", hub2stringStream.str());
  return info;
}

boost::property_tree::ptree JPetParamSaverAscii::dataModuleToInfo(const JPetDataModule& dataModule)
{
  // Converting TRB address from decimal to hex and to string
  std::stringstream trb2stringStream;
  trb2stringStream << std::hex << dataModule.getTBRNetAddress();

  boost::property_tree::ptree info;
  info.put("id", dataModule.getID());
  info.put("type", dataModule.getType());
  info.put("trbnet_address", trb2stringStream.str());
  info.put("channels_number", dataModule.getChannelsNumber());
  info.put("channels_offset", dataModule.getChannelsOffset());
  info.put(objectsNames.at(ParamObjectType::kDataSource) + "_id", dataModule.getDataSource().getID());
  return info;
}

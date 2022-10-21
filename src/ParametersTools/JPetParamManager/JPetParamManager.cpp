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
 *  @file JPetParamManager.cpp
 */

#include "JPetParamManager/JPetParamManager.h"
#include "JPetOptionsTools/JPetOptionsTools.h"
#include "JPetParamGetterAscii/JPetParamGetterAscii.h"

#include <TFile.h>
#include <boost/property_tree/xml_parser.hpp>

std::shared_ptr<JPetParamManager> JPetParamManager::generateParamManager(const std::map<std::string, boost::any>& options)
{
  using namespace jpet_options_tools;
  if (isLocalDB(options))
  {
    std::set<ParamObjectType> expectMissing;
    if (file_type_checker::getInputFileType(options) == file_type_checker::kScope)
    {
      expectMissing.insert(ParamObjectType::kTRB);
      expectMissing.insert(ParamObjectType::kFEB);
      expectMissing.insert(ParamObjectType::kFrame);
      expectMissing.insert(ParamObjectType::kLayer);
      expectMissing.insert(ParamObjectType::kTOMBChannel);
      expectMissing.insert(ParamObjectType::kDataSource);
      expectMissing.insert(ParamObjectType::kDataModule);
    }
    if (file_type_checker::getInputFileType(options) == file_type_checker::kMCGeant)
    {
      expectMissing.insert(ParamObjectType::kPM);
      expectMissing.insert(ParamObjectType::kPMCalib);
      expectMissing.insert(ParamObjectType::kFEB);
      expectMissing.insert(ParamObjectType::kTRB);
      expectMissing.insert(ParamObjectType::kTOMBChannel);
      expectMissing.insert(ParamObjectType::kDataSource);
      expectMissing.insert(ParamObjectType::kDataModule);
    }
    return std::make_shared<JPetParamManager>(new JPetParamGetterAscii(getLocalDB(options)), expectMissing);
  }
  else
  {
    ERROR("No local database file found.");
    return std::make_shared<JPetParamManager>();
  }
}

JPetParamManager::~JPetParamManager()
{
  if (fBank)
  {
    delete fBank;
    fBank = 0;
  }
  if (fParamGetter)
  {
    delete fParamGetter;
    fParamGetter = 0;
  }
}

std::map<int, JPetTRB*>& JPetParamManager::getTRBs(const int runID) { return getTRBFactory(runID).getTRBs(); }

JPetTRBFactory& JPetParamManager::getTRBFactory(const int runID)
{
  if (fTRBFactories.count(runID) == 0)
  {
    fTRBFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID), std::forward_as_tuple(*fParamGetter, runID));
  }
  return fTRBFactories.at(runID);
}

std::map<int, JPetFEB*>& JPetParamManager::getFEBs(const int runID) { return getFEBFactory(runID).getFEBs(); }

JPetFEBFactory& JPetParamManager::getFEBFactory(const int runID)
{
  if (fFEBFactories.count(runID) == 0)
  {
    fFEBFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID), std::forward_as_tuple(*fParamGetter, runID, getTRBFactory(runID)));
  }
  return fFEBFactories.at(runID);
}

std::map<int, JPetFrame*>& JPetParamManager::getFrames(const int runID) { return getFrameFactory(runID).getFrames(); }

JPetFrameFactory& JPetParamManager::getFrameFactory(const int runID)
{
  if (fFrameFactories.count(runID) == 0)
  {
    fFrameFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID), std::forward_as_tuple(*fParamGetter, runID));
  }
  return fFrameFactories.at(runID);
}

std::map<int, JPetLayer*>& JPetParamManager::getLayers(const int runID) { return getLayerFactory(runID).getLayers(); }

JPetLayerFactory& JPetParamManager::getLayerFactory(const int runID)
{
  if (fLayerFactories.count(runID) == 0)
  {
    fLayerFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                            std::forward_as_tuple(*fParamGetter, runID, getFrameFactory(runID)));
  }
  return fLayerFactories.at(runID);
}

std::map<int, JPetBarrelSlot*>& JPetParamManager::getBarrelSlots(const int runID) { return getBarrelSlotFactory(runID).getBarrelSlots(); }

JPetBarrelSlotFactory& JPetParamManager::getBarrelSlotFactory(const int runID)
{
  if (fBarrelSlotFactories.count(runID) == 0)
  {
    fBarrelSlotFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                                 std::forward_as_tuple(*fParamGetter, runID, getLayerFactory(runID)));
  }
  fBarrelSlotFactories.at(runID);
  return fBarrelSlotFactories.at(runID);
}

std::map<int, JPetScin*>& JPetParamManager::getScins(const int runID) { return getScinFactory(runID).getScins(); }

JPetScinFactory& JPetParamManager::getScinFactory(const int runID)
{
  if (fScinFactories.count(runID) == 0)
  {
    fScinFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                           std::forward_as_tuple(*fParamGetter, runID, getBarrelSlotFactory(runID)));
  }
  return fScinFactories.at(runID);
}

std::map<int, JPetPM*>& JPetParamManager::getPMs(const int runID) { return getPMFactory(runID).getPMs(); }

JPetPMFactory& JPetParamManager::getPMFactory(const int runID)
{
  if (fPMFactories.count(runID) == 0)
  {
    fPMFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                         std::forward_as_tuple(*fParamGetter, runID, getFEBFactory(runID), getScinFactory(runID), getBarrelSlotFactory(runID)));
  }
  return fPMFactories.at(runID);
}

std::map<int, JPetTOMBChannel*>& JPetParamManager::getTOMBChannels(const int runID) { return getTOMBChannelFactory(runID).getTOMBChannels(); }

JPetTOMBChannelFactory& JPetParamManager::getTOMBChannelFactory(const int runID)
{
  if (fTOMBChannelFactories.count(runID) == 0)
  {
    fTOMBChannelFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                                  std::forward_as_tuple(*fParamGetter, runID, getFEBFactory(runID), getTRBFactory(runID), getPMFactory(runID)));
  }
  return fTOMBChannelFactories.at(runID);
}

std::map<int, JPetDataSource*>& JPetParamManager::getDataSources(const int runID) { return getDataSourceFactory(runID).getDataSources(); }

JPetDataSourceFactory& JPetParamManager::getDataSourceFactory(const int runID)
{
  if (fDataSourceFactories.count(runID) == 0)
  {
    fDataSourceFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID), std::forward_as_tuple(*fParamGetter, runID));
  }
  return fDataSourceFactories.at(runID);
}

std::map<int, JPetDataModule*>& JPetParamManager::getDataModules(const int runID) { return getDataModuleFactory(runID).getDataModules(); }

JPetDataModuleFactory& JPetParamManager::getDataModuleFactory(const int runID)
{
  if (fDataModuleFactories.count(runID) == 0)
  {
    fDataModuleFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                                 std::forward_as_tuple(*fParamGetter, runID, getDataSourceFactory(runID)));
  }
  return fDataModuleFactories.at(runID);
}

void JPetParamManager::fillParameterBank(const int run)
{
  if (fBank)
  {
    delete fBank;
    fBank = 0;
  }
  fBank = new JPetParamBank();
  if (!fExpectMissing.count(ParamObjectType::kTRB))
  {
    for (auto& trbp : getTRBs(run))
    {
      auto& trb = *trbp.second;
      fBank->addTRB(trb);
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kFEB))
  {
    for (auto& febp : getFEBs(run))
    {
      auto& feb = *febp.second;
      fBank->addFEB(feb);
      fBank->getFEB(feb.getID()).setTRB(fBank->getTRB(feb.getTRB().getID()));
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kFrame))
  {
    for (auto& framep : getFrames(run))
    {
      auto& frame = *framep.second;
      fBank->addFrame(frame);
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kLayer))
  {
    for (auto& layerp : getLayers(run))
    {
      auto& layer = *layerp.second;
      fBank->addLayer(layer);
      fBank->getLayer(layer.getID()).setFrame(fBank->getFrame(layer.getFrame().getID()));
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kBarrelSlot))
  {
    for (auto& barrelSlotp : getBarrelSlots(run))
    {
      auto& barrelSlot = *barrelSlotp.second;
      fBank->addBarrelSlot(barrelSlot);
      if (barrelSlot.hasLayer())
      {
        fBank->getBarrelSlot(barrelSlot.getID()).setLayer(fBank->getLayer(barrelSlot.getLayer().getID()));
      }
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kScintillator))
  {
    for (auto& scinp : getScins(run))
    {
      auto& scin = *scinp.second;
      fBank->addScintillator(scin);
      fBank->getScintillator(scin.getID()).setBarrelSlot(fBank->getBarrelSlot(scin.getBarrelSlot().getID()));
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kPM))
  {
    for (auto& pmp : getPMs(run))
    {
      auto& pm = *pmp.second;
      fBank->addPM(pm);
      if (pm.hasFEB())
      {
        fBank->getPM(pm.getID()).setFEB(fBank->getFEB(pm.getFEB().getID()));
      }
      fBank->getPM(pm.getID()).setScin(fBank->getScintillator(pm.getScin().getID()));
      fBank->getPM(pm.getID()).setBarrelSlot(fBank->getBarrelSlot(pm.getBarrelSlot().getID()));
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kTOMBChannel))
  {
    for (auto& tombChannelp : getTOMBChannels(run))
    {
      auto& tombChannel = *tombChannelp.second;
      fBank->addTOMBChannel(tombChannel);
      fBank->getTOMBChannel(tombChannel.getChannel()).setFEB(fBank->getFEB(tombChannel.getFEB().getID()));
      fBank->getTOMBChannel(tombChannel.getChannel()).setTRB(fBank->getTRB(tombChannel.getTRB().getID()));
      fBank->getTOMBChannel(tombChannel.getChannel()).setPM(fBank->getPM(tombChannel.getPM().getID()));
    }
  }

  if (!fExpectMissing.count(ParamObjectType::kDataSource))
  {
    for (auto& dataSourceElement : getDataSources(run))
    {
      auto& dataSource = *dataSourceElement.second;
      fBank->addDataSource(dataSource);
    }
  }

  if (!fExpectMissing.count(ParamObjectType::kDataModule))
  {
    for (auto& dataModuleElement : getDataModules(run))
    {
      auto& dataModule = *dataModuleElement.second;
      fBank->addDataModule(dataModule);
      fBank->getDataModule(dataModule.getID()).setDataSource(fBank->getDataSource(dataModule.getDataSource().getID()));
    }
  }
}

bool JPetParamManager::readParametersFromFile(JPetReader* reader)
{
  assert(reader);
  if (!reader->isOpen())
  {
    ERROR("Cannot read parameters from file. The provided JPetReader is closed.");
    return false;
  }
  fBank = static_cast<JPetParamBank*>(reader->getObjectFromFile("ParamBank;1"));
  if (!fBank)
    return false;
  return true;
}

bool JPetParamManager::saveParametersToFile(JPetWriter* writer)
{
  assert(writer);
  if (!writer->isOpen())
  {
    ERROR("Could not write parameters to file. The provided JPetWriter is closed.");
    return false;
  }
  writer->writeObject(fBank, "ParamBank");
  return true;
}

bool JPetParamManager::readParametersFromFile(std::string filename)
{
  TFile file(filename.c_str(), "READ");
  if (!file.IsOpen())
  {
    ERROR("Could not read from file.");
    return false;
  }
  fBank = static_cast<JPetParamBank*>(file.Get("ParamBank;1"));
  if (!fBank)
    return false;
  return true;
}

const JPetParamBank& JPetParamManager::getParamBank() const
{
  DEBUG("getParamBank() from JPetParamManager");
  static JPetParamBank DummyResult(true);
  if (fBank)
    return *fBank;
  else
    return DummyResult;
}

bool JPetParamManager::saveParametersToFile(std::string filename)
{
  TFile file(filename.c_str(), "UPDATE");
  if (!file.IsOpen())
  {
    ERROR("Could not write to file.");
    return false;
  }
  file.cd();
  assert(fBank);
  file.WriteObject(fBank, "ParamBank");
  return true;
}

void JPetParamManager::clearParameters()
{
  assert(fBank);
  fBank->clear();
}

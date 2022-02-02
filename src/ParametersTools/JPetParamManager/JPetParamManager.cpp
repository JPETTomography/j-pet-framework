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
      expectMissing.insert(ParamObjectType::kSetup);
      expectMissing.insert(ParamObjectType::kLayer);
      expectMissing.insert(ParamObjectType::kChannel);
      expectMissing.insert(ParamObjectType::kDataSource);
      expectMissing.insert(ParamObjectType::kDataModule);
    }
    if (file_type_checker::getInputFileType(options) == file_type_checker::kMCGeant)
    {
      expectMissing.insert(ParamObjectType::kMatrix);
      expectMissing.insert(ParamObjectType::kPM);
      expectMissing.insert(ParamObjectType::kChannel);
      expectMissing.insert(ParamObjectType::kDataSource);
      expectMissing.insert(ParamObjectType::kDataModule);
    }
    return std::make_shared<JPetParamManager>(new JPetParamGetterAscii(getLocalDB(options)), expectMissing);
  }
  else
  {
    ERROR(Form("No local database file found: %s", getLocalDB(options).c_str()));
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

std::map<int, JPetSetup*>& JPetParamManager::getSetups(const int runID) { return getSetupFactory(runID).getSetups(); }

JPetSetupFactory& JPetParamManager::getSetupFactory(const int runID)
{
  if (fSetupFactories.count(runID) == 0)
  {
    fSetupFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID), std::forward_as_tuple(*fParamGetter, runID));
  }
  return fSetupFactories.at(runID);
}

std::map<int, JPetLayer*>& JPetParamManager::getLayers(const int runID) { return getLayerFactory(runID).getLayers(); }

JPetLayerFactory& JPetParamManager::getLayerFactory(const int runID)
{
  if (fLayerFactories.count(runID) == 0)
  {
    fLayerFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                            std::forward_as_tuple(*fParamGetter, runID, getSetupFactory(runID)));
  }
  return fLayerFactories.at(runID);
}

std::map<int, JPetSlot*>& JPetParamManager::getSlots(const int runID) { return getSlotFactory(runID).getSlots(); }

JPetSlotFactory& JPetParamManager::getSlotFactory(const int runID)
{
  if (fSlotFactories.count(runID) == 0)
  {
    fSlotFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                           std::forward_as_tuple(*fParamGetter, runID, getLayerFactory(runID)));
  }
  fSlotFactories.at(runID);
  return fSlotFactories.at(runID);
}

std::map<int, JPetScin*>& JPetParamManager::getScins(const int runID) { return getScinFactory(runID).getScins(); }

JPetScinFactory& JPetParamManager::getScinFactory(const int runID)
{
  if (fScinFactories.count(runID) == 0)
  {
    fScinFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                           std::forward_as_tuple(*fParamGetter, runID, getSlotFactory(runID)));
  }
  return fScinFactories.at(runID);
}

std::map<int, JPetMatrix*>& JPetParamManager::getMatrices(const int runID) { return getMatrixFactory(runID).getMatrices(); }

JPetMatrixFactory& JPetParamManager::getMatrixFactory(const int runID)
{
  if (fMatrixFactories.count(runID) == 0)
  {
    fMatrixFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                             std::forward_as_tuple(*fParamGetter, runID, getScinFactory(runID)));
  }
  return fMatrixFactories.at(runID);
}

std::map<int, JPetPM*>& JPetParamManager::getPMs(const int runID) { return getPMFactory(runID).getPMs(); }

JPetPMFactory& JPetParamManager::getPMFactory(const int runID)
{
  if (fPMFactories.count(runID) == 0)
  {
    fPMFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                         std::forward_as_tuple(*fParamGetter, runID, getMatrixFactory(runID)));
  }
  return fPMFactories.at(runID);
}

std::map<int, JPetChannel*>& JPetParamManager::getChannels(const int runID) { return getChannelFactory(runID).getChannels(); }

JPetChannelFactory& JPetParamManager::getChannelFactory(const int runID)
{
  if (fChannelFactories.count(runID) == 0)
  {
    fChannelFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runID),
                              std::forward_as_tuple(*fParamGetter, runID, getPMFactory(runID), getDataModuleFactory(runID)));
  }
  return fChannelFactories.at(runID);
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

void JPetParamManager::fillParameterBank(const int runID)
{
  if (fBank)
  {
    delete fBank;
    fBank = 0;
  }
  fBank = new JPetParamBank();
  if (!fExpectMissing.count(ParamObjectType::kSetup))
  {
    for (auto& setup_p : getSetups(runID))
    {
      auto& setup = *setup_p.second;
      fBank->addSetup(setup);
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kLayer))
  {
    for (auto& layer_p : getLayers(runID))
    {
      auto& layer = *layer_p.second;
      fBank->addLayer(layer);
      if (!fExpectMissing.count(ParamObjectType::kSetup))
      {
        fBank->getLayer(layer.getID()).setSetup(fBank->getSetup(layer.getSetup().getID()));
      }
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kSlot))
  {
    for (auto& slot_p : getSlots(runID))
    {
      auto& slot = *slot_p.second;
      fBank->addSlot(slot);
      if (!fExpectMissing.count(ParamObjectType::kLayer))
      {
        fBank->getSlot(slot.getID()).setLayer(fBank->getLayer(slot.getLayer().getID()));
      }
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kScin))
  {
    for (auto& scin_p : getScins(runID))
    {
      auto& scin = *scin_p.second;
      fBank->addScin(scin);
      if (!fExpectMissing.count(ParamObjectType::kSlot))
      {
        fBank->getScin(scin.getID()).setSlot(fBank->getSlot(scin.getSlot().getID()));
      }
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kMatrix))
  {
    for (auto& mtx_p : getMatrices(runID))
    {
      auto& mtx = *mtx_p.second;
      fBank->addMatrix(mtx);
      if (!fExpectMissing.count(ParamObjectType::kScin))
      {
        fBank->getMatrix(mtx.getID()).setScin(fBank->getScin(mtx.getScin().getID()));
      }
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kPM))
  {
    for (auto& pm_p : getPMs(runID))
    {
      auto& pm = *pm_p.second;
      fBank->addPM(pm);
      if (!fExpectMissing.count(ParamObjectType::kMatrix))
      {
        fBank->getPM(pm.getID()).setMatrix(fBank->getMatrix(pm.getMatrix().getID()));
      }
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kChannel))
  {
    for (auto& channel_p : getChannels(runID))
    {
      auto& channel = *channel_p.second;
      fBank->addChannel(channel);
      if (!fExpectMissing.count(ParamObjectType::kPM))
      {
        fBank->getChannel(channel.getID()).setPM(fBank->getPM(channel.getPM().getID()));
      }
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kDataSource))
  {
    for (auto& dataSourceElement : getDataSources(runID))
    {
      auto& dataSource = *dataSourceElement.second;
      fBank->addDataSource(dataSource);
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kDataModule))
  {
    for (auto& dataModuleElement : getDataModules(runID))
    {
      auto& dataModule = *dataModuleElement.second;
      fBank->addDataModule(dataModule);
      if (!fExpectMissing.count(ParamObjectType::kDataSource))
      {
        fBank->getDataModule(dataModule.getID()).setDataSource(fBank->getDataSource(dataModule.getDataSource().getID()));
      }
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
  fBank = static_cast<JPetParamBank*>(reader->getObjectFromFile("ParamBank"));
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
  fBank = static_cast<JPetParamBank*>(file.Get("ParamBank"));
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
  file.WriteObject(fBank, "ParamBank;1");
  return true;
}

void JPetParamManager::clearParameters()
{
  assert(fBank);
  fBank->clear();
}

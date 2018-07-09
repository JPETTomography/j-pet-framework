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
 *  @file JPetParamManager.cpp
 */

#include "./JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "./JPetOptionsTools/JPetOptionsTools.h"
#include <boost/property_tree/xml_parser.hpp>
#include "JPetParamManager.h"
#include <TFile.h>

std::shared_ptr<JPetParamManager> JPetParamManager::generateParamManager(
  const std::map<std::string, boost::any>& options)
{
  using namespace jpet_options_tools;
  if (isLocalDB(options)) {
    std::set<ParamObjectType> expectMissing;
    if (FileTypeChecker::getInputFileType(options) == FileTypeChecker::kScope) {
      expectMissing.insert(ParamObjectType::kTRB);
      expectMissing.insert(ParamObjectType::kFEB);
      expectMissing.insert(ParamObjectType::kFrame);
      expectMissing.insert(ParamObjectType::kLayer);
      expectMissing.insert(ParamObjectType::kTOMBChannel);
    }
    return std::make_shared<JPetParamManager>(new JPetParamGetterAscii(getLocalDB(options)), expectMissing);
  } else {
    ERROR("No local database file found.");
    return std::make_shared<JPetParamManager>();
  }
}

JPetParamManager::~JPetParamManager()
{
  if (fBank) {
    delete fBank;
    fBank = 0;
  }
  if (fParamGetter) {
    delete fParamGetter;
    fParamGetter = 0;
  }
}

std::map<int, JPetTRB*>& JPetParamManager::getTRBs(const int runId)
{
  return getTRBFactory(runId).getTRBs();
}

JPetTRBFactory& JPetParamManager::getTRBFactory(const int runId)
{
  if (fTRBFactories.count(runId) == 0) {
    fTRBFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runId), std::forward_as_tuple(*fParamGetter, runId));
  }
  return fTRBFactories.at(runId);
}

std::map<int, JPetFEB*>& JPetParamManager::getFEBs(const int runId)
{
  return getFEBFactory(runId).getFEBs();
}

JPetFEBFactory& JPetParamManager::getFEBFactory(const int runId)
{
  if (fFEBFactories.count(runId) == 0) {
    fFEBFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runId), std::forward_as_tuple(*fParamGetter, runId, getTRBFactory(runId)));
  }
  return fFEBFactories.at(runId);
}

std::map<int, JPetFrame*>& JPetParamManager::getFrames(const int runId)
{
  return getFrameFactory(runId).getFrames();
}

JPetFrameFactory& JPetParamManager::getFrameFactory(const int runId)
{
  if (fFrameFactories.count(runId) == 0) {
    fFrameFactories.emplace(std::piecewise_construct, std::forward_as_tuple(runId), std::forward_as_tuple(*fParamGetter, runId));
  }
  return fFrameFactories.at(runId);
}

std::map<int, JPetLayer*>& JPetParamManager::getLayers(const int runId)
{
  return getLayerFactory(runId).getLayers();
}

JPetLayerFactory& JPetParamManager::getLayerFactory(const int runId)
{
  if (fLayerFactories.count(runId) == 0) {
    fLayerFactories.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(runId),
      std::forward_as_tuple(*fParamGetter, runId, getFrameFactory(runId))
    );
  }
  return fLayerFactories.at(runId);
}

std::map<int, JPetBarrelSlot*>& JPetParamManager::getBarrelSlots(const int runId)
{
  return getBarrelSlotFactory(runId).getBarrelSlots();
}

JPetBarrelSlotFactory& JPetParamManager::getBarrelSlotFactory(const int runId)
{
  if (fBarrelSlotFactories.count(runId) == 0) {
    fBarrelSlotFactories.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(runId),
      std::forward_as_tuple(*fParamGetter, runId, getLayerFactory(runId))
    );
  }
  fBarrelSlotFactories.at(runId);
  return fBarrelSlotFactories.at(runId);
}

std::map<int, JPetScin*>& JPetParamManager::getScins(const int runId)
{
  return getScinFactory(runId).getScins();
}

JPetScinFactory& JPetParamManager::getScinFactory(const int runId)
{
  if (fScinFactories.count(runId) == 0) {
    fScinFactories.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(runId),
      std::forward_as_tuple(*fParamGetter, runId, getBarrelSlotFactory(runId))
    );
  }
  return fScinFactories.at(runId);
}

std::map<int, JPetPM*>& JPetParamManager::getPMs(const int runId)
{
  return getPMFactory(runId).getPMs();
}

JPetPMFactory& JPetParamManager::getPMFactory(const int runId)
{
  if (fPMFactories.count(runId) == 0) {
    fPMFactories.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(runId),
      std::forward_as_tuple(
        *fParamGetter,
        runId,
        getFEBFactory(runId),
        getScinFactory(runId),
        getBarrelSlotFactory(runId)
      )
    );
  }
  return fPMFactories.at(runId);
}

std::map<int, JPetTOMBChannel*>& JPetParamManager::getTOMBChannels(const int runId)
{
  return getTOMBChannelFactory(runId).getTOMBChannels();
}

JPetTOMBChannelFactory& JPetParamManager::getTOMBChannelFactory(const int runId)
{
  if (fTOMBChannelFactories.count(runId) == 0) {
    fTOMBChannelFactories.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(runId),
      std::forward_as_tuple(
        *fParamGetter,
        runId,
        getFEBFactory(runId),
        getTRBFactory(runId),
        getPMFactory(runId)
      )
    );
  }
  return fTOMBChannelFactories.at(runId);
}

void JPetParamManager::fillParameterBank(const int run)
{
  if (fBank) {
    delete fBank;
    fBank = 0;
  }
  fBank = new JPetParamBank();
  if (!fExpectMissing.count(ParamObjectType::kTRB)) {
    for (auto& trbp : getTRBs(run)) {
      auto& trb = *trbp.second;
      fBank->addTRB(trb);
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kFEB)) {
    for (auto& febp : getFEBs(run)) {
      auto& feb = *febp.second;
      fBank->addFEB(feb);
      fBank->getFEB(feb.getID()).setTRB(fBank->getTRB(feb.getTRB().getID()));
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kFrame)) {
    for (auto& framep : getFrames(run)) {
      auto& frame = *framep.second;
      fBank->addFrame(frame);
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kLayer)) {
    for (auto& layerp : getLayers(run)) {
      auto& layer = *layerp.second;
      fBank->addLayer(layer);
      fBank->getLayer(layer.getID()).setFrame(fBank->getFrame(layer.getFrame().getID()));
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kBarrelSlot)) {
    for (auto& barrelSlotp : getBarrelSlots(run)) {
      auto& barrelSlot = *barrelSlotp.second;
      fBank->addBarrelSlot(barrelSlot);
      if (barrelSlot.hasLayer()) {
        fBank->getBarrelSlot(barrelSlot.getID()).setLayer(fBank->getLayer(barrelSlot.getLayer().getID()));
      }
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kScintillator)) {
    for (auto& scinp : getScins(run)) {
      auto& scin = *scinp.second;
      fBank->addScintillator(scin);
      fBank->getScintillator(scin.getID()).setBarrelSlot(
        fBank->getBarrelSlot(scin.getBarrelSlot().getID())
      );
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kPM)) {
    for (auto& pmp : getPMs(run)) {
      auto& pm = *pmp.second;
      fBank->addPM(pm);
      if (pm.hasFEB()) {
        fBank->getPM(pm.getID()).setFEB(fBank->getFEB(pm.getFEB().getID()));
      }
      fBank->getPM(pm.getID()).setScin(fBank->getScintillator(pm.getScin().getID()));
      fBank->getPM(pm.getID()).setBarrelSlot(
        fBank->getBarrelSlot(pm.getBarrelSlot().getID())
      );
    }
  }
  if (!fExpectMissing.count(ParamObjectType::kTOMBChannel)) {
    for (auto& tombChannelp : getTOMBChannels(run)) {
      auto& tombChannel = *tombChannelp.second;
      fBank->addTOMBChannel(tombChannel);
      fBank->getTOMBChannel(tombChannel.getChannel()).setFEB(
        fBank->getFEB(tombChannel.getFEB().getID())
      );
      fBank->getTOMBChannel(tombChannel.getChannel()).setTRB(
        fBank->getTRB(tombChannel.getTRB().getID())
      );
      fBank->getTOMBChannel(tombChannel.getChannel()).setPM(
        fBank->getPM(tombChannel.getPM().getID())
      );
    }
  }
}

bool JPetParamManager::readParametersFromFile(JPetReader* reader)
{
  assert(reader);
  if (!reader->isOpen()) {
    ERROR("Cannot read parameters from file. The provided JPetReader is closed.");
    return false;
  }
  fBank = static_cast<JPetParamBank*>(reader->getObjectFromFile("ParamBank"));
  if (!fBank) return false;
  return true;
}

bool JPetParamManager::saveParametersToFile(JPetWriter* writer)
{
  assert(writer);
  if (!writer->isOpen()) {
    ERROR("Could not write parameters to file. The provided JPetWriter is closed.");
    return false;
  }
  writer->writeObject(fBank, "ParamBank");
  return true;
}

bool JPetParamManager::readParametersFromFile(std::string filename)
{
  TFile file(filename.c_str(), "READ");
  if (!file.IsOpen()) {
    ERROR("Could not read from file.");
    return false;
  }
  fBank = static_cast<JPetParamBank*>(file.Get("ParamBank"));
  if (!fBank) return false;
  return true;
}

const JPetParamBank& JPetParamManager::getParamBank() const
{
  DEBUG("getParamBank() from JPetParamManager");
  static JPetParamBank DummyResult(true);
  if (fBank) return *fBank;
  else return DummyResult;
}

bool JPetParamManager::saveParametersToFile(std::string filename)
{
  TFile file(filename.c_str(), "UPDATE");
  if (!file.IsOpen()) {
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

void JPetParamManager::createXMLFile(const std::string& channelDataFileName,
  int channelOffset, int numberOfChannels)
{
  using boost::property_tree::ptree;
  ptree pt;
  std::string debug = "OFF";
  std::string dataSourceType = "TRB3_S";
  std::string dataSourceTrbNetAddress = "8000";
  std::string dataSourceHubAddress = "8000";
  std::string dataSourceReferenceChannel = "0";
  std::string dataSourceCorrectionFile = "raw";
  pt.put("READOUT.DEBUG", debug);
  pt.put("READOUT.DATA_SOURCE.TYPE", dataSourceType);
  pt.put("READOUT.DATA_SOURCE.TRBNET_ADDRESS", dataSourceTrbNetAddress);
  pt.put("READOUT.DATA_SOURCE.HUB_ADDRESS", dataSourceHubAddress);
  pt.put("READOUT.DATA_SOURCE.REFERENCE_CHANNEL", dataSourceReferenceChannel);
  pt.put("READOUT.DATA_SOURCE.CORRECTION_FILE", dataSourceCorrectionFile);
  ptree& externalNode = pt.add("READOUT.DATA_SOURCE.MODULES", "");
  ptree& internalNode = externalNode.add("MODULE", "");
  internalNode.put("TYPE", "LATTICE_TDC");
  internalNode.put("TRBNET_ADDRESS", "e000");
  internalNode.put("NUMBER_OF_CHANNELS", numberOfChannels);
  internalNode.put("CHANNEL_OFFSET", channelOffset);
  internalNode.put("RESOLUTION", "100");
  internalNode.put("MEASUREMENT_TYPE", "TDC");
  write_xml(channelDataFileName, pt);
}

void JPetParamManager::getTOMBDataAndCreateXMLFile(const int p_run_id)
{
  fillParameterBank(p_run_id);
  int TOMBChannelsSize = fBank->getTOMBChannelsSize();
  int channelOffset = 0;
  int numberOfChannels = 0;
  if (TOMBChannelsSize) {
    for (int i = 0; i < TOMBChannelsSize; ++i) {
      if (i == 0) {
        std::string description = fBank->getTOMBChannel(i).getDescription();
        channelOffset = JPetParamGetter::getTOMBChannelFromDescription(description);
      }
      ++numberOfChannels;
    }
    createXMLFile("conf.xml", channelOffset, numberOfChannels);
    return;
  }
  ERROR("TOMBChannelsSize is equal to zero.");
}

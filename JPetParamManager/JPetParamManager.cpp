/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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

#include "JPetParamManager.h"

#include <TFile.h>
#include <boost/property_tree/xml_parser.hpp>

using namespace std;


JPetParamManager::JPetParamManager(bool isNull):
  fParamGetter(new JPetDBParamGetter()),
  fBank(0),
  fIsNullObject(isNull)
{
  /* */
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

void JPetParamManager::fillParameterBank(const int run)
{
  if (fBank) {
    delete fBank;
    fBank = 0;
  }
  fBank = fParamGetter->generateParamBank(run);
}

bool JPetParamManager::readParametersFromFile(JPetReader * reader)
{
  if (!reader->isOpen()) {
    ERROR("Cannot read parameters from file. The provided JPetReader is closed.");
    return false;
  }
  fBank = static_cast<JPetParamBank*>(reader->getObject("ParamBank"));

  if (!fBank) return false;
  return true;
}

bool JPetParamManager::saveParametersToFile(JPetWriter * writer)
{
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

const JPetParamBank& JPetParamManager::getParamBank() const{
	static JPetParamBank DummyResult(true);
	if(fBank)return *fBank;
	else return DummyResult;
}


bool JPetParamManager::getParametersFromScopeConfig(const scope_config::Config& config)
{
  if (fBank) {
    delete fBank;
    fBank = 0;
  }
  fBank = fScopeParamGetter.generateParamBank(config);
  if (!fBank) return false;
  return true;
}

bool JPetParamManager::saveParametersToFile(std::string filename)
{
  TFile file(filename.c_str(), "UPDATE");
  if (!file.IsOpen()) {
    ERROR("Could not write to file.");
    return false;
  }
  file.cd();
  file.WriteObject(fBank, "ParamBank");
  return true;
}

void JPetParamManager::clearParameters()
{
  assert(fBank);
  fBank->clear();
}

void JPetParamManager::createXMLFile(const std::string &channelDataFileName, int channelOffset, int numberOfChannels)
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
  
  ptree &externalNode = pt.add("READOUT.DATA_SOURCE.MODULES", "");
  
  ptree &internalNode = externalNode.add("MODULE", "");
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
  
  if(TOMBChannelsSize)
  {
    for(int i=0;i<TOMBChannelsSize;++i)
    {
      if(i==0)
      {
        std::string description = fBank->getTOMBChannel(i).getDescription();
        channelOffset = JPetParamBank::getTOMBChannelFromDescription(description);
      }
      ++numberOfChannels;
    }
    createXMLFile("conf.xml", channelOffset, numberOfChannels);
    return;
  }
  ERROR("TOMBChannelsSize is equal to zero.");
}

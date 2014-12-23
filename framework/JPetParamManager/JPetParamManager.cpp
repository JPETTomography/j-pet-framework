#include "JPetParamManager.h"

#include <TFile.h>
#include <boost/property_tree/xml_parser.hpp>

using namespace std;


JPetParamManager::JPetParamManager():
  fBank(0)
{
  /* */
}

/// @param DBConfigFile configuration file with the database connection settings
JPetParamManager::JPetParamManager(const char* dBConfigFile):
  fDBParamGetter(dBConfigFile),
  fBank(0)
{
}

JPetParamManager::~JPetParamManager()
{
  if (fBank) {
    delete fBank;
    fBank = 0;
  }
}

void JPetParamManager::getParametersFromDatabase(const int run)
{
  if (fBank) {
    delete fBank;
    fBank = 0;
  }
  fBank = fDBParamGetter.generateParamBank(run);
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

bool JPetParamManager::readParametersFromFile(const char* filename)
{
  TFile file(filename, "READ");
  if (!file.IsOpen()) {
    ERROR("Could not read from file.");
    return false;
  }
  fBank = static_cast<JPetParamBank*>(file.Get("ParamBank"));

  if (!fBank) return false;
  return true;
}

bool JPetParamManager::saveParametersToFile(const char* filename)
{
  TFile file(filename, "UPDATE");
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
  fDBParamGetter.fillTOMBChannels(p_run_id, *fBank);//private (add friend)
  int TOMBChannelsSize = fBank->getTOMBChannelsSize();
  int channelOffset = 0;
  int numberOfChannels = 0;
  
  if(TOMBChannelsSize)
  {
    for(unsigned int i=0;i<TOMBChannelsSize;++i)
    {
      if(i==0)
      {
	std::string description = fBank->getTOMBChannel(i).getDescription();
	channelOffset = fDBParamGetter.getTOMBChannelFromDescription(description);//private (add friend)
      }
      ++numberOfChannels;
    }
    createXMLFile("conf.xml", channelOffset, numberOfChannels);
    return;
  }
  ERROR("TOMBChannelsSize is equal to zero.");
}

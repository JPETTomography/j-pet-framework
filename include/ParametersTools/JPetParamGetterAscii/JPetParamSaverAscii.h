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
 *  @file JPetParamSaverAscii.h
 */

#ifndef JPETPARAMSAVERASCII_H
#define JPETPARAMSAVERASCII_H

#include "JPetParamBank/JPetParamBank.h"
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <string>

class JPetParamSaverAscii
{
public:
  JPetParamSaverAscii() {}
  void saveParamBank(const JPetParamBank& bank, const int runNumber, const std::string& filename);

private:
  JPetParamSaverAscii(const JPetParamSaverAscii& paramSaver);
  JPetParamSaverAscii& operator=(const JPetParamSaverAscii& paramSaver);
  boost::property_tree::ptree getTreeFromFile(const std::string& filename);
  void addToTree(boost::property_tree::ptree& tree, const JPetParamBank& bank, const std::string& runNumber);

  void fillSetups(boost::property_tree::ptree& runContents, const JPetParamBank& bank);
  void fillLayers(boost::property_tree::ptree& runContents, const JPetParamBank& bank);
  void fillSlots(boost::property_tree::ptree& runContents, const JPetParamBank& bank);
  void fillScins(boost::property_tree::ptree& runContents, const JPetParamBank& bank);
  void fillMatrices(boost::property_tree::ptree& runContents, const JPetParamBank& bank);
  void fillPMs(boost::property_tree::ptree& runContents, const JPetParamBank& bank);
  void fillChannels(boost::property_tree::ptree& runContents, const JPetParamBank& bank);
  void fillDataSources(boost::property_tree::ptree& runContents, const JPetParamBank& bank);
  void fillDataModules(boost::property_tree::ptree& runContents, const JPetParamBank& bank);

  boost::property_tree::ptree setupToInfo(const JPetSetup& setup);
  boost::property_tree::ptree layerToInfo(const JPetLayer& layer);
  boost::property_tree::ptree slotToInfo(const JPetSlot& slot);
  boost::property_tree::ptree scinToInfo(const JPetScin& scin);
  boost::property_tree::ptree matrixToInfo(const JPetMatrix& mtx);
  boost::property_tree::ptree pmToInfo(const JPetPM& pm);
  boost::property_tree::ptree channelToInfo(const JPetChannel& channel);
  boost::property_tree::ptree dataSourceToInfo(const JPetDataSource& dataSource);
  boost::property_tree::ptree dataModuleToInfo(const JPetDataModule& dataModule);
};

#endif /* !JPETPARAMSAVERASCII_H */

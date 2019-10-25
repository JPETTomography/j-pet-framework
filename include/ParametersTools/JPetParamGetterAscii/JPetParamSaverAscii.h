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
 *  @file JPetParamGetterAscii.h
 */

#ifndef JPETPARAMSAVERASCII_H
#define JPETPARAMSAVERASCII_H

#include "./JPetParamBank/JPetParamBank.h"
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <map>

class JPetParamSaverAscii
{
public:
  JPetParamSaverAscii() {}
  void saveParamBank(const JPetParamBank & bank, const int runNumber, const std::string & filename);

private:
  JPetParamSaverAscii(const JPetParamSaverAscii &paramSaver);
  JPetParamSaverAscii& operator=(const JPetParamSaverAscii &paramSaver);
  boost::property_tree::ptree getTreeFromFile(const std::string & filename);
  void addToTree(boost::property_tree::ptree & tree, const JPetParamBank & bank, const std::string & runNumber);
  void fillScintillators(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
  void fillPMs(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
  void fillBarrelSlots(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
  void fillLayers(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
  void fillFrames(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
  void fillFEBs(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
  void fillTRBs(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
  void fillTOMBChannels(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
  boost::property_tree::ptree scintillatorToInfo(const JPetScin & scin);
  boost::property_tree::ptree PMToInfo(const JPetPM & pm);
  boost::property_tree::ptree barrelSlotToInfo(const JPetBarrelSlot & bs);
  boost::property_tree::ptree layerToInfo(const JPetLayer & layer);
  boost::property_tree::ptree frameToInfo(const JPetFrame & frame);
  boost::property_tree::ptree FEBToInfo(const JPetFEB & feb);
  boost::property_tree::ptree TRBToInfo(const JPetTRB & trb);
  boost::property_tree::ptree TOMBChannelToInfo(const JPetTOMBChannel & tomb);
};

#endif /* !JPETPARAMSAVERASCII_H */

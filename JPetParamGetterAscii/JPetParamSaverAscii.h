/**
 *  @copyright Copyright (c) 2015, J-PET collaboration
 *  @file JPetParamGetterAscii.h
 *  @author Tomasz Kisielewski, tymorl@gmail.com
 *  @brief Class to save a parameter bank to an ASCII file in the JSON format.
 */

#ifndef JPETPARAMSAVERASCII_H
#define JPETPARAMSAVERASCII_H

#include<map>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include "../JPetParamBank/JPetParamBank.h"

class JPetParamSaverAscii {
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
		void fillPMCalibs(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
		void fillBarrelSlots(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
		void fillLayers(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
		void fillFrames(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
		void fillFEBs(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
		void fillTRBs(boost::property_tree::ptree & runContents, const JPetParamBank & bank);
		void fillTOMBChannels(boost::property_tree::ptree & runContents, const JPetParamBank & bank);

		boost::property_tree::ptree scintillatorToInfo(const JPetScin & scin);
		boost::property_tree::ptree PMToInfo(const JPetPM & pm);
		boost::property_tree::ptree PMCalibToInfo(const JPetPMCalib & pmCalib);
		boost::property_tree::ptree barrelSlotToInfo(const JPetBarrelSlot & bs);
		boost::property_tree::ptree layerToInfo(const JPetLayer & layer);
		boost::property_tree::ptree frameToInfo(const JPetFrame & frame);
		boost::property_tree::ptree FEBToInfo(const JPetFEB & feb);
		boost::property_tree::ptree TRBToInfo(const JPetTRB & trb);
		boost::property_tree::ptree TOMBChannelToInfo(const JPetTOMBChannel & tomb);

};

#endif /*  !JPETPARAMSAVERASCII_H */

/**
 *  @copyright Copyright (c) 2015, J-PET collaboration
 *  @file JPetParamGetterAscii.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief Class to generate parameter bank based on ASCII file content.
 */ 

#ifndef JPETPARAMGETTERASCII_H 
#define JPETPARAMGETTERASCII_H 

#include <map>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include "../JPetParamBank/JPetParamBank.h"

class JPetParamGetterAscii : public JPetParamGetter {
public:
  JPetParamGetterAscii(const char* filename) : filename(filename) {}
  JPetParamBank* generateParamBank(const int runNumber);

private:
  JPetParamGetterAscii(const JPetParamGetterAscii &paramGetterAscii);
  JPetParamGetterAscii& operator=(const JPetParamGetterAscii &paramGetterAscii);

  JPetParamBank* loadFileContent(int runNumber);

		void fillScintillators(boost::property_tree::ptree & runContents, JPetParamBank & bank);
		void fillPMs(boost::property_tree::ptree & runContents, JPetParamBank & bank);
		void fillPMCalibs(boost::property_tree::ptree & runContents, JPetParamBank & bank);
		void fillBarrelSlots(boost::property_tree::ptree & runContents, JPetParamBank & bank);
		void fillLayers(boost::property_tree::ptree & runContents, JPetParamBank & bank);
		void fillFrames(boost::property_tree::ptree & runContents, JPetParamBank & bank);
		void fillFEBs(boost::property_tree::ptree & runContents, JPetParamBank & bank);
		void fillTRBs(boost::property_tree::ptree & runContents, JPetParamBank & bank);
		void fillTOMBChannels(boost::property_tree::ptree & runContents, JPetParamBank & bank);

		JPetScin scintillatorFromInfo(boost::property_tree::ptree & info);
		JPetPM PMFromInfo(boost::property_tree::ptree & info);
		JPetPMCalib PMCalibFromInfo(boost::property_tree::ptree & info);
		JPetBarrelSlot barrelSlotFromInfo(boost::property_tree::ptree & info);
		JPetLayer layerFromInfo(boost::property_tree::ptree & info);
		JPetFrame frameFromInfo(boost::property_tree::ptree & info);
		JPetFEB FEBFromInfo(boost::property_tree::ptree & info);
		JPetTRB TRBFromInfo(boost::property_tree::ptree & info);
		JPetTOMBChannel TOMBChannelFromInfo(boost::property_tree::ptree & info);

		std::map<int, int> scintillatorIdTranslation(JPetParamBank & bank);
		std::map<int, int> PMIdTranslation(JPetParamBank & bank);
		std::map<int, int> barrelSlotIdTranslation(JPetParamBank & bank);
		std::map<int, int> layerIdTranslation(JPetParamBank & bank);
		std::map<int, int> frameIdTranslation(JPetParamBank & bank);
		std::map<int, int> FEBIdTranslation(JPetParamBank & bank);
		std::map<int, int> TRBIdTranslation(JPetParamBank & bank);
		std::map<int, int> TOMBChannelIdTranslation(JPetParamBank & bank);

		void fillScintillatorTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank, std::map<std::string, std::map<int, int> > & idTranslations);
		void fillPMTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank, std::map<std::string, std::map<int, int> > & idTranslations);
		void fillBarrelSlotTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank, std::map<std::string, std::map<int, int> > & idTranslations);
		void fillLayerTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank, std::map<std::string, std::map<int, int> > & idTranslations);
		void fillFEBTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank, std::map<std::string, std::map<int, int> > & idTranslations);
		void fillTOMBChannelTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank, std::map<std::string, std::map<int, int> > & idTranslations);

  std::string filename;

};

#endif /*  !JPETPARAMGETTERASCII_H */

/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetParamGetterAscii.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetParamGetterAscii.h"
#include "./JPetParamAsciiConstants.h"
#include "../JPetParamBank/JPetParamBank.h"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>

JPetParamBank* JPetParamGetterAscii::generateParamBank(const int runNumber)
{
				return loadFileContent(runNumber);
}

/// assuming that file is in json format
//
JPetParamBank* JPetParamGetterAscii::loadFileContent(int runNumber)
{
		std::string runNumberS = boost::lexical_cast<std::string>(runNumber);
  JPetParamBank* bank = 0;
  if (boost::filesystem::exists(filename)) {
    boost::property_tree::ptree dataFromFile;
    boost::property_tree::read_json(filename, dataFromFile);
				if (auto possibleRunContents = dataFromFile.get_child_optional(runNumberS)) {
						auto runContents = *possibleRunContents;
						bank = new JPetParamBank();
						fillScintillators(runContents, *bank);
						fillPMs(runContents, *bank);
						fillPMCalibs(runContents, *bank);
						fillBarrelSlots(runContents, *bank);
						fillLayers(runContents, *bank);
						fillFrames(runContents, *bank);
						fillFEBs(runContents, *bank);
						fillTRBs(runContents, *bank);
						fillTOMBChannels(runContents, *bank);
						//TRefs need to be filled after creating everything.
						//The IDs in the bank don't match the ids in the DB, so we need a translation.
						fillScintillatorTRefs(runContents, *bank);
						fillPMTRefs(runContents, *bank);
						fillBarrelSlotTRefs(runContents, *bank);
						fillLayerTRefs(runContents, *bank);
						fillFEBTRefs(runContents, *bank);
						fillTOMBChannelTRefs(runContents, *bank);
				} else {
						ERROR(std::string("No run with such id:") + runNumberS);
				}
  } else {
    ERROR(std::string("Input file does not exist:") + filename);
  }
  return bank;
}


void JPetParamGetterAscii::fillScintillators(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(scintillatorsName)) {
				auto infos = * possibleInfos;
				for (auto info : infos) {
						bank.addScintillator(scintillatorFromInfo(info.second));
				}
		} else {
				ERROR("No scintillators in the specified run.");
		}
}

void JPetParamGetterAscii::fillScintillatorTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(scintillatorsName)) {
				auto infos = * possibleInfos;
				for (auto infoRaw : infos) {
						auto info = infoRaw.second;
						int id = info.get<int>("id");
						int relId = info.get<int>(barrelSlotsName+"_id");
						bank.getScintillator(id).setBarrelSlot(bank.getBarrelSlot(relId));
				}
		} else {
				ERROR("No scintillators in the specified run.");
		}
}

JPetScin JPetParamGetterAscii::scintillatorFromInfo(boost::property_tree::ptree & info)
{
		int id = info.get<int>("id");
		double attenuationLength = info.get<double>("attenuation_length");
		double length = info.get<double>("length");
		double width = info.get<double>("width");
		double height = info.get<double>("height");
		return JPetScin(id, attenuationLength, length, height, width);
}


void JPetParamGetterAscii::fillPMs(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(PMsName)) {
				auto infos = * possibleInfos;
				for (auto info : infos) {
						bank.addPM(PMFromInfo(info.second));
				}
		} else {
				ERROR("No PMs in the specified run.");
		}
}

void JPetParamGetterAscii::fillPMTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(PMsName)) {
				auto infos = * possibleInfos;
				for (auto infoRaw : infos) {
						auto info = infoRaw.second;
						int id = info.get<int>("id");
						int relId = info.get<int>(barrelSlotsName+"_id");
						bank.getPM(id).setBarrelSlot(bank.getBarrelSlot(relId));
						relId = info.get<int>(FEBsName+"_id");
						bank.getPM(id).setFEB(bank.getFEB(relId));
						relId = info.get<int>(scintillatorsName+"_id");
						bank.getPM(id).setScin(bank.getScintillator(relId));
				}
		} else {
				ERROR("No PMs in the specified run.");
		}
}

JPetPM JPetParamGetterAscii::PMFromInfo(boost::property_tree::ptree & info)
{
		int id = info.get<int>("id");
		JPetPM::Side side = info.get<bool>("is_right_side") ? JPetPM::Side::SideB : JPetPM::Side::SideA;
		JPetPM result;
		result.setID(id);
		result.setSide(side);
		return result;
}


void JPetParamGetterAscii::fillPMCalibs(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(PMCalibsName)) {
				auto infos = * possibleInfos;
				for (auto info : infos) {
						bank.addPMCalib(PMCalibFromInfo(info.second));
				}
		} else {
				ERROR("No PMCalibs in the specified run.");
		}
}

JPetPMCalib JPetParamGetterAscii::PMCalibFromInfo(boost::property_tree::ptree & info)
{
		int id = info.get<int>("id");
		std::string name = info.get<std::string>("name");
		double opthv = info.get<double>("opthv");
		double c2e1 = info.get<double>("c2e1");
		double c2e2 = info.get<double>("c2e2");
		double gainAlpha = info.get<double>("gain_alpha");
		double gainBeta = info.get<double>("gain_beta");
		int assignmentId = info.get<int>("assignment_id");
		int assignmentPMId = info.get<int>("assignment_photomultiplier_id");
		return JPetPMCalib(id, name, opthv, c2e1, c2e2, gainAlpha, gainBeta, assignmentId, assignmentPMId);
}


void JPetParamGetterAscii::fillBarrelSlots(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(barrelSlotsName)) {
				auto infos = * possibleInfos;
				for (auto info : infos) {
						bank.addBarrelSlot(barrelSlotFromInfo(info.second));
				}
		} else {
				ERROR("No barrel slots in the specified run.");
		}
}

void JPetParamGetterAscii::fillBarrelSlotTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(barrelSlotsName)) {
				auto infos = * possibleInfos;
				for (auto infoRaw : infos) {
						auto info = infoRaw.second;
						int id = info.get<int>("id");
						int relId = info.get<int>(layersName+"_id");
						bank.getBarrelSlot(id).setLayer(bank.getLayer(relId));
				}
		} else {
				ERROR("No barrel slots in the specified run.");
		}
}

JPetBarrelSlot JPetParamGetterAscii::barrelSlotFromInfo(boost::property_tree::ptree & info)
{
		int id = info.get<int>("id");
		bool active = info.get<bool>("active");
		std::string name = info.get<std::string>("name");
		double theta1 = info.get<double>("theta1");
		int frameId = info.get<int>("frame_id");
		return JPetBarrelSlot(id, active, name, theta1, frameId);
}


void JPetParamGetterAscii::fillLayers(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(layersName)) {
				auto infos = * possibleInfos;
				for (auto info : infos) {
						bank.addLayer(layerFromInfo(info.second));
				}
		} else {
				ERROR("No layers in the specified run.");
		}
}

void JPetParamGetterAscii::fillLayerTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(layersName)) {
				auto infos = * possibleInfos;
				for (auto infoRaw : infos) {
						auto info = infoRaw.second;
						int id = info.get<int>("id");
						int relId = info.get<int>(framesName+"_id");
						bank.getLayer(id).setFrame(bank.getFrame(relId));
				}
		} else {
				ERROR("No layers in the specified run.");
		}
}

JPetLayer JPetParamGetterAscii::layerFromInfo(boost::property_tree::ptree & info)
{
		int id = info.get<int>("id");
		bool active = info.get<bool>("active");
		std::string name = info.get<std::string>("name");
		double radius = info.get<double>("radius");
		return JPetLayer(id, active, name, radius);
}


void JPetParamGetterAscii::fillFrames(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(framesName)) {
				auto infos = * possibleInfos;
				for (auto info : infos) {
						bank.addFrame(frameFromInfo(info.second));
				}
		} else {
				ERROR("No frames in the specified run.");
		}
}

JPetFrame JPetParamGetterAscii::frameFromInfo(boost::property_tree::ptree & info)
{
		int id = info.get<int>("id");
		bool active = info.get<bool>("active");
		std::string status = info.get<std::string>("status");
		std::string description = info.get<std::string>("description");
		int version = info.get<int>("version");
		int creatorId = info.get<int>("creator_id");
		return JPetFrame(id, active, status, description, version, creatorId);
}


void JPetParamGetterAscii::fillFEBs(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(FEBsName)) {
				auto infos = * possibleInfos;
				for (auto info : infos) {
						bank.addFEB(FEBFromInfo(info.second));
				}
		} else {
				ERROR("No FEBs in the specified run.");
		}
}

void JPetParamGetterAscii::fillFEBTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(FEBsName)) {
				auto infos = * possibleInfos;
				for (auto infoRaw : infos) {
						auto info = infoRaw.second;
						int id = info.get<int>("id");
						int relId = info.get<int>(TRBsName+"_id");
						bank.getFEB(id).setTRB(bank.getTRB(relId));
				}
		} else {
				ERROR("No FEBs in the specified run.");
		}
}

JPetFEB JPetParamGetterAscii::FEBFromInfo(boost::property_tree::ptree & info)
{
		int id = info.get<int>("id");
		bool active = info.get<bool>("active");
		std::string status = info.get<std::string>("status");
		std::string description = info.get<std::string>("description");
		int version = info.get<int>("version");
		int creatorId = info.get<int>("creator_id");
		int timeOutputsPerInput = info.get<int>("time_outputs_per_input");
		int noTimeOutputsPerInput = info.get<int>("no_time_outputs_per_input");
		return JPetFEB(id, active, status, description, version, creatorId, timeOutputsPerInput, noTimeOutputsPerInput);
}


void JPetParamGetterAscii::fillTRBs(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(TRBsName)) {
				auto infos = * possibleInfos;
				for (auto info : infos) {
						bank.addTRB(TRBFromInfo(info.second));
				}
		} else {
				ERROR("No TRBs in the specified run.");
		}
}

JPetTRB JPetParamGetterAscii::TRBFromInfo(boost::property_tree::ptree & info)
{
		int id = info.get<int>("id");
		int type = info.get<int>("type");
		int channel = info.get<int>("channel");
		return JPetTRB(id, type, channel);
}


void JPetParamGetterAscii::fillTOMBChannels(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(TOMBChannelsName)) {
				auto infos = * possibleInfos;
				for (auto info : infos) {
						bank.addTOMBChannel(TOMBChannelFromInfo(info.second));
				}
		} else {
				ERROR("No TOMBChannels in the specified run.");
		}
}

void JPetParamGetterAscii::fillTOMBChannelTRefs(boost::property_tree::ptree & runContents, JPetParamBank & bank)
{
		if (auto possibleInfos = runContents.get_child_optional(TOMBChannelsName)) {
				auto infos = * possibleInfos;
				for (auto infoRaw : infos) {
						auto info = infoRaw.second;
						int id = info.get<int>("id");
						int relId = info.get<int>(TRBsName+"_id");
						bank.getTOMBChannel(id).setTRB(bank.getTRB(relId));
						relId = info.get<int>(FEBsName+"_id");
						bank.getTOMBChannel(id).setFEB(bank.getFEB(relId));
						relId = info.get<int>(PMsName+"_id");
						bank.getTOMBChannel(id).setPM(bank.getPM(relId));
				}
		} else {
				ERROR("No TOMB channels in the specified run.");
		}
}

JPetTOMBChannel JPetParamGetterAscii::TOMBChannelFromInfo(boost::property_tree::ptree & info)
{
		unsigned int id = info.get<unsigned int>("id");
		unsigned int channel = info.get<unsigned int>("channel");
		unsigned int FEB = info.get<unsigned int>("FEB");
		float threshold = info.get<float>("threshold");
		JPetTOMBChannel result(id);
		result.setLocalChannelNumber(channel);
		result.setFEBInputNumber(FEB);
		result.setThreshold(threshold);
		return result;
}

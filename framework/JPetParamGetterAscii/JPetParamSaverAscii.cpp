/**
		*  @copyright Copyright (c) 2014, J-PET collaboration
		*  @file JPetParamSaverAscii.cpp
		*  @author Tomasz Kisielewski, tymorl@gmail.com
		*/

#include "./JPetParamSaverAscii.h"
#include "./JPetParamAsciiConstants.h"
#include "../JPetParamBank/JPetParamBank.h"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>

void JPetParamSaverAscii::saveParamBank(const JPetParamBank & bank, const int runNumber, const std::string & filename)
{
	std::string runNumberS = boost::lexical_cast<std::string>(runNumber);
	auto fileTree = getTreeFromFile(filename);
	addToTree(fileTree, bank, runNumberS);
	write_json(filename, fileTree);
}

boost::property_tree::ptree JPetParamSaverAscii::getTreeFromFile(const std::string & filename)
{
	boost::property_tree::ptree result;
	if (boost::filesystem::exists(filename)) {
		boost::property_tree::read_json(filename, result);
	}
	return result;
}

void JPetParamSaverAscii::addToTree(boost::property_tree::ptree & tree, const JPetParamBank & bank, const std::string & runNumber)
{
	if (tree.count(runNumber) != 0) {
		WARNING("Overwriting parameters in run number " + runNumber + ". I hope you wanted to do that.");
		tree.erase(runNumber);
	}
	boost::property_tree::ptree runContents;

	fillScintillators(runContents, bank);
	fillPMs(runContents, bank);
	fillPMCalibs(runContents, bank);
	fillBarrelSlots(runContents, bank);
	fillLayers(runContents, bank);
	fillFrames(runContents, bank);
	fillFEBs(runContents, bank);
	fillTRBs(runContents, bank);
	fillTOMBChannels(runContents, bank);

	tree.add_child(runNumber, runContents);
}


void JPetParamSaverAscii::fillScintillators(boost::property_tree::ptree & runContents, const JPetParamBank & bank)
{
	boost::property_tree::ptree infos;
	for (auto scin : bank.getScintillators()) {
		infos.push_back(std::make_pair("", scintillatorToInfo(*scin)));
	}
	runContents.add_child(scintillatorsName, infos);
}

boost::property_tree::ptree JPetParamSaverAscii::scintillatorToInfo(const JPetScin & scin)
{
	boost::property_tree::ptree info;
	info.put("id", scin.getID());
	info.put("attenuation_length", scin.getAttenLen());
	auto dimensions = scin.getScinSize();
	info.put("length", dimensions.fLength);
	info.put("width", dimensions.fWidth);
	info.put("height", dimensions.fHeight);

	info.put(barrelSlotsName+"_id", scin.getBarrelSlot().getID());
	return info;
}


void JPetParamSaverAscii::fillPMs(boost::property_tree::ptree & runContents, const JPetParamBank & bank)
{
	boost::property_tree::ptree infos;
	for (auto pm : bank.getPMs()) {
		infos.push_back(std::make_pair("", PMToInfo(*pm)));
	}
	runContents.add_child(PMsName, infos);
}

boost::property_tree::ptree JPetParamSaverAscii::PMToInfo(const JPetPM & pm)
{
	boost::property_tree::ptree info;
	info.put("id", pm.getID());
	info.put("is_right_side", (pm.getSide() == JPetPM::Side::SideB));

	info.put(barrelSlotsName+"_id", pm.getBarrelSlot().getID());
	info.put(FEBsName+"_id", pm.getFEB().getID());
	info.put(scintillatorsName+"_id", pm.getScin().getID());
	return info;
}


void JPetParamSaverAscii::fillPMCalibs(boost::property_tree::ptree & runContents, const JPetParamBank & bank)
{
	boost::property_tree::ptree infos;
	for (auto pmCalib : bank.getPMCalibs()) {
		infos.push_back(std::make_pair("", PMCalibToInfo(*pmCalib)));
	}
	runContents.add_child(PMCalibsName, infos);
}

boost::property_tree::ptree JPetParamSaverAscii::PMCalibToInfo(const JPetPMCalib & pmCalib)
{
	boost::property_tree::ptree info;
	info.put("id", pmCalib.GetId());
	info.put("name", pmCalib.GetNamePM());
	info.put("opthv", pmCalib.GetOpthv());
	info.put("c2e1", pmCalib.GetECalConst1());
	info.put("c2e2", pmCalib.GetECalConst2());
	info.put("gain_alpha", pmCalib.GetGainalpha());
	info.put("gain_beta", pmCalib.GetGainbeta());
	auto assignment = pmCalib.GetPMCalibAssignment();
	info.put("assignment_id", assignment.id);
	info.put("assignment_photomultiplier_id", assignment.photomultiplier_id);
	return info;
}


void JPetParamSaverAscii::fillBarrelSlots(boost::property_tree::ptree & runContents, const JPetParamBank & bank)
{
	boost::property_tree::ptree infos;
	for (auto bs : bank.getBarrelSlots()) {
		infos.push_back(std::make_pair("", barrelSlotToInfo(*bs)));
	}
	runContents.add_child(barrelSlotsName, infos);
}

boost::property_tree::ptree JPetParamSaverAscii::barrelSlotToInfo(const JPetBarrelSlot & bs)
{
	boost::property_tree::ptree info;
	info.put("id", bs.getID());
	info.put("active", bs.isActive());
	info.put("name", bs.getName());
	info.put("theta1", bs.getTheta());
	info.put("frame_id", bs.getInFrameID());

	info.put(layersName+"_id", bs.getLayer().getId());
	return info;
}


void JPetParamSaverAscii::fillLayers(boost::property_tree::ptree & runContents, const JPetParamBank & bank)
{
	boost::property_tree::ptree infos;
	for (auto layer : bank.getLayers()) {
		infos.push_back(std::make_pair("", layerToInfo(*layer)));
	}
	runContents.add_child(layersName, infos);
}

boost::property_tree::ptree JPetParamSaverAscii::layerToInfo(const JPetLayer & layer)
{
	boost::property_tree::ptree info;
	info.put("id", layer.getId());
	info.put("active", layer.getIsActive());
	info.put("name", layer.getName());
	info.put("radius", layer.getRadius());

	info.put(framesName+"_id", layer.getFrame().getId());
	return info;
}


void JPetParamSaverAscii::fillFrames(boost::property_tree::ptree & runContents, const JPetParamBank & bank)
{
	boost::property_tree::ptree infos;
	for (auto frame : bank.getFrames()) {
		infos.push_back(std::make_pair("", frameToInfo(*frame)));
	}
	runContents.add_child(framesName, infos);
}

boost::property_tree::ptree JPetParamSaverAscii::frameToInfo(const JPetFrame & frame)
{
	boost::property_tree::ptree info;
	info.put("id", frame.getId());
	info.put("active", frame.getIsActive());
	info.put("status", frame.getStatus());
	info.put("description", frame.getDescription());
	info.put("version", frame.getVersion());
	info.put("creator_id", frame.getCreator());
	return info;
}


void JPetParamSaverAscii::fillFEBs(boost::property_tree::ptree & runContents, const JPetParamBank & bank)
{
	boost::property_tree::ptree infos;
	for (auto feb : bank.getFEBs()) {
		infos.push_back(std::make_pair("", FEBToInfo(*feb)));
	}
	runContents.add_child(FEBsName, infos);
}

boost::property_tree::ptree JPetParamSaverAscii::FEBToInfo(const JPetFEB & feb)
{
	boost::property_tree::ptree info;
	info.put("id", feb.getID());
	info.put("active", feb.isActive());
	info.put("status", feb.status());
	info.put("description", feb.description());
	info.put("version", feb.version());
	info.put("creator_id", feb.getCreator());
	info.put("time_outputs_per_input", feb.getNtimeOutsPerInput());
	info.put("no_time_outputs_per_input", feb.getNnotimeOutsPerInput());

	info.put(TRBsName+"_id", feb.getTRB().getID());
	return info;
}


void JPetParamSaverAscii::fillTRBs(boost::property_tree::ptree & runContents, const JPetParamBank & bank)
{
	boost::property_tree::ptree infos;
	for (auto trb : bank.getTRBs()) {
		infos.push_back(std::make_pair("", TRBToInfo(*trb)));
	}
	runContents.add_child(TRBsName, infos);
}

boost::property_tree::ptree JPetParamSaverAscii::TRBToInfo(const JPetTRB & trb)
{
	boost::property_tree::ptree info;
	info.put("id", trb.getID());
	info.put("type", trb.getType());
	info.put("channel", trb.getChannel());
	return info;
}


void JPetParamSaverAscii::fillTOMBChannels(boost::property_tree::ptree & runContents, const JPetParamBank & bank)
{
	boost::property_tree::ptree infos;
	for (auto tomb : bank.getTOMBChannels()) {
		infos.push_back(std::make_pair("", TOMBChannelToInfo(*tomb)));
	}
	runContents.add_child(TOMBChannelsName, infos);
}

boost::property_tree::ptree JPetParamSaverAscii::TOMBChannelToInfo(const JPetTOMBChannel & tomb)
{
	boost::property_tree::ptree info;
	info.put("id", tomb.getChannel());
	info.put("channel", tomb.getLocalChannelNumber());
	info.put("FEB", tomb.getFEBInputNumber());
	info.put("threshold", tomb.getThreshold());

	info.put(TRBsName+"_id", tomb.getTRB().getID());
	info.put(FEBsName+"_id", tomb.getFEB().getID());
	info.put(PMsName+"_id", tomb.getPM().getID());
	return info;
}

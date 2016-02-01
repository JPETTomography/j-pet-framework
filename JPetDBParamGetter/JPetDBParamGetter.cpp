/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetDBParamGetter.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */ 

#include "./JPetDBParamGetter.h"
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <TThread.h>
#include "../DBHandler/HeaderFiles/DBHandler.h"
#include <cstdint>

std::map<int, JPetParamBank*> JPetDBParamGetter::fParamCache;

JPetDBParamGetter::JPetDBParamGetter()
{
}

/// @param DBConfigFile configuration file with the database connection settings
JPetDBParamGetter::JPetDBParamGetter(const char* dBConfigFile)
{
  DB::SERVICES::DBHandler::getInstance(dBConfigFile); // this command aims to load the configuration file, the return value is irrelevant
  /// ToDo: It is very bad that such command is in a non-singleton's constructor
}

JPetDBParamGetter::~JPetDBParamGetter()
{
}

/// dopisac ze ktos inny musi zniszczyc
JPetParamBank* JPetDBParamGetter::generateParamBank(const int p_run_id) 
{
    /// we use new ... explanation
    TThread::Lock();
    if(fParamCache.find(p_run_id) == fParamCache.end())
    {
        JPetParamBank *pParamBank = new JPetParamBank;
        fillScintillators(p_run_id, *pParamBank);
        fillPMs(p_run_id, *pParamBank);
        fillPMCalibs(p_run_id, *pParamBank);
        fillBarrelSlot(p_run_id, *pParamBank);
        fillLayer(p_run_id, *pParamBank);
        fillFrame(p_run_id, *pParamBank);
        fillFEBs(p_run_id, *pParamBank);
        fillTRBs(p_run_id, *pParamBank);
        fillTOMBChannels(p_run_id, *pParamBank);
        fParamCache[p_run_id] = pParamBank;
    }
    JPetParamBank* returnedParamBank = new JPetParamBank(*fParamCache[p_run_id]);
    fillAllTRefs(p_run_id, *returnedParamBank);
    TThread::UnLock();
    return returnedParamBank;
}

void JPetDBParamGetter::fillScintillators(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling Scintillators container.");
    //"SELECT * FROM getDataFromScintillators(" + l_run_id + ");";
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getDataFromScintillators",l_run_id);


  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
      JPetScin l_scin = generateScintillator(row);
      paramBank.addScintillator(l_scin);
    }
  } else {
    printErrorMessageDB("getDataFromScintillators", p_run_id);
  }
}

std::string JPetDBParamGetter::generateSelectQuery(const std::string& sqlFun, const std::string& arguments) 
{
  std::string sqlQuerry = "SELECT * FROM ";
  sqlQuerry += sqlFun;
  sqlQuerry += "(" +arguments + ");";
  return sqlQuerry;
}

/// @brief method calls the remote PostgreSQL function sqlfunction with the id argument and returns results from database
pqxx::result JPetDBParamGetter::getDataFromDB(const std::string& sqlfunction,const  std::string& arguments) 
{
  //std::string l_run_id = boost::lexical_cast<std::string>(id);
  std::string l_sqlQuerry = generateSelectQuery(sqlfunction,arguments);
  DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();
  return  l_dbHandlerInstance.querry(l_sqlQuerry);
}


void JPetDBParamGetter::printErrorMessageDB(std::string sqlFunction, int p_run_id) {
    std::string l_error(sqlFunction);
    l_error += "() querry for run_id = ";
    l_error += boost::lexical_cast<std::string>(p_run_id) + " return 0 records.";
    ERROR(l_error.c_str());
}



void JPetDBParamGetter::fillPMs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling PMs container.");

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getDataFromPhotoMultipliers",l_run_id);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
      JPetPM l_pm = generatePM(row);
      paramBank.addPM(l_pm);
    }
  } else {
    printErrorMessageDB("getDataFromPhotoMultipliers", p_run_id);
  }
}

void JPetDBParamGetter::fillPMCalibs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling PMCalibs container.");

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getPmCalibration",l_run_id);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
      JPetPMCalib l_pmCalib = generatePMCalib(row);
      paramBank.addPMCalib(l_pmCalib);
    }
  } else {
    printErrorMessageDB("getPmCalibration", p_run_id);
  }
}

void JPetDBParamGetter::fillBarrelSlot(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling BarrelSlot container.");

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getBarrelSlot", l_run_id);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
      JPetBarrelSlot l_barrelSlot = generateBarrelSlot(row);
      paramBank.addBarrelSlot(l_barrelSlot);
    }
  } else {
    printErrorMessageDB("getBarrelSlot", p_run_id);
  }
}

void JPetDBParamGetter::fillLayer(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling Layer container.");

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getLayer", l_run_id);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
      JPetLayer l_layer = generateLayer(row);
      paramBank.addLayer(l_layer);
    }
  } else {
    printErrorMessageDB("getLayer", p_run_id);
  }
}

void JPetDBParamGetter::fillFrame(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling Frame container.");

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getFrame", l_run_id);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
      JPetFrame l_frame = generateFrame(row);
      paramBank.addFrame(l_frame);
    }
  } else {
    printErrorMessageDB("getFrame", p_run_id);
  }
}

void JPetDBParamGetter::fillFEBs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling FEBs container.");

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getDataFromKonradBoards",l_run_id);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
      JPetFEB l_FEB = generateFEB(row);
      paramBank.addFEB(l_FEB);
    }
  } else {
    printErrorMessageDB("getDataFromKonradBoards", p_run_id);
  }
}

void JPetDBParamGetter::fillTRBs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling TRBs container.");

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getDataFromTRBs",l_run_id);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
      JPetTRB l_TRB = generateTRB(row);
      paramBank.addTRB(l_TRB);
    }
  } else {
    printErrorMessageDB("getDataFromTRBs", p_run_id);
  }
}



void JPetDBParamGetter::fillTOMBChannels(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling TOMBChannels container.");

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getEverythingVsTOMB",l_run_id);
  
  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    {
      for (pqxx::result::const_iterator row = l_runDbResults.begin(); 
	   row != l_runDbResults.end(); 
	   ++row) {
	JPetTOMBChannel l_TOMBChannel = generateTOMBChannel(row);
	paramBank.addTOMBChannel(l_TOMBChannel);
    }

    }
  } else {
    printErrorMessageDB("getDataFromTOMBChannels", p_run_id);
  }
}


JPetScin JPetDBParamGetter::generateScintillator(pqxx::result::const_iterator row) {
      int l_scintillator_id = row["scintillator_id"].as<int>();

      double l_scintillator_length = row["scintillator_length"].as<double>();
      double l_scintillator_width = row["scintillator_width"].as<double>();
      double l_scintillator_height = row["scintillator_height"].as<double>();

      JPetScin l_scin(l_scintillator_id,
                      0.f,			/// @todo what is attenuation length in database?
                      l_scintillator_length,
                      l_scintillator_height,
                      l_scintillator_width);

      return l_scin;
}


JPetPM JPetDBParamGetter::generatePM(pqxx::result::const_iterator row) {
      bool l_hvpmconnection_isrightside = row["hvpmconnection_isrightside"].as<bool>();

      int l_photomultiplier_id = row["photomultiplier_id"].as<int>();

      JPetPM::Side l_side = (l_hvpmconnection_isrightside) ? JPetPM::Side::SideB : JPetPM::Side::SideA;

      JPetPM l_pm;
      l_pm.setID(l_photomultiplier_id);
      l_pm.setSide(l_side);

      return  l_pm;
}

JPetPMCalib JPetDBParamGetter::generatePMCalib(pqxx::result::const_iterator row)
{
  int l_pm_calibration_id = row["pm_calibration_id"].as<int>();
  std::string l_pm_calibration_name = row["pm_calibration_name"].as<std::string>();
  double l_pm_calibration_opthv = row["pm_calibration_opthv"].as<double>();
  double l_pm_calibration_c2e_1 = row["pm_calibration_c2e_1"].as<double>();
  double l_pm_calibration_c2e_2 = row["pm_calibration_c2e_2"].as<double>();
  double l_pm_calibration_gainalpha = row["pm_calibration_gainalpha"].as<double>();
  double l_pm_calibration_gainbeta = row["pm_calibration_gainbeta"].as<double>();
  int l_pm_calibration_assignment_id = row["pm_calibration_assignment_id"].as<int>();
  int l_pm_calibration_assignment_photomuliplier_id = row["pm_calibration_assignment_photomuliplier_id"].as<int>();
  
  JPetPMCalib l_PMCalib(l_pm_calibration_id,
			l_pm_calibration_name,
			l_pm_calibration_opthv,
			l_pm_calibration_c2e_1,
			l_pm_calibration_c2e_2,
			l_pm_calibration_gainalpha,
			l_pm_calibration_gainbeta,
			l_pm_calibration_assignment_id,
			l_pm_calibration_assignment_photomuliplier_id);
  
  return l_PMCalib;
}

JPetBarrelSlot JPetDBParamGetter::generateBarrelSlot(pqxx::result::const_iterator row)
{
  int l_slot_id = row["slot_id"].as<int>();
  bool l_slot_isActive = row["slot_isActive"].as<bool>();
  std::string l_slot_name = row["slot_name"].as<std::string>();
  double l_slot_theta1 = row["slot_theta1"].as<double>();
  int l_slot_inFrameId = row["slot_inFrameId"].as<int>();

  JPetBarrelSlot l_barrelSlot(l_slot_id,
			      l_slot_isActive,
			      l_slot_name,
			      l_slot_theta1,
			      l_slot_inFrameId);
//  JPetBarrelSlot l_barrelSlot(l_slot_id,
//			      l_slot_isActive,
//			      l_slot_name,
//			      l_slot_theta1,
//			      l_slot_inFrameId,
//			      l_layer_id);
//  
  return l_barrelSlot;
}

JPetLayer JPetDBParamGetter::generateLayer(pqxx::result::const_iterator row)
{
  int l_layer_id = row["layer_id"].as<int>();
  bool l_layer_isActive = row["layer_isActive"].as<bool>();
  std::string l_layer_name = row["layer_name"].as<std::string>();
  double l_layer_radius = row["layer_radius"].as<double>();
  
  JPetLayer l_layer(l_layer_id,
        	    l_layer_isActive,
        	    l_layer_name,
        	    l_layer_radius);

  //JPetLayer l_layer(l_layer_id,
  //      	    l_layer_isActive,
  //      	    l_layer_name,
  //      	    l_layer_radius,
  //      	    l_frame_id);
  //
  return l_layer;
}

JPetFrame JPetDBParamGetter::generateFrame(pqxx::result::const_iterator row)
{
  int l_frame_id = row["frame_id"].as<int>();
  bool l_frame_isActive = row["frame_isActive"].as<bool>();
  std::string l_frame_status = row["frame_status"].as<std::string>();
  std::string l_frame_description = row["frame_description"].as<std::string>();
  int l_frame_version = row["frame_version"].as<int>();
  int l_frame_creator_id = row["frame_creator_id"].as<int>();

  JPetFrame l_frame(l_frame_id,
		    l_frame_isActive,
		    l_frame_status,
		    l_frame_description,
		    l_frame_version,
		    l_frame_creator_id);
  
  return l_frame;
}

JPetFEB JPetDBParamGetter::generateFEB(pqxx::result::const_iterator row) {
      int l_konradboard_id = row["konradboard_id"].as<int>();
      bool l_konradboard_isactive = row["konradboard_isactive"].as<bool>();
      std::string l_konradboard_status = row["konradboard_status"].as<std::string>();
      std::string l_konradboard_description = row["konradboard_description"].as<std::string>();
      int l_konradboard_version = row["konradboard_version"].as<int>();
      int l_konradboard_creator_id = row["konradboard_creator_id"].as<int>();
      int l_time_outputs_per_input = row["time_outputs_per_input"].as<int>();
      int l_notime_outputs_per_input = row["notime_outputs_per_input"].as<int>();
      
      JPetFEB l_FEB(l_konradboard_id,
                    l_konradboard_isactive,
                    l_konradboard_status,
                    l_konradboard_description,
                    l_konradboard_version,
                    l_konradboard_creator_id,
		    l_time_outputs_per_input,
		    l_notime_outputs_per_input);
    return l_FEB;
}

JPetTRB JPetDBParamGetter::generateTRB(pqxx::result::const_iterator row) {
      int l_TRB_id = row["TRB_id"].as<int>();

      JPetTRB l_TRB(l_TRB_id,
                    0,		/// @todo what is type in database
                    0);		/// @todo what is channel in database
  return l_TRB;
}


int JPetDBParamGetter::getTOMBChannelFromDescription(std::string p_desc) const
{
  // parsing the string description of a TOMB channel to extract the channel number
  // convention: tast 4 characters of the description represent the number
     const char * l_pattern = ".*\\s(\\d{1,4}).*";
     boost::regex l_regex(l_pattern);
     boost::smatch l_matches;

     int l_TOMB_no = -1;

     if (boost::regex_match(p_desc, l_matches, l_regex))
       {
	l_TOMB_no = boost::lexical_cast<int>( l_matches[1] );
       }else
       {
	 // @todo: handle parsing error somehow 
	 ERROR( "Unable to parse TOMBInput description to get channel number." );
      }
     return l_TOMB_no;
}


JPetTOMBChannel JPetDBParamGetter::generateTOMBChannel(pqxx::result::const_iterator row) {
  
     std::string l_TOMB_description = row["tomb"].as<std::string>();
     int l_TOMB_no = getTOMBChannelFromDescription( l_TOMB_description );

     JPetTOMBChannel l_TOMBChannel(l_TOMB_no);
     l_TOMBChannel.setLocalChannelNumber(row["thr_num"].as<int>());
     l_TOMBChannel.setFEBInputNumber(row["feb_input"].as<int>());
     return l_TOMBChannel;
}




void JPetDBParamGetter::fillPMsTRefs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling PMs TRefs.");

		std::string runId = boost::lexical_cast<std::string>(p_run_id);
  int l_PMsSize = paramBank.getPMsSize();
  int l_FEBsSize = paramBank.getFEBsSize();
  int l_ScinsSize = paramBank.getScintillatorsSize();
  int l_BarrelSlotSize = paramBank.getBarrelSlotsSize();

  if (l_PMsSize > 0 && l_FEBsSize > 0 && l_ScinsSize > 0 && l_BarrelSlotSize > 0) {

    for (auto & content : paramBank.getPMs()) {
						JPetPM & pm = *content.second;
						std::string pmId = boost::lexical_cast<std::string>(pm.getID());
						std::string args = pmId + "," + runId;

      pqxx::result l_runDbResults = getDataFromDB("getKonradBoardsForPhotoMultiplier", args);
						for (auto row : l_runDbResults) {
								int relatedId = row["KonradBoard_id"].as<int>();

								pm.setFEB(paramBank.getFEB(relatedId));
						}

      l_runDbResults = getDataFromDB("getScintillatorsForPhotoMultiplier", args);
						for (auto row : l_runDbResults) {
								int relatedId = row["Scintillator_id"].as<int>();

								pm.setScin(paramBank.getScintillator(relatedId));
						}

      l_runDbResults = getDataFromDB("getbarrelslotforphotomultiplier", args);
						for (auto row : l_runDbResults) {
								int relatedId = row["hvpmconnection_slot_id"].as<int>();

								pm.setBarrelSlot(paramBank.getBarrelSlot(relatedId));
						}
    }
  } else {
    if (l_PMsSize == 0)
      ERROR("PMs container is empty.");
    if (l_FEBsSize == 0)
      ERROR("FEBs container is empty.");
    if (l_ScinsSize == 0)
      ERROR("Scintillators container is empty.");
    if(l_BarrelSlotSize == 0)
						ERROR("Barrelslot container is empty.");
  }
}

void JPetDBParamGetter::fillFEBsTRefs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling FEBs TRefs.");

		std::string runId = boost::lexical_cast<std::string>(p_run_id);
  int l_FEBsSize = paramBank.getFEBsSize();
  int l_TRBsSize = paramBank.getTRBsSize();

  if (l_FEBsSize > 0 && l_TRBsSize > 0) {

    for (auto & content : paramBank.getFEBs()) {
						JPetFEB & feb = *content.second;
						std::string febId = boost::lexical_cast<std::string>(feb.getID());
						std::string args = febId + "," + runId;

      pqxx::result l_runDbResults = getDataFromDB("getTRBsForKonradBoard",args);
						for (auto row : l_runDbResults) {
								int relatedId = row["TRB_id"].as<int>();

								feb.setTRB(paramBank.getTRB(relatedId));
						}
    }
  } else {
    if (l_FEBsSize == 0)
      ERROR("FEBs container is empty.");
    if (l_TRBsSize == 0)
      ERROR("TRBs container is empty.");
  }
}

void JPetDBParamGetter::fillTOMBChannelsTRefs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling TOMBChannels TRefs.");

		std::string runId = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getEverythingVsTOMB", runId);
  
		if (l_runDbResults.size() == 0) {
				printErrorMessageDB("getDataFromTOMBChannels", p_run_id);
		}

		for (auto row : l_runDbResults) {
				int TOMBId = getTOMBChannelFromDescription(row["tomb"].as<std::string>());
				int TRBId = row["trb_id"].as<int>();
				int FEBId = row["konradboard_id"].as<int>();
				int PMId = row["photomultiplier_id"].as<int>();
				float threshold = row["threshold"].as<float>();

				paramBank.getTOMBChannel(TOMBId).setTRB(paramBank.getTRB(TRBId));
				paramBank.getTOMBChannel(TOMBId).setFEB(paramBank.getFEB(FEBId));
				paramBank.getTOMBChannel(TOMBId).setPM(paramBank.getPM(PMId));
				paramBank.getTOMBChannel(TOMBId).setThreshold(threshold);
		}
}

void JPetDBParamGetter::fillBarrelSlotTRefs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling slot TRefs.");
  
		std::string runId = boost::lexical_cast<std::string>(p_run_id);
  int l_barrelSlotsSize = paramBank.getBarrelSlotsSize();
  int l_layersSize = paramBank.getLayersSize();

  if(l_barrelSlotsSize > 0 && l_layersSize > 0) {
    for (auto & content : paramBank.getBarrelSlots()) {
						JPetBarrelSlot & slot = *content.second;
						std::string slotId = boost::lexical_cast<std::string>(slot.getID());
						std::string args = slotId + "," + runId;

      pqxx::result l_runDbResults = getDataFromDB("getLayerForBarrelSlot", args);
      if (l_runDbResults.size() == 0) {
								std::string querry = "getLayerForBarrelSlot(" + args + ")";
								ERROR("0 result from querry = " + querry);
      }
						for (auto row : l_runDbResults) {
								int relatedId = row["layer_id"].as<int>();

								slot.setLayer(paramBank.getLayer(relatedId));
						}
    }
  } else {
    if(l_barrelSlotsSize == 0) {
      ERROR("BarrelSlot container is empty.");
    }
    if(l_layersSize == 0) {
      ERROR("Layer container is empty.");
    }
  }
}

void JPetDBParamGetter::fillLayerTRefs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling layer TRefs.");
  
		std::string runId = boost::lexical_cast<std::string>(p_run_id);
  int l_layersSize = paramBank.getLayersSize();
  int l_framesSize = paramBank.getFramesSize();
  
  if(l_layersSize > 0 && l_framesSize > 0) {
    for (auto & content : paramBank.getLayers()) {
						JPetLayer & layer = *content.second;
						std::string layerId = boost::lexical_cast<std::string>(layer.getId());
						std::string args = layerId + "," + runId;

      pqxx::result l_runDbResults = getDataFromDB("getFrameForLayer", args);
      if (l_runDbResults.size() == 0) {
								std::string querry = "getFrameForLayer(" + args + ")";
								ERROR("0 result from querry = " + querry);
      }
						for (auto row : l_runDbResults) {
								int relatedId = row["frame_id"].as<int>();

								layer.setFrame(paramBank.getFrame(relatedId));
						}
    }
  } else {
    if(l_layersSize == 0) {
      ERROR("Layer container is empty.");
    }
    if(l_framesSize == 0) {
      ERROR("Frame container is empty.");
    }
  }
}

void JPetDBParamGetter::fillScinTRef(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling Scintillator TRef.");
  
		std::string runId = boost::lexical_cast<std::string>(p_run_id);
  int l_scintillatorSize = paramBank.getScintillatorsSize();
  int l_barrelSlotSize = paramBank.getBarrelSlotsSize();
  
  if(l_scintillatorSize > 0 && l_barrelSlotSize > 0) {
    for (auto & content : paramBank.getScintillators()) {
						JPetScin & scin = *content.second;
						std::string scinId = boost::lexical_cast<std::string>(scin.getID());
						std::string args = scinId + "," + runId;

      pqxx::result l_runDbResults = getDataFromDB("getbarrelslotforscintillator", args);
      if (l_runDbResults.size() == 0) {
								std::string querry = "getbarrelslotforscintillator(" + args + ")";
								ERROR("0 result from querry = " + querry);
      }
						for (auto row : l_runDbResults) {
								int relatedId = row["slscconnection_slot_id"].as<int>();

								scin.setBarrelSlot(paramBank.getBarrelSlot(relatedId));
						}
    }
  } 
  else
  {
    if(l_scintillatorSize == 0) {
						ERROR("Scintillator container is empty.");
				}
    if(l_barrelSlotSize == 0) {
						ERROR("Barrelslot container is empty.");
				}
  }
}

void JPetDBParamGetter::fillAllTRefs(const int p_run_id, JPetParamBank& paramBank)
{
  if (paramBank.getScintillatorsSize() > 0
      && paramBank.getPMsSize() > 0
      && paramBank.getFEBsSize() > 0
      && paramBank.getTRBsSize() > 0
      && paramBank.getBarrelSlotsSize() > 0
      && paramBank.getLayersSize() > 0
      && paramBank.getFramesSize() > 0
     ) {
    fillPMsTRefs(p_run_id, paramBank);
    fillFEBsTRefs(p_run_id, paramBank);
    //fillTRBsTRefs(p_run_id, paramBank);
    fillTOMBChannelsTRefs(p_run_id, paramBank);
    
    fillBarrelSlotTRefs(p_run_id, paramBank);
    fillLayerTRefs(p_run_id, paramBank);
    fillScinTRef(p_run_id, paramBank);
  } else {
    ERROR("Containers are empty.");
  }
}

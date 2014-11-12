/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetDBParamGetter.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */ 

#include "./JPetDBParamGetter.h"
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include "../DBHandler/HeaderFiles/DBHandler.h"

JPetDBParamGetter::JPetDBParamGetter()
{
}

/// @param DBConfigFile configuration file with the database connection settings
JPetDBParamGetter::JPetDBParamGetter(const char* dBConfigFile)
{
  DB::SERVICES::DBHandler::getInstance(dBConfigFile); /// this command aims to load the configuration file, the return value is irrelevant

}

/// dopisac ze ktos inny musi zniszczyc
JPetParamBank* JPetDBParamGetter::generateParamBank(const int p_run_id) 
{
  /// we use new ... explanation 
  JPetParamBank* pParamBank =  new JPetParamBank;
  fillScintillators(p_run_id, *pParamBank);
  fillPMs(p_run_id, *pParamBank);
  fillPMCalibs(p_run_id, *pParamBank);
  fillFEBs(p_run_id, *pParamBank);
  fillTRBs(p_run_id, *pParamBank);
  fillTOMBChannels(p_run_id, *pParamBank);
  fillAllTRefs(p_run_id, *pParamBank);
  return pParamBank;
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
    l_error += p_run_id + " return 0 records.";
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
  pqxx::result l_runDbResults = getDataFromDB("getDataFromPhotoMultipliersCalibration",l_run_id);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
      JPetPMCalib l_pmCalib = generatePMCalib(row);
      paramBank.addPMCalib(l_pmCalib);
    }
  } else {
    printErrorMessageDB("getDataFromPhotoMultipliersCalibration", p_run_id);
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

      int l_setup_id = row["setup_id"].as<int>();
      int l_run_id = row["run_id"].as<int>();
      

      JPetScin l_scin(l_scintillator_id,
                      0.f,			/// @todo what is attenuation length in database?
                      l_scintillator_length,
                      l_scintillator_height,
                      l_scintillator_width);

      return l_scin;
}


JPetPM JPetDBParamGetter::generatePM(pqxx::result::const_iterator row) {
      int l_hvpmconnection_id = row["hvpmconnection_id"].as<int>();
      bool l_hvpmconnection_isrightside = row["hvpmconnection_isrightside"].as<bool>();

      int l_photomultiplier_id = row["photomultiplier_id"].as<int>();

      int l_setup_id = row["setup_id"].as<int>();
      int l_run_id = row["run_id"].as<int>();

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

JPetFEB JPetDBParamGetter::generateFEB(pqxx::result::const_iterator row) {
      int l_konradboard_id = row["konradboard_id"].as<int>();
      bool l_konradboard_isactive = row["konradboard_isactive"].as<bool>();
      std::string l_konradboard_status = row["konradboard_status"].as<std::string>();
      std::string l_konradboard_description = row["konradboard_description"].as<std::string>();
      int l_konradboard_version = row["konradboard_version"].as<int>();
      int l_konradboard_creator_id = row["konradboard_creator_id"].as<int>();

      int l_setup_id = row["setup_id"].as<int>();
      int l_run_id = row["run_id"].as<int>();

      JPetFEB l_FEB(l_konradboard_id,
                    l_konradboard_isactive,
                    l_konradboard_status,
                    l_konradboard_description,
                    l_konradboard_version,
                    l_konradboard_creator_id);
    return l_FEB;
}

JPetTRB JPetDBParamGetter::generateTRB(pqxx::result::const_iterator row) {
      int l_TRB_id = row["TRB_id"].as<int>();

      int l_setup_id = row["setup_id"].as<int>();
      int l_run_id = row["run_id"].as<int>();

      JPetTRB l_TRB(l_TRB_id,
                    0,		/// @todo what is type in database
                    0);		/// @todo what is channel in database
  return l_TRB;
}


int JPetDBParamGetter::getTOMBChannelFromDescription(std::string p_desc) const
{
  // parsing the string description of a TOMB channel to extract the channel number
  // convention: tast 4 characters of the description represent the number
     const char * l_pattern = ".*(\\d{4}).*";
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
    return l_TOMBChannel;
}




void JPetDBParamGetter::fillPMsTRefs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling PMs TRefs.");

  int l_PMsSize = paramBank.getPMsSize();
  int l_FEBsSize = paramBank.getFEBsSize();
  int l_ScinsSize = paramBank.getScintillatorsSize();

  if (l_PMsSize > 0 && l_FEBsSize > 0) {

    for (unsigned int l_PM_index = 0u; l_PM_index < l_PMsSize; ++l_PM_index) {
    std::string pm_id = boost::lexical_cast<std::string>(paramBank.getPM(l_PM_index).getID());
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
    std::string args = pm_id + "," + l_run_id;

      pqxx::result l_runDbResults = getDataFromDB("getKonradBoardsForPhotoMultiplier", args);

      size_t l_sizeResultQuerry = l_runDbResults.size();

      if (l_sizeResultQuerry) {
        for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
          int l_KonradBoard_id = row["KonradBoard_id"].as<int>();

          for (unsigned int l_FEB_index = 0u; l_FEB_index < l_FEBsSize; ++l_FEB_index) {
            int l_FEB_id = paramBank.getFEB(l_FEB_index).getID();

            if (l_FEB_id == l_KonradBoard_id) {
              paramBank.getPM(l_PM_index).setFEB(paramBank.getFEB(l_FEB_index) );
            }
          }
        }
      }
    }
  } else {
    if (l_PMsSize == 0)
      ERROR("PMs container is empty.");
    if (l_FEBsSize == 0)
      ERROR("FEBs container is empty.");
  }


  if (l_PMsSize > 0 && l_ScinsSize > 0) {

    for (unsigned int l_PM_index = 0u; l_PM_index < l_PMsSize; ++l_PM_index) {
    std::string pm_id = boost::lexical_cast<std::string>(paramBank.getPM(l_PM_index).getID());
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  std::string args = pm_id + "," + l_run_id;

      pqxx::result l_runDbResults = getDataFromDB("getScintillatorsForPhotoMultiplier", args);

      size_t l_sizeResultQuerry = l_runDbResults.size();

      if (l_sizeResultQuerry) {
        for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
          int l_scin_id = row["Scintillator_id"].as<int>();
          for (unsigned int l_scin_index = 0u; l_scin_index < l_ScinsSize; ++l_scin_index) {
            int l_ScinId = paramBank.getScintillator(l_scin_index).getID();

            if (l_scin_id == l_ScinId) {
              paramBank.getPM(l_PM_index).setScin(paramBank.getScintillator(l_scin_index) );
            }
          }
        }
      }
    }
  } else {
    if (l_PMsSize == 0)
      ERROR("PMs container is empty.");
    if (l_ScinsSize == 0)
      ERROR("Scintillators container is empty.");
  }


}

void JPetDBParamGetter::fillFEBsTRefs(const int p_run_id, JPetParamBank& paramBank)
{
  INFO("Start filling FEBs TRefs.");

  int l_FEBsSize = paramBank.getFEBsSize();
  int l_TRBsSize = paramBank.getTRBsSize();

  if (l_FEBsSize > 0 && l_TRBsSize > 0) {

    for (unsigned int l_FEB_index = 0u; l_FEB_index < l_FEBsSize; ++l_FEB_index) {

//     ((JPetFEB*)fFEBs[l_FEB_index])->clearTRefTRBs();
 ///wk!!!     paramBank.getFEB(l_FEB_index).clearTRefTRBs();

//      std::string l_FEB_id = boost::lexical_cast<std::string>(((JPetFEB*)fFEBs[l_FEB_index])->getID());
    std::string feb_id = boost::lexical_cast<std::string>(paramBank.getFEB(l_FEB_index).getID());
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
    std::string args = feb_id + "," + l_run_id;
      pqxx::result l_runDbResults = getDataFromDB("getTRBsForKonradBoard",args);

      size_t l_sizeResultQuerry = l_runDbResults.size();

      if (l_sizeResultQuerry) {
        for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
          //int l_KonradBoardOutput_id = row["KonradBoardOutput_id"].as<int>();
          //int l_FEBTRBConnection_id = row["KBTRBConnection_id"].as<int>();
          //int l_TRBInput_id = row["TRBInput_id"].as<int>();
          int l_TRB_id = row["TRB_id"].as<int>();

          for (unsigned int l_TRB_index = 0u; l_TRB_index < l_TRBsSize; ++l_TRB_index) {
//            int l_TRBId = ((JPetTRB*)fTRBs[l_TRB_index])->getID();
            int l_TRBId = paramBank.getTRB(l_TRB_index).getID();

            if (l_TRBId == l_TRB_id) {
              // ((JPetFEB*)fFEBs[l_FEB_index])->setTRefTRB( *((JPetTRB*)fTRBs[l_TRB_index]) );
              paramBank.getFEB(l_FEB_index).setTRB( paramBank.getTRB(l_TRB_index));
            }
          }
        }
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

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  pqxx::result l_runDbResults = getDataFromDB("getEverythingVsTOMB",l_run_id);
  
  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    {
      for (pqxx::result::const_iterator row = l_runDbResults.begin(); 
	   row != l_runDbResults.end(); 
	   ++row) 
	{
	  std::string l_TOMB_description =  row["tomb"].as<std::string>();
	  int l_TOMB_no = getTOMBChannelFromDescription(l_TOMB_description);
	  int l_TRB_id = row["trb_id"].as<int>();
	  int l_FEB_id = row["konradboard_id"].as<int>();
	  int l_PM_id = row["photomultiplier_id"].as<int>();
	  int l_Slot_id = row["slot_id"].as<int>();
	  float l_Threshold = row["threshold"].as<float>();
	  
	  // find index of TOMBChannel with l_TOMB_no
	  int tombch_index;
	  for(tombch_index=0;
	      tombch_index < paramBank.getTOMBChannelsSize();
	      tombch_index++)
	    {
	      if( l_TOMB_no == paramBank.getTOMBChannel(tombch_index).getChannel() ){
		break;
	      }
	    }
	  // TRBs
	  for(int l_trb_index=0;
	      l_trb_index < paramBank.getTRBsSize();
	      l_trb_index++)
	    {
	      if( paramBank.getTRB(l_trb_index).getID() == l_TRB_id ){
		paramBank.getTOMBChannel(tombch_index).setTRB( paramBank.getTRB(l_trb_index) );
	      }
	    }

	  // FEBs
	  for(int l_feb_index=0;
	      l_feb_index < paramBank.getFEBsSize();
	      l_feb_index++)
	    {
	      if( paramBank.getFEB(l_feb_index).getID() == l_FEB_id ){
		paramBank.getTOMBChannel(tombch_index).setFEB( paramBank.getFEB(l_feb_index) );
	      }
	    }

	  // PMs
	  for(int l_pm_index=0;
	      l_pm_index < paramBank.getPMsSize();
	      l_pm_index++)
	    {
	      if( paramBank.getPM(l_pm_index).getID() == l_PM_id ){
		paramBank.getTOMBChannel(tombch_index).setPM( paramBank.getPM(l_pm_index) );
	      }
	    }

	  // thresholds
	  paramBank.getTOMBChannel(tombch_index).setThreshold( l_Threshold );
	}

    }
  } else {
    printErrorMessageDB("getDataFromTOMBChannels", p_run_id);
  }
}

void JPetDBParamGetter::fillAllTRefs(const int p_run_id, JPetParamBank& paramBank)
{
  if (paramBank.getScintillatorsSize() > 0
      && paramBank.getPMsSize() > 0
      && paramBank.getFEBsSize() > 0
      && paramBank.getTRBsSize() > 0
     ) {
    fillPMsTRefs(p_run_id, paramBank);
    fillFEBsTRefs(p_run_id, paramBank);
    fillTRBsTRefs(p_run_id, paramBank);
    fillTOMBChannelsTRefs(p_run_id, paramBank);
  } else {
    ERROR("Containers are empty.");
  }
}


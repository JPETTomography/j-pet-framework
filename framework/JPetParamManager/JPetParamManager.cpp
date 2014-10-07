#include "JPetParamManager.h"
#include "../DBHandler/HeaderFiles/DBHandler.h"
#include <boost/lexical_cast.hpp>
#include "../JPetLogger/JPetLogger.h"
//#include "../JPetLogger/JPetLoggerInclude.h"

#include <TFile.h>

using namespace std;


JPetParamManager::JPetParamManager()
{
}

/// @param DBConfigFile configuration file with the database connection settings
JPetParamManager::JPetParamManager(const char* dBConfigFile)
{
  DB::SERVICES::DBHandler::getInstance(dBConfigFile); /// this command aims to load the configuration file, the return value is irrelevant

}

bool JPetParamManager::saveParametersToFile(const char* filename)
{
  TFile file(filename, "UPDATE");
  if (!file.IsOpen()) {
    ERROR("Could not write to file.");
    return false;
  }
  file.cd();
  file.WriteObject(&fBank, "ParamBank");
  return true;
}

bool JPetParamManager::readParametersFromFile(const char* filename)
{
  TFile file(filename, "READ");
  if (!file.IsOpen()) {
    ERROR("Could not read from file.");
    return false;
  }
  JPetParamBank* bank = static_cast<JPetParamBank*>(file.Get("ParamBank"));
  fBank = *bank; /// @warning that might not work
  if (!bank) return false;
  return true;
}

std::string JPetParamManager::generateSelectQuery(std::string sqlFun, std::string run_id) {
  std::string sqlQuerry = "SELECT * FROM ";
  sqlQuerry += sqlFun;
  sqlQuerry += "(" +run_id + ");";
  return sqlQuerry;
}

void JPetParamManager::fillScintillators(const int p_run_id)
{
  INFO("Start filling Scintillators container.");
  DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);


  std::string l_sqlQuerry = generateSelectQuery("getDataFromScintillators",l_run_id);
    //"SELECT * FROM getDataFromScintillators(" + l_run_id + ");";

  pqxx::result l_runDbResults = l_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {

      int l_scintillator_id = row["scintillator_id"].as<int>();

      double l_scintillator_length = row["scintillator_length"].as<double>();
      double l_scintillator_width = row["scintillator_width"].as<double>();
      double l_scintillator_height = row["scintillator_height"].as<double>();

      int l_setup_id = row["setup_id"].as<int>();
      int l_run_id = row["run_id"].as<int>();

      /*JPetScin *l_scin = new JPetScin(l_scintillator_id,
      	       0.f,			/// @todo what is attenuation length in database?
      	       l_scintillator_length,
      	       l_scintillator_height,
      	       l_scintillator_width);

      fScintillators.push_back(l_scin);*/

      JPetScin l_scin(l_scintillator_id,
                      0.f,			/// @todo what is attenuation length in database?
                      l_scintillator_length,
                      l_scintillator_height,
                      l_scintillator_width);

      fBank.addScintillator(l_scin);
    }
  } else {
    std::string l_error("getDataFromScintillators() querry for run_id = ");
    l_error += p_run_id + " return 0 records.";
    ERROR(l_error.c_str());
  }
}

void JPetParamManager::fillPMs(const int p_run_id)
{
  INFO("Start filling PMs container.");
  DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);

  std::string l_sqlQuerry = generateSelectQuery("getDataFromPhotoMultipliers",l_run_id);
//  std::string l_sqlQuerry = "SELECT * FROM getDataFromPhotoMultipliers(" + l_run_id + ");";
  pqxx::result l_runDbResults = l_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {

      int l_hvpmconnection_id = row["hvpmconnection_id"].as<int>();
      bool l_hvpmconnection_isrightside = row["hvpmconnection_isrightside"].as<bool>();

      int l_photomultiplier_id = row["photomultiplier_id"].as<int>();

      int l_setup_id = row["setup_id"].as<int>();
      int l_run_id = row["run_id"].as<int>();

      JPetPM::Side l_side = (l_hvpmconnection_isrightside) ? JPetPM::Side::kRight : JPetPM::Side::kLeft;

      /* Implementarion for
      JPetPM *l_pm = new JPetPM();
      l_pm->setID(l_photomultiplier_id);
      l_pm->setSide(l_side);

      fPMs.push_back(l_pm);*/

      JPetPM l_pm;
      l_pm.setID(l_photomultiplier_id);
      l_pm.setSide(l_side);

      fBank.addPM(l_pm);
    }
  } else {
    std::string l_error("getDataFromPhotoMultipliers() querry for run_id = ");
    l_error += p_run_id + " return 0 records.";
    ERROR(l_error.c_str());
  }
}

void JPetParamManager::fillFEBs(const int p_run_id)
{
  INFO("Start filling FEBs container.");
  DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);

  std::string l_sqlQuerry = "SELECT * FROM getDataFromKonradBoards(" + l_run_id + ");";
  pqxx::result l_runDbResults = l_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
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

      fBank.addFEB(l_FEB);
    }
  } else {
    std::string l_error("getDataFromKonradBoards() querry for run_id = ");
    l_error += p_run_id + " return 0 records.";
    ERROR(l_error.c_str());
  }
}

void JPetParamManager::fillTRBs(const int p_run_id)
{
  INFO("Start filling TRBs container.");
  DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);

  std::string l_sqlQuerry = "SELECT * FROM getDataFromTRBs(" + l_run_id + ");";
  pqxx::result l_runDbResults = l_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
      int l_TRB_id = row["TRB_id"].as<int>();

      int l_setup_id = row["setup_id"].as<int>();
      int l_run_id = row["run_id"].as<int>();

      /*JPetTRB *l_TRB = new JPetTRB(l_TRB_id,
      	    0,		/// @todo what is type in database
      	    0);		/// @todo what is channel in database

      fTRBs.push_back(l_TRB);*/

      JPetTRB l_TRB(l_TRB_id,
                    0,		/// @todo what is type in database
                    0);		/// @todo what is channel in database

      fBank.addTRB(l_TRB);
    }
  } else {
    std::string l_error("getDataFromTRBs() querry for run_id = ");
    l_error += p_run_id + " return 0 records.";
    ERROR(l_error.c_str());
  }
}

void JPetParamManager::fillTOMB(const int p_run_id)
{
  INFO("Start filling TOMBs container.");
  DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();

  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);

  std::string l_sqlQuerry = "SELECT * FROM getDataFromTOMB(" + l_run_id + ");";
  pqxx::result l_runDbResults = l_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if (l_sizeResultQuerry) {
    //for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row)
    {
      pqxx::result::const_iterator row = l_runDbResults.begin();

      int l_TOMB_id = row["TOMB_id"].as<int>();
      std::string l_TOMB_description = row["TOMB_description"].as<std::string>();
      //int l_TOMB_setup_id = row["TOMB_setup_id"].as<int>();

      int l_setup_id = row["setup_id"].as<int>();
      int l_run_id = row["run_id"].as<int>();

      //fTOMB = new JPetTOMB(l_TOMB_id, l_TOMB_description);

      JPetTOMB l_TOMB(l_TOMB_id, l_TOMB_description);

      fBank.setTOMB(l_TOMB);
    }
  } else {
    std::string l_error("getDataFromTOMB() querry for run_id = ");
    l_error += p_run_id + " return 0 records.";
    ERROR(l_error.c_str());
  }
}

void JPetParamManager::getParametersFromDatabase(const int run)
{
  fillAllContainers(run);
}

void JPetParamManager::fillAllContainers(const int p_run_id)
{
  fillScintillators(p_run_id);
  fillPMs(p_run_id);
  fillFEBs(p_run_id);
  fillTRBs(p_run_id);
  fillTOMB(p_run_id);
}

void JPetParamManager::fillScintillatorsTRefs()
{
  INFO("Start filling Scintillators TRefs.");

  int l_scintillatorsSize = fBank.getScintillatorsSize();
  int l_PMsSize = fBank.getPMsSize();

  if (l_scintillatorsSize > 0 && l_PMsSize > 0) {
    DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();

    for (unsigned int l_scintillator_index = 0u; l_scintillator_index < l_scintillatorsSize; ++l_scintillator_index) {
      fBank.getScintillator(l_scintillator_index).clearTRefPMs();
//      ((JPetScin*)fScintillators[l_scintillator_index])->clearTRefPMs();

//      std::string l_scitillator_id = boost::lexical_cast<std::string>(((JPetScin*)fScintillators[l_scintillator_index])->getID());
      std::string l_scitillator_id = boost::lexical_cast<std::string>(fBank.getScintillator(l_scintillator_index).getID());

      std::string l_sqlQuerry = "SELECT * FROM getPhotoMultipliersForScintillator(" + l_scitillator_id + ");";
      pqxx::result l_runDbResults = l_dbHandlerInstance.querry(l_sqlQuerry);

      size_t l_sizeResultQuerry = l_runDbResults.size();

      if (l_sizeResultQuerry) {
        for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
          int l_SLSCConnection_id = row["SLSCConnection_id"].as<int>();
          int l_TOMB_id = row["Slot_id"].as<int>();
          int l_HVPMConnection_id = row["HVPMConnection_id"].as<int>();
          int l_PhotoMultiplier_id = row["PhotoMultiplier_id"].as<int>();

          for (unsigned int l_PM_index = 0u; l_PM_index < l_PMsSize; ++l_PM_index) {
            //        int l_PM_id = ((JPetPM*)fPMs[l_PM_index])->getID();
            int l_PM_id = fBank.getPM(l_PM_index).getID();

            if (l_PM_id == l_PhotoMultiplier_id) {
              //            JPetPM::Side l_PM_side = ((JPetPM*)fPMs[l_PM_index])->getSide();
              JPetPM::Side l_PM_side = fBank.getPM(l_PM_index).getSide();

              if (l_PM_side == JPetPM::Side::kLeft) {
                //      ((JPetScin*)fScintillators[l_scintillator_index])->setLeftTRefPM( *((JPetPM*)fPMs[l_PM_index]) );
                fBank.getScintillator(l_scintillator_index).setLeftTRefPM(fBank.getPM(l_PM_index));
              } else if (l_PM_side == JPetPM::Side::kRight) {
                //         ((JPetScin*)fScintillators[l_scintillator_index])->setRightTRefPM( *((JPetPM*)fPMs[l_PM_index]) );
                fBank.getScintillator(l_scintillator_index).setRightTRefPM( fBank.getPM(l_PM_index) );
              }
            }
          }
        }
      }
    }
  } else {
    if (l_scintillatorsSize == 0)
      ERROR("Scintillators container is empty.");
    if (l_PMsSize == 0)
      ERROR("PMs container is empty.");
  }
}

void JPetParamManager::fillPMsTRefs()
{
  INFO("Start filling PMs TRefs.");

  int l_PMsSize = fBank.getPMsSize();
  int l_FEBsSize = fBank.getFEBsSize();

  if (l_PMsSize > 0 && l_FEBsSize > 0) {
    DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();

    for (unsigned int l_PM_index = 0u; l_PM_index < l_PMsSize; ++l_PM_index) {
//      ((JPetPM*)fPMs[l_PM_index])->clearTRefFEBs();
      fBank.getPM(l_PM_index).clearTRefKBs();

      //std::string l_PM_id = boost::lexical_cast<std::string>(((JPetPM*)fPMs[l_PM_index])->getID());
      std::string l_PM_id = boost::lexical_cast<std::string>(fBank.getPM(l_PM_index).getID());

      std::string l_sqlQuerry = "SELECT * FROM getKonradBoardsForPhotoMultiplier(" + l_PM_id + ");";
      pqxx::result l_runDbResults = l_dbHandlerInstance.querry(l_sqlQuerry);

      size_t l_sizeResultQuerry = l_runDbResults.size();

      if (l_sizeResultQuerry) {
        for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
          int l_PMFEBConnection_id = row["PMKBConnection_id"].as<int>();
          int l_KonradBoardInput_id = row["KonradBoardInput_id"].as<int>();
          int l_KonradBoard_id = row["KonradBoard_id"].as<int>();

          for (unsigned int l_FEB_index = 0u; l_FEB_index < l_FEBsSize; ++l_FEB_index) {
//            int l_FEB_id = ((JPetFEB*)fFEBs[l_FEB_index])->id();
            int l_FEB_id = fBank.getFEB(l_FEB_index).id();

            if (l_FEB_id == l_KonradBoard_id) {
//              ((JPetPM*)fPMs[l_PM_index])->setTRefFEB( *((JPetFEB*)fFEBs[l_FEB_index]) );
              fBank.getPM(l_PM_index).setTRefKB(fBank.getFEB(l_FEB_index) );
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
}

void JPetParamManager::fillFEBsTRefs()
{
  INFO("Start filling FEBs TRefs.");

  int l_FEBsSize = fBank.getFEBsSize();
  int l_TRBsSize = fBank.getTRBsSize();

  if (l_FEBsSize > 0 && l_TRBsSize > 0) {
    DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();

    for (unsigned int l_FEB_index = 0u; l_FEB_index < l_FEBsSize; ++l_FEB_index) {

//     ((JPetFEB*)fFEBs[l_FEB_index])->clearTRefTRBs();
      fBank.getFEB(l_FEB_index).clearTRefTRBs();

//      std::string l_FEB_id = boost::lexical_cast<std::string>(((JPetFEB*)fFEBs[l_FEB_index])->id());
      std::string l_FEB_id = boost::lexical_cast<std::string>(fBank.getFEB(l_FEB_index).id());

      std::string l_sqlQuerry = "SELECT * FROM getTRBsForKonradBoard(" + l_FEB_id + ");";
      pqxx::result l_runDbResults = l_dbHandlerInstance.querry(l_sqlQuerry);

      size_t l_sizeResultQuerry = l_runDbResults.size();

      if (l_sizeResultQuerry) {
        for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
          int l_KonradBoardOutput_id = row["KonradBoardOutput_id"].as<int>();
          int l_FEBTRBConnection_id = row["KBTRBConnection_id"].as<int>();
          int l_TRBInput_id = row["TRBInput_id"].as<int>();
          int l_TRB_id = row["TRB_id"].as<int>();

          for (unsigned int l_TRB_index = 0u; l_TRB_index < l_TRBsSize; ++l_TRB_index) {
//            int l_TRBId = ((JPetTRB*)fTRBs[l_TRB_index])->getID();
            int l_TRBId = fBank.getTRB(l_TRB_index).getID();

            if (l_TRBId == l_TRB_id) {
              // ((JPetFEB*)fFEBs[l_FEB_index])->setTRefTRB( *((JPetTRB*)fTRBs[l_TRB_index]) );
              fBank.getFEB(l_FEB_index).setTRefTRB( fBank.getTRB(l_TRB_index));
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

void JPetParamManager::fillTRBsTRefs()
{
  INFO("Start filling TRBs TRefs.");

  int l_TRBsSize = fBank.getTRBsSize();
  int l_TOMBSize = 1;

  if (l_TRBsSize > 0 && l_TOMBSize > 0) {
    DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();

    for (unsigned int l_TRB_index = 0u; l_TRB_index < l_TRBsSize; ++l_TRB_index) {
//      ((JPetTRB*)fTRBs[l_TRB_index])->clearTRefTOMB();
      fBank.getTRB(l_TRB_index).clearTRefTOMB();

      //std::string l_TRB_id = boost::lexical_cast<std::string>(((JPetTRB*)fTRBs[l_TRB_index])->getID());
      std::string l_TRB_id = boost::lexical_cast<std::string>(fBank.getTRB(l_TRB_index).getID());

      std::string l_sqlQuerry = "SELECT * FROM getTOMBForTRB(" + l_TRB_id + ");";
      pqxx::result l_runDbResults = l_dbHandlerInstance.querry(l_sqlQuerry);

      size_t l_sizeResultQuerry = l_runDbResults.size();

      if (l_sizeResultQuerry) {
        for (pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) {
          int l_TRBOutput_id = row["TRBOutput_id"].as<int>();
          int l_TRBTOMBConnection_id = row["TRBTOMBConnection_id"].as<int>();
          int l_TOMBInput_id = row["TOMBInput_id"].as<int>();
          int l_TOMB_id = row["TOMB_id"].as<int>();

          for (unsigned int l_TOMB_index = 0u; l_TOMB_index < l_TOMBSize; ++l_TOMB_index) {
//            int l_TOMBId = ((JPetTOMB*)fTOMB[l_TOMB_index])->id();
            int l_TOMBId = fBank.getTOMB().id();

            if (l_TOMBId == l_TOMB_id) {
              // ((JPetTRB*)fTRBs[l_TRB_index])->setTRefTOMB( *((JPetTOMB*)fTOMB[l_TOMB_index]) );
              fBank.getTRB(l_TRB_index).setTRefTOMB(fBank.getTOMBAddress());
            }
          }
        }
      }
    }
  } else {
    if (l_TRBsSize == 0)
      ERROR("TRBs container is empty.");
    if (l_TOMBSize == 0)
      ERROR("TOMBs container is empty.");
  }
}

void JPetParamManager::fillAllTRefs()
{
  if (fBank.getScintillatorsSize() > 0
      && fBank.getPMsSize() > 0
      && fBank.getFEBsSize() > 0
      && fBank.getTRBsSize() > 0
     ) {
    fillScintillatorsTRefs();
    fillPMsTRefs();
    fillFEBsTRefs();
    fillTRBsTRefs();
  } else {
    ERROR("Containers are empty.");
  }
}


void JPetParamManager::clearParameters()
{
  fBank.clear();
}

// Main - Main.cpp
#include <iostream>
#include <cstdlib>
#include "../HeaderFiles/Declarations.h"
//#include "../HeaderFiles/DBHandler.h"
#include "../HeaderFiles/ParamServer.h"
//#include "../HeaderFiles/Functions.h"

using namespace std;


int main(int argc, char* argv[])
{  
  cout << "We are in main function - working." << endl;
  
  /*
  //DB::SERVICES::DBHandler *l_dBHandler = new DB::SERVICES::DBHandler("testDB", "andrzej", "max07", "127.0.0.1", "5432");
  DB::SERVICES::DBHandler *l_dBHandler = new DB::SERVICES::DBHandler();
  l_dBHandler->connect();
  //
  l_dBHandler->saveTableMyTabToFile();
  //
  l_dBHandler->insertIntoTableMyTab(3, "Adam" , 25);
  //
  l_dBHandler->disconnect();	// NOTICE:  there is no transaction in progress
  
  delete l_dBHandler;
  */

  // test zapytania
  /*DB::SERVICES::DBHandler *l_dBHandler = new DB::SERVICES::DBHandler();

  //l_dBHandler->querryTest();
  //l_dBHandler->insertIntoTableMyTab(1, "ala", 20);

  delete l_dBHandler;*/

  DB::SERVER::ParamServer *l_paramServer = new DB::SERVER::ParamServer();

  l_paramServer->fillPhotoMultiplierMap();
  l_paramServer->showPhotoMultiplierMap();

  boost::optional<std::pair<int, int> > l_pairOfPhotoMultiplierBoostOptionalForSlotId_1 = l_paramServer->pairOfPhotoMultiplierForSlotId(1);
  if(l_pairOfPhotoMultiplierBoostOptionalForSlotId_1)
  {
    std::pair<int, int> l_pairOfPhotoMultiplierForSlotId = l_pairOfPhotoMultiplierBoostOptionalForSlotId_1.get();
    std::cout << "l_pairOfPhotoMultiplierForSlotId.first = " << l_pairOfPhotoMultiplierForSlotId.first << " l_pairOfPhotoMultiplierForSlotId.second = " << l_pairOfPhotoMultiplierForSlotId.second << std::endl;
  }

  boost::optional<std::pair<int, int> > l_pairOfPhotoMultiplierBoostOptionalForSlotId_2 = l_paramServer->pairOfPhotoMultiplierForSlotId(2);
  if(l_pairOfPhotoMultiplierBoostOptionalForSlotId_2)
  {
    std::pair<int, int> l_pairOfPhotoMultiplierForSlotId = l_pairOfPhotoMultiplierBoostOptionalForSlotId_2.get();
    std::cout << "l_pairOfPhotoMultiplierForSlotId = " << l_pairOfPhotoMultiplierForSlotId.first << " l_pairOfPhotoMultiplierForSlotId.secon = " << l_pairOfPhotoMultiplierForSlotId.second << std::endl;
  }

  l_paramServer->savePhotoMultiplierMapToFile();

  // test runDataMap
  l_paramServer->fillRunDataMap();
  std::cout << "l_paramServer->sizeOfRunDataMap() = " << l_paramServer->sizeOfRunDataMap() << std::endl;
  l_paramServer->showRunDataMap();

  DB::DATA::RunData ll = l_paramServer->dataFromRun(1).get();
  std::cout << ll.runStart() << std::endl;

  delete l_paramServer;

//read config file
/*
  DB::FUNCTIONS::DBConfigData l_dbconfig;
  DB::FUNCTIONS::DBConfigControler::readConfigFileAndFillDBConfigData("../Config/configDB.cfg", l_dbconfig);

  std::cout << "m_configFileName : " << l_dbconfig.m_db_configFileName << std::endl;
*/

  //deleteSingletonInstances();
  //DB::SERVICES::DBHandler::deleteInstance();

  return (EXIT_SUCCESS);
}

// g++ ../HeaderFiles/DBHandler.h ../SourceFiles/DBHandler.cpp ../HeaderFiles/ParamServer.h ../SourceFiles/ParamServer.cpp ../SourceFiles/Main.cpp -I/usr/local/include/ -Wall -lpqxx -lpq -o main && ./main

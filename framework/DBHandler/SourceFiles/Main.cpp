// Main - Main.cpp
#include <iostream>
#include <cstdlib>
#include "../HeaderFiles/Declarations.h"
//#include "../HeaderFiles/DBHandler.h"
#include "../HeaderFiles/ParamServer.h"
//#include "../HeaderFiles/Functions.h"
#include "../HeaderFiles/ParamData.h"
#include "../HeaderFiles/TOMBInputMap.h"

using namespace std;


int main(int argc, char* argv[])
{
  cout << "We are in main - working." << endl;

  DB::SERVER::ParamServer *l_paramServer = new DB::SERVER::ParamServer();

  std::cout << "\nPhotoMultiplierMap\n" << std::endl;
  l_paramServer->photoMultiplier_Map().fillMap(1);
  l_paramServer->photoMultiplier_Map().showMap();

  std::cout << "\nRunDataMap\n" << std::endl;
  l_paramServer->runData_Map().fillMap();
  l_paramServer->runData_Map().showMap();

  std::cout << "\nTRBThreshold_Map\n" << std::endl;
  l_paramServer->TRBThreshold_Map().fillMap(1);
  l_paramServer->TRBThreshold_Map().showMap();

  std::cout << "\nPhotoMultiplierIdMap\n" << std::endl;
  l_paramServer->photoMultiplierId_Map().fillMap(1);
  l_paramServer->photoMultiplierId_Map().showMap();

  std::cout << "\nTOMBInput_Map\n" << std::endl;
  l_paramServer->TOMBInput_Map().fillMap(1);
  l_paramServer->TOMBInput_Map().showMap();

  std::cout << "\nPassedInformation_Map\n" << std::endl;
  l_paramServer->passedInformation_Map().fillMap(1);
  l_paramServer->passedInformation_Map().showMap();

  /********************************************************/
  DB::DATA::ParamData *l_paramData = new DB::DATA::ParamData(*l_paramServer);
  std::pair<DB::DATA::TOMB_INPUT_MAP_KEY_TYPE, DB::DATA::TOMB_INPUT_MAP_VALUE_TYPE > l_firstElementFromTOMBInputMap = *l_paramServer->TOMBInput_Map().firstElement();
  std::cout << "\n TOMBInputIdFromTOMBInputMap = " << l_paramData->getTOMBInputIdFromTOMBInputMap(l_firstElementFromTOMBInputMap.first) << std::endl;
  DB::DATA::TOMB_INPUT_MAP_KEY_TYPE l_TRBIdAndTRBoutputIdFromTOMBInputMap = *l_paramData->getTRBIdAndTRBoutputIdFromTOMBInputMap(l_firstElementFromTOMBInputMap.second);
  //DB::DATA::TOMB_INPUT_MAP_KEY_TYPE l_TRBIdAndTRBoutputIdFromTOMBInputMap = *l_paramData->getTRBIdAndTRBoutputIdFromTOMBInputMap(4);
  std::cout << "\n l_TRBIdAndTRBoutputIdFromTOMBInputMap.first = " << l_TRBIdAndTRBoutputIdFromTOMBInputMap.first << std::endl;
  std::cout << "\n l_TRBIdAndTRBoutputIdFromTOMBInputMap.second = " << l_TRBIdAndTRBoutputIdFromTOMBInputMap.second << std::endl;
  std::cout << "\n TRBIdFromTOMBInputMap = " << l_paramData->getTRBIdFromTOMBInputMap(l_firstElementFromTOMBInputMap.second) << std::endl;
  std::cout << "\n TRBOutputIdFromTOMBInputMap = " << l_paramData->getTRBOutputIdFromTOMBInputMap(l_firstElementFromTOMBInputMap.second) << std::endl;
  delete l_paramData;
  /********************************************************/

  //std::pair<int, int> l_pair(3,4);
  //std::cout << l_pair << std::endl;

  delete l_paramServer;

  return (EXIT_SUCCESS);
}

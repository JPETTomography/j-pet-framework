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

  delete l_paramServer;

  return (EXIT_SUCCESS);
}

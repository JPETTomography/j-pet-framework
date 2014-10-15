#include "JPetParamManager.h"

#include <TFile.h>

using namespace std;


JPetParamManager::JPetParamManager()
{
}

/// @param DBConfigFile configuration file with the database connection settings
JPetParamManager::JPetParamManager(const char* dBConfigFile):fDBParamGetter(dBConfigFile)
{
}

void JPetParamManager::getParametersFromDatabase(const int run)
{
  fBank = fDBParamGetter.generateParamBank(run);
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


void JPetParamManager::clearParameters()
{
  fBank.clear();
}

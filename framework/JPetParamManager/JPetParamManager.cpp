#include "JPetParamManager.h"

#include <TFile.h>

using namespace std;


JPetParamManager::JPetParamManager():
  fBank(0)
{
  /* */
}

JPetParamManager::~JPetParamManager()
{
  if (fBank) {
    delete fBank;
    fBank = 0;
  }
}

/// @param DBConfigFile configuration file with the database connection settings
JPetParamManager::JPetParamManager(const char* dBConfigFile):
  fDBParamGetter(dBConfigFile),
  fBank(0)
{
}

void JPetParamManager::getParametersFromDatabase(const int run)
{
  if (fBank) {
    delete fBank;
    fBank = 0;
  }
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
  file.WriteObject(fBank, "ParamBank");
  return true;
}

bool JPetParamManager::saveParametersToFile(JPetWriter * writer)
{
  if (!writer->isOpen()) {
    ERROR("Could not write parameters to file. The provided JPetWriter is closed.");
    return false;
  }
  writer->WriteObject(fBank, "ParamBank");
  return true;
}


bool JPetParamManager::readParametersFromFile(JPetReader * reader)
{
  if (!reader->isOpen()) {
    ERROR("Cannot read parameters from file. The provided JPetReader is closed.");
    return false;
  }
  fBank = static_cast<JPetParamBank*>(reader->GetObject("ParamBank"));

  if (!fBank) return false;
  return true;
}

bool JPetParamManager::readParametersFromFile(const char* filename)
{
  TFile file(filename, "READ");
  if (!file.IsOpen()) {
    ERROR("Could not read from file.");
    return false;
  }
  fBank = static_cast<JPetParamBank*>(file.Get("ParamBank"));

  if (!fBank) return false;
  return true;
}


void JPetParamManager::clearParameters()
{
  assert(fBank);
  fBank->clear();
}

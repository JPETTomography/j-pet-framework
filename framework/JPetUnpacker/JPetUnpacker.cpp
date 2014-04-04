#include "./JPetUnpacker.h"
#include "../../JPetLoggerInclude.h"
#include <boost/filesystem.hpp>
#include <cassert>

ClassImp(JPetUnpacker);

JPetUnpacker::JPetUnpacker():
fUnpacker(0),
fEventsToProcess(0),
fHldFile(""),
fCfgFile("")
{
  /**/
}


JPetUnpacker::~JPetUnpacker()
{
  if (fUnpacker) {
    delete fUnpacker;
    fUnpacker = 0;
  }
}


void JPetUnpacker::setParams(const std::string& hldFile,  int numOfEvents, const std::string& cfgFile)
{
  fHldFile = hldFile;
  fCfgFile = cfgFile;
  fEventsToProcess = numOfEvents;
}

void JPetUnpacker::Exec()
{
  assert(getEventsToProcess() > 0);
  if ( !boost::filesystem::exists(getHldFile())) 
  {
    ERROR("The hld file doesnt exist");
    return;
  }
  if (!boost::filesystem::exists(getCfgFile())) 
  {
    ERROR("The config file doesnt exist");
    return;
  }
  if (fUnpacker) {
    delete fUnpacker;
    fUnpacker = 0;
  }
  fUnpacker = new Unpacker2(fHldFile.c_str(), fCfgFile.c_str(), fEventsToProcess);
}




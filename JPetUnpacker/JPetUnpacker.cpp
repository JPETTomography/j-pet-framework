#include "./JPetUnpacker.h"
#include "../JPetLoggerInclude.h"
#include <boost/filesystem.hpp>
#include <cassert>

#include "JPetPostUnpackerFilter.h"

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

bool JPetUnpacker::exec()
{
  if ( !boost::filesystem::exists(getHldFile())) 
  {
    ERROR("The hld file doesnt exist");
    return false;
  }
  if (!boost::filesystem::exists(getCfgFile())) 
  {
    ERROR("The config file doesnt exist");
    return false;
  }
  if(getEventsToProcess() <= 0)
  {
    ERROR("No events to process");
    return false;
  }
  if (fUnpacker) {
    delete fUnpacker;
    fUnpacker = 0;
  }
  fUnpacker = new Unpacker2(fHldFile.c_str(), fCfgFile.c_str(), fEventsToProcess);

  // apply post-unpacking filters
  string newFileName = fHldFile + ".root";

  // @todo: handle the following parameters needed by calculate_times
  const char * calibFileName = "";
  int refChannelOffset = 65;
  JPetPostUnpackerFilter::calculate_times(fEventsToProcess, newFileName.c_str(), refChannelOffset, "");

  newFileName = newFileName.substr(0, newFileName.size() - 5);
  newFileName += "_times.root";
  
  JPetPostUnpackerFilter::calculate_hits(fEventsToProcess, newFileName.c_str());
  
  return true;
}




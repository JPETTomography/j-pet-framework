/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetUnpacker.cpp
 *  @brief facade for Unpacker program which unpacks raw data to root files
 */

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
    ERROR(std::string( "The hld file doesnt exist: ") + getHldFile() );
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
  string newFileName = fHldFile + ".raw.root";

  // @todo: handle the following parameters needed by calculate_times
  //const char * calibFileName = "";
  int refChannelOffset = 65;
  JPetPostUnpackerFilter::calculate_times(fEventsToProcess, newFileName.c_str(), refChannelOffset, "");

  newFileName = newFileName.substr(0, newFileName.size() - 8);
  newFileName += "times.root";
  
  JPetPostUnpackerFilter::calculate_hits(fEventsToProcess, newFileName.c_str());
  
  return true;
}




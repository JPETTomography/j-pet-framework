/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 */

#include "./JPetLoggerInclude.h"
#include <boost/filesystem.hpp>
#include "./JPetUnpacker.h"
#include <cassert>

JPetUnpacker::JPetUnpacker(): fUnpacker(0), fEventsToProcess(0), fHldFile(""),
  fCfgFile(""), fTOTCalibFile(""), fTDCCalibFile("") {}

JPetUnpacker::~JPetUnpacker()
{
  if (fUnpacker) {
    delete fUnpacker;
    fUnpacker = 0;
  }
}

void JPetUnpacker::setParams(const std::string& hldFile, int numOfEvents,
                             const std::string& cfgFile, const std::string& totCalibFile,
                             const std::string& tdcCalibFile)
{
  fHldFile = hldFile;
  fCfgFile = cfgFile;
  fTOTCalibFile = totCalibFile;
  fTDCCalibFile = tdcCalibFile;
  fEventsToProcess = numOfEvents;
}

bool JPetUnpacker::exec()
{
  if ( !boost::filesystem::exists(getHldFile())) {
    ERROR(std::string( "The hld file doesnt exist: ") + getHldFile() );
    return false;
  }
  if (!boost::filesystem::exists(getCfgFile())) {
    ERROR("The config file doesnt exist");
    return false;
  }
  if (getTOTCalibFile() != "" && !boost::filesystem::exists(getTOTCalibFile())) {
    ERROR("The provided calibration file with TOT stretcher offsets does not exist");
    return false;
  }
  if (getTDCCalibFile() != "" && !boost::filesystem::exists(getTDCCalibFile())) {
    ERROR("The provided file with TDC nonlinearity calibration does not exist");
    return false;
  }
  if (getEventsToProcess() <= 0) {
    ERROR("No events to process");
    return false;
  }
  if (fUnpacker) {
    delete fUnpacker;
    fUnpacker = 0;
  }
  fUnpacker = new Unpacker2();
  int refChannelOffset = 65;
  fUnpacker->UnpackSingleStep(fHldFile.c_str(), fCfgFile.c_str(),
                              fEventsToProcess, refChannelOffset,
                              fTOTCalibFile.c_str(), fTDCCalibFile.c_str()
                             );
  return true;
}

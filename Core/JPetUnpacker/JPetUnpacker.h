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
 *  @file JPetUnpacker.h
 */

#ifndef _JPETUNPACKER_H_
#define _JPETUNPACKER_H_
#include "./Unpacker2/Unpacker2/Unpacker2.h"
#include <string>

class Unpacker2;

/**
 * @brief Facade for Unpacker program which unpacks raw data to root files
 */
class JPetUnpacker
{
public:
  ~JPetUnpacker();
  bool exec();
  inline int getEventsToProcess() const
  {
    return fEventsToProcess;
  }
  inline std::string getHldFile() const
  {
    return fHldFile;
  }
  inline std::string getCfgFile() const
  {
    return fCfgFile;
  }
  inline std::string getTOTCalibFile() const
  {
    return fTOTCalibFile;
  }
  inline std::string getTDCCalibFile() const
  {
    return fTDCCalibFile;
  }
  void setParams(const std::string& hldFile,
                 int numOfEvents = 100000000,
                 const std::string& cfgFile = "conf_trb3.xml",
                 const std::string& totCalibFile = "",
                 const std::string& tdcCalibFile = ""
                );

private:
  Unpacker2* fUnpacker = nullptr;
  int fEventsToProcess = 0;
  std::string fHldFile = "";
  std::string fCfgFile = "";
  std::string fTOTCalibFile = "";
  std::string fTDCCalibFile = "";
};

#endif /* !_JPETUNPACKER_H_ */

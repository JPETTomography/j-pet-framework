/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetUnpackTask.h
 */

#ifndef JPETUNPACKTASK_H
#define JPETUNPACKTASK_H

#include "JPetTask/JPetTask.h"
#include "Unpacker2D.h"
#include "Unpacker2.h"

class Unpacker2D;
class Unpacker2;

class JPetUnpackTask: public JPetTask
{
public:
  using OptsStrAny = std::map<std::string, boost::any>;
  explicit JPetUnpackTask(const char* name = "");
  bool init(const JPetParams& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParams& outOptions) override;

private:
  const std::string kTDCnonlinearityCalibKey = "Unpacker_TDCnonlinearityCalib_std::string";
  const std::string kTOTOffsetCalibKey = "Unpacker_TOToffsetCalib_std::string";
  std::string fTDCnonlinearityCalibFile;
  std::string fTOTOffsetCalibFile;
  std::string fXMLConfFile;

  std::string fInputFile = std::string("");
  std::string fInputFilePath = std::string("");
  std::string fOutputFilePath = std::string("");

  int fEventsToProcess = 100000000;

  Unpacker2D* fUnpacker2D = nullptr;
  Unpacker2* fUnpacker2 = nullptr;
  OptsStrAny fOptions;

};

#endif /* !JPETUNPACKTASK_H */

/**
 *  @copyright Copyright 2022 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetInputHandlerHLD.h
 */

#ifndef JPETINPUTHANDLERHLD_H
#define JPETINPUTHANDLERHLD_H

#include <fstream>
#include <string>

#include <TObject.h>

#include "JPetParamBank/JPetParamBank.h"
#include "JPetTaskIO/JPetInputHandler.h"

#include "unpacker_types.hpp"

using ENDPData = std::vector<unpacker::hit_t>;

class JPetHLDdata : public TObject
{
public:
  unpacker::meta_t fMetaData;
  std::unordered_map<unsigned int, ENDPData> fOriginalData;
  std::unordered_map<unsigned int, std::vector<unpacker::hit_t>> fFilteredData;
  std::unordered_map<unsigned int, std::vector<unpacker::sigmat_t>> fPreprocData;
};

class JPetInputHandlerHLD : public JPetInputHandler
{
public:
  JPetInputHandlerHLD();
  JPetInputHandlerHLD(const JPetInputHandlerHLD&) = delete;
  void operator=(const JPetInputHandlerHLD&) = delete;

  bool nextEntry() override;
  bool openInput(const char* inputFileName, const JPetParams& params) override;
  void closeInput() override;

  TObject& getEntry() override;

  bool setEntryRange(const jpet_options_tools::OptsStrAny& options) override;
  std::tuple<bool, long long, long long> calculateEntryRange(const jpet_options_tools::OptsStrAny& options) const override;

  bool loadTDCCalib(const JPetParams& params);

private:
  std::ifstream fFile;
  JPetHLDdata fEntryData;
  unpacker::tdc_calib_t fTDCCalib;
  const std::string kTOTOffsetCalibKey = "Unpacker_TDCnonlinearityCalib_std::string";
};

#endif /*  !JPETINPUTHANDLERHLD_H */

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
 *  @file JPetInputHandlerROOT.h
 */

#ifndef JPETINPUTHANDLERROOT_H
#define JPETINPUTHANDLERROOT_H

#include "JPetTaskIO/JPetInputHandler.h"
#include <TObject.h>

class JPetInputHandlerROOT : public JPetInputHandler
{
public:
  JPetInputHandlerROOT();
  JPetInputHandlerROOT(const JPetInputHandlerROOT&) = delete;
  void operator=(const JPetInputHandlerROOT&) = delete;

  bool nextEntry() override;
  bool openInput(const char* inputFileName, const JPetParams& params) override;
  void closeInput() override;

  TObject& getEntry() override;

  bool setEntryRange(const jpet_options_tools::OptsStrAny& options) override;
  std::tuple<bool, long long, long long> calculateEntryRange(const jpet_options_tools::OptsStrAny& options) const override;

  JPetTreeHeader* getHeaderClone() override;


protected:
  std::unique_ptr<JPetReaderInterface> fReader{nullptr};

private:
};

#endif /*  !JPETINPUTHANDLERROOT_H */
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
 *  @file JPetInputHandler.h
 */

#ifndef JPETINPUTHANDLER_H
#define JPETINPUTHANDLER_H

#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetParams/JPetParams.h"
#include "./JPetReader/JPetReader.h"
#include "./JPetTreeHeader/JPetTreeHeader.h"
#include <memory.h>

struct EntryRange
{
  long long firstEntry = 0ll;
  long long lastEntry = 0ll;
  long long currentEntry = -1ll;
};

class JPetInputHandler
{

public:
  JPetInputHandler();
  JPetInputHandler(const JPetInputHandler&) = delete;
  void operator=(const JPetInputHandler&) = delete;

  virtual bool openInput(const char* inputFileName, const JPetParams& params) = 0;
  virtual void closeInput() = 0;
  virtual bool setEntryRange(const jpet_options_tools::OptsStrAny& options) = 0;
  virtual TObject& getEntry() = 0;
  virtual bool nextEntry() = 0;
  /// Function calculates the correct entry range [first, last] based on the options provided and the internal reader state
  virtual std::tuple<bool, long long, long long> calculateEntryRange(const jpet_options_tools::OptsStrAny& options) const = 0;

  EntryRange getEntryRange() const;
  long long getFirstEntryNumber() const;
  long long getLastEntryNumber() const;
  long long getCurrentEntryNumber() const;

  virtual JPetTreeHeader* getHeaderClone();

protected:
  EntryRange fEntryRange;
};
#endif /*  !JPETINPUTHANDLER_H */

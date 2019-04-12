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

#include <memory.h>
#include "./JPetReader/JPetReader.h"
#include "./JPetParams/JPetParams.h"
#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetTreeHeader/JPetTreeHeader.h"

struct EntryRange {
  long long firstEntry = 0ll;
  long long lastEntry = 0ll;
  long long currentEntry = -1ll;
};

class JPetInputHandler
{

public:
  JPetInputHandler();

  bool openInput(const char* inputFileName, const JPetParams& params);
  void closeInput();
  bool setEntryRange(const jpet_options_tools::OptsStrAny& options);
  EntryRange getEntryRange() const;
  long long getFirstEntryNumber() const;
  long long getLastEntryNumber() const;
  long long getCurrentEntryNumber() const;
  TObject& getEntry();
  bool nextEntry();

  /// Function calculates the correct entry range [first, last] based on the options provided and the internal reader state
  std::tuple<bool, long long, long long> calculateEntryRange(const jpet_options_tools::OptsStrAny& options) const;

  JPetTreeHeader* getHeaderClone(); /// @todo what to do with this function?
protected:
  std::unique_ptr<JPetReaderInterface> fReader{nullptr};

private:
  JPetInputHandler(const JPetInputHandler&);
  void operator=(const JPetInputHandler&);
  EntryRange fEntryRange;

};
#endif /*  !JPETINPUTHANDLER_H */

/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetInputHandler.cpp
 */

#include "JPetTaskIO/JPetInputHandler.h"
#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "JPetTaskIO/JPetTaskIOTools.h"

JPetInputHandler::JPetInputHandler() { fReader = jpet_common_tools::make_unique<JPetReader>(); }

bool JPetInputHandler::openInput(const char* inputFilename, const JPetParams& params)
{
  using namespace jpet_options_tools;
  auto options = params.getOptions();
  if (fReader->openFileAndLoadData(inputFilename, JPetReader::kRootTreeName.c_str()))
  {
    /// For all types of files which has not hld format we assume
    /// that we can read paramBank from the file.
    if (file_type_checker::getInputFileType(options) != file_type_checker::kHldRoot &&
        file_type_checker::getInputFileType(options) != file_type_checker::kMCGeant)
    {
      auto paramManager = params.getParamManager();
      assert(paramManager);
      if (!paramManager->readParametersFromFile(dynamic_cast<JPetReader*>(fReader.get())))
      {
        ERROR("Failed to read paramBank from input file.");
        return false;
      }
      assert(paramManager->getParamBank().getPMsSize() > 0);
    }
  }
  else
  {
    ERROR(inputFilename + std::string(": Unable to open the input file or load the tree"));
    return false;
  }
  return true;
}

void JPetInputHandler::closeInput()
{
  if (fReader)
  {
    fReader->closeFile();
  }
}

EntryRange JPetInputHandler::getEntryRange() const { return fEntryRange; }

bool JPetInputHandler::setEntryRange(const jpet_options_tools::OptsStrAny& options)
{
  bool isOK = false;
  auto firstEntry = 0ll;
  auto lastEntry = 0ll;
  std::tie(isOK, firstEntry, lastEntry) = calculateEntryRange(options);
  if (!isOK)
  {
    ERROR("Some error occured in setEntryRange");
    return false;
  }
  fEntryRange.firstEntry = firstEntry;
  fEntryRange.lastEntry = lastEntry;
  fEntryRange.currentEntry = firstEntry;
  assert(fReader);
  return fReader->nthEntry(fEntryRange.currentEntry);
}

std::tuple<bool, long long, long long> JPetInputHandler::calculateEntryRange(const jpet_options_tools::OptsStrAny& options) const
{
  auto totalEntries = 0ll;
  if (fReader)
  {
    totalEntries = fReader->getNbOfAllEntries();
  }
  else
  {
    WARNING("no JPETReader,  totalEntries set to -1");
    totalEntries = -1;
  }
  return JPetTaskIOTools::setUserLimits(options, totalEntries);
}

TObject& JPetInputHandler::getEntry()
{
  assert(fReader);
  auto& ob = fReader->getCurrentEntry();
  return ob;
}

bool JPetInputHandler::nextEntry()
{
  if (fEntryRange.currentEntry == fEntryRange.lastEntry)
  {
    return false;
  }
  fEntryRange.currentEntry++;
  assert(fReader);
  return fReader->nextEntry();
}

long long JPetInputHandler::getCurrentEntryNumber() const
{
  assert(fReader);
  return fReader->getCurrentEntryNumber();
}

long long JPetInputHandler::getFirstEntryNumber() const { return fEntryRange.firstEntry; }

long long JPetInputHandler::getLastEntryNumber() const { return fEntryRange.lastEntry; }

JPetTreeHeader* JPetInputHandler::getHeaderClone()
{
  assert(fReader);
  return dynamic_cast<JPetReader*>(fReader.get())->getHeaderClone();
}

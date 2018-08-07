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
 *  @file JPetInputHandler.cpp
 */

#include "./JPetInputHandler.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "JPetTaskIOTools.h"
#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"

JPetInputHandler::JPetInputHandler()
{
  fReader = jpet_common_tools::make_unique<JPetReader>() ;
}

std::tuple<bool, long long, long long> JPetInputHandler::getEventRange(const jpet_options_tools::OptsStrAny& options) const
{
  auto totalEntries = 0ll;
  if (fReader) {
    totalEntries = fReader->getNbOfAllEntries();
  } else {
    WARNING("no JPETReader,  totalEntries set to -1");
    totalEntries = -1;
  }
  return JPetTaskIOTools::setUserLimits(options, totalEntries);
}

bool JPetInputHandler::openInput(const char* inputFilename, const JPetParams& params)
{
  using namespace jpet_options_tools;
  auto options = params.getOptions();
  if (fReader->openFileAndLoadData(inputFilename, JPetReader::kRootTreeName.c_str())) {
    /// For all types of files which has not hld format we assume
    /// that we can read paramBank from the file.
    if (FileTypeChecker::getInputFileType(options) != FileTypeChecker::kHldRoot &&
        FileTypeChecker::getInputFileType(options) != FileTypeChecker::kMCGeant ) {
      auto paramManager = params.getParamManager();
      assert(paramManager);
      if (!paramManager->readParametersFromFile(dynamic_cast<JPetReader*> (fReader.get()))) {
        ERROR("Failed to read paramBank from input file.");
        return false;
      }
      assert(paramManager->getParamBank().getPMsSize() > 0);
    }
  } else {
    ERROR(inputFilename + std::string(": Unable to open the input file or load the tree"));
    return false;
  }
  return true;
}


void JPetInputHandler::closeInput()
{
  if (fReader) {
    fReader->closeFile();
  }
}

TObject& JPetInputHandler::getNextEntry()
{
  assert (fReader);
  ///@todo this is bad code. To be changed.
  auto& ob = fReader->getCurrentEntry();
  fReader->nextEntry();
  return ob;
}

JPetTreeHeader* JPetInputHandler::getHeaderClone()
{
  assert(fReader);
  return dynamic_cast<JPetReader*>(fReader.get())->getHeaderClone();
}

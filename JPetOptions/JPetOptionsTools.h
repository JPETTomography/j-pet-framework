/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetOptionsTools.h
 */

#ifndef JPETOPTIONSTOOLS_H
#define JPETOPTIONSTOOLS_H
#include <map>
#include <boost/any.hpp>

/**
 * @brief Set of helper methods to operate on options provided by users.
 *
 * Options are represented as:
 *  1)std::map<std::string, boost::any> a.k.a. OptionsStrAny
 *  2)std::map<std::string, std::string> a.k.a. OptionsStrStr
 *
 */
namespace jpet_options_tools
{

typedef std::map<std::string, std::string> OptionsStrStr;
typedef std::map<std::string, boost::any> OptionsStrAny;

bool isOptionSet(const OptionsStrAny& opts, const std::string& optionName);
boost::any getOptionValue(const OptionsStrAny& opts, std::string optionName);

class FileTypeChecker
{
public:
  FileTypeChecker();
  enum FileType {
    kNoType, kScope, kRaw, kRoot, kHld, kZip, kPhysEve, kPhysHit, kPhysSig, kRawSig, kRecoSig, kTslotCal, kTslotRaw, kUndefinedFileType
  };
  static FileType getInputFileType(const OptionsStrAny& opts);
  static FileType getOutputFileType(const OptionsStrAny& opts);

private:
  static void handleErrorMessage(const std::string& errorMessage, const std::out_of_range& outOfRangeException);
  static FileType getFileType(const OptionsStrAny& opts, const std::string& fileType);

  static std::map<std::string, FileType> fStringToFileType;
};

///Helper functions to extract option values with correct types

/// This function returns a valid result only if the inputFile option is given
/// in the untransformed form std::vector<std::string>
std::vector<std::string> getInputFiles(const OptionsStrAny& opts);

/// This function returns a valid result only if the inputFile option is given
/// in the transformed form std::string
const char* getInputFile(const OptionsStrAny& opts);

const char* getScopeConfigFile(const OptionsStrAny& opts);
const char* getScopeInputDirectory(const OptionsStrAny& opts);
const char* getOutputFile(const OptionsStrAny& opts);
const char* getOutputPath(const OptionsStrAny& opts);
long long getFirstEvent(const OptionsStrAny& opts);
long long getLastEvent(const OptionsStrAny& opts);
long long getTotalEvents(const OptionsStrAny& opts);
int getRunNumber(const OptionsStrAny& opts);
bool isProgressBar(const OptionsStrAny& opts);
bool isLocalDB(const OptionsStrAny& opts);
std::string getLocalDB(const OptionsStrAny& opts);
bool isLocalDBCreate(const OptionsStrAny& opts);
std::string getLocalDBCreate(const OptionsStrAny& opts);
const char* getUnpackerConfigFile(const OptionsStrAny& opts);
const char* getUnpackerCalibFile(const OptionsStrAny& opts);

OptionsStrAny resetEventRange(const OptionsStrAny& srcOpts);

bool createConfigFileFromOptions(const OptionsStrStr& options, const std::string& outFile = "");
OptionsStrAny createOptionsFromConfigFile(const std::string& inFile);

void printOptionsToLog(const OptionsStrAny& opts, const std::string& firstLine);

}
#endif /*  !JPETOPTIONSTOOLS_H */

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
 *  @file JPetOptionsTools.h
 */

#ifndef JPETOPTIONSTOOLS_H
#define JPETOPTIONSTOOLS_H

#include "JPetOptionsTools/JPetOptionsTransformators.h"
#include <boost/any.hpp>
#include <map>
#include <vector>

/**
 * @brief Set of helper methods to operate on options.
 *
 * Options are represented as:
 * std::map<std::string, boost::any> a.k.a. OptsStrAny
 */
namespace jpet_options_tools
{
using OptsStrAny = std::map<std::string, boost::any>;
using OptsStrStr = std::map<std::string, std::string>;
bool isOptionSet(const OptsStrAny& opts, const std::string& optionName);
boost::any getOptionValue(const OptsStrAny& opts, const std::string& optionName);
bool getOptionAsBool(const OptsStrAny& opts, const std::string& optionName);
int getOptionAsInt(const OptsStrAny& opts, const std::string& optionName);
float getOptionAsFloat(const OptsStrAny& opts, const std::string& optionName);
double getOptionAsDouble(const OptsStrAny& opts, const std::string& optionName);
std::string getOptionAsString(const OptsStrAny& opts, const std::string& optionName);
std::vector<std::string> getOptionAsVectorOfStrings(const OptsStrAny& opts, const std::string& optionName);
std::vector<int> getOptionAsVectorOfInts(const OptsStrAny& opts, const std::string& optionName);
std::vector<double> getOptionAsVectorOfDoubles(const OptsStrAny& opts, const std::string& optionName);
std::vector<std::string> getInputFiles(const OptsStrAny& opts);
std::string getInputFile(const OptsStrAny& opts);
std::string getScopeConfigFile(const OptsStrAny& opts);
std::string getScopeInputDirectory(const OptsStrAny& opts);
std::string getOutputFile(const OptsStrAny& opts);
std::string getOutputPath(const OptsStrAny& opts);
long long getFirstEvent(const OptsStrAny& opts);
long long getLastEvent(const OptsStrAny& opts);
long long getTotalEvents(const OptsStrAny& opts);
int getRunNumber(const OptsStrAny& opts);
bool isProgressBar(const OptsStrAny& opts);
bool isDirectProcessing(const OptsStrAny& opts);
bool isLocalDB(const OptsStrAny& opts);
std::string getLocalDB(const OptsStrAny& opts);
bool isLocalDBCreate(const OptsStrAny& opts);
std::string getLocalDBCreate(const OptsStrAny& opts);
std::string getUnpackerConfigFile(const OptsStrAny& opts);
std::string getConfigFileName(const OptsStrAny& optsMap);
void printOptions(const OptsStrAny& opts);
void printOptionsToLog(const OptsStrAny& opts, const std::string& firstLine);
bool createConfigFileFromOptions(const OptsStrStr& options, const std::string& outFile = "");
OptsStrAny createOptionsFromConfigFile(const std::string& inFile);
void handleErrorMessage(const std::string& errorMessage, const std::out_of_range& outOfRangeException);

namespace file_type_checker
{
enum FileType
{
  kNoType,
  kRoot,
  kScope,
  kHld,
  kHldRoot,
  kZip,
  kMCGeant,
  kUndefinedFileType,
  kMCGate
};
FileType getFileType(const OptsStrAny& opts, const std::string& fileType);
FileType getInputFileType(const OptsStrAny& opts);
FileType getOutputFileType(const OptsStrAny& opts);
} // namespace file_type_checker

namespace detector_type_checker
{
enum DetectorType
{
  kBarrel,
  kModular
};
DetectorType getDetectorType(const OptsStrAny& opts);

} // namespace detector_type_checker

}; // namespace jpet_options_tools

#endif /* !JPETOPTIONSTOOLS_H */

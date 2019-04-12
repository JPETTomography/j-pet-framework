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
 *  @file JPetTaskIOTools.h
 */

#ifndef JPETTASKIOTOOLS_H
#define JPETTASKIOTOOLS_H

#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetParams/JPetParams.h"

namespace JPetTaskIOTools
{
/// @brief Function returns (isOK, firstEvent, lastEvent) based on provided options.
/// if isOK is set to false, that means that an error has occured.
std::tuple<bool, long long, long long> setUserLimits(const jpet_options_tools::OptsStrAny& opts, const long long totalNumEvents);
/// @brief Function returns (isOK, inputFile, outputFileFullPath, isResetOutputPath) based on provided options.
/// if isOK is set to false, that means that an error has occured.
std::tuple<bool, std::string, std::string, bool> setInputAndOutputFile(const OptsStrAny& opts, bool prevResetOutputPath, const std::string& inFileType, const std::string& outFileType);

OptsStrAny setOutputOptions(const JPetParams& oldParams, bool resetOutputPath, const std::string& fullOutPath);


};
#endif /*  !JPETTASKIOTOOLS_H */

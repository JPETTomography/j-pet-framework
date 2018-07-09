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
 *  @file JPetOptionsGeneratorTools.h
 */

#ifndef JPETOPTIONSGENERATORTOOLS_H
#define JPETOPTIONSGENERATORTOOLS_H

#include "./JPetOptionsTools/JPetOptionsTools.h"
#include "boost/program_options.hpp"
#include <boost/any.hpp>
#include <string>
#include <map>

namespace po = boost::program_options;
using OptsStrAny = std::map<std::string, boost::any>;
using TransformersMap = std::map<std::string, std::vector<jpet_options_tools::Transformer>>;

namespace jpet_options_generator_tools
{
OptsStrAny transformOptions(const TransformersMap& transformationMap, const OptsStrAny& optionsMap);
OptsStrAny generateOptionsForTask(const OptsStrAny& inOptions, const OptsStrAny& controlSettings);
OptsStrAny transformToStrAnyMap(const po::variables_map& variablesMap);
OptsStrAny addMissingDefaultOptions(const OptsStrAny& options);
TransformersMap generateTransformationMap(OptsStrAny& options);
OptsStrAny resetEventRange(const OptsStrAny& srcOpts);
OptsStrAny addTypeSuffixes(const OptsStrAny& oldMap);
OptsStrAny getDefaultOptions();
void addTransformFunction(TransformersMap& oldMap,  const std::string& name,
  jpet_options_tools::Transformer transformFunction);
void addNewOptionsFromCfgFile(const std::string& cfgFile, OptsStrAny& options);
void setOutputFileType(OptsStrAny& options, const std::string& fileType);
void setResetEventRangeOption(OptsStrAny& options, bool isReset);
void setOutputFile(OptsStrAny& options, const std::string& file);
void setOutputPath(OptsStrAny& options, const std::string& path);
};
#endif /* !JPETOPTIONSGENERATORTOOLS_H */

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
 *  @file JPetOptionsGeneratorTools.h
 */

#ifndef JPETOPTIONSGENERATORTOOLS_H
#define JPETOPTIONSGENERATORTOOLS_H
#include <map>
#include <string>
#include <boost/any.hpp>
#include "boost/program_options.hpp" // Library parsing command line arguments
#include "../JPetOptionsTools/JPetOptionsTools.h"

namespace po = boost::program_options;
using OptsStrAny = std::map<std::string, boost::any>;
using TransformersMap = std::map<std::string, std::vector<jpet_options_tools::Transformer> >;

namespace jpet_options_generator_tools
{

OptsStrAny transformToStrAnyMap(const po::variables_map& variablesMap);
/// Methods add type suffixes to the elements of
/// the map according to the key name.
OptsStrAny addTypeSuffixes(const OptsStrAny& oldMap);
OptsStrAny getDefaultOptions();
OptsStrAny addMissingDefaultOptions(const OptsStrAny& options);
void addNewOptionsFromCfgFile(const std::string& cfgFile, OptsStrAny& options);

OptsStrAny transformOptions(const TransformersMap& transformationMap, const OptsStrAny& optionsMap);

TransformersMap generateTransformationMap(OptsStrAny& options);
void addTransformFunction(TransformersMap& oldMap,  const std::string& name, jpet_options_tools::Transformer transformFunction);

};
#endif /*  !JPETOPTIONSGENERATORTOOLS_H */

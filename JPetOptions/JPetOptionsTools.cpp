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
 *  @file JPetOptionsTools.cpp
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "./JPetOptionsTools.h"
#include "../JPetOptions/JPetOptions.h"
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetLoggerInclude.h"


namespace pt = boost::property_tree;

namespace jpet_options_tools
{
bool createConfigFileFromOptions(const Options& options, const std::string& outFile)
{
  pt::ptree optionsTree;
  for (auto & entry : options)
    optionsTree.put (entry.first, entry.second);
  try {
    pt::write_json(outFile, optionsTree);
  } catch (pt::json_parser_error) {
    ERROR("ERROR IN WRITING OPTIONS TO JSON FILE");
    return false;
  }
  return true;
}

Options createOptionsFromConfigFile(const std::string& filename)
{
  pt::ptree optionsTree;
  Options mapOptions, emptyMap;
  if (JPetCommonTools::ifFileExisting(filename)) {
    try {
      pt::read_json(filename, optionsTree);
      for (auto & item : optionsTree) {
        auto key = item.first;
        auto value = item.second.get_value<std::string>();
        mapOptions.insert(std::make_pair(key, value));
      }
    } catch (pt::json_parser_error) {
      ERROR("ERROR IN READINIG OPTIONS FROM JSON FILE! FILENAME:" + filename );
      return emptyMap;
    }
  } else {
    ERROR("JSON CONFIG FILE DOES NOT EXIST! FILENAME:" + filename);
  }
  return mapOptions;
}
}

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
 *  @file JPetOptionsTransformators.cpp
 */

#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetOptionsTransformators.h"
#include "./JPetOptionsTools.h"
#include <boost/any.hpp>
#include <iostream>
#include <string>

using boost::any_cast;

namespace jpet_options_tools
{

std::pair <std::string, boost::any>appendSlash(boost::any option)
{
  auto path = JPetCommonTools::appendSlashToPathIfAbsent(any_cast<std::string>(option));
  return std::make_pair("outputPath_std::string", path);
}

std::pair <std::string, boost::any>generateLowerEventBound(boost::any option)
{
  int firstEvent = any_cast<std::vector<int>>(option)[0];
  if (firstEvent >= 0) {
    return std::make_pair("firstEvent_int", firstEvent);
  } else
    return std::make_pair("wrongFirstEvent_int", -1);
}

std::pair <std::string, boost::any>generateHigherEventBound(boost::any option)
{
  int lastEvent = any_cast<std::vector<int>>(option)[1];
  if (lastEvent >= 0) {
    return std::make_pair("lastEvent_int", lastEvent);
  } else
    return std::make_pair("wrongLastEvent_int", -1);
}

/**
 * Function generates transformation function for file type if the input file
 * name terminates with hld.root and the file type value is set to root then
 * the file type value is changed to hldRoot. At this stage the options might be
 * for many input file names as there are stored std::vector<std::string> array,
 * so getInputFiles() method must be used. This distinction is important because
 * hld.root files have different internal structure than all other root files
 * used in the framework
 */
Transformer generateSetFileTypeTransformator(const std::map<std::string, boost::any>& options)
{
  auto setFileType = [options](boost::any option)->std::pair <std::string, boost::any> {
    std::string optionKey = "inputFileType_std::string";
    if (!isOptionSet(options, "file_std::vector<std::string>"))
    {
      return std::make_pair(optionKey , any_cast<std::string>(option));
    }
    auto fileNames = getInputFiles(options);
    bool areHLdRootType = true;
    for (const auto& file : fileNames)
    {
      areHLdRootType = areHLdRootType & boost::algorithm::ends_with(file, "hld.root");
    }
    if (areHLdRootType )
    {
      return std::make_pair(optionKey , std::string("hldRoot"));
    } else {
      return std::make_pair(optionKey, any_cast<std::string>(option));
    }
  };
  return setFileType;
}

}

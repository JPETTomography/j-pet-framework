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
 *  @file JPetCmdParser.cpp
 */

#include "./JPetLoggerInclude.h"
#include "JPetCmdParser.h"
#include <iostream>
#include <stdexcept>

/**
 * Constructor with definitios of input arguments for an executable file
 */
JPetCmdParser::JPetCmdParser(): fOptionsDescriptions("Allowed options")
{
  fOptionsDescriptions.add_options()
  ("help,h", "Displays this help message.")
  ("type,t", po::value<std::string>()->required(), "Type of file: hld, zip, root or scope.")
  ("file,f", po::value< std::vector<std::string> >()->required()->multitoken(), "File(s) to open.")
  ("outputPath,o", po::value<std::string>(), "Location to which the outputFiles will be saved.")
  ("range,r", po::value< std::vector<int> >()->multitoken()->default_value({ -1, -1}, ""), "Range of events to process e.g. -r 1 1000 .")
  ("unpackerConfigFile,p", po::value<std::string>(), "xml file with TRB settings used by the unpacker program.")
  ("unpackerCalibFile,c", po::value<std::string>(), "ROOT file with TRB calibration used by the unpacker program.")
  ("runId,i", po::value<int>(), "Run id.")
  ("progressBar,b", po::bool_switch()->default_value(false), "Progress bar.")
  ("localDB,l", po::value<std::string>(), "The file to use as the parameter database.")
  ("localDBCreate,L", po::value<std::string>(), "File name to which the parameter database will be saved.")
  ("userCfg,u", po::value<std::string>(), "Json file with optional user parameters.");
}

/**
 * Destructor
 */
JPetCmdParser::~JPetCmdParser(){}

/**
 * This function can throw std::invalid_argument exception.
 */
po::variables_map JPetCmdParser::parseCmdLineArgs(int argc, const char** argv) const
{
  po::variables_map variablesMap;
  if (argc == 1) {
    ERROR("No options provided.");
    std::cerr << getOptionsDescription() << "\n";
    throw std::invalid_argument("No options provided.");
  }
  po::store(po::parse_command_line(argc, argv, fOptionsDescriptions), variablesMap);

  // Print out help
  if (variablesMap.count("help")) {
    std::cout << getOptionsDescription() << "\n";
    exit(0);
  }
  po::notify(variablesMap);
  return variablesMap;
}

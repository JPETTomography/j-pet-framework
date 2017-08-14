/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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

#include "JPetCmdParser.h"
#include <iostream>
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetLoggerInclude.h"
#include "../JPetScopeConfigParser/JPetScopeConfigParser.h"
#include <stdexcept>


JPetCmdParser::JPetCmdParser(): fOptionsDescriptions("Allowed options"), fGenerator()
{
  fOptionsDescriptions.add_options()
  ("help,h", "Displays this help message.")
  ("type,t", po::value<std::string>()->required()->implicit_value(""), "Type of file: hld, zip, root or scope.")
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

  //("help,h", "Displays this help message.")
  //("type_std::string,t", po::value<std::string>()->required()->implicit_value(""), "Type of file: hld, zip, root or scope.")
  //("file_std::vector<std::string>,f", po::value< std::vector<std::string> >()->required()->multitoken(), "File(s) to open.")
  //("outputPath_std::string,o", po::value<std::string>(), "Location to which the outputFiles will be saved.")
  //("range_std::vector<int>,r", po::value< std::vector<int> >()->multitoken()->default_value({ -1, -1}, ""), "Range of events to process e.g. -r 1 1000 .")
  //("unpackerConfigFile_std::string,p", po::value<std::string>(), "xml file with TRB settings used by the unpacker program.")
  //("unpackerCalibFile_std::string,c", po::value<std::string>(), "ROOT file with TRB calibration used by the unpacker program.")
  //("runId_int,i", po::value<int>(), "Run id.")
  //("progressBar_bool,b", po::bool_switch()->default_value(false), "Progress bar.")
  //("localDB_std::string,l", po::value<std::string>(), "The file to use as the parameter database.")
  //("localDBCreate_std::string,L", po::value<std::string>(), "File name to which the parameter database will be saved.")
  //("userCfg_std::string,u", po::value<std::string>(), "Json file with optional user parameters.");
}

JPetCmdParser::~JPetCmdParser()
{
  /**/
}

JPetOptionsGenerator& JPetCmdParser::getGenerator()
{
  return fGenerator;
}

std::vector<JPetOptions> JPetCmdParser::parseAndGenerateOptions(int argc, const char** argv)
{
  po::variables_map variablesMap;
  if (argc == 1) {
    ERROR("No options provided.");
    std::cerr << getOptionsDescription() << "\n";
    throw std::invalid_argument("No options provided.");
  }

  po::store(po::parse_command_line(argc, argv, fOptionsDescriptions), variablesMap);
  /* print out help */
  if (variablesMap.count("help")) {
    std::cout << getOptionsDescription() << "\n";
    exit(0);
  }
  po::notify(variablesMap);
  return fGenerator.generateOptions(variablesMap);
}


//#endif /* __CINT__ */

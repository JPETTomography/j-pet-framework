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
 *  @file JPetCmdParser.h
 */

#ifndef _JPET_CMD_PARSER_H_
#define _JPET_CMD_PARSER_H_

class JPetCmdParser;

#include "boost/program_options.hpp" // Library parsing command line arguments
#include <string>
#include "../JPetOptions/JPetOptions.h"

namespace po = boost::program_options;

class JPetCmdParser
{
public:
  JPetCmdParser();
  ~JPetCmdParser();
  std::vector<JPetOptions> parseAndGenerateOptions(int argc, const char** argv);

  inline const po::options_description getOptionsDescription() const {
    return fOptionsDescriptions;
  }
  std::vector<JPetOptions> generateOptions(const po::variables_map& cmdLineOptions) const;

  bool areCorrectOptions(const po::variables_map& options) const;
  inline const std::vector<std::string>& getFileNames(const po::variables_map& variablesMap) const {
    return variablesMap["file"].as< std::vector<std::string> >();
  }
  inline bool isCorrectFileType(const std::string& type) const {
    if (type == "hld" || type == "root" || type == "scope") {
      return true;
    }
    return false;
  }
  inline const std::string& getFileType(const po::variables_map& variablesMap) const {
    return variablesMap["type"].as<std::string>();
  }
  inline bool IsFileTypeSet(const po::variables_map& variablesMap) const {
    return (bool)variablesMap.count("type");
  }
  inline int getLowerEventBound(const po::variables_map& variablesMap) const {
    return variablesMap["range"].as< std::vector<int> >()[0];
  }
  inline int getHigherEventBound(const po::variables_map& variablesMap) const {
    return variablesMap["range"].as< std::vector<int> >()[1];
  }
  inline bool isParamSet(const po::variables_map& variablesMap) const {
    return (bool)variablesMap.count("param");
  }
  inline const std::string& getParam(const po::variables_map& variablesMap) const {
    return variablesMap["param"].as< std::string >();
  }

  inline bool isRunNumberSet(const po::variables_map& variablesMap) const {
    return (bool)variablesMap.count("runId");
  }
  inline const int getRunNumber(const po::variables_map& variablesMap) const {
    return variablesMap["runId"].as<int>();
  }

  inline bool isProgressBarSet(const po::variables_map& variablesMap) const {
    return (bool)variablesMap.count("progressBar");
  }

protected:
  po::options_description fOptionsDescriptions;

private:
  JPetCmdParser(const JPetCmdParser& cmdParser);
  JPetCmdParser& operator=(const JPetCmdParser& cmdParser);
};

#endif /* _JPET_CMD_PARSER_H_ */

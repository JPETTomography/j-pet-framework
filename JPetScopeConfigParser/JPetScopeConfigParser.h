/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetScopeConfigParser.h
 */

#ifndef JPET_SCOPE_CONFIG_PARSER_H
#define JPET_SCOPE_CONFIG_PARSER_H

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "JPetScopeConfigPOD.h"

class JPetScopeConfigParser
{
  
public:
  JPetScopeConfigParser() {}
  std::vector<scope_config::Config> getConfigs(const std::string& configFileName) const;
  std::vector<std::string> getInputFileNames(std::string configFileName) const;
  std::vector<int> transformToNumbers(const std::vector<std::string>& positions) const;
  std::vector<std::string>  generateFileNames(const std::string& configFileName, const std::string& configName, const std::vector<int>& positions) const;
  boost::property_tree::ptree getJsonContent(const std::string &configFileName) const;

protected:
  scope_config::Config getConfig(std::string configName, boost::property_tree::ptree const& configContent) const;
  std::vector<std::string> getPositions(boost::property_tree::ptree const& configContent) const;
  std::string getLocation(boost::property_tree::ptree const& content) const;
  std::vector<scope_config::BSlot> getBSlots(boost::property_tree::ptree const& content) const;
  std::vector<scope_config::PM> getPMs(boost::property_tree::ptree const& content) const;
  std::vector<scope_config::Scin> getScins(boost::property_tree::ptree const& content) const;
                                               
private:
  JPetScopeConfigParser(const JPetScopeConfigParser&);
  void operator=(const JPetScopeConfigParser&);
};

#endif // JPET_SCOPE_CONFIG_PARSER_H

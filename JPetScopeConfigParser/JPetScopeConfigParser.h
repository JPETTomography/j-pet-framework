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


class JPetScopeConfigParser
{
public:
  struct BSlot
  {
    BSlot(int id = -1, bool active = false, const std::string& name="", float theta=-1.0, int frame =-1):
      fId(id),
      fActive(active),
      fName(name),
      fTheta(theta),
      fFrame(frame)
    {/**/}
    int fId;
    bool fActive;
    std::string fName;
    float fTheta;
    int fFrame;
  };

  struct PM 
  {
    PM(int id = -1, const std::string& prefix =""):
      fId(id),
      fPrefix(prefix)
    {  }
    int fId;
    std::string fPrefix;
  };
  struct Scin
  {
    Scin(int id = -1):
      fId(id)
    { /**/ }
    int fId;
  };

  struct Config
  {
    Config()
    { /* */} 
    Config(const std::string& name, const std::vector<BSlot>& bslots, 
           const std::vector<PM>& pms, const std::vector<Scin>& scins,
           const std::string& location, const std::vector<std::string> positions):
            fName(name),
            fBSlots(bslots),
            fPMs(pms),
            fScins(scins),
            fLocation(location),
            fCollimatorPositions(positions)
    { /* */} 
    std::string fName;
    std::vector<BSlot> fBSlots;  
    std::vector<PM> fPMs;  
    std::vector<Scin> fScins;  
    std::string fLocation;
    std::vector<std::string> fCollimatorPositions;
  };
  
public:
  JPetScopeConfigParser() {}
  boost::property_tree::ptree getJsonContent(const std::string &configFileName) const;
  bool loadConfigFile(std::string configName);
  inline boost::property_tree::ptree getLoadedConfigData() const { return fLoadedConfigData; }
  std::vector<std::string> getInputFileNames(std::string configFileName) const;

  std::vector<int> transformToNumbers(const std::vector<std::string>& positions) const;
  std::vector<std::string>  generateFileNames(const std::string& configFileName, const std::string& configName, const std::vector<int>& positions) const;
  std::vector<Config> getConfigs(const std::string& configFileName) const;

protected:
  Config getConfig(std::string configName, boost::property_tree::ptree const& configContent) const;
  Config getConfig(boost::property_tree::ptree const& configContent) const;
  std::vector<std::string> getPositions(boost::property_tree::ptree const& configContent) const;
  std::string getLocation(boost::property_tree::ptree const& content) const;
  std::vector<JPetScopeConfigParser::BSlot> getBSlots(boost::property_tree::ptree const& content) const;
  std::vector<JPetScopeConfigParser::PM> getPMs(boost::property_tree::ptree const& content) const;
  std::vector<JPetScopeConfigParser::Scin> getScins(boost::property_tree::ptree const& content) const;
                                               
  boost::property_tree::ptree fLoadedConfigData; 
private:
  JPetScopeConfigParser(const JPetScopeConfigParser&);
  void operator=(const JPetScopeConfigParser&);
};

#endif // JPET_SCOPE_CONFIG_PARSER_H

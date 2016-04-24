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

//#include <iostream>
#include <string>
#include <vector>
//#include <cstdint>
#include <boost/property_tree/ptree.hpp>


//nigdy nie używaj using namespace w header 
//przegoogluj ten temat, bo już drugi raz to robisz
//using namespace std;
using boost::property_tree::ptree;

//zmien nazwe na JPetScopeConfigParser
//bo parsera chcemy uzyc nie tylko w ScopeReaderze
class JPetScopeConfigParser
{
protected:
  struct JPetParamObject
  {
  protected:
    unsigned int id;
    
  public:
    JPetParamObject() = default;
    JPetParamObject(unsigned int paramId) : id(paramId)
    {}
    
    friend JPetScopeConfigParser;
  };
  
  struct JPetBSlotData : JPetParamObject
  {
  protected:
    bool active;//TODO daje nazwe active zeby bylo konsystentnie z *.json-ew. mozna wszedzie ustali nazwe?
    std::string name;
    float theta;
    int frame;
    
  public:
    JPetBSlotData() = default;
    JPetBSlotData(unsigned int paramId, bool paramActive, std::string paramName, float paramTheta, int paramFrame) : 
      JPetParamObject(paramId), 
      active(paramActive), 
      name(paramName), 
      theta(paramTheta), 
      frame(paramFrame)
    {}
    
    friend JPetScopeConfigParser;
  };
  
  struct JPetPMData : JPetParamObject
  {
  protected:
    std::string prefix;
    
  public:
    JPetPMData() = default;
    JPetPMData(unsigned int paramId, std::string paramPrefix) : 
      JPetParamObject(paramId), 
      prefix(paramPrefix)
    {}
    
    friend JPetScopeConfigParser;
  };
  
  struct JPetScinData : JPetParamObject
  {
  public:
    JPetScinData() = default;
    JPetScinData(unsigned int paramId) :
      JPetParamObject(paramId)
    {}
    
    friend JPetScopeConfigParser;
  };
  
  std::string fileName;
  std::string filesLocation;
  std::vector<std::string> outputFileNames;
  std::vector<int> positions;
  std::vector<JPetBSlotData> bSlotData;
  std::vector<JPetPMData> pmData;
  std::vector<JPetScinData> scinData;
  
public:
  JPetScopeConfigParser();

//wk najlepiej zdefiniowac pomocnicza strukture
//np. 
//struct BSlotData 
//{
// int fId;
// bool fIsActive;
// string fName;
// float fTheta;
// int fFrame;
//};
// i dodac metode:
// std::vector<BSlotData> getBslotData(ptree const& conf_data) const;
// patrz JPetScopeReader linijki od 78
// dodatkowo jezeli potrzebne można dodać pomocnicze
// std::vector<std::string> getBSlotNames(ptree const& conf_data) const;
// itd.
  
//    files_location = conf_data.get<string>("location");
//    zamienic na getFilesLocation(ptree const& conf_data) const;
  
  bool createParamObject(ptree const& conf_data);
  bool getFilesLocation(ptree const& conf_data);
  bool createOutputFileNames(const std::string &configFileName, const int position);
  bool readData(const std::string &configFileName);  
  //brakuje const  gdy metoda nic nie zmienia w obiekcie
  std::string getFileName() const { return fileName; }
  std::string getFilesLocation() const { return filesLocation; };
  std::vector<std::string> getOutputFileNames() const { return outputFileNames; }
  std::vector<int> getPositions() const { return positions; }
  std::vector<JPetBSlotData> getBSlotData() const { return bSlotData; }
  std::vector<JPetPMData> getPMData() const { return pmData; }
  std::vector<JPetScinData> getScinData() const { return scinData; }
};

#endif // JPET_SCOPE_CONFIG_PARSER_H

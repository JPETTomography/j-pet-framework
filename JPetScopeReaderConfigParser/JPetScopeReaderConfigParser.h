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
 *  @file JPetScopeReaderConfigParser.h
 */

#ifndef JPET_SCOPE_READER_CONFIG_PARSER_H
#define JPET_SCOPE_READER_CONFIG_PARSER_H

#include <iostream>
#include <string>
#include <vector>
//#include <cstdint>


//nigdy nie używaj using namespace w header 
//przegoogluj ten temat, bo już drugi raz to robisz
using namespace std;

//zmien nazwe na JPetScopeConfigParser
//bo parsera chcemy uzyc nie tylko w ScopeReaderze
class JPetScopeReaderConfigParser
{
protected:
  string fileName;
  vector<int> positions;
  
public:
  JPetScopeReaderConfigParser();

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
  
  void readData(const string &configFileName);
  //brakuje const  gdy metoda nic nie zmienia w obiekcie
  string getFileName() { return fileName; }
  vector<int> getPositions() { return positions; }
};

#endif // JPET_SCOPE_READER_CONFIG_PARSER_H

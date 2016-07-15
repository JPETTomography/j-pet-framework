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
 *  @file JPetAuxilliaryData.cpp
 */

#include "JPetAuxilliaryData.h"
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetLoggerInclude.h"
#include <sstream>
#include <limits>

ClassImp(JPetAuxilliaryData);

const double JPetAuxilliaryData::Unset = -std::numeric_limits<double>::infinity();

JPetAuxilliaryData::JPetAuxilliaryData():
  TNamed("Auxilliary Data", "")
{
}

JPetAuxilliaryData::JPetAuxilliaryData(std::string name):
  TNamed(name.c_str(), name.c_str())
{
}

void JPetAuxilliaryData::createVector(std::string name, int initial_size){
  if( fVectors.count(name) > 0 ){
    WARNING("JPetAuxilliaryData: A vector with the requested name already exists and will be overwritten.");
    fVectors[name].clear();
  }
  fVectors[name].resize(initial_size, Unset);
}

void JPetAuxilliaryData::createMap(std::string name){
  if( fDictionaries.count(name) > 0 ){
    WARNING("JPetAuxilliaryData: A map with the requested name already exists and will be overwritten.");
    fDictionaries[name].clear();
  }
  fDictionaries[name];
}

void JPetAuxilliaryData::setValue(std::string container_name, unsigned int index, double value){
  if( fVectors.count(container_name) > 0 &&
      index < fVectors[container_name].size() ){
    fVectors[container_name][index] = value;
  }
}

void JPetAuxilliaryData::setValue(std::string container_name, std::string key, double value){
  if( fDictionaries.count(container_name) > 0 ){
    fDictionaries[container_name][key] = value;
  }
}

double JPetAuxilliaryData::getValue(std::string container_name, unsigned int index) const {
  if( fVectors.count(container_name) > 0 ){
    if(index < fVectors.at(container_name).size() ){
      return fVectors.at(container_name).at(index);
    }else{
      WARNING(Form("JPetAuxilliaryData: Index %d is out of bounds"
		   " of the vector \"%s\"", index, container_name.c_str()));
    }
  }else{
    WARNING(Form("JPetAuxilliaryData: Referring to a non-existent container \"%s\"",
		 container_name.c_str()));
  }
  return JPetAuxilliaryData::Unset;
}

double JPetAuxilliaryData::getValue(std::string container_name, std::string key) const {
  if( fDictionaries.count(container_name) > 0 ){
    if( fDictionaries.at(container_name).count(key) > 0 ){
      return fDictionaries.at(container_name).at(key);
    }else{
      WARNING(Form("JPetAuxilliaryData: Referring to a non-existent key \"%s\""
		   " in a map \"%s\"", key.c_str(), container_name.c_str()));
    }
  }else{
    WARNING(Form("JPetAuxilliaryData: Referring to a non-existent container \"%s\"",
		 container_name.c_str()));
  }
  return JPetAuxilliaryData::Unset;
}

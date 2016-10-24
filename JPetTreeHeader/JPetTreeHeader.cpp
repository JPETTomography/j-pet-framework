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
 *  @file JPetTreeHeader.cpp
 */

#include "JPetTreeHeader.h"
#include "../JPetCommonTools/JPetCommonTools.h"
#include <sstream>

ClassImp(JPetTreeHeader);

JPetTreeHeader::JPetTreeHeader():
  fRunNo(-1),
  fBaseFilename("filename not set"),
  fSourcePosition(-1),
  emptyStage({"module not set", "description not set", -1, "-1"})
{
}

JPetTreeHeader::JPetTreeHeader(int run):
  fRunNo(run),
  fBaseFilename("filename not set"),
  fSourcePosition(-1),
  emptyStage({"module not set", "description not set", -1, "-1"})
{
}

std::string JPetTreeHeader::stringify() const
{
  std::ostringstream tmp;
  tmp<<"-----------------------------------------------------------------\n" ;
  tmp<<"------------------------- General Info --------------------------\n" ;
  tmp<<"-----------------------------------------------------------------\n" ;
  tmp<< "Run number              : " << JPetCommonTools::Itoa(fRunNo) <<"\n";
  tmp<< "Base file name          : "<<getBaseFileName()<<"\n";
  tmp<< "Source (if any) position: "<< Form("%lf",getSourcePosition())<<"\n";

tmp << stringifyHistory();
tmp << stringifyDictionary();

return tmp.str();
}

void JPetTreeHeader::addStageInfo(std::string p_name, std::string p_title, int p_version, std::string p_time_stamp )
{
  ProcessingStageInfo stage;
  stage.fModuleName = p_name;
  stage.fModuleDescription = p_title;
  stage.fModuleVersion = p_version;
  stage.fCreationTime = p_time_stamp;
  fStages.push_back( stage );
}

std::string JPetTreeHeader::stringifyDictionary() const {

  std::ostringstream tmp;
  tmp<<"-----------------------------------------------------------------\n";
  tmp<<"--------------------- User-defined variables --------------------\n";
  tmp<<"-----------------------------------------------------------------\n";

  for(auto const &entry : fDictionary){
    tmp<<entry.first << "   =   " << entry.second <<"\n";
    tmp<<"-----------------------------------------------------------------\n";
  }
  return tmp.str();
}

std::string JPetTreeHeader::stringifyHistory() const {

  std::ostringstream tmp;
  tmp<<"-----------------------------------------------------------------\n";
  tmp<<"-------------- Processing history (oldest first) ----------------\n";
  tmp<<"-----------------------------------------------------------------\n";

  for (int i = 0; i < getStagesNb(); i++ ) {
    const ProcessingStageInfo & info = getProcessingStageInfo(i);
    tmp<< "Module Name         : " << info.fModuleName<<"\n";
    tmp<< "Module desc.        : " << info.fModuleDescription<<"\n";
    tmp<< "Module version      : " << JPetCommonTools::Itoa( info.fModuleVersion ) <<"\n";
    tmp<< "Started processing  : " << info.fCreationTime <<"\n";
    tmp<<"-----------------------------------------------------------------\n";
  }  
  return tmp.str();
}

/**
 * @brief Sets the textual value of an existing variable named 'name' or 
 * creates such variable if it was nonexistent
 *
 * @param name name of the variable (existing or not)
 * @param value value of the variable
 *
 * Use this method to store any additional information in the TreeHeader.
 * All values must be encoded as text.
 *
 * Example:
 * header.setVariable("source position", "X=10cm; Y=2cm; Z=20cm")
 *
 */
void JPetTreeHeader::setVariable(std::string name, std::string value){
  fDictionary[name] = value;
}

/**
 * @brief Returns the textual value of a variable (see the setVariable method)
 *
 * @param name name of the variable
 *
 * Use this method to access any additional information previously stored
 * in the TreeHeader with the setVariable method. If a name of a non-existent variable
 * is provided, an empty string will be returned.
 *
 */
std::string JPetTreeHeader::getVariable(std::string name) const {
	if(fDictionary.find(name)!= fDictionary.end()) return fDictionary.at(name);
	else return " ";
}

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
 *  @file JPetTreeHeader.h
 */

#ifndef _JPET_TREE_HEADER_H_
#define _JPET_TREE_HEADER_H_

#include <TObject.h>
#include <TString.h>
#include <iostream>
#include <ostream>
#include <vector>
#include <map>

/**
 * @brief A class representing a header with info on JPet ROOT Trees.
 *
 * Encapsulates information from the top-level of JPet data files as defined in Report 19, tables 37+. A TreeHeader object is intended to be stored in evert JPet ROOT file along with a respective TTree which it describes.
 *
 * The Header also contains the processing history and a dictionary of auxilliary information about the data in the ROOT tree.
 *
 * The processing history is a list of records added by each JPetTask which processed the data starting from raw data.
 *
 * The auvilliary information if a dictionary of variables with textual names and textual values, which can be used to encode any additional information, e.g. a variable named "source position" with a value of "Xcm;Ycm;Zcm" can be added to the dictionary.
 *
 */
class JPetTreeHeader: public TObject{
 protected:
  struct ProcessingStageInfo
  {
    std::string fModuleName;
    std::string fModuleDescription;
    int fModuleVersion;
    std::string fCreationTime;
  };


 public:
  JPetTreeHeader();
  JPetTreeHeader(int run);
  void Print(Option_t* opt = "") const { std::cout << this->stringify(); }

  /// produce a std::string edscribing all the information dontained in this object
  std::string stringify() const;

  inline int getRunNumber()  const { return fRunNo; }
  inline void setRunNumber(int p_run_no) { fRunNo = p_run_no; }
  
  inline std::string getBaseFileName() const {return fBaseFilename;}
  inline void setBaseFileName(const char * p_name){ fBaseFilename = p_name; }
  
  /// set source position in mm or -1 of no source was used
  inline double getSourcePosition() const { return fSourcePosition; }
  /// get source position in mm; -1 means no source was used
  inline void setSourcePosition(double p_pos) { fSourcePosition = p_pos; }

  /// add information on one processing stage, i.e. one module
  int addStageInfo(std::string name, std::string title, int version, std::string time_stamp);
  int getStagesNb()const{ return fStages.size(); }

  const ProcessingStageInfo & getProcessingStageInfo(int i)const{ return fStages.at(i); }

  void setVariable(std::string name, std::string value);
  std::string getVariable(std::string name) const;
  
protected:

  /// auxilliary methods for the Print() functionality
  std::string stringifyDictionary() const;
  std::string stringifyHistory() const;

  int fRunNo;
  std::string fBaseFilename;
  double fSourcePosition;

  std::vector<ProcessingStageInfo> fStages;
  std::map<std::string, std::string> fDictionary;

  ClassDef(JPetTreeHeader, 3);
};

#endif

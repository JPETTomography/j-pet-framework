/**
 *  @file JPetTreeHeader.h
 *  @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 */
#ifndef _JPET_TREE_HEADER_H_
#define _JPET_TREE_HEADER_H_

#include <TObject.h>
#include <TString.h>
#include <iostream>
#include <ostream>
#include <vector>


/**
 * @brief A class representing a header with info on JPet ROOT Trees.
 *
 * Encapsulates information from the top-level of JPet data files as defined in Report 19, tables 37+. A TreeHeader object is intended to be stored in evert JPet ROOT file along with a respective TTree which it describes.
 */
class JPetTreeHeader: public TObject{
 protected:
  struct ProcessingStageInfo
  {
    TString fModuleName;
    TString fModuleDescription;
    int fModuleVersion;
    TString fCreationTime;
  };


 public:
  JPetTreeHeader();
  JPetTreeHeader(int run);
  void Print(Option_t* opt = "") const { std::cout << this->stringify(); }

  /// produce a TString edscribing all the information dontained in this object
  TString stringify() const;

  inline int getRunNumber()  const { return fRunNo; }
  inline void setRunNumber(int p_run_no) { fRunNo = p_run_no; }
  
  inline TString getBaseFileName() const {return fBaseFilename;}
  inline void setBaseFileName(const char * p_name){ fBaseFilename = p_name; }
  
  /// set source position in mm or -1 of no source was used
  inline double getSourcePosition() const { return fSourcePosition; }
  /// get source position in mm; -1 means no source was used
  inline void setSourcePosition(double p_pos) { fSourcePosition = p_pos; }

  /// add information on one processing stage, i.e. one module
  int addStageInfo(TString name, TString title, int version, TString time_stamp);
  int getStagesNb()const{ return fStages.size(); }

  const ProcessingStageInfo & getProcessingStageInfo(int i)const{ return fStages.at(i); }

  ClassDef(JPetTreeHeader, 2);

protected:

  int fRunNo;
  TString fBaseFilename;
  double fSourcePosition;

  std::vector<ProcessingStageInfo> fStages;

};

#endif

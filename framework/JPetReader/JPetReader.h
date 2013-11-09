/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetReader.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETREADER_H 
#define JPETREADER_H 

#include <cstddef>

#include <TBranch.h>
#include <TFile.h>
#include <TNamed.h>
#include <TTree.h>

#include "../../JPetLoggerInclude.h"

class JPetReader {
 public:
  JPetReader();
  virtual ~JPetReader();
  
  virtual void CloseFile();
  virtual long long GetEntries () const;
  virtual int GetEntry (int entry);
  virtual void OpenFile(const char* filename);
  virtual void ReadData(const char* objname = "");
  virtual TNamed& GetData () {return *fObject;}

 protected:
  
  TBranch* fBranch;
  TFile* fFile;
  TNamed* fObject;
  TTree* fTree;

};
#endif /*  !JPETREADER_H */

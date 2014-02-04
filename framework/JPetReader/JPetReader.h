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
  explicit JPetReader(const char* filename);
  virtual ~JPetReader();
  
  virtual void CloseFile();
  virtual long long GetEntries () const { return fTree->GetEntries(); }
  virtual int GetEntry (int entryNo) {return fTree->GetEntry(entryNo); } /// the name of the function is bad but it mimics ROOT function 
  virtual bool OpenFile(const char* filename);
  virtual void ReadData(const char* objname = "");
  virtual TNamed& GetData () {return *fObject;}

 protected:
  TBranch* fBranch;
  TNamed* fObject;
  TTree* fTree;
  TFile fFile;

 private:
  JPetReader(const JPetReader&);
  void operator=(const JPetReader);

};
#endif /*  !JPETREADER_H */

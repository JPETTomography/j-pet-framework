/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetHLDReader.h
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief The interface only mimics the JPetReader class
 */
#ifndef _J_PET_HLD_READER_H_
#define _J_PET_HLD_READER_H_

#include <TBranch.h>
#include <TFile.h>
#include <TNamed.h>
#include <TTree.h>

#include "../../JPetLoggerInclude.h"

#include "../JPetUnpacker/Unpacker2/Event.h"

class Event;

/**
 * @brief A class responsible for reading any data from an unpacked HLD file.
 *
 * This if a special case of JPetReader adapted for reading the ROOT files produced by the JPetUnpacker of HLD files. It should be used in the first JPetAnalysisModule whose processing is not preceded by any other module. In all subsequent modules, JPetReader should be used instead.
 */
class JPetHLDReader
{
public:
  JPetHLDReader();
  explicit JPetHLDReader(const char* filename);
  virtual ~JPetHLDReader();

  void CloseFile();
  long long GetEntries () const {
    return fTree->GetEntries();
  }
  int GetEntry (int entryNo) {
    return fTree->GetEntry(entryNo);
  }
  bool OpenFile(const char* filename);
  void ReadData();
  Event& GetData() {
    return *fEvent;
  }

protected:
  TBranch* fBranch;
  TTree* fTree;
  Event* fEvent;
  TFile* fFile;

private:
  JPetHLDReader(const JPetHLDReader&);
  void operator=(const JPetHLDReader);
};
#endif

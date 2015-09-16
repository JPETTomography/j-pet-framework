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
#include "../JPetReaderInterface/JPetReaderInterface.h"

class Event;

/**
 * @brief A class responsible for reading any data from an unpacked HLD file.
 *
 * This if a special case of JPetReader adapted for reading the ROOT files produced by the JPetUnpacker of HLD files. It should be used in the first JPetAnalysisModule whose processing is not preceded by any other module. In all subsequent modules, JPetReader should be used instead.
 */
class JPetHLDReader : public JPetReaderInterface 
{
public:
  JPetHLDReader();
  explicit JPetHLDReader(const char* filename);
  virtual ~JPetHLDReader();
  
public:
  virtual Event& getCurrentEvent();   
  virtual bool nextEvent();
  virtual bool firstEvent();
  virtual bool lastEvent();
  virtual bool nthEvent(int n);
  virtual long long getCurrentEventNumber() const {
    return fCurrentEventNumber;
  }
  virtual long long getNbOfAllEvents() const {
    return fTree ? fTree->GetEntries() : 0;
  } 
  virtual bool openFileAndLoadData(const char* filename, const char* treename = "tree") {
    if (openFile(filename) ) {
      return loadData(treename);
    }
    return false;
  }
  virtual void closeFile();
  virtual bool isOpen() const {
    if (fFile) return (fFile->IsOpen() && !fFile->IsZombie());
    else return false;
  }

protected:
  virtual bool openFile(const char* filename);
  virtual bool loadData(const char* treename = "T");
  bool loadCurrentEvent() {
    if (fTree) {
      int entryCode = fTree->GetEntry(fCurrentEventNumber);
      return isCorrectTreeEntryCode(entryCode);
    } 
    return false;
  }
  
  inline bool isCorrectTreeEntryCode (int entryCode) const  ///see TTree GetEntry method
  {
    if (entryCode == -1) return false;
    if (entryCode == 0) return false; 
    return true;
  }

  TBranch* fBranch;
  TTree* fTree;
  Event* fEvent;
  TFile* fFile;
  long long fCurrentEventNumber;

private:
  JPetHLDReader(const JPetHLDReader&);
  void operator=(const JPetHLDReader);
};
#endif

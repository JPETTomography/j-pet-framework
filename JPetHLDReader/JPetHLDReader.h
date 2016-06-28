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
 *  @file JPetHLDReader.h
 *  @brief The interface only mimics the JPetReader class
 */

#ifndef _J_PET_HLD_READER_H_
#define _J_PET_HLD_READER_H_

#include <TBranch.h>
#include <TFile.h>
#include <TNamed.h>
#include <TTree.h>

#include "../JPetLoggerInclude.h"

#include "../JPetUnpacker/Unpacker2/EventIII.h"
#include "../JPetReaderInterface/JPetReaderInterface.h"

/**
 * @brief A class wraps Event to be able to return it as TNamed pointer
 *
 */
class WrappedEvent :public EventIII,  public TNamed
{
 public:
  WrappedEvent(const EventIII& ev):EventIII(ev), TNamed("EventWrapper", "EventWrapper")
  {/**/}
};


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
  virtual EventIII& getCurrentEvent();   
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

  virtual TObject* getObject(const char* name){
    if (fFile) return fFile->Get(name);
    else return 0;
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
  EventIII* fEvent;
  WrappedEvent* fEventW;
  TFile* fFile;
  long long fCurrentEventNumber;

private:
  JPetHLDReader(const JPetHLDReader&);
  void operator=(const JPetHLDReader);
};
#endif

// JPetReader.h - Reader
#ifndef JPETREADER_H
#define JPETREADER_H

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <vector>

#ifndef __CINT__
#include <boost/noncopyable.hpp>
#else
namespace boost;
class boost::noncopyable;
#endif /* __CINT __ */

/*
#include "../JPetScin/JPetScin.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetFEB/JPetFEB.h"
#include "../JPetTRB/JPetTRB.h"
*/
#include "../JPetTreeHeader/JPetTreeHeader.h"
#include "../JPetReaderInterface/JPetReaderInterface.h"

#include "../JPetLoggerInclude.h"

/**
 * @brief A class responsible for reading any data from ROOT trees.
 *
 * All objects inheriting from JPetAnalysisModule should use this class in order to access and read data from ROOT files.
 */
class JPetReader : private boost::noncopyable, public JPetReaderInterface
{
public:
  JPetReader(void); //maybe remove this one
  explicit JPetReader(const char* p_filename);
  virtual ~JPetReader(void);

  virtual JPetReaderInterface::MyEvent& getCurrentEvent();
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
  JPetTreeHeader* getHeaderClone() const;

  virtual TObject* getObject(const char* name) {
    if (fFile) return fFile->Get(name);
    else return 0;
  }
  virtual bool isOpen() const {
    if (fFile) return (fFile->IsOpen() && !fFile->IsZombie());
    else return false;
  }

protected:
  virtual bool openFile(const char* filename);
  virtual bool loadData(const char* treename = "tree");
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
  JPetReaderInterface::MyEvent* fEvent;
  TTree* fTree;
  TFile* fFile;
  long long fCurrentEventNumber;
};

#endif	// JPETREADER_H

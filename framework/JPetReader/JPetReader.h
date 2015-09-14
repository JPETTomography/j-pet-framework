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

#include "../../JPetLoggerInclude.h"

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

  virtual Event& getCurrentEvent();
  virtual bool nextEvent();
  virtual bool firstEvent();
  virtual bool lastEvent();
  virtual bool nthEvent(int n);
  virtual long long getCurrentEventNumber() const {
    return fCurrentEventNumber;
  };
  virtual long long getNbOfAllEvents() const {
    return fTree->GetEntries();
  };


  virtual bool openFileAndLoadData(const char* filename, const char* treename = "tree") {
    if (openFile(filename) ) {
      return loadData(treename);
    }
    return false;
  }
  virtual void closeFile();
  JPetTreeHeader* getHeaderClone() const;
//it will go protected
  virtual bool openFile(const char* filename);
  virtual bool loadData(const char* treename = "tree");
//it will be removed
  virtual bool readData(const char* objname = "tree");
  virtual long long getEntries () const {
    return fTree->GetEntries();
  }
  virtual int getEntry (int entryNo) {
    return fTree->GetEntry(entryNo);  /// the name of the function is bad but it mimics ROOT function
  }
  virtual TNamed& getData () {
    return *fEvent;
  }

  //wtf?
  virtual TObject* getObject(const char* name) {
    if (fFile) return fFile->Get(name);
    else return 0;
  }
  virtual bool isOpen() const {
    if (fFile) return (fFile->IsOpen() && !fFile->IsZombie());
    else return false;
  }
  template <class T>
  void fillContainer(std::vector<T>& p_container, const std::string& p_objectName);

protected:
  bool loadCurrentEvent() { return fTree->GetEntry(fCurrentEventNumber); }
  TBranch* fBranch;
  TNamed* fEvent;
  TTree* fTree;
  TFile* fFile;
  long long fCurrentEventNumber;
};


template <class T>
void JPetReader::fillContainer(std::vector<T>& p_container, const std::string& p_objectName)
{
  TList* l_TList = static_cast<TList*>(fFile->Get(p_objectName.c_str()));
  TObject* l_obj;

  TIter next(l_TList);
  while (l_obj = next()) {
    T* l_item = static_cast<T*>(l_obj);
    p_container.push_back(*l_item);
  }
}

#endif	// JPETREADER_H

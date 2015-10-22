
#ifndef JPETWRITER_H
#define JPETWRITER_H

#include <vector>
#include <string>
#include <TFile.h>
#include <TList.h>
#include <TTree.h>

#ifndef __CINT__
#include <boost/noncopyable.hpp>
#else
namespace boost;
class boost::noncopyable;
#endif /* __CINT __ */

#include "../../JPetLoggerInclude.h"

#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetLOR/JPetLOR.h"
#include "../JPetHit/JPetHit.h"
#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetTimeWindow/JPetTimeWindow.h"

#include "../JPetScin/JPetScin.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetFEB/JPetFEB.h"
#include "../JPetTRB/JPetTRB.h"


/**
 * @brief A class responsible for writing any data to ROOT trees.
 *
 * All objects inheriting from JPetAnalysisModule should use this class in order to access and write to ROOT files.
 */
class JPetWriter : private boost::noncopyable
{
public:
  JPetWriter(const char* p_fileName);
  virtual ~JPetWriter(void);

  template <class T>
  bool write(const T& obj);
  virtual bool isOpen() const {
    if (fFile) return (fFile->IsOpen() && !fFile->IsZombie());
    else return false;
  }
  void writeHeader(TObject* header);
  void closeFile();

  int writeObject(const TObject* obj, const char* name) {
    return fFile->WriteObject(obj, name);
  }


protected:
  std::string fFileName;
  TFile* fFile;
  bool fIsBranchCreated;
  TTree* fTree;

  TList fTList;
};

template <class T>
bool JPetWriter::write(const T& obj)
{
  ;

  if ( !fFile->IsOpen() ) {
    ERROR("Could not write to file. Have you closed it already?");
    return false;
  }
  assert(fFile);

  fFile->cd(/*fFileName.c_str()*/); // -> http://root.cern.ch/drupal/content/current-directory

  T* filler = const_cast<T*>(&obj);
  assert(filler);
  if (!fIsBranchCreated) {
    fTree->Branch(filler->GetName(), filler->GetName(), &filler);
    fIsBranchCreated = true;
  }

  fTree->Fill();
  return true;
}

#endif	// JPETWRITER_H

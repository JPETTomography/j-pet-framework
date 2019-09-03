/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetWriter.h
 */

#ifndef JPETWRITER_H
#define JPETWRITER_H

#ifndef __CINT__
#include <boost/noncopyable.hpp>
#else
namespace boost;
class boost::noncopyable;
#endif /* __CINT __ */

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetPhysSignal/JPetPhysSignal.h"
#include "./JPetTimeWindow/JPetTimeWindow.h"
#include "./JPetSigCh/JPetSigCh.h"
#include "./JPetEvent/JPetEvent.h"
#include "./JPetLoggerInclude.h"
#include "./JPetScin/JPetScin.h"
#include "./JPetHit/JPetHit.h"
#include "./JPetLOR/JPetLOR.h"
#include "./JPetFEB/JPetFEB.h"
#include "./JPetTRB/JPetTRB.h"
#include "./JPetPM/JPetPM.h"
#include <TFile.h>
#include <TList.h>
#include <TTree.h>
#include <vector>
#include <string>

/**
 * @brief A class responsible for writing any data to ROOT trees.
 *
 * All objects inheriting from JPetAnalysisModule should use this class
 * in order to access and write to ROOT files.
 * @todo Extract consts because it should be common both for Writer and Reader.
 */
class JPetWriter : private boost::noncopyable
{
public:
  /**
   * The name of the root tree read from the file.
   */
  static const std::string kRootTreeName;

  /**
   * Variable corresponds to the number of events buffered before saving the tree.
   */
  static const long long kTreeBufferSize;

  JPetWriter(const char* p_fileName);
  virtual ~JPetWriter(void);
  void closeFile();
  template <class T> bool write(const T& obj);
  void writeHeader(TObject* header);
  void writeCollection(const TCollection* hash, const char* dirname,
    const char* subdirname = "");
  int writeObject(const TObject* obj, const char* name)
  {
    return fFile->WriteTObject(obj, name);
  }
  virtual bool isOpen() const
  {
    if (fFile) return (fFile->IsOpen() && !fFile->IsZombie());
    else return false;
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
  DEBUG("JPetWriter");
  if ( !fFile->IsOpen() ) {
    ERROR("Could not write to file. Have you closed it already?");
    return false;
  }
  assert(fFile);
  DEBUG("cd");
  // http://root.cern.ch/drupal/content/current-director
  fFile->cd();
  DEBUG("filler");
  T* filler = const_cast<T*>(&obj);
  assert(filler);
  if (!fIsBranchCreated) {
    DEBUG("Branch name:" + std::string(filler->GetName()));
    assert(fTree);
    fTree->Branch(filler->GetName(), filler->GetName(), &filler);
    fIsBranchCreated = true;
  }
  DEBUG("fTree->Fill()");
  fTree->Fill();
  return true;
}

#endif /* !JPETWRITER_H */

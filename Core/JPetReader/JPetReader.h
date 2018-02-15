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
 *  @file JPetReader.h
 */

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
#include "./JPetScin/JPetScin.h"
#include "./JPetPM/JPetPM.h"
#include "./JPetFEB/JPetFEB.h"
#include "./JPetTRB/JPetTRB.h"
*/
#include "./JPetTreeHeader/JPetTreeHeader.h"
#include "./JPetReaderInterface/JPetReaderInterface.h"

#include "./JPetLoggerInclude.h"

/**
 * @brief A class responsible for reading any data from ROOT trees.
 *
 * All objects inheriting from JPetAnalysisModule should use this class in order to access and read data from ROOT files.
 */
class JPetReader : private boost::noncopyable, public JPetReaderInterface
{
public:
  static const std::string kRootTreeName; /// The name of the root tree read from the file.
  static const std::string kRootMCHITTreeName; /// The name of the root tree read from the file.

  JPetReader(void); //maybe remove this one
  JPetReader(const char* p_filename, const char* treeName = "T");
  virtual ~JPetReader(void);

  virtual JPetReaderInterface::MyEvent& getCurrentEntry();
  virtual bool nextEntry() override;
  virtual bool firstEntry() override;
  virtual bool lastEntry() override;
  virtual bool nthEntry(long long n) override;
  virtual long long getCurrentEntryNumber() const override;
  virtual long long getNbOfAllEntries() const override;
  virtual bool openFileAndLoadData(const char* filename, const char* treename = "T") override;
  virtual void closeFile();
  JPetTreeHeader* getHeaderClone() const;
  virtual TObject* getObjectFromFile(const char* name);
  virtual bool isOpen() const;

protected:
  virtual bool openFile(const char* filename);
  virtual bool loadData(const char* treename = "T");
  bool loadCurrentEntry();
  inline bool isCorrectTreeEntryCode (int entryCode) const;  ///see TTree GetEntry method

  TBranch* fBranch = nullptr;
  TObject* fEntry = nullptr;
  TTree* fTree = nullptr;
  TFile* fFile = nullptr;
  long long fCurrentEntryNumber = -1;
};

#endif	// JPETREADER_H

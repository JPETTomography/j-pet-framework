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
 *  @file JPetReader.h
 */

#ifndef JPETREADER_H
#define JPETREADER_H

#include "./JPetReaderInterface/JPetReaderInterface.h"
#include "./JPetTreeHeader/JPetTreeHeader.h"
#include "./JPetLoggerInclude.h"
#include <TBranch.h>
#include <TFile.h>
#include <TTree.h>
#include <vector>

#ifndef __CINT__
#include <boost/noncopyable.hpp>
#else
namespace boost;
class boost::noncopyable;
#endif /* __CINT __ */

/**
 * @brief A class responsible for reading any data from ROOT trees.
 *
 * All objects inheriting from JPetAnalysisModule should use this class
 * in order to access and read data from ROOT files.
 * @todo Add the correct file to 'file_with_no_jpettreeheader' test and
 * see TTree GetEntry method, add test of file with no JPetTreeHeader
 */
class JPetReader: private boost::noncopyable, public JPetReaderInterface
{
public:
  static const std::string kRootTreeName;
  JPetReader(void);
  JPetReader(const char* p_filename, const char* treeName = "T");
  virtual ~JPetReader(void);
  virtual JPetReaderInterface::MyEvent& getCurrentEntry();
  virtual bool nextEntry() override;
  virtual bool firstEntry() override;
  virtual bool lastEntry() override;
  virtual bool nthEntry(long long n) override;
  virtual long long getCurrentEntryNumber() const override;
  virtual long long getNbOfAllEntries() const override;
  virtual bool openFileAndLoadData(
    const char* filename, const char* treename = "T") override;
  virtual void closeFile();
  JPetTreeHeader* getHeaderClone() const;
  virtual TObject* getObjectFromFile(const char* name);
  virtual bool isOpen() const;

protected:
  virtual bool openFile(const char* filename);
  virtual bool loadData(const char* treename = "T");
  bool loadCurrentEntry();
  inline bool isCorrectTreeEntryCode (int entryCode) const;

  TBranch* fBranch = nullptr;
  TObject* fEntry = nullptr;
  TTree* fTree = nullptr;
  TFile* fFile = nullptr;
  long long fCurrentEntryNumber = -1;
};

#endif /* !JPETREADER_H */

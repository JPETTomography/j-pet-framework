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
 *  @file JPetReader.cpp
 */

#include "./JPetUserInfoStructure/JPetUserInfoStructure.h"
#include "JPetReader.h"
#include <cassert>

/**
 * The Tree name is "T" and it is compatible with the Tree name produced by the Unpacker.
 */
const std::string JPetReader::kRootTreeName = "T";

JPetReader::JPetReader() {}

JPetReader::JPetReader(const char* p_filename, const char* treeName)
{
  if (!openFileAndLoadData(p_filename, treeName)) {
    ERROR("error in opening file");
  }
}

JPetReader::~JPetReader()
{
  if (fFile) {
    delete fFile;
    fFile = 0;
  }
}

JPetReader::MyEvent& JPetReader::getCurrentEntry()
{
  if (loadCurrentEntry()) {
    return *fEntry;
  } else {
    ERROR("Could not read the current event");
    if (fEntry) {
      delete fEntry;
    }
    fEntry = new TNamed("Empty event", "Empty event");
  }
  return *fEntry;
}

bool JPetReader::JPetReader::nextEntry()
{
  fCurrentEntryNumber++;
  return loadCurrentEntry();
}

bool JPetReader::firstEntry()
{
  fCurrentEntryNumber = 0;
  return loadCurrentEntry();
}

bool JPetReader::lastEntry()
{
  fCurrentEntryNumber = getNbOfAllEntries() - 1;
  return loadCurrentEntry();
}

bool JPetReader::nthEntry(long long n)
{
  fCurrentEntryNumber = n;
  return loadCurrentEntry();
}

long long JPetReader::getCurrentEntryNumber() const
{
  return fCurrentEntryNumber;
}

long long JPetReader::getNbOfAllEntries() const
{
  return fTree ? fTree->GetEntries() : 0;
}

bool JPetReader::openFileAndLoadData(const char* filename, const char* treename)
{
  if (openFile(filename) ) {
    return loadData(treename);
  }
  return false;
}

void JPetReader::closeFile ()
{
  if (fFile) delete fFile;
  fFile = 0;
  fBranch = 0;
  fEntry = 0;
  fTree = 0;
  fCurrentEntryNumber = -1;
}

bool JPetReader::openFile (const char* filename)
{
  closeFile();
  fFile = new TFile(filename);
  if ((!isOpen()) || fFile->IsZombie()) {
    ERROR(std::string("Cannot open file: ") + std::string(filename));
    return false;
  }
  return true;
}

bool JPetReader::loadData(const char* treename)
{
  if (!isOpen()) {
    ERROR("File not open");
    return false;
  }
  if (!treename) {
    ERROR("empty tree name");
    return false;
  }
  fTree = dynamic_cast<TTree*>(fFile->Get(treename));
  if (!fTree) {
    ERROR("in reading tree");
    return false;
  }
  TObjArray* arr = fTree->GetListOfBranches();
  fBranch = (TBranch*)(arr->At(0));
  if (!fBranch) {
    ERROR("in reading branch from tree");
    return false;
  }
  fBranch->SetAddress(&fEntry);
  firstEntry();
  return true;
}

/**
 * @brief Returns a copy of the header read from input file.
 *
 * Using a copy rather than direct pointer is essential as the original header
 * belongs to JPetReader::fTree and would be deleted along with it.
 */
JPetTreeHeader* JPetReader::getHeaderClone() const
{
  if (!fTree) {
    ERROR("No tree available");
    return 0;
  }
  auto  listOfObjects = fTree->GetUserInfo();
  JPetTreeHeader* header =  static_cast<JPetTreeHeader*>(listOfObjects->At(JPetUserInfoStructure::kHeader));
  if (!header) {
    WARNING("No JPetTreeHeader found in the tree - it is ok if the tree is a hld.root type");
    return nullptr;
  }
  return new JPetTreeHeader(*header);
}

TObject* JPetReader::getObjectFromFile(const char* name)
{
  if (fFile) return fFile->Get(name);
  else return 0;
}

bool JPetReader::isOpen() const
{
  if (fFile) return (fFile->IsOpen() && !fFile->IsZombie());
  else return false;
}

bool JPetReader::loadCurrentEntry()
{
  if (fTree) {
    int entryCode = fTree->GetEntry(fCurrentEntryNumber);
    return isCorrectTreeEntryCode(entryCode);
  }
  return false;
}

inline bool JPetReader::isCorrectTreeEntryCode (int entryCode) const
{
  if (entryCode == -1) return false;
  if (entryCode == 0) return false;
  return true;
}

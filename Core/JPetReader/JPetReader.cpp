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
 *  @file JPetReader.cpp
 */

#include "JPetReader.h"
#include <cassert>
#include "./JPetUserInfoStructure/JPetUserInfoStructure.h"

const std::string JPetReader::kRootTreeName = "T"; /// This tree name is compatible with the tree name produced by the unpacker.

JPetReader::JPetReader() :
  fBranch(0),
  fEvent(0),
  fTree(0),
  fFile(NULL),
  fCurrentEventNumber(-1)
{
  /**/
}

JPetReader::JPetReader(const char* p_filename, const char* treeName) :
  fBranch(0),
  fEvent(0),
  fTree(0),
  fFile(0),
  fCurrentEventNumber(-1)
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

JPetReader::MyEvent& JPetReader::getCurrentEvent()
{
  if (loadCurrentEvent()) {
    return *fEvent;
  } else {
    ERROR("Could not read the current event");
    if (fEvent) {
      delete fEvent;
    }
    fEvent = new TNamed("Empty event", "Empty event");
  }
  return *fEvent;
}

bool JPetReader::JPetReader::nextEvent()
{
  fCurrentEventNumber++;
  return loadCurrentEvent();
}

bool JPetReader::firstEvent()
{
  fCurrentEventNumber = 0;
  return loadCurrentEvent();
}

bool JPetReader::lastEvent()
{
  fCurrentEventNumber = getNbOfAllEvents() - 1;
  return loadCurrentEvent();
}

bool JPetReader::nthEvent(long long n)
{
  fCurrentEventNumber = n;
  return loadCurrentEvent();
}

void JPetReader::closeFile ()
{
  if (fFile) delete fFile;
  fFile = 0;
  fBranch = 0;
  fEvent = 0;
  fTree = 0;
  fCurrentEventNumber = -1;
}


bool JPetReader::openFile (const char* filename)
{
  closeFile();
  fFile = new TFile(filename);
  if ((!isOpen()) || fFile->IsZombie()) {
    ERROR(std::string("Cannot open file:") + std::string(filename));
    return false;
  }
  return true;
}

bool JPetReader::loadData(const char* treename)
{
  if (!isOpen() ) {
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
  fBranch->SetAddress(&fEvent);
  firstEvent();
  return true;
}


/**
 * @brief Returns a copy of the header read from input file.
 *
 * Using a copy rather than direct pointer is essential as the original header belongs to JPetReader::fTree and would be deleted along with it.
 */
JPetTreeHeader* JPetReader::getHeaderClone() const
{
  if (!fTree) {
    ERROR("No tree available");
    return 0;
  }
  // get a pointer to a header wchich belongs to fTree
  auto  listOfObjects = fTree->GetUserInfo();
  JPetTreeHeader* header =  static_cast<JPetTreeHeader*>(listOfObjects->At(JPetUserInfoStructure::kHeader));
  if (!header) {
    WARNING("No JPetTreeHeader found!! in the tree - it is ok if the tree is a hld.root type");
    return nullptr;
  }
  // return a COPY of this header
  return new JPetTreeHeader( *header );
}

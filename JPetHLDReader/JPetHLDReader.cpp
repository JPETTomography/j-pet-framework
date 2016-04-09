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
 *  @file JPetHLDReader.cpp
 *  @brief The interface only mimics the JPetReader class
 */

#include "JPetHLDReader.h"
#include <iostream>
#include <cassert>

JPetHLDReader::JPetHLDReader():
  fBranch(0),
  fTree(0),
  fEvent(0),
  fFile(NULL),
  fCurrentEventNumber(-1)
{
  /* */
}

JPetHLDReader::JPetHLDReader (const char* filename):
  fBranch(0),
  fTree(0),
  fEvent(0),
  fFile(NULL),
  fCurrentEventNumber(-1)
{
  if (!openFileAndLoadData(filename, "T")) {
    ERROR("error in opening file");
  }
}

JPetHLDReader::~JPetHLDReader ()
{
  closeFile();
}


EventIII& JPetHLDReader::getCurrentEvent()
{
  if (loadCurrentEvent()) {
    fEventW  = new  WrappedEvent(*fEvent);
    return *fEventW;
    //return *fEvent;
  } else {
    ERROR("Could not read the current event");
    if (fEvent) {
      delete fEvent;
    }
    fEvent = new EventIII();
  }
  fEventW  = new WrappedEvent(*fEvent);
  return *fEventW;
}

bool JPetHLDReader::nextEvent()
{
  fCurrentEventNumber++;
  return loadCurrentEvent();
}

bool JPetHLDReader::firstEvent()
{
  fCurrentEventNumber = 0;
  return loadCurrentEvent();
}

bool JPetHLDReader::lastEvent()
{
  fCurrentEventNumber = getNbOfAllEvents() - 1;
  return loadCurrentEvent();
}

bool JPetHLDReader::nthEvent(int n)
{
  fCurrentEventNumber = n;
  return loadCurrentEvent();
}

void JPetHLDReader::closeFile ()
{
  if (fFile != NULL) {
    if (fFile->IsOpen()) fFile->Close();
    delete fFile;
    fFile = NULL;
  }
  fBranch = 0;
  fEvent = 0;
  fTree = 0;
}

bool JPetHLDReader::loadData(const char* treename)
{
  if (!isOpen() ) {
    ERROR("File not open");
    return false;
  }
  if (!treename) {
    ERROR("empty tree name");
    return false;
  }
  fTree = static_cast<TTree*>(fFile->Get(treename));
  if (!fTree) {
    ERROR("in reading tree");
    return false;
  }
  fBranch = fTree->GetBranch("eventIII");
  if (!fBranch) {
    ERROR("in reading branch from tree");
    return false;
  }
  fBranch->SetAddress(&fEvent);
  firstEvent();
  return true;
}


bool JPetHLDReader::openFile (const char* filename)
{
  closeFile();
  fFile = new TFile(filename);

  if ((!fFile->IsOpen()) || fFile->IsZombie()) {
    ERROR("Cannot open file.");
    closeFile();
    return false;
  }
  return true;
}



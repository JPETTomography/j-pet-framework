#include "JPetHLDReader.h"
#include <iostream>
#include <cassert>

JPetHLDReader::JPetHLDReader():
  fBranch(0),
  fEvent(0),
  fTree(0),
  fFile(NULL),
  fCurrentEventNumber(-1)
{
  /* */
}

JPetHLDReader::JPetHLDReader (const char* filename):
  fBranch(0),
  fEvent(0),
  fTree(0),
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


Event& JPetHLDReader::getCurrentEvent()
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
    fEvent = new Event();
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
  fBranch = fTree->GetBranch("event");
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



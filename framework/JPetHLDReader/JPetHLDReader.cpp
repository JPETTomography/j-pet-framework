#include "JPetHLDReader.h"
#include <iostream>
#include <cassert>

JPetHLDReader::JPetHLDReader():
  fBranch(0),
  fEvent(0),
  fTree(0),
  fFile(NULL)
{
  /* */
}

JPetHLDReader::JPetHLDReader (const char* filename):
  fBranch(0),
  fEvent(0),
  fTree(0),
  fFile(NULL)
{
  if (openFile(filename) ) readData();
}

JPetHLDReader::~JPetHLDReader ()
{
  closeFile();
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


void JPetHLDReader::readData ()
{
  fTree = static_cast<TTree*>(fFile->Get("T")); /// @todo add some comment
  assert(fTree);
  fBranch = fTree->GetBranch("event");
  assert(fBranch);
  fBranch->SetAddress(&fEvent);
}

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
  if (OpenFile(filename) ) ReadData();
}

JPetHLDReader::~JPetHLDReader ()
{
  CloseFile();
}

void JPetHLDReader::CloseFile ()
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


bool JPetHLDReader::OpenFile (const char* filename)
{
  CloseFile();
  fFile = new TFile(filename);

  if ((!fFile->IsOpen()) || fFile->IsZombie()) {
    ERROR("Cannot open file.");
    CloseFile();
    return false;
  }
  return true;
}


void JPetHLDReader::ReadData ()
{
<<<<<<< HEAD
  fTree = static_cast<TTree*>(fFile->Get("T")); /// @todo add some comment
=======
  fTree = static_cast<TTree*>(fFile.Get("T"));
>>>>>>> develop
  assert(fTree);
  fBranch = fTree->GetBranch("event");
  assert(fBranch);
  fBranch->SetAddress(&fEvent);
}

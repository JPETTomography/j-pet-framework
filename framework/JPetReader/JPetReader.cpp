#include "JPetReader.h"

JPetReader::JPetReader () : fBranch(NULL), fFile(NULL), fObject(NULL), fTree(NULL) {
}

JPetReader::~JPetReader () {
  CloseFile();
}

void JPetReader::CloseFile () {
  if (fFile != NULL) {
    if (fFile->IsOpen()) fFile->Close();
    delete fFile;
  }
  fBranch = NULL;
  fFile = NULL;
  fObject = NULL;
  fTree = NULL;
}

long long JPetReader::GetEntries () const {
  return fTree->GetEntries();
}

int JPetReader::GetEntry (int entryNo) {
  return fTree->GetEntry(entryNo);
}

void JPetReader::OpenFile (const char* filename) {
  CloseFile();
  fFile = new TFile(filename);

  if ((!fFile->IsOpen())||fFile->IsZombie()) {
    ERROR("Cannot open file.");
    delete fFile;
    fFile = NULL;
    return;
  }

  return;
}

void JPetReader::ReadData (const char* objname) {
  if (objname[0]==NULL) {
    ERROR("No object name specified");
    return;
  }
  fTree = static_cast<TTree*>(fFile->Get(objname));
  fBranch = fTree->GetBranch(objname);
  fBranch->SetAddress(&fObject);
}

#include "./JPetTSlotRawReader.h"

#include <iostream>

JPetTSlotRawReader::JPetTSlotRawReader() :
      fTSlot(NULL), fBranch(NULL), fFile(NULL), fTree(NULL) {
}

JPetTSlotRawReader::JPetTSlotRawReader(const char* filename) :
      fTSlot(NULL), fBranch(NULL), fFile(NULL), fTree(NULL) {

  OpenFile(filename);
}

JPetTSlotRawReader::~JPetTSlotRawReader() {
  
  CloseFile();
}

void JPetTSlotRawReader::CloseFile() {
  
  if (fFile!=NULL) {
    if (fFile->IsOpen())fFile->Close();
    delete fFile;
  }

  fTSlot = NULL;
  fBranch = NULL;
  fFile = NULL;
  fTree = NULL;
}

void JPetTSlotRawReader::OpenFile (const char* filename) {
  
  CloseFile();
  fFile = new TFile(filename);
  
  if ((!fFile->IsOpen())||fFile->IsZombie()) {
    delete fFile;
    fFile = NULL;
    return;
  }

  fTree = static_cast<TTree*>(fFile->Get("JPetTSlot"));
  //fTree->SetBranchAddress("JPetTSlot",&fTSlot,&fBranch);
  fBranch = fTree->GetBranch("JPetTSlot");
  fBranch->SetAddress(&fTSlot);

  return;
}

long long JPetTSlotRawReader::GetEntries () const {
  
  return fTree->GetEntries();
}

int JPetTSlotRawReader::GetEntry(int number) {
  
  return fTree->GetEntry(number);
}

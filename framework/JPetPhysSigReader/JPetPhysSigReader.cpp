#include "./JPetPhysSigReader.h"

#include <iostream>

JPetPhysSigReader::JPetPhysSigReader() :
      fSignal(NULL), fBranch(NULL), fFile(NULL), fTree(NULL) {
}

JPetPhysSigReader::JPetPhysSigReader(const char* filename) :
      fSignal(NULL), fBranch(NULL), fFile(NULL), fTree(NULL) {

  OpenFile(filename);
}

JPetPhysSigReader::~JPetPhysSigReader() {
  
  CloseFile();
}

void JPetPhysSigReader::CloseFile() {
  
  if (fFile!=NULL) {
    if (fFile->IsOpen())fFile->Close();
    delete fFile;
  }

  fSignal = NULL;
  fBranch = NULL;
  fFile = NULL;
  fTree = NULL;
}

void JPetPhysSigReader::OpenFile (const char* filename) {
  
  CloseFile();
  fFile = new TFile(filename);
  
  if ((!fFile->IsOpen())||fFile->IsZombie()) {
    delete fFile;
    fFile = NULL;
    return;
  }

  fTree = static_cast<TTree*>(fFile->Get("PhysSig"));
  //fTree->SetBranchAddress("JPetSignal",&fSignal,&fBranch);
  TBranch* branch = fTree->GetBranch("JPetSignal");
  branch->SetAddress(&fSignal);

  return;
}

long long JPetPhysSigReader::GetEntries () const {
  
  return fTree->GetEntries();
}

int JPetPhysSigReader::GetEntry(int number) {
  
  return fTree->GetEntry(number);
}

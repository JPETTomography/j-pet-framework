#include "./JPetAnalysisModuleA.h"

#include <JPetSigCh/JPetSigCh.h>
#include <JPetSignal/JPetSignal.h>

#include <vector>

#include <TSystem.h>

using namespace std;

ClassImp(JPetAnalysisModuleA);

JPetAnalysisModuleA::JPetAnalysisModuleA():JPetAnalysisModule(), fEventNb(0), fWriter(NULL) {
  gSystem->Load("libTree");
}

JPetAnalysisModuleA::JPetAnalysisModuleA(const char* name, const char* title):JPetAnalysisModule(name, title), fEventNb(0), fWriter(NULL) {
  gSystem->Load("libTree");
}

JPetAnalysisModuleA::~JPetAnalysisModuleA() {
  if (fWriter != NULL) delete fWriter;
}

void JPetAnalysisModuleA::createInputObjects(const char* inputFilename) {
  
  const char* filename = "./test.hld.root";
  fInFile = new TFile(filename);
  
  if (fInFile->IsZombie()) {
    delete fInFile;
    return;
  }
  
  fInFile->GetObject("T",fInTree);
  if(!fInTree) {
    delete fInFile;
    return;
  }
  
  fEventNb = fInTree->GetEntries(); 

};

void JPetAnalysisModuleA::createOutputObjects(const char* outputFilename) {
  const char* filename = "phys.sig.root";
  fWriter = new JPetWriter(filename);
}

void JPetAnalysisModuleA::exec() {
  
  Int_t TDCHits_;
  Int_t totalNTDCHits;
  Int_t TDCHits_channel[8];
  Float_t TDCHits_leadTime1[8];
  Float_t TDCHits_trailTime1[8];

  TBranch* b_event_TDCHits_;
  TBranch* b_event_totalNTDCHits;
  TBranch* b_TDCHits_channel;
  TBranch* b_TDCHits_leadTime1;
  TBranch* b_TDCHits_trailTime1;
  
  fInTree->SetMakeClass(1);
  fInTree->SetBranchAddress("TDCHits", &TDCHits_, &b_event_TDCHits_);
  fInTree->SetBranchAddress("totalNTDCHits", &totalNTDCHits, &b_event_totalNTDCHits);
  fInTree->SetBranchAddress("TDCHits.channel", TDCHits_channel, &b_TDCHits_channel);
  fInTree->SetBranchAddress("TDCHits.leadTime1", TDCHits_leadTime1, &b_TDCHits_leadTime1);
  fInTree->SetBranchAddress("TDCHits.trailTime1", TDCHits_trailTime1, &b_TDCHits_trailTime1);
  
  b_event_TDCHits_->GetEvent(fEvent);
  b_event_totalNTDCHits->GetEvent(fEvent);
  b_TDCHits_channel->GetEvent(fEvent);
  b_TDCHits_leadTime1->GetEvent(fEvent);
  b_TDCHits_trailTime1->GetEvent(fEvent);

  JPetSigCh* fSigCh = 0;
  JPetSigCh* rSigCh = 0;
  JPetSignal* signal = 0;
  //vector<JPetSigCh> leading, trailing;
  vector<ExtendedThreshold> leading, trailing;
  JPetSigCh currSigCh;
  History history; /// auxiliary struct defined in JPetSignal.h
  for (int i = 0; i < 4; ++i) {
    currSigCh.addCh(0, TDCHits_leadTime1[i]);
    leading.push_back(ExtendedThreshold(history,0,0,0, currSigCh));
    currSigCh.addCh(TDCHits_leadTime1[i+4],0);
    trailing.push_back(ExtendedThreshold(history,0,0,0, currSigCh));
  }
  
  signal = new JPetSignal(0,0,(fEvent%2)==1,leading,trailing);
  fWriter->write(*signal);
}

void JPetAnalysisModuleA::terminate() {
  fWriter->closeFile();
}

//Program to create the test root file.
//for the unit test saving_trefs_in_different_processes.
//It must be created separately in distinct
//processes.

#include  "TestEvent.h"
#include "FakeParamBank.h"

#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TList.h>
#include <TTree.h>
#include <TClonesArray.h>

int main(int argc, const char* argv[])
{
  std::cout << "Creating file testXX.root for the test unit saving_trefs_in_different_processes" << std::endl;

  TFile* file = new TFile("dataXX.root", "RECREATE", "", 0);


  /// param id:1  <--- data event 10
  /// param id:2  <--- data event 20
  /// param id:2 is stored in the TList*
  /// param id:1 is stored in TClonesArray
  FakeParamBank*  params = new FakeParamBank;
  TTree* dataTree  = new TTree ("T", "dataTree");
  TestEvent* eve = 0;
  dataTree->Branch("TestEvent", "TestEvent", &eve);
  TestEvent* pParam = new TestEvent(0, 1);
  params->addParam(*pParam);
  eve = new TestEvent(pParam, 10);
  dataTree->Fill();

  ///the same but with TList
  TestEvent* pParam2 = new TestEvent(0, 2);
  TList* paramList = params->getList();
  paramList->Add(pParam2);
  eve = new TestEvent(static_cast<TestEvent*>(paramList->At(0)), 20);
  dataTree->Fill();

  file->WriteObject(params, "params");
  file->Write();
  file->Close("R");
  delete file;
  return 0;
}

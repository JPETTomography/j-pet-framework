#include "../EventClass.h"
#include "../ParamClass.h"

#include <cstddef>
#include <cstdlib>

#include <iostream>

#include <TFile.h>
#include <TList.h>
#include <TTree.h>

using namespace std;

void writeData()
{
  Long_t events = 0;
  
  // Open file for data
  TFile* file1 = new TFile ("list2.db.root", "RECREATE", "", 0);

  // Create simple data
  TList* dblist = new TList();

  ParamClass* a = new ParamClass ("Alpha", 1);

  dblist->Add(a);

  // Open file and create tree
  TFile* file2 = new TFile ("tree2.eve.root", "RECREATE", "", 0);
  TTree* tree  = new TTree ("T", Form ("Test Tree for %ld events.", events));

  // Create branch for events
  EventClass* eve = 0;

  tree->Branch("EventClass", "EventClass", &eve);
  
  // Fill tree with events
  eve = new EventClass (a, 1);

  // Set TRef using my function
  eve->setTRef(*a);
  ParamClass *b = eve->getTRef();
  std::cout << "b->GetId() " << b->GetId() << std::endl;
  
  tree->Fill();

  // write data and close files
  file1->WriteObject (dblist, "DataBase");
  file2->Write();

  file1->Close();
  file2->Close();
}

int main (int argc, char** argv) 
{
  writeData();
  return 0;
}

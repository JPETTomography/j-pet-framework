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

  // Open file and create tree
  TFile* file = new TFile ("tree1.root", "RECREATE", "", 0);
  TTree* tree = new TTree ("T", Form ("Test Tree for %ld events.", events));

  // Create simple data
  ParamClass* a = new ParamClass ("Alpha", 1);
  a->simpleField = 101;

  tree->GetUserInfo()->Add(a);

  // Create branch for events
  EventClass* eve = 0;

  tree->Branch("EventClass", "EventClass", &eve);
  
  // Fill tree with events
  eve = new EventClass (a, 1);
  
  // Set TRef using my function
  ParamClass* c = new ParamClass ("C", 1);
  eve->setTRef(*c);
  ParamClass *b = eve->getTRef();
  std::cout << "b->GetId() " << b->GetId() << std::endl;

  tree->Fill();

  // write data and close file
  file->Write();
  file->Close();
}

int main (int argc, char** argv) 
{
  writeData();
  return 0;
}

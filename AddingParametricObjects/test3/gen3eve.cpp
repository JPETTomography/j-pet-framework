#include "../EventClass.h"
#include "../ParamClass.h"

#include <cstddef>
#include <cstdlib>

#include <iostream>

#include <TFile.h>
#include <TList.h>
#include <TTree.h>

using namespace std;

void Generate (Long_t events) {
  
  Long_t r;
  //srand (0);

  // Open file for Database
  

  TFile* file1 = new TFile ("list3.db.root", "READ", "", 0);

  // Create simple database

  TList* dblist = (TList*)file1->Get("DataBase");

  ParamClass* a = (ParamClass*)dblist->At(0);
  ParamClass* b = (ParamClass*)dblist->At(1);
  ParamClass* c = (ParamClass*)dblist->At(2);
  ParamClass* d = (ParamClass*)dblist->At(3);

  // Open file and create tree

  TFile* file2 = new TFile ("tree3.eve.root", "RECREATE", "", 0);
  TTree* tree  = new TTree ("T", Form ("Test Tree for %ld events.", events));

  // Create branch for events
  
  EventClass* eve = 0;

  tree->Branch("EventClass", "EventClass", &eve);
  
  // Fill tree with events

  for (Long_t i = 0; i < events; ++i) {
    
    //r = rand()%4;
    r = i%4;
    switch (r) {
    
      case 0:
      
      eve = new EventClass (a, 1);
      break;

      case 1:

      eve = new EventClass (b, 2);
      break;

      case 2:

      eve = new EventClass (c, 3);
      break;

      case 3:

      eve = new EventClass (d, 4);
      break;

      default:

      break;
    }

    tree->Fill();
  }


  // write data and close files

  //file1->Write();
  file2->Write();

  file1->Close();
  file2->Close();

}

int main (int argc, char** argv) {

  Generate(1000);
  return 0;

}

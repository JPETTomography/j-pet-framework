#include "../EventClass.h"
#include "../ParamClass.h"

#include <cstddef>
#include <cstdlib>

#include <iostream>

#include <TFile.h>
#include <TTree.h>

using namespace std;

void Generate (Long_t events) {
  
  Long_t r;
  //srand (0);

  // Open file and create tree

  TFile* file = new TFile ("tree1.root", "RECREATE", "", 0);
  TTree* tree = new TTree ("T", Form ("Test Tree for %ld events.", events));

  // Create simple database

  ParamClass* a = new ParamClass ("Alpha",       1);
  ParamClass* b = new ParamClass ("Bravo",       2);
  ParamClass* c = new ParamClass ("ChuckNorris", 3);
  ParamClass* d = new ParamClass ("Damian",      4);

  tree->GetUserInfo()->Add(a);
  tree->GetUserInfo()->Add(b);
  tree->GetUserInfo()->Add(c);
  tree->GetUserInfo()->Add(d);

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

  // write data and close file

  file->Write();
  file->Close();

}

int main (int argc, char** argv) {

  Generate(1000);
  return 0;

}

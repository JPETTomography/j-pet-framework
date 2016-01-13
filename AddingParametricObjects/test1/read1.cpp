#include "../EventClass.h"
#include "../ParamClass.h"

#include <cstddef>
#include <cstdlib>

#include <iostream>

#include <TFile.h>
#include <TTree.h>

using namespace std;

void Read() {

  // Open file and tree

  TFile* file = new TFile ("tree1.root", "READ", "", 0);
  TTree* tree = (TTree*)file->Get("T");

  // Set branch

  TBranch* b_eve;
  EventClass* eve = 0;
  tree->SetBranchAddress("EventClass", &eve, &b_eve);

  // Read few events
  
  ParamClass* prm = 0;

  for (Int_t i = 0; i < 8; ++i) {

    b_eve->GetEvent(i);

    prm = eve->GetParam();

    // Print info from ParamClass

    if(prm != 0)
      cout<<prm->GetInfo()->Data()<<endl;
    else
      cout<<"nullptr"<<endl;
  }

  // Close file

  file->Close();

}

int main (int argc, char** argv) {

  Read();
  return 0;

}

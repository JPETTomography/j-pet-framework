#include "../EventClass.h"
#include "../ParamClass.h"

#include <cstddef>
#include <cstdlib>

#include <iostream>

#include <TFile.h>
#include <TTree.h>

using namespace std;

void readData()
{
  // Open files and read data and tree
  TFile* file1 = new TFile ("list2.db.root",  "READ", "", 0);
  TList* dblist = (TList*)file1->Get("DataBase");

  TFile* file2 = new TFile ("tree2.eve.root", "READ", "", 0);
  TTree* tree   = (TTree*)file2->Get("T");

  // Set branch
  TBranch* b_eve;
  EventClass* eve = 0;
  tree->SetBranchAddress("EventClass", &eve, &b_eve);

  // Read few events
  ParamClass* prm = 0;
  
  b_eve->GetEvent(0);

  prm = eve->GetParam();

  // Get TRef using my function
  ParamClass* PARAM = eve->getTRef();
  std::cout << "PARAM->GetId() " << PARAM->GetId() << std::endl;
    
  // Print info from ParamClass
  if(prm != 0)
  {
    cout<<prm->GetInfo()->Data()<<endl; // ok
    std::cout << "prm->GetId() " << prm->GetId() << std::endl; // ok
  }
  else
    cout<<"nullptr"<<endl;

  // Close file
  file1->Close();
  file2->Close();
  
  if(prm != 0)
  {
    cout<<prm->GetInfo()->Data()<<endl; // ok
    std::cout << "prm->GetId() " << prm->GetId() << std::endl; // ok
  }
  else
    cout<<"nullptr"<<endl;
}

int main (int argc, char** argv) 
{
  readData();
  return 0;
}

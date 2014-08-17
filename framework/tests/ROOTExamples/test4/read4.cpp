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
  // Open file and tree
  TFile* file = new TFile ("tree1.root", "READ", "", 0);
  TTree* tree = (TTree*)file->Get("T");

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
  
  // Get TRef using my function (vector)
  PARAM = eve->getTRefKB(0);
  if(PARAM!= 0) // nullptr
  {
    std::cout << "PARAM->GetId() " << PARAM->GetId() << std::endl;
  }
  else
    cout<<"PARAM nullptr"<<endl;
  
  // Print info from ParamClass
  if(prm != 0)
  {
    cout<<prm->GetInfo()->Data()<<endl; // ok
    std::cout << "prm->GetId() " << prm->GetId() << std::endl; // ok
  }
  else
    cout<<"nullptr"<<endl;

  // Close file
  file->Close();
  
  if(prm != 0)
  {
    cout<<prm->GetInfo()->Data()<<endl; // ok
    std::cout << "prm->GetId() " << prm->GetId() << std::endl; // sometimes not ok 8600
    std::cout << "prm->simpleField " << prm->simpleField << std::endl; // ok
  }
  else
    cout<<"nullptr"<<endl;
  
  //std::cout << "PARAM->GetId() " << PARAM->GetId() << std::endl; // segmentation violation
}

int main (int argc, char** argv) 
{
  readData();
  return 0;
}

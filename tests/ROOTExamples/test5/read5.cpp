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
  EventClass* eve = 0;

  // Read few events
  ParamClass* prm = 0;

  prm = eve->GetParam();

  // Get TRef using my function
  ParamClass* PARAM = eve->getTRef();
  std::cout << "PARAM->GetId() " << PARAM->GetId() << std::endl;
  
  // Get TRef using my function
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
}

int main (int argc, char** argv) 
{
  //!!!!!!!!!!!!!!!!!!!!!!!!!
  //readData();
  return 0;
}

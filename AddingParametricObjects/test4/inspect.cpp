#include "../EventClass.h"
#include "../ParamClass.h"

#include <cstddef>
#include <cstdlib>

#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TProcessID.h>

using namespace std;

void Inspect() {

  TFile* file1 = new TFile ("list4.db.root",  "READ", "", 0);
  TList* list1 = (TList*)file1->Get("DataBase");

  TFile* file2 = new TFile ("list4.dbreg.root",  "READ", "", 0);
  TList* list2 = (TList*)file2->Get("DataBase");

  TFile* file3 = new TFile ("tree4.eve.root", "READ", "", 0);
  TTree* tree   = (TTree*)file3->Get("T");

  cout<<"*********************************"<<endl;
  cout<<"files pid's:"<<endl;
  cout<<endl;
  file1->GetListOfProcessIDs()->Print();
  file2->GetListOfProcessIDs()->Print();
  file3->GetListOfProcessIDs()->Print();
  cout<<endl;
  
  cout<<"*********************************"<<endl;
  cout<<"file1 pid details:"<<endl;
  cout<<endl;
  ((TProcessID*)file1->GetListOfProcessIDs()->At(0))->GetObjects()->Print();
  cout<<endl;
  ((TProcessID*)file1->GetListOfProcessIDs()->At(0))->GetPID()->Print();
  cout<<endl;
  ((TProcessID*)file1->GetListOfProcessIDs()->At(0))->GetPIDs()->Print();
  cout<<endl;
  ((TProcessID*)file1->GetListOfProcessIDs()->At(0))->GetSessionProcessID()->Print();
  cout<<endl;
  
  cout<<"*********************************"<<endl;
  cout<<"file2 pid details:"<<endl;
  cout<<endl;
  ((TProcessID*)file2->GetListOfProcessIDs()->At(0))->GetObjects()->Print();
  cout<<endl;
  ((TProcessID*)file2->GetListOfProcessIDs()->At(0))->GetPID()->Print();
  cout<<endl;
  ((TProcessID*)file2->GetListOfProcessIDs()->At(0))->GetPIDs()->Print();
  cout<<endl;
  ((TProcessID*)file2->GetListOfProcessIDs()->At(0))->GetSessionProcessID()->Print();
  cout<<endl;

  //cout<<"*********************************"<<endl;
  //cout<<"file3 pid details:"<<endl;
  //((TProcessID*)file3->GetListOfProcessIDs()->At(0))->GetObjects()->Print();
  //cout<<endl;
  //((TProcessID*)file3->GetListOfProcessIDs()->At(0))->GetPID()->Print();
  //cout<<endl;
  //((TProcessID*)file3->GetListOfProcessIDs()->At(0))->GetPIDs()->Print();
  //cout<<endl;
  //((TProcessID*)file3->GetListOfProcessIDs()->At(0))->GetSessionProcessID()->Print();
  //cout<<endl;

  file1->Close();
  file2->Close();
  file3->Close();

}

int main (int argc, char** argv) {

  Inspect();
  return 0;

}

#include "../EventClass.h"
#include "../ParamClass.h"

#include <cstddef>
#include <cstdlib>

#include <iostream>

#include <TFile.h>
#include <TList.h>
#include <TProcessID.h>

using namespace std;

void Generate (Long_t events) {
  
  Long_t r;
  //srand (0);

  // Open file for Database

  TFile* file = new TFile ("list3.db.root", "RECREATE", "", 0);

  // Create simple database

  TList* dblist = new TList();

  ParamClass* a = new ParamClass ("Alpha",       1);
  ParamClass* b = new ParamClass ("Bravo",       2);
  ParamClass* c = new ParamClass ("ChuckNorris", 3);
  ParamClass* d = new ParamClass ("Damian",      4);

  // Important!
  // Database objects must have assigned ID's 

  TProcessID::AssignID(a);
  TProcessID::AssignID(b);
  TProcessID::AssignID(c);
  TProcessID::AssignID(d);

  // Add objects to list

  dblist->Add(a);
  dblist->Add(b);
  dblist->Add(c);
  dblist->Add(d);

  // write data and close file

  file->WriteObject (dblist, "DataBase");
  file->Close();

}

int main (int argc, char** argv) {

  Generate(1000);
  return 0;

}

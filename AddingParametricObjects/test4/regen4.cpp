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

  // Open file with old database

  TFile* infile  = new TFile ("list4.db.root",    "READ",     "", 0);

  // Crate file for new database

  TFile* outfile = new TFile ("list4.dbreg.root", "RECREATE", "", 0);

  // Load old database

  TList* olddb = (TList*)infile->Get("DataBase");

  ParamClass* a = (ParamClass*)olddb->At(0);
  ParamClass* b = (ParamClass*)olddb->At(1);
  ParamClass* c = (ParamClass*)olddb->At(2);
  ParamClass* d = (ParamClass*)olddb->At(3);

  // Create new database

  TList* newdb = new TList();

  //ParamClass* e = (ParamClass*)a->Clone("ParamClass");
  //ParamClass* f = (ParamClass*)b->Clone("ParamClass");
  //ParamClass* g = (ParamClass*)c->Clone("ParamClass")
  //ParamClass* h = (ParamClass*)d->Clone("ParamClass");;
  
  ParamClass* e = new ParamClass ("AlphaReg",       5);
  ParamClass* f = new ParamClass ("BravoReg",       6);
  ParamClass* g = new ParamClass ("ChuckNorrisReg", 7);
  ParamClass* h = new ParamClass ("DamianReg",      8);

  // Important!
  // New database objects must have the same ID's as corresponding objects
  // in old database

  e->SetUniqueID(a->GetUniqueID());
  f->SetUniqueID(b->GetUniqueID());
  g->SetUniqueID(c->GetUniqueID());
  h->SetUniqueID(d->GetUniqueID());

  // Important!
  // SetUniqueID method does not autoset kIsReferenced flag
  // must be set manually
  
  e->SetBit(kIsReferenced);
  f->SetBit(kIsReferenced);
  g->SetBit(kIsReferenced);
  h->SetBit(kIsReferenced);
  
  // Add objects to list

  newdb->Add(e);
  newdb->Add(f);
  newdb->Add(g);
  newdb->Add(h);

  // write new data and close file

  outfile->WriteObject (newdb, "DataBase");

  // close file with old database
  // Important!
  // file with old database must not be closed before writing data to new one

  infile->Close();
  outfile->Close();

}

int main (int argc, char** argv) {

  Generate(1000);
  return 0;

}

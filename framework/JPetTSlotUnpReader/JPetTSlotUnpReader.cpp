/**
  *  @copyright Copyright (c) 2013, Wojciech Krzemien
  *  @file JPetTSlotUnpReader.cc
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */ 

#include "./JPetTSlotUnpReader.h"
#include <TFile.h> 
#include <TTree.h> 
#include "./Event.h" 

JPetTSlotUnpReader::JPetTSlotUnpReader() :
  fInputFile(0),
  fTree(0),
  fEvent(0) 
{ }

JPetTSlotUnpReader::JPetTSlotUnpReader(const char* filename) :
  fInputFile(0),
  fTree(0),
  fEvent(0) 
{
  OpenFile(filename);
}

JPetTSlotUnpReader::~JPetTSlotUnpReader() 
{ 
  CloseFile();
}
 

void JPetTSlotUnpReader::OpenFile(const char* filename) 
{
  CloseFile();
  TFile* fInputFile = new TFile(filename);
  assert(fInputFile);
  fTree = static_cast<TTree*> (fInputFile->Get("T"));
  assert(fTree);
  TBranch* branch = fTree->GetBranch("event");
  assert(branch);
  branch->SetAddress(&fEvent);
}

void JPetTSlotUnpReader::CloseFile() 
{
  if (fEvent != 0) {
    delete fEvent;
    fEvent = 0;
  }
  if (fTree != 0) {
    delete fTree;
    fTree = 0;
  }
  assert(fInputFile == 0);
  if (fInputFile != 0) {
    delete fInputFile;
    fInputFile = 0;
  }
  assert(fInputFile == 0);
}

long long JPetTSlotUnpReader::GetEntries() const 
{
  if (fTree == 0) {
    return 0;
  } else {
    return fTree->GetEntries();  
  }
}

int JPetTSlotUnpReader::GetEntry(int number)
{
  if (fTree == 0) {
    return 0;
  } else {
    return fTree->GetEntry();  
  }
}

#include "JPetReader.h"

TFile* JPetReader::fFile = NULL;

JPetReader::JPetReader() 
{
}

JPetReader::~JPetReader() 
{
}

bool JPetReader::OpenFile(const char* filename) {
  
  CloseFile();
  fFile = new TFile(filename, "READ");

  if (fFile->IsZombie()) return false;

  return true;
}

void JPetReader::CloseFile() {

  if (fFile==NULL) return;
  
  if(fFile->IsOpen()) fFile->Close();
  delete fFile;
  fFile = NULL;
  
  return;
}

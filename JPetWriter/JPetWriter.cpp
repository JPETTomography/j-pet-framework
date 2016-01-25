// JPetWriter.cpp - Writer
#include "JPetWriter.h"
#include "../JPetUserInfoStructure/JPetUserInfoStructure.h"


JPetWriter::JPetWriter(const char* p_fileName) :
  fFileName(p_fileName),			// string z nazwą pliku
  fFile(0),	// plik
  fIsBranchCreated(false),
  fTree(0)
{
  fFile = new TFile(fFileName.c_str(), "RECREATE");
  if (!isOpen()) {
    ERROR("Could not open file to write.");
  } else {
    fTree = new TTree("tree", "tree");
    fTree->SetAutoSave(10000);
  }
}

JPetWriter::~JPetWriter()
{
  if (isOpen()) {
    fTree->AutoSave("SaveSelf");
    delete fFile;
    fFile = 0;
    fTree = 0;
  }
}

void JPetWriter::closeFile()
{
  if (isOpen() ) {
    fTree->AutoSave("SaveSelf");
    delete fFile;
    fFile = 0;
  }
  fFileName.clear();
  fIsBranchCreated = false;
}

void JPetWriter::writeHeader(TObject* header)
{
  // @todo as the second argument should be passed some enum to indicate position of header
  fTree->GetUserInfo()->AddAt(header, JPetUserInfoStructure::kHeader);
}


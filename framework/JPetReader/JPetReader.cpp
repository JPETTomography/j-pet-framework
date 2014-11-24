// JPetReader.cpp - Reader
#include "JPetReader.h"
#include <cassert>
#include "../JPetUserInfoStructure/JPetUserInfoStructure.h"


JPetReader::JPetReader() :
  fBranch(0),
  fObject(0),
  fTree(0),
  fFile(0)
{}

JPetReader::JPetReader(const char* p_filename) :
  fBranch(0),
  fObject(0),
  fTree(0),
  fFile(0)
{
  if (OpenFile(p_filename)) {
    ReadData("tree");
  }
}

JPetReader::~JPetReader()
{
  if (fFile) {
    delete fFile;
    fFile = 0;
  }
}

void JPetReader::CloseFile ()
{
  if (fFile) delete fFile;
  fFile = 0;
  fBranch = 0;
  fObject = 0;
  fTree = 0;
}


bool JPetReader::OpenFile (const char* filename)
{
  CloseFile();
  fFile = new TFile(filename);
  if ((!isOpen()) || fFile->IsZombie()) {
    ERROR("Cannot open file");
    return false;
  }
  return true;
}

bool JPetReader::ReadData (const char* treename)
{
  
  if (!isOpen() ) {
    ERROR("File not open");
    return false;
  }
  if (!treename) {
    ERROR("empty tree name");
    return false;
  }
  fTree = static_cast<TTree*>(fFile->Get(treename));
  if (!fTree) {
    ERROR("in reading tree");
    return false;
  }
  TObjArray* arr = fTree->GetListOfBranches();
  fBranch = (TBranch*)(arr->At(0));
  if (!fBranch) {
    ERROR("in reading branch from tree");
    return false;
  }
  fBranch->SetAddress(&fObject);
  return true;
}

/**
 * @brief Returns a copy of the header read from input file.
 *
 * Using a copy rather than direct pointer is essential as the original header belongs to JPetReader::fTree and would be deleted along with it.
 */
JPetTreeHeader* JPetReader::GetHeaderClone() const
{
  // get a pointer to a header wchich belongs to fTree
  JPetTreeHeader* header =  (JPetTreeHeader*)fTree->GetUserInfo()->At(JPetUserInfoStructure::kHeader);
  // return a COPY of this header
  return new JPetTreeHeader( *header );
}


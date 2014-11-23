// JPetReader.cpp - Reader
#include "JPetReader.h"
#include <cassert>
#include "../JPetUserInfoStructure/JPetUserInfoStructure.h"


JPetReader::JPetReader() :
  fBranch(0),
  fObject(0),
  fTree(0),
  fFile(NULL)
{}

JPetReader::JPetReader(const char* p_filename) :
  fBranch(0),
  fObject(0),
  fTree(0),
  fFile(NULL)
{
  if (OpenFile(p_filename)) {
    ReadData("tree");
  }
}

JPetReader::~JPetReader()
{
  if (isOpen()) {
    delete fFile;
    fFile = NULL;
  }
}

void JPetReader::CloseFile ()
{
  if (fFile != NULL) {
    if (fFile->IsOpen()) fFile->Close();
    delete fFile;
    fFile = NULL;
  }
  fBranch = 0;
  fObject = 0;
  fTree = 0;
}


bool JPetReader::OpenFile (const char* filename)
{
  CloseFile();

  fFile = new TFile(filename);

  if ((!fFile->IsOpen()) || fFile->IsZombie()) {
    ERROR("Cannot open file.");
    CloseFile();
    return false;
  }
  return true;
}

void JPetReader::ReadData (const char* objname)
{
  assert(objname);
  fTree = static_cast<TTree*>(fFile->Get(objname));
  assert(fTree);
  TObjArray* arr = fTree->GetListOfBranches();
  fBranch = (TBranch*)(arr->At(0));
  assert(fBranch);
  fBranch->SetAddress(&fObject);
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


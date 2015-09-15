// JPetReader.cpp - Reader
#include "JPetReader.h"
#include <cassert>
#include "../JPetUserInfoStructure/JPetUserInfoStructure.h"


JPetReader::JPetReader() :
  fBranch(0),
  fEvent(0),
  fTree(0),
  fFile(0),
  fCurrentEventNumber(-1)
{}

JPetReader::JPetReader(const char* p_filename) :
  fBranch(0),
  fEvent(0),
  fTree(0),
  fFile(0),
  fCurrentEventNumber(-1)
{
  if (!openFileAndLoadData(p_filename, "tree")) {
    ERROR("error in opening file");
  }
}

JPetReader::~JPetReader()
{
  if (fFile) {
    delete fFile;
    fFile = 0;
  }
}

JPetReader::Event& JPetReader::getCurrentEvent()
{
  if (loadCurrentEvent()) {
    return *fEvent;
  } else {
    ERROR("Could not read the current event");
    if (fEvent) {
      delete fEvent;
    }
    fEvent = new TNamed("Empty event", "Empty event");
  }
  return *fEvent;
}

bool JPetReader::JPetReader::nextEvent()
{
  fCurrentEventNumber++;
  return loadCurrentEvent();
}

bool JPetReader::firstEvent()
{
  fCurrentEventNumber = 0;
  return loadCurrentEvent();
}

bool JPetReader::lastEvent()
{
  fCurrentEventNumber = getNbOfAllEvents() - 1;
  return loadCurrentEvent();
}

bool JPetReader::nthEvent(int n)
{
  fCurrentEventNumber = n;
  return loadCurrentEvent();
}

void JPetReader::closeFile ()
{
  if (fFile) delete fFile;
  fFile = 0;
  fBranch = 0;
  fEvent = 0;
  fTree = 0;
  fCurrentEventNumber = -1;
}


bool JPetReader::openFile (const char* filename)
{
  closeFile();
  fFile = new TFile(filename);
  if ((!isOpen()) || fFile->IsZombie()) {
    ERROR(std::string("Cannot open file:")+std::string(filename));
    return false;
  }
  return true;
}

bool JPetReader::loadData(const char* treename)
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
  fBranch->SetAddress(&fEvent);
  firstEvent();
  return true;
}


/**
 * @brief Returns a copy of the header read from input file.
 *
 * Using a copy rather than direct pointer is essential as the original header belongs to JPetReader::fTree and would be deleted along with it.
 */
JPetTreeHeader* JPetReader::getHeaderClone() const
{
  if (!fTree) {
    ERROR("No tree available");  
    return 0;
  }
  // get a pointer to a header wchich belongs to fTree
  JPetTreeHeader* header =  (JPetTreeHeader*)fTree->GetUserInfo()->At(JPetUserInfoStructure::kHeader);
  // return a COPY of this header
  return new JPetTreeHeader( *header );
}

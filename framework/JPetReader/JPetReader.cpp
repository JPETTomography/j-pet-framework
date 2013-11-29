#include "JPetReader.h"
#include <cassert> 

JPetReader::JPetReader () : fBranch(NULL), fFile(NULL), fObject(NULL), fTree(NULL) {
}

JPetReader::~JPetReader () {
  CloseFile();
}

void JPetReader::CloseFile () {
  if (fFile != NULL) {
    if (fFile->IsOpen()) fFile->Close();
    delete fFile;
  }
  fBranch = NULL;
  fFile = NULL;
  fObject = NULL;
  fTree = NULL;
}


bool JPetReader::OpenFile (const char* filename) {
  CloseFile();
  fFile = new TFile(filename);

  if ((!fFile->IsOpen())||fFile->IsZombie()) {
    ERROR("Cannot open file.");
    delete fFile;
    fFile = NULL;
    return false;
  }

  return true;
}

/* tu też bym zwrócił boola i wyszczególnił przypadek,
 * gdy nie ma obiektu o danej nazwie w pliku - Karol
 */
void JPetReader::ReadData (const char* objname) {
  assert(objname);
  if (objname[0]== 0) { ///@warning nie rozumiem tego warunku
    ERROR("No object name specified");
    return;
  }
  fTree = static_cast<TTree*>(fFile->Get(objname));
  assert(fTree);
  fBranch = fTree->GetBranch(objname);
  assert(fBranch);
  fBranch->SetAddress(&fObject);
}

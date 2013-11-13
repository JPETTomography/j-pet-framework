#include "JPetReader.h"

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
/* Tę bym zrobił jako inline, szybciej się będzie wykonywać - Karol */
long long JPetReader::GetEntries () const {
  return fTree->GetEntries();
}

/* Dziwna nazwa, ale rootowska - Karol */
int JPetReader::GetEntry (int entryNo) {
  return fTree->GetEntry(entryNo);
}

/* Tu bym zwrócił boola - Karol */
void JPetReader::OpenFile (const char* filename) {
  CloseFile();
  fFile = new TFile(filename);

  if ((!fFile->IsOpen())||fFile->IsZombie()) {
    ERROR("Cannot open file.");
    delete fFile;
    fFile = NULL;
    return;
  }

  return;
}

/* tu też bym zwrócił boola i wyszczególnił przypadek,
 * gdy nie ma obiektu o danej nazwie w pliku - Karol
 */
void JPetReader::ReadData (const char* objname) {
  if (objname[0]==NULL) {
    ERROR("No object name specified");
    return;
  }
  fTree = static_cast<TTree*>(fFile->Get(objname));
  fBranch = fTree->GetBranch(objname);
  fBranch->SetAddress(&fObject);
}

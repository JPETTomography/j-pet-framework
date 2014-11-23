// JPetWriter.cpp - Writer
#include "JPetWriter.h"
#include "../JPetUserInfoStructure/JPetUserInfoStructure.h"


JPetWriter::JPetWriter(const char* p_fileName) : 
						fFileName(p_fileName),			// string z nazwą pliku
						fFile(fFileName.c_str(), "RECREATE"),	// plik
						fIsBranchCreated(false)
{
  if(fFile.IsZombie())
  {
    ERROR("Could not open file to write.");
  }
//  fTree.SetAutoSave(10000);
}

JPetWriter::~JPetWriter()
{
  //  closeTFile();
}

void JPetWriter::CloseFile() {
    if (IsOpenFile() ) {
      fFile.cd();
      fTree.Write();
      fFile.Close();
    }
    fFileName.clear();
    fIsBranchCreated = false;
}

void JPetWriter::WriteHeader(TObject* header){
     // @todo as the second argument should be passed some enum to indicate position of header
    fTree.GetUserInfo()->AddAt(header, JPetUserInfoStructure::kHeader);
}


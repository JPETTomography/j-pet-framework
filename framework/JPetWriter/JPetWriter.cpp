// JPetWriter.cpp - Writer
#include "JPetWriter.h"
#include "../JPetUserInfoStructure/JPetUserInfoStructure.h"


JPetWriter::JPetWriter(const char* p_fileName) : 
						fFileName(p_fileName),			// string z nazwą pliku
						fFile(fFileName.c_str(), "RECREATE"),	// plik
						fIsBranchCreated(false),
						fTFile(p_fileName, "RECREATE")
{
  if(fFile.IsZombie())
  {
    ERROR("Could not open file to write.");
  }
  
  if(fTFile.IsZombie())
  {
    ERROR("Could not open file to write.");
  }
}

JPetWriter::~JPetWriter()
{
  closeTFile();
}

void JPetWriter::CloseFile() {
    if (fFile.IsOpen() ) {
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

void JPetWriter::closeTFile()
{
  if(fTFile.IsOpen())
  {
    fTFile.cd();
    fTFile.Close();
  }
}

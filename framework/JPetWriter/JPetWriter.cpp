/*
 *  JPetWriter.cpp
 *  
 *
 *  Created by Karol Stola on 13-09-02.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "JPetWriter.h"

//TFile* JPetWriter::fFile = NULL;

JPetWriter::JPetWriter(const char* file_name)
   : fFileName(file_name)  // string z nazwą pliku
   , fFile(fFileName.c_str(),"RECREATE")        // plik
   , fIsBranchCreated(false)
{
    if ( fFile.IsZombie() ){
        ERROR("Could not open file to write.");
    }
}

JPetWriter::~JPetWriter() {
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
    fTree.GetUserInfo()->AddAt(header, 0);
}
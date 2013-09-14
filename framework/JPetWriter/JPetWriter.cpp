/*
 *  JPetWriter.cpp
 *  
 *
 *  Created by Karol Stola on 13-09-02.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "JPetWriter.h"

TFile* JPetWriter::fFile = NULL;

JPetWriter::JPetWriter(){
    
}

bool JPetWriter::OpenFile(const char* filename){
    if (fFile != NULL && fFile->IsOpen() ){
        fFile->Close();
        delete fFile;
    }
    fFile = new TFile(filename, "RECREATE");
    
    if ( fFile->IsOpen() ) return true;
    else return false;
}

void JPetWriter::CloseFile(){
    if (fFile != NULL && fFile->IsOpen()) {
        fFile->Close();
        delete fFile;
    }
}
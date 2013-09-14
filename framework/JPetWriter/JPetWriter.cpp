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

bool JPetWriter::OpenFile(const char* filename){
    CloseFile();
    fFile = new TFile(filename, "UPDATE");
    
    if ( fFile->IsZombie() ) return false;
    else return true;
}

void JPetWriter::CloseFile(){
    if (fFile != NULL) {
        if (fFile->IsOpen() )fFile->Close();
        delete fFile;
        fFile = NULL;
    }
}
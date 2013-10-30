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

bool JPetWriter::Write(const vector<TNamed>& obj, const char* file_name) {
	//TFile *file = new TFile(file_name, "RECREATE");
	TTree tree;
	
	TNamed* filler = new TNamed;
	
	if ( !fFile->IsOpen() ) {
		ERROR("Could not write to file. Have you forgotten to open it?");
		return false;
	}
	
	tree.Branch(filler->GetName(), filler->GetName(), &filler);
	
	for (int i = 0; i < obj.size(); i++){
		*filler = obj[i];
		tree.Fill();
	}
	
	tree.Write();
	
	//tree.Print();
	//tree.Show(2);
	
	//file->Close();
    
    delete filler;
    //delete file;
    
	return true;
}

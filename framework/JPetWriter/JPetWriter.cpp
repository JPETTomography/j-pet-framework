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
{
    if ( fFile.IsZombie() ){
        ERROR("Could not open file to write.");
    }
}

bool JPetWriter::Write(const TNamed& obj){
    vector<TNamed> wrapper;
    wrapper.push_back(obj);
    Write(wrapper);
}

void JPetWriter::CloseFile(){
    if (fFile.IsOpen() ) fFile.Close();
}

bool JPetWriter::Write( vector<TNamed>& obj) {
	
    if (obj.size() == 0) {
        WARNING("Vector passed is empty");
        return false;
    }
    
    if ( !fFile.IsOpen() ) {
		ERROR("Could not write to file. Have you closed it already?");
		return false;
	}
    
    fFile.cd(fFileName.c_str()); // -> http://root.cern.ch/drupal/content/current-directory
    
    TTree tree;
	
	TNamed* filler = &obj[0];
    
	tree.Branch(filler->GetName(), filler->GetName(), &filler);
	
	for (int i = 0; i < obj.size(); i++){
        filler = &obj[i]; 
		tree.Fill();      
	}
	
	tree.Write();
    
	return true;
}

JPetWriter::~JPetWriter(){
    CloseFile();
}

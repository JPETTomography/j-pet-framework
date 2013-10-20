/*
 *  JPetTslotRawWriter.cpp
 *  
 *
 *  Created by Karol Stola on 13-09-14.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "JPetTSlotRawWriter.h"

bool JPetTSlotRawWriter::Write(const vector<JPetTSlot>& obj, const char* file_name) {
	TFile *file = new TFile(file_name, "RECREATE");
	TTree tree;
	
	JPetTSlot* filler = new JPetTSlot;
	
	if ( !file->IsOpen() ) {
		ERROR("Could not write to file.");
		return false;
	}
	
	tree.Branch("JPetTSlot", "JPetTSlot", &filler);
	
	for (int i = 0; i < obj.size(); i++){
		*filler = obj[i];
		tree.Fill();
	}
	
	tree.Write();
	
	//tree.Print();
	//tree.Show(2);
	
	file->Close();
    
    delete filler;
    delete file;
    
	return true;
}
#include "JPetTSlotWriter.h"

bool JPetTSlotWriter::write(const vector<JPetTSlot>& obj, const char* file_name) const {
	TFile *file = new TFile(file_name, "RECREATE");
	TTree tree;
	
	JPetTSlot* filler = new JPetTSlot;
	
	if ( !file->IsOpen() ) {
		ERROR("Could not write to file.");
		return false;
	}
	
	//tree.SetAddress(&filler);
	tree.Branch("JPetTSlot branch", "JPetTSlot", &filler);
	
	
	for (int i = 0; i < obj.size(); i++){
		*filler = obj[i];
		tree.Write();
	}
	tree.Print();
	tree.Show();
	
	file->Close();
	return true;
}
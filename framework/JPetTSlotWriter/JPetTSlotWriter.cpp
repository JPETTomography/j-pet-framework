#include "JPetTSlotWriter.h"

bool JPetTSlotWriter::write(const vector<JPetTSlot>& obj, const char* file_name) const {
	TFile *file = new TFile(file_name, "RECREATE");
	TTree tree;
	
	if ( !file->IsOpen() ) {
		ERROR("Could not write to file.");
		return false;
	}
	
	tree.Branch("JPetTSlot", "vector<JPetTSlot>", (void *)&obj);
	
	tree.Write();
	
	file->Close();
	return true;
}
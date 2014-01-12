#include "JPetHLDReader.h"
#include <iostream>

bool JPetHLDReader::OpenFile (const char* filename){
	JPetReader::OpenFile(filename);
	ReadData("T");
	//fTree->Print();
	fTree->SetBranchAddress("event", &fEvent);
}
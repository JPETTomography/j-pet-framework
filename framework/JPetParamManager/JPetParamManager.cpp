#include "JPetParamManager.h"

void JPetParamManager::readFile(const char * file_name){
	assert(file_name != NULL);
	
	string line;
	istringstream iss(line);
	
	ifstream file(file_name);
	
	while ( !file.eof() ){
		int trb, scin;
		getline(file, line);
		iss >> trb;
		iss >> scin;
		fTRBNumbers.push_back(trb);
		fScinNumbers.push_back(scin);
	}
	
	
}
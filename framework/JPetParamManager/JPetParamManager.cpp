#include "JPetParamManager.h"

void JPetParamManager::readFile(const char * file_name){
	assert(file_name != NULL);
	
	string line;
	
	ifstream file(file_name);
	if( ! file.is_open() ){
		ERROR("No such file!");
		return;
	}
	
	while ( !file.eof() ){
		int trb = 0, scin = 0;
		
		getline(file, line);
		istringstream iss(line);
		
		iss >> trb;
		iss >> scin;
		fTRBNumbers.push_back(trb);
		fScinNumbers.push_back(scin);
	}
}
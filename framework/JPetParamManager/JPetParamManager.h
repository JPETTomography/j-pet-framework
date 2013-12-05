#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include "../../JPetLoggerInclude.h"

using namespace std;

class JPetParamManager {
public:
	void readFile(const char* file_name);
	int getTRBNumber(int i){ return fTRBNumbers[i]; }
	int getScinNumber(int i){ return fScinNumbers[i]; }
	int getDataSize() { assert(fTRBNumbers.size() == fScinNumbers.size()); return fTRBNumbers.size() ;}
private:
	vector<int> fTRBNumbers;
	vector<int> fScinNumbers;
};

#endif
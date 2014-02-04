#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include "../../JPetLoggerInclude.h"


class JPetParamManager {
public:
	void readFile(const char* file_name);
	int getTRBNumber(int i) const { return fTRBNumbers[i]; }
	int getScinNumber(int i) const { return fScinNumbers[i]; }
	int getDataSize() const { assert(fTRBNumbers.size() == fScinNumbers.size()); return fTRBNumbers.size() ;}
private:
        std::vector<int> fTRBNumbers;
        std::vector<int> fScinNumbers;
};

#endif

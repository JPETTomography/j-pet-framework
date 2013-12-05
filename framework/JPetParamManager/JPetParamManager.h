#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class JPetParamManager {
public:
	void readFile(const char* file_name);
private:
	vector<int> fTRBNumbers;
	vector<int> fScinNumbers;
};

#endif
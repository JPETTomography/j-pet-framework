#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
//#include <TFile.h>
//#include <TList.h>
#include "../../JPetLoggerInclude.h"
#include "../JPetKB/JPetKB.h"


class JPetParamManager
{
public:
	JPetParamManager(const std::string &p_KBsDataObjectName = "KBsData");
  
	void readFile(const char* file_name);
	int getTRBNumber(int i) const { return fTRBNumbers[i]; }
	int getScinNumber(int i) const { return fScinNumbers[i]; }
	int getDataSize() const { assert(fTRBNumbers.size() == fScinNumbers.size()); return fTRBNumbers.size() ;}
	
	void fillKBsData(const int p_run_id);
	void fillKBsData(const char *p_fileName);
	void generateRootFileWithKBsData(const char *p_fileName);
	std::vector<JPetKB>& getKBsData(void)
	{
	  return m_KBsData;
	}
	JPetKB getKBData(const unsigned int p_index) const
	{
	  return m_KBsData[p_index];
	}
	int getKBsDataSize(void) const 
	{
	  return m_KBsData.size();
	}
private:
	std::string m_KBsDataObjectName;
        std::vector<int> fTRBNumbers;
        std::vector<int> fScinNumbers;
	std::vector<JPetKB> m_KBsData;
};

#endif

#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include "../../JPetLoggerInclude.h"
#include "../JPetScin/JPetScin.h"
#include <TClonesArray.h>
#include "../JPetWriter/JPetWriter.h"
#include "../JPetReader/JPetReader.h"

class JPetParamManager {
public:
	JPetParamManager()
	{}

	void readFile(const char* file_name);
	//int getTRBNumber(int i) const { return fTRBNumbers[i]; }
	//int getScinNumber(int i) const { return fScinNumbers[i]; }
	//int getDataSize() const { assert(fTRBNumbers.size() == fScinNumbers.size()); return fTRBNumbers.size() ;}
	
	bool setWriter(JPetWriter *writer);
	bool setReader(JPetReader *reader);
	
	void addScintillator(JPetScin &scintillator);
	std::vector<JPetScin*> getScintillators();
	JPetScin* getScintillator(int i);
	int getScintillatorsSize() const { return fScintillators.size(); }
	
	void addPM(JPetPM &pm);
	std::vector<JPetPM*> getPMs();
	JPetPM* getPM(int i);
	int getPMsSize() const { return fPMs.size(); }
	
	void addKB(JPetKB &kb);
	std::vector<JPetKB*> getKB();
	JPetKB* getKB(int i);
	int getKBsSize() const { return fKBs.size(); }
	
	void addTRB(JPetTRB &trb);
	std::vector<JPetTRB*> getTRB();
	JPetTRB* getTRB(int i);
	int getTRBsSize() const { return fTRBs.size(); }
	
	void setTOMB(JPetTOMB &tomb);
	JPetTOMB* getTOMB();
	
	bool writerAllContainers(const char *fileName);
	bool readAllContainers(const char *fileName);
	
private:
        //std::vector<int> fTRBNumbers;
        //std::vector<int> fScinNumbers;
	JPetWriter* fWriter;
	JPetReader* fReader;
	
	std::vector<JPetScin*> fScintillators;
	std::vector<JPetPM*> fPMs;
	std::vector<JPetKB*> fKBs;
	std::vector<JPetTRB*> fTRBs;
	JPetTOMB* fTOMB;//for one run it is only one TOMB module
};

#endif

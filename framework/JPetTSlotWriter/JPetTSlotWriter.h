#ifndef _J_PET_TSLOTWRITER_H_
#define _J_PET_TSLOTWRITER_H_

//#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <cstdlib>
#include "../../Event.h"
#include "../../JPetLoggerInclude.h"
#include "../JPetTSlot/JPetTSlot.h"
#include "../JPetSigCh/JPetSigCh.h"

class JPetTSlotWriter {
public:
	bool write(const vector<JPetTSlot>& obj, const char* file_name) const;		
};

#endif
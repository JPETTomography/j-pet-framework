#ifndef _J_PET_TSLOTWRITER_H_
#define _J_PET_TSLOTWRITER_H_

//#include <TObject.h>
#include <TFile.h>
#include "../../JPetLoggerInclude.h"
#include "../JPetTSlot/JPetTSlot.h"
#include "../JPetSigCh/JPetSigCh.h"

class JPetTSlotWriter {
public:
	bool write(const JPetTSlot& obj, const char* file_name) const {
		TFile *file = new TFile(file_name, "RECREATE");
		
		if ( !file->IsOpen() ) {
			ERROR("Could not write to file.");
			return false;
		}
		
		obj.Write();
		
		file->Close();
	}
		
};

#endif
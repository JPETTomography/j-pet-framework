#ifndef _J_PET_HLD_READER_H_
#define _J_PET_HLD_READER_H_

#include <TObjArray.h>
#include "../JPetReader/JPetReader.h"
#include "../Event/Event.h"

class JPetHLDReader: protected JPetReader {
public:
	bool OpenFile(const char* filename);
	Event& GetEvent(int i) {
		fBranch->GetEntry(i);
		return *fEvent;
	}
private:
	Event* fEvent;
};

#endif
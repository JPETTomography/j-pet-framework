#ifndef _JPETTRB_H_
#define _JPETTRB_H_

#include "TNamed.h"

class JPetTRB: public TNamed {
public:
	int getID() const { return fID; }
	ClassDef(JPetTRB,1);
private:
	int fID;
	int fType;
	int fChan;
	// do implementacji
	//JPetKB* KBId;
	//KBType;
	//KBChan;
};

#endif

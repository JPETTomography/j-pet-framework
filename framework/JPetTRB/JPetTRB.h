#ifndef _JPETTRB_H_
#define _JPETTRB_H_

#include "TNamed.h"

class JPetTRB: public TNamed {
public:
    JPetTRB();
    JPetTRB(int id, int type, int channel);
    void setId(int id) { fID = id;}
    void setType(int type) { fType = type;}
    void setChannel(int channel) { fChan = channel;}
	int getID() const { return fID; }
    int getChannel() const { return fChan; }
    int getType() const { return fType; }
	ClassDef(JPetTRB,1);
private:
	int fID;
	int fType;
	int fChan;
	void init();
    // do implementacji
	//JPetKB* KBId;
	//KBType;
	//KBChan;
};

#endif

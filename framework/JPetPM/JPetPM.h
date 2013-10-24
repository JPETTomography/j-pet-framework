#ifndef _JPET_PM_
#define _JPET_PM_

#include "TNamed.h"

class JPetPM: public TNamed {
public:
	enum Side {kLeft, kRight};
	int getID() const {return fID;}
	void setID(int id) { fID = id; }
	ClassDef(JPetPM,1);
private:
	Side fSide;
	int fID;
	int fHVset;
	int fHVopt;
	float fHVgain[2];
};

#endif

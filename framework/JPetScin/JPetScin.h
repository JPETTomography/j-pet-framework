#ifndef _JPETSCIN_H_
#define _JPETSCIN_H_

#include "TNamed.h"
#include <map>

using namespace std;

class JPetScin: public TNamed {
public:
	enum Dimension {kLen, kHei, kWid};
	int getID() const { return fScinID; }

	ClassDef(JPetScin,1);
private:
	int fScinID;
	float fAttenLen;
	map< Dimension, float > fScinSize;
};

#endif

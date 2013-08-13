#ifndef _JPETSCIN_H_
#define _JPETSCIN_H_

#include <map>

using namespace std;

class JPetScin {
public:
	enum Dimension {kLen, kHei, kWid};
	int getID() const { return fScinID; }
private:
	int fScinID;
	float fAttenLen;
	map< Dimension, float > fScinSize;
};

#endif
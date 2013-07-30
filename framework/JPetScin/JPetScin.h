#ifndef _JPETSCIN_H_
#define _JPETSCIN_H_

#include <map>

using namespace std;

class JPetScin {
public:
	typedef enum Dimension {kLen, kHei, kWid};
private:
	int fScinID;
	float fAttenLen;
	map< Dimension, float > fScinSize;
};

#endif
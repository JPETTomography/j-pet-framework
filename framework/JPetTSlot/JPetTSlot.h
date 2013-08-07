#ifndef _JPETTSLOT_H_
#define _JPETTSLOT_H_

#include <vector>
#include <map>
#include "../JPetSigCh/JPetSigCh.h"

using namespace std;

class JPetTSlot {
public:
	JPetTSlot();
	JPetTSlot(const vector<JPetSigCh> new_vector): fSigChannels(new_vector) {}
	virtual ~JPetTSlot();
	int GetNumberOfSigCh(){ return fSigChannels.size(); }
	const vector<JPetSigCh>& GetSigChVect() const {return fSigChannels;}
	const JPetSigCh & GetSigCh(int index) const { return fSigChannels[index]; }
private:
	vector<JPetSigCh> fSigChannels;
};

#endif
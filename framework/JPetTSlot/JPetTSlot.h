#ifndef _JPETTSLOT_H_
#define _JPETTSLOT_H_

#include <vector>
#include <map>
#include "../JPetSigChannel/JPetSigChannel.h"

using namespace std;

class JPetTSlot {
public:
	JPetTSlot();
	JPetTSlot(const vector<JPetSigChannel> new_vector): fSigChannels(new_vector) {}
	virtual ~JPetTSlot();
	int GetNumberOfSigCh(){ return fSigChannels.size(); }
	const vector<JPetSigChannel>& GetSigChVect() const {return fSigChannels;}
	const JPetSigChannel & GetSigCh(int index) const { return fSigChannels[index]; }
private:
	vector<JPetSigChannel> fSigChannels;
};

#endif
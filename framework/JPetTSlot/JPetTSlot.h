#ifndef _JPETTSLOT_H_
#define _JPETTSLOT_H_

#include <vector>
#include <map>
#include <TNamed.h>
#include "../JPetSigCh/JPetSigCh.h"

using namespace std;

class JPetTSlot: public TNamed {
public:
	JPetTSlot(){SetName("JPetTSlot");}
	JPetTSlot(const vector<JPetSigCh>& new_vector): fSigChannels(new_vector) {}
	
	void addCh(const JPetSigCh& new_ch ){ fSigChannels.push_back(new_ch); }
	
	unsigned int size() const { return fSigChannels.size(); }
	int getNumberOfSigCh(){ return fSigChannels.size(); }
	const vector<JPetSigCh>& getSigChVect() const {return fSigChannels;}
	const JPetSigCh & operator[](int index) const { return fSigChannels[index]; }

	virtual ~JPetTSlot(){}

	ClassDef(JPetTSlot,1);
private:
	vector<JPetSigCh> fSigChannels;
};

#endif

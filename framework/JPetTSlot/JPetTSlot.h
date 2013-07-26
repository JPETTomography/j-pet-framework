#ifndef _JPETTSLOT_H_
#define _JPETTSLOT_H_

#include <vector>
#include <map>
#include "../JPetSigChannel/JPetSigChannel.h"

using namespace std;

class JPetTSlot {
public:
	int getChannelsNo(){ return fSigChannels.size(); }
private:
	vector<JPetSigChannel> fSigChannels;
};

#endif
#ifndef _JPETSIGCHANNEL_H_
#define _JPETSIGCHANNEL_H_

#include <vector>
#include <map>

#include "../JPetPM/JPetPM.h"

using namespace std;

class JPetSigChannel {
public:
	JPetSigChannel(float EdgeTime, float FallEdgeTime = 0);
	typedef enum EdgeType { kEdge, kFalling };
	bool isSlow() { return fIsSlow; }
	float getTime(EdgeType Type) { return fChannels[0][Type]; }
	float getTime(int ChanNo, EdgeType Type) { return fChannels[ChanNo][Type]; }
	void addChan(float EdgeTime, float FallEdgeTime);
	void setPM(JPetPM* PM) { fPM = PM; }
private:
	typedef map < EdgeType, float > SingleChan;
	typedef vector < SingleChan > ChanSet;
	//float fAmpl;
	 
	ChanSet fChannels;
	bool fIsSlow;
	JPetPM* fPM;
};

#endif
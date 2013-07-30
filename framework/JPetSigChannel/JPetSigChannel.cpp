#include "JPetSigChannel.h"

JPetSigChannel::JPetSigChannel(float EdgeTime, float FallEdgeTime){
	if (FallEdgeTime == 0) fIsSlow = 1;
	addChan(EdgeTime, FallEdgeTime);
}
	
void JPetSigChannel::addChan(float EdgeTime, float FallEdgeTime){
	SingleChan tmp;
	tmp[kEdge] = EdgeTime;
	tmp[kFalling] = FallEdgeTime;
	fChannels.push_back(tmp);
}
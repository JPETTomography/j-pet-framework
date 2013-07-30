#include "JPetSigChannel.h"

JPetSigChannel::JPetSigChannel(bool IsSlow):
	fIsSlow(IsSlow) {}
	
void JPetSigChannel::addChan(float EdgeTime, float FallEdgeTime){
	SingleChan tmp;
	tmp[kEdge] = EdgeTime;
	tmp[kFalling] = FallEdgeTime;
	fChannels.push_back(tmp);
}
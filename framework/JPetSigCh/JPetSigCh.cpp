#include "JPetSigCh.h"

JPetSigCh::JPetSigCh(float EdgeTime, float FallEdgeTime){
	if (FallEdgeTime == 0) fIsSlow = 1;
	addCh(EdgeTime, FallEdgeTime);
}
	
void JPetSigCh::addCh(float EdgeTime, float FallEdgeTime){
	SingleCh tmp;
	tmp[kEdge] = EdgeTime;
	tmp[kFalling] = FallEdgeTime;
	fChannels.push_back(tmp);
}
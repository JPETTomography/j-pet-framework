#include "JPetSigCh.h"

JPetSigCh::JPetSigCh(float EdgeTime, float FallEdgeTime){
	fPM = NULL;
	fTRB = NULL;
	fScin = NULL;
	fBarrelSlot = NULL;
	if (FallEdgeTime == 0) fIsSlow = 1;
	addCh(EdgeTime, FallEdgeTime);
}
	
void JPetSigCh::addCh(float EdgeTime, float FallEdgeTime){
	SingleCh tmp;
	tmp[kRising] = EdgeTime;
	tmp[kFalling] = FallEdgeTime;
	fChannels.push_back(tmp);
}
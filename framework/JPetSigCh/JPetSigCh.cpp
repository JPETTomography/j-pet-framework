#include "JPetSigCh.h"

JPetSigCh::JPetSigCh(const JPetSigCh& obj){

}

JPetSigCh::JPetSigCh(float edge_time, float fall_edge_time){
	fPM = NULL;
	fTRB = NULL;
	fScin = NULL;
	fBarrelSlot = NULL;
	if (fall_edge_time == 0) fIsSlow = 1;
	addCh(edge_time, fall_edge_time);
}
	
void JPetSigCh::addCh(float edge_time, float fall_edge_time){
	SingleCh tmp;
	tmp[kRising] = edge_time;
	tmp[kFalling] = fall_edge_time;
	fChannels.push_back(tmp);
}
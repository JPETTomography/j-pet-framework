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

void JPetSigCh::setPM(const JPetPM& pm){
	if (fPM != NULL) delete fPM;
	
	try { fPM = new JPetPM; }
	catch(bad_alloc& b_a){
		ERROR("Could not allocate memory.");
		ERROR(b_a.what());
		throw;
	}
	
	*fPM = pm;
}
	
void JPetSigCh::addCh(float edge_time, float fall_edge_time){
	SingleCh tmp;
	tmp[kRising] = edge_time;
	tmp[kFalling] = fall_edge_time;
	fChannels.push_back(tmp);
}
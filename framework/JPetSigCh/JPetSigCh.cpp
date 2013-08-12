#include "JPetSigCh.h"

void JPetSigCh::init(){
	fPM = NULL;
	fTRB = NULL;
	fScin = NULL;
	fBarrelSlot = NULL;
	fAmpl = 0;
}

JPetSigCh::JPetSigCh(const JPetSigCh& obj){
	init();
	*this = obj;
}

JPetSigCh::JPetSigCh(float edge_time, float fall_edge_time){
	init();
	if (fall_edge_time == 0) fIsSlow = 1;
	addCh(edge_time, fall_edge_time);
}

template <class T>
void JPetSigCh::set(T** dest, const T& source) throw(bad_alloc){
	assert(dest != NULL);
	
	if ( &source == NULL && *dest != NULL ){
		delete *dest;
		*dest = NULL;
		return;
	}
	
	if (*dest == NULL) {
		try { *dest = new T; }
		catch(bad_alloc& b_a){
			ERROR("Could not allocate memory.");
			ERROR(b_a.what());
			throw;
		}
	}
	**dest = source;
}
	
void JPetSigCh::addCh(float edge_time, float fall_edge_time){
	SingleCh tmp;
	tmp[kRising] = edge_time;
	tmp[kFalling] = fall_edge_time;
	fChannels.push_back(tmp);
}

JPetSigCh& JPetSigCh::operator=(const JPetSigCh& obj){
	if (this != &obj){
		setPM(obj.getPM());
		setTRB(obj.getTRB());
		setScin(obj.getScin());
		setBarrelSlot(obj.getBarrelSlot());
	}
	return *this;
}
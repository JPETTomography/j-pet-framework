#ifndef _JPETSIGCH_H_
#define _JPETSIGCH_H_


#include <cassert>
#include <vector>
#include <map>

#include "../JPetPM/JPetPM.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetTRB/JPetTRB.h"
#include "../../JPetLoggerInclude.h"

using namespace std;

class JPetSigCh {

public:
	JPetSigCh() { init(); }
	JPetSigCh(const JPetSigCh& obj);
	JPetSigCh(float EdgeTime, float FallEdgeTime = 0);
	
	enum EdgeType { kRising, kFalling };
	
	float getAmpl() const { return fAmpl; }
	float getTime(EdgeType type, int ch_no = 0) const { return fChannels[ch_no].find(type)->second; }
	const JPetPM& getPM() const { assert(fPM != NULL); return *fPM; }
	const JPetTRB& getTRB() const { assert(fTRB != NULL); return *fTRB; }
	const JPetScin& getScin() const { assert(fScin != NULL); return *fScin; }
	const JPetBarrelSlot& getBarrelSlot() const { assert(fBarrelSlot != NULL); return *fBarrelSlot; }
	
	void addCh(float edge_time, float fall_edge_time);
	
	void setPM(const JPetPM& pm) throw(bad_alloc) { set(&fPM, pm); }
	void setTRB(const JPetTRB& trb) throw(bad_alloc) { set(&fTRB, trb); }
	void setScin(const JPetScin& scin) throw(bad_alloc) { set(&fScin, scin); }
	void setBarrelSlot(const JPetBarrelSlot& barrel_slot) throw(bad_alloc) { set(&fBarrelSlot, barrel_slot); }	
	
	JPetSigCh& operator= (const JPetSigCh& obj);

private:
	typedef map < EdgeType, float > SingleCh;
	typedef vector < SingleCh > ChSet;
	
	float fAmpl; 
	ChSet fChannels;
	bool fIsSlow;
	JPetPM* fPM;
	JPetTRB* fTRB;
	JPetScin* fScin;
	JPetBarrelSlot* fBarrelSlot;
	
	template <class T> void set(T** dest, const T& source) throw(bad_alloc);
	void init();
};

#endif

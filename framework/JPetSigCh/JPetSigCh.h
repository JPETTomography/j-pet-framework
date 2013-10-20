#ifndef _JPETSIGCH_H_
#define _JPETSIGCH_H_


#include <cassert>
#include <vector>
#include <map>
#include <TClass.h>

#include "../JPetPM/JPetPM.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetTRB/JPetTRB.h"
#include "../../JPetLoggerInclude.h"

using namespace std;

class JPetSigCh: public TNamed {

public:
	enum EdgeType { kRising, kFalling };
	typedef map < EdgeType, float > SingleCh;
	typedef vector < SingleCh > ChSet;

	JPetSigCh(): TNamed("JPetSigCh", "Signal Channel Structure")  { init(); }
	JPetSigCh(const JPetSigCh& obj);
	JPetSigCh(float EdgeTime, float FallEdgeTime = 0);
	
	bool isSlow() const {return fIsSlow;}
	
	unsigned int size() const {return fChannels.size(); }
	float getAmpl() const { return fAmpl; }
	float getTime(EdgeType type, int ch_no = 0) const { return fChannels[ch_no].find(type)->second; }
	const JPetPM& getPM() const { /*assert(fPM != NULL);*/ return *fPM; }
	const JPetTRB& getTRB() const { /*assert(fTRB != NULL);*/ return *fTRB; }
	const JPetScin& getScin() const { /*assert(fScin != NULL);*/ return *fScin; }
	const JPetBarrelSlot& getBarrelSlot() const { /*assert(fBarrelSlot != NULL);*/ return *fBarrelSlot; }
	const ChSet& getChSet() const {return fChannels;}
	
	void addCh(float edge_time, float fall_edge_time);
	
	void setPM(const JPetPM& pm) { set(&fPM, pm); }
	void setTRB(const JPetTRB& trb) { set(&fTRB, trb); }
	void setScin(const JPetScin& scin) { set(&fScin, scin); }
	void setBarrelSlot(const JPetBarrelSlot& barrel_slot) { set(&fBarrelSlot, barrel_slot); }	
	
	JPetSigCh& operator= (const JPetSigCh& obj);

	ClassDef(JPetSigCh,1);

protected:
	
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

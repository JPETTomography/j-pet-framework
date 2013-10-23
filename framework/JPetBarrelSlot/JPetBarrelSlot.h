#ifndef _JPETBARRELSLOT_H_
#define	_JPETBARRELSLOT_H_

#include "TNamed.h"

class JPetBarrelSlot: public TNamed {
public:
	ClassDef(JPetBarrelSlot,1);

private:
	int fSlotId;
	int fLayerId;
	int fLayerRad;
	float SlotTheta;
};

#endif

#ifndef _JPETBARRELSLOT_H_
#define	_JPETBARRELSLOT_H_

#include "TNamed.h"

class JPetBarrelSlot: public TNamed
{
 public:
  JPetBarrelSlot();
  JPetBarrelSlot(int slotId, int layerID, int layerRad, float slotTheta);
  inline int getSlotID() const { return fSlotID; }
  inline int getLayerID() const { return fLayerID; }
  inline int getLayerRad() const { return fLayerRad; }
  inline float getSlotTheta() const { return fSlotTheta; }
  inline void setSlotID(int id) { fSlotID = id; }
  inline void setLayerID(int id) { fLayerID = id; }
  inline void setLayerRad(int layerRad) { fLayerRad = layerRad; }
  inline void setSlotTheta(float slotTheta) { fSlotTheta = slotTheta;}

 private:
  int fSlotID;
  int fLayerID;
  int fLayerRad;
  float fSlotTheta;
  ClassDef(JPetBarrelSlot, 1);
};

#endif

#include "JPetBarrelSlot.h"
ClassImp(JPetBarrelSlot);

JPetBarrelSlot::JPetBarrelSlot():
  fSlotID(0),
  fLayerID(0),
  fLayerRad(0),
  fSlotTheta(0.)
{ /* */ }

JPetBarrelSlot::JPetBarrelSlot(int slotID, int layerID, int layerRad, float slotTheta):
  fSlotID(slotID),
  fLayerID(layerID),
  fLayerRad(layerRad),
  fSlotTheta(slotTheta)
{ /* */ }

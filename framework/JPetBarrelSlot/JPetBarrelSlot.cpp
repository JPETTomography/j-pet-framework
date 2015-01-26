#include "JPetBarrelSlot.h"

JPetBarrelSlot::JPetBarrelSlot():
  fSlotID(0),
  fLayerID(0),
  fLayerRad(0),
  fSlotTheta(0.)
{
  SetName("JPetBarrelSlot");
}

JPetBarrelSlot::JPetBarrelSlot(int slotID, int layerID, int layerRad, float slotTheta):
  fSlotID(slotID),
  fLayerID(layerID),
  fLayerRad(layerRad),
  fSlotTheta(slotTheta)
{
  SetName("JPetBarrelSlot");
}

JPetBarrelSlot::JPetBarrelSlot(int id, bool isActive, std::string name, float theta, int layerId, int inFrameId):
  fId(id),
  fIsActive(isActive),
  fName(name),
  fTheta(theta),
  fLayerId(layerId),
  fInFrameId(inFrameId)
{
  SetName("JPetBarrelSlot");
}

JPetBarrelSlot::~JPetBarrelSlot()
{
}

ClassImp(JPetBarrelSlot);
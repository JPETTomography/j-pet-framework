#include "JPetBarrelSlot.h"

JPetBarrelSlot::JPetBarrelSlot():
  fId(-1),
  fIsActive(false),
  fName(""),
  fTheta(-1.f),
  fInFrameID(-1)
{
  SetName("JPetBarrelSlot");
}


JPetBarrelSlot::JPetBarrelSlot(int id, bool isActive, std::string name, float theta, int inFrameID):
  fId(id),
  fIsActive(isActive),
  fName(name),
  fTheta(theta),
  fInFrameID(inFrameID)
{
  SetName("JPetBarrelSlot");
}

ClassImp(JPetBarrelSlot);

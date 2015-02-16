#include "JPetBarrelSlot.h"

JPetBarrelSlot::JPetBarrelSlot():
  fId(-1),
  fIsActive(false),
  fName(""),
  fTheta(-1.f)
{
  SetName("JPetBarrelSlot");
}


JPetBarrelSlot::JPetBarrelSlot(int id, bool isActive, std::string name, float theta):
  fId(id),
  fIsActive(isActive),
  fName(name),
  fTheta(theta)
{
  SetName("JPetBarrelSlot");
}

ClassImp(JPetBarrelSlot);

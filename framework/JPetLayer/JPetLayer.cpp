// JPet Layer - JPetLayer.cpp
#include "JPetLayer.h"


JPetLayer::JPetLayer() : 
  fId(-1),
  fIsActive(false),
  fName(std::string("")),
  fRadius(-1.f),
  fTRefFrame(NULL)
{
  SetName("JPetLayer");
}

JPetLayer::JPetLayer(int id, bool isActive, std::string name, float radius) :
  fId(id),
  fIsActive(isActive),
  fName(name),
  fRadius(radius),
  fTRefFrame(NULL)
{
  SetName("JPetLayer");
}

ClassImp(JPetLayer);

// JPet Layer - JPetLayer.cpp
#include "JPetLayer.h"


JPetLayer::JPetLayer() : 
  fId(-1),
  fIsActive(false),
  fName(std::string("")),
  fRadius(-1.f)
{
  SetName("JPetLayer");
}

JPetLayer::JPetLayer(int id, bool isActive, std::string name, float radius) :
  fId(id),
  fIsActive(isActive),
  fName(name),
  fRadius(radius)
{
  SetName("JPetLayer");
}

ClassImp(JPetLayer);

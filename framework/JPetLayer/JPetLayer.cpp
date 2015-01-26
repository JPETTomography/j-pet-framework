// JPet Layer - JPetLayer.cpp
#include "JPetLayer.h"


JPetLayer::JPetLayer() : 
  fId(0),
  fIsActive(false),
  fName(std::string("")),
  fRadius(0.f),
  fFrameId(0)
{
  SetName("JPetLayer");
}

JPetLayer::JPetLayer(int id, bool isActive, std::string name, float radius, int frameId) :
  fId(id),
  fIsActive(isActive),
  fName(name),
  fRadius(radius),
  fFrameId(frameId)
{
  SetName("JPetLayer");
}

JPetLayer::~JPetLayer()
{
}

ClassImp(JPetLayer);
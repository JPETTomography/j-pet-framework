// JPet Frame - JPetFrame.cpp
#include "JPetFrame.h"


JPetFrame::JPetFrame() :
  fId(0),
  fIsActive(false),
  fStatus(std::string("")),
  fDescription(std::string("")),
  fVersion(0),
  fCreator_id(0)
{
  SetName("JPetFrame");
}
  
JPetFrame::JPetFrame(int id, bool isActive, std::string status, std::string description, int version, int creator_id) :
  fId(id),
  fIsActive(isActive),
  fStatus(status),
  fDescription(description),
  fVersion(version),
  fCreator_id(creator_id)
{
  SetName("JPetFrame");
}

JPetFrame::~JPetFrame()
{
}

ClassImp(JPetFrame);
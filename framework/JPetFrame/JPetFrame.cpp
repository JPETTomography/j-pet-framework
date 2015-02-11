// JPet Frame - JPetFrame.cpp
#include "JPetFrame.h"


JPetFrame::JPetFrame() :
  fId(-1),
  fIsActive(false),
  fStatus(std::string("")),
  fDescription(std::string("")),
  fVersion(-1),
  fCreator_id(-1)
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

ClassImp(JPetFrame);

// JPet Slot - JPetSlot.cpp
#include "JPetSlot.h"


ClassImp(JPetSlot);


JPetSlot::JPetSlot(int p_id, 
		   std::string p_name, 
		   float p_thetaAngle, 
		   JPetLayer &p_JPetLayer, 
		   JPetFrame &p_JPetFrame, 
		   JPetScin &p_JPetScin) : 
					  m_id(p_id),
					  m_name(p_name),
					  m_thetaAngle(p_thetaAngle),
					  m_JPetLayer(p_JPetLayer),
					  m_JPetFrame(p_JPetFrame),
					  m_JPetScin(p_JPetScin)
{
}

JPetSlot::~JPetSlot()
{
}

int JPetSlot::id() const
{
  return m_id;
}

std::string JPetSlot::name() const
{
  return m_name;
}

float JPetSlot::thetaAngle() const
{
  return m_thetaAngle;
}

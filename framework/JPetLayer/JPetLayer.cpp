// JPet Layer - JPetLayer.cpp
#include "JPetLayer.h"


ClassImp(JPetLayer);


JPetLayer::JPetLayer(int p_id, 
		     std::string p_name, 
		     float p_radius, 
		     JPetSlot &p_JPetSlot, 
		     JPetFrame &p_JPetFrame) : 
					      m_id(p_id),
					      m_name(p_name),
					      m_radius(p_radius),
					      m_JPetSlot(p_JPetSlot),
					      m_JPetFrame(p_JPetFrame)
{
}

JPetLayer::~JPetLayer()
{
}

int JPetLayer::id() const
{
  return m_id;
}

std::string JPetLayer::name() const
{
  return m_name;
}

float JPetLayer::radius() const
{
  return m_radius;
}

// JPet TOMB - JPetTOMB.cpp
#include "JPetTOMB.h"


ClassImp(JPetTOMB);


JPetTOMB::JPetTOMBInput::JPetTOMBInput(int p_id, std::string p_description) : m_id(p_id), m_description(p_description)
{
}

JPetTOMB::JPetTOMB(int p_id, 
		   std::string p_description,
		   int p_TOMBInputId, 
		   std::string p_TOMBInputDescription) :
							  m_id(p_id),
							  m_description(p_description),
							  m_TOMBInput(p_TOMBInputId, p_TOMBInputDescription)
{
}

JPetTOMB::~JPetTOMB()
{
}

int JPetTOMB::id() const
{
  return m_id;
}

std::string JPetTOMB::description() const
{
  return m_description;
}

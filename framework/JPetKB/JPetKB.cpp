// JPet Konrad Board - JPetKB.cpp
#include "JPetKB.h"


ClassImp(JPetKB);


JPetKB::JPetKBInput::JPetKBInput(int p_KBId) : JPetKBChannel(), m_KBId(p_KBId)
{
}

JPetKB::JPetKBOutput::JPetKBOutput(bool p_passedInformationIsTime,
				    std::string p_passedInformation, 
				    int p_KBId, 
				    int p_inputId, 
				    int p_KBInputId) : 
						      JPetKBChannel(),
						      m_passedInformationIsTime(p_passedInformationIsTime),
						      m_passedInformation(p_passedInformation),
						      m_KBId(p_KBId),
						      m_inputId(p_inputId),
						      m_KBInputId(p_KBInputId)
{
}


JPetKB::JPetKB(int p_id, 
	       bool p_isActive, 
	       std::string p_status, 
	       std::string p_description, 
	       int p_version, 
	       JPetUser &p_JPetUser) :
				      m_id(p_id),
				      m_isActive(p_isActive),
				      m_status(p_status),
				      m_description(p_description),
				      m_version(p_version),
				      m_JPetUser(p_JPetUser) 
{
}

JPetKB::~JPetKB()
{
}

int JPetKB::id() const
{
  return m_id;
}

bool JPetKB::isActive() const
{
  return m_isActive;
}

std::string JPetKB::status() const
{
  return m_status;
}

std::string JPetKB::description() const
{
  return m_description;
}

int JPetKB::version() const
{
  return m_version;
}

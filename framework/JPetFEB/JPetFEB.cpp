// JPet Konrad Board - JPetFEB.cpp
#include "JPetFEB.h"


ClassImp(JPetFEB);


JPetFEB::JPetFEBInput::JPetFEBInput(int p_FEBId) : JPetFEBChannel(), m_FEBId(p_FEBId)
{
}

JPetFEB::JPetFEBOutput::JPetFEBOutput(bool p_passedInformationIsTime,
				    std::string p_passedInformation, 
				    int p_FEBId, 
				    int p_inputId, 
				    int p_FEBInputId) : 
						      JPetFEBChannel(),
						      m_passedInformationIsTime(p_passedInformationIsTime),
						      m_passedInformation(p_passedInformation),
						      m_FEBId(p_FEBId),
						      m_inputId(p_inputId),
						      m_FEBInputId(p_FEBInputId)
{
}

JPetFEB::JPetFEB() :
				      m_id(0),
				      m_isActive(false),
				      m_status(""),
				      m_description(""),
				      m_version(0),
				      m_userId(0) 
{
  SetName("JPetFEB");
}


JPetFEB::JPetFEB(int p_id, 
	       bool p_isActive, 
	       std::string p_status, 
	       std::string p_description, 
	       int p_version, 
	       int p_userId) :
				      m_id(p_id),
				      m_isActive(p_isActive),
				      m_status(p_status),
				      m_description(p_description),
				      m_version(p_version),
				      m_userId(p_userId) 
{
  SetName("JPetFEB");
}

JPetFEB::~JPetFEB()
{
}

int JPetFEB::id() const
{
  return m_id;
}

bool JPetFEB::isActive() const
{
  return m_isActive;
}

std::string JPetFEB::status() const
{
  return m_status;
}

std::string JPetFEB::description() const
{
  return m_description;
}

int JPetFEB::version() const
{
  return m_version;
}

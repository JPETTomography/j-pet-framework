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
				    int p_FEBInputId ) : 
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
				      m_userId(0),
				      m_n_time_outputs_per_input(0),
				      m_n_notime_outputs_per_input(0)
{
  SetName("JPetFEB");
}


JPetFEB::JPetFEB(int p_id, 
	       bool p_isActive, 
	       std::string p_status, 
	       std::string p_description, 
	       int p_version, 
	       int p_userId,
	       int p_n_time_outputs_per_input,
	       int p_n_notime_outputs_per_input) :
				      m_id(p_id),
				      m_isActive(p_isActive),
				      m_status(p_status),
				      m_description(p_description),
				      m_version(p_version),
				      m_userId(p_userId),
				      m_n_time_outputs_per_input(p_n_time_outputs_per_input),
				      m_n_notime_outputs_per_input(p_n_notime_outputs_per_input) 
{
  SetName("JPetFEB");
}

JPetFEB::~JPetFEB()
{
}

int JPetFEB::getID() const
{
  return m_id;
}

void JPetFEB::setID(int p_id)
{
  m_id = p_id;
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

/**
 * @brief Get number of output time channels per one FEB input channel
 *
 */
int JPetFEB::getNtimeOutsPerInput(void) const
{
  return m_n_time_outputs_per_input;
}

/**
 * @brief Get number of output non-time (e.g. TOT or charge) channels per one FEB input channel
 *
 */
int JPetFEB::getNnotimeOutsPerInput(void) const
{
  return m_n_notime_outputs_per_input;
}

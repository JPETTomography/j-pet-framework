// JPet Setup - JPetSetup.cpp
#include "JPetSetup.h"
#include "../CommonTools/CommonTools.h"


ClassImp(JPetSetup);


JPetSetup::JPetSetup(int p_id,
		     std::string p_name,
		     std::string p_description,
		     JPetUser &p_JPetUser) :
					    m_id(p_id),
					    m_name(p_name),
					    m_description(p_description),
					    m_JPetUser(p_JPetUser)
{
  std::string l_currentDateTime = CommonTools::currentDateTime();
  m_creationDate = l_currentDateTime;
  m_modifiedDate = l_currentDateTime;
}

JPetSetup::~JPetSetup()
{
}

int JPetSetup::id() const
{
  return m_id;
}

std::string JPetSetup::name() const
{
  return m_name;
}

std::string JPetSetup::creationDate() const
{
  return m_creationDate;
}

std::string JPetSetup::modifiedDate() const
{
  return m_modifiedDate;
}

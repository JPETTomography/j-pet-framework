// JPet User - JPetUser.cpp
#include "JPetUser.h"
#include "../CommonTools/CommonTools.h"


ClassImp(JPetUser);


bool JPetUser::m_isUserLogged = false;


JPetUser::JPetUser(int p_id, 
		   std::string p_name, 
		   std::string p_lastName, 
		   std::string p_login, 
		   std::string p_password, 
		   bool p_isRoot) :
				    m_id(p_id),
				    m_name(p_name),
				    m_lastName(p_lastName),
				    m_login(p_login),
				    m_password(p_password),
				    m_isRoot(p_isRoot)
{
  std::string l_currentDateTime = CommonTools::currentDateTime();
  m_creationDate = l_currentDateTime;
  m_lastLoginDate = l_currentDateTime;
}

JPetUser::~JPetUser()
{
}

std::string JPetUser::password() const
{
  return m_password;
}

bool JPetUser::isUserLogged()
{
  return m_isUserLogged;
}

bool JPetUser::logIn()
{
  toggleUserLoggedStatus();
  
  // TODO
  return false;
}

bool JPetUser::logOut()
{
  toggleUserLoggedStatus();
  
  // TODO
  return false;
}

bool JPetUser::changeLogin()
{
  // TODO
  return false;
}

bool JPetUser::changePassword()
{
  // TODO
  return false;
}

int JPetUser::id() const
{
  return m_id;
}

std::string JPetUser::name() const
{
  return m_name;
}

std::string JPetUser::lastName() const
{
  return m_lastName;
}

std::string JPetUser::login() const
{
  return m_login;
}

bool JPetUser::isRoot() const
{
  return m_isRoot;
}

std::string JPetUser::creationDate() const
{
  return m_creationDate;
}

std::string JPetUser::lastLoginDate() const
{
  return m_lastLoginDate;
}

// JPet User - JPetUser.h
#ifndef JPET_USER_H
#define JPET_USER_H

#include "TNamed.h"


class JPetUser: public TNamed
{
protected:
  const int m_id;
  std::string m_name;
  std::string m_lastName;
  std::string m_login;
  std::string m_password;
  const bool m_isRoot;
  std::string m_creationDate;
  std::string m_lastLoginDate;
  
  static bool m_isUserLogged;
  inline void toggleUserLoggedStatus()
  {
    m_isUserLogged = !m_isUserLogged;
  }
  virtual std::string password(void) const;
  
public:
  JPetUser(void);
  JPetUser(int p_id, 
	   std::string p_name, 
	   std::string p_lastName, 
	   std::string p_login, 
	   std::string p_password, 
	   bool p_isRoot,
	   std::string p_creationDate,
	   std::string p_lastLoginDate);
  virtual ~JPetUser(void);
  
private:
  JPetUser(const JPetUser &user);
  JPetUser& operator=(const JPetUser &user);
  
public:
  static bool isUserLogged(void);
  virtual bool logIn(void);
  virtual bool logOut(void);
  virtual bool changeLogin(void);
  virtual bool changePassword(void);
  
  virtual int id(void) const;
  virtual std::string name(void) const;
  virtual std::string lastName(void) const;
  virtual std::string login(void) const;
  virtual bool isRoot(void) const;
  virtual std::string creationDate(void) const;
  virtual std::string lastLoginDate(void) const;

  inline bool operator==(const JPetUser& user) { return id() == user.id(); }
  inline bool operator!=(const JPetUser& user) { return id() != user.id(); }
  
private:
  ClassDef(JPetUser, 1);
};

#endif // JPET_USER_H

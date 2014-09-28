// JPet Setup - JPetSetup.h
#ifndef JPET_SETUP_H
#define JPET_SETUP_H

#include "TNamed.h"
#include "../JPetUser/JPetUser.h"

/**
 * @brief Parametric class representing database information on a single setup of the PET system.
 *
 */
class JPetSetup: public TNamed
{
protected:
  int m_id;
  std::string m_name;
  std::string m_description;
  std::string m_creationDate;
  std::string m_modifiedDate;
  JPetUser &m_JPetUser;		//creatorId
  /*
  frame_id
  highvoltage_id
  lowvoltage_id
  parent_id
  */
public:
  JPetSetup(int p_id, std::string p_name, std::string p_description, JPetUser &p_JPetUser);
  virtual ~JPetSetup(void);
  
  virtual int id(void) const;
  virtual std::string name(void) const;
  virtual std::string creationDate(void) const;
  virtual std::string modifiedDate(void) const;
  
private:
  ClassDef(JPetSetup, 1);
};

#endif // JPET_SETUP_H

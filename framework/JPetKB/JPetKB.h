// JPet Konrad board - JPetKB.h
#ifndef JPET_KB_H
#define JPET_KB_H

#include "TNamed.h"
#include "../JPetUser/JPetUser.h"


class JPetKB: public TNamed
{
protected:
  struct JPetKBChannel
  {
    int m_id;
    bool m_isActive;
    std::string m_status;
    int m_portNumber;
    std::string m_description;
  };
  
  struct JPetKBInput : public JPetKBChannel
  {
    JPetKBInput(int p_KBId);
    
    int m_KBId;
  };

  struct JPetKBOutput : public JPetKBChannel
  {
    JPetKBOutput(bool p_passedInformationIsTime, std::string p_passedInformation, int p_KBId, int p_inputId, int p_KBInputId);
    
    bool m_passedInformationIsTime;
    std::string m_passedInformation;
    int m_KBId;
    int m_inputId;
    int m_KBInputId;
  };
  
  int m_id;
  bool m_isActive;
  std::string m_status;
  std::string m_description;
  int m_version;
  JPetUser &m_JPetUser;		//creatorId

public:
  JPetKB(int p_id, bool p_isActive, std::string p_status, std::string p_description, int p_version, JPetUser &p_JPetUser);
  virtual ~JPetKB(void);
  
  virtual int id(void) const;
  virtual bool isActive(void) const;
  virtual std::string status(void) const;
  virtual std::string description(void) const;
  virtual int version(void) const;
  
private:
  ClassDef(JPetKB, 1);
};

#endif // JPET_KB_H

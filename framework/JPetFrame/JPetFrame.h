// JPet Frame - JPetFrame.h
#ifndef JPET_FRAME_H
#define JPET_FRAME_H

#include "TNamed.h"
#include "../JPetUser/JPetUser.h"
#include "../JPetLayer/JPetLayer.h"
#include "../JPetSlot/JPetSlot.h"


class JPetLayer;
class JPetSlot;

class JPetFrame: public TNamed
{
protected:
  int m_id;
  std::string m_status;
  std::string m_description;
  int m_version;
  JPetUser &m_JPetUser;		//creatorId
  JPetLayer &m_JPetLayer;
  JPetSlot &m_JPetSlot;
  
public:
  JPetFrame(int p_id, std::string p_status, std::string p_description, int p_version, JPetUser &p_JPetUser, JPetLayer &p_JPetLayer, JPetSlot &p_JPetSlot);
  virtual ~JPetFrame(void);
  
  virtual int id(void) const;
  virtual std::string status(void) const;
  virtual std::string description(void) const;
  virtual int version(void) const;
  
private:
  ClassDef(JPetFrame, 1);
};

#endif // JPET_FRAME_H

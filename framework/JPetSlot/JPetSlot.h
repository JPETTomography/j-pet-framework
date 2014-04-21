// JPet Slot - JPetSlot.h
#ifndef JPET_SLOT_H
#define JPET_SLOT_H

#include "TNamed.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetLayer/JPetLayer.h"
#include "../JPetFrame/JPetFrame.h"


class JPetLayer;
class JPetFrame;
class JPetScin;

class JPetSlot: public TNamed
{
protected:
  int m_id;
  std::string m_name;
  float m_thetaAngle;
  JPetLayer &m_JPetLayer;
  JPetFrame &m_JPetFrame;
  JPetScin &m_JPetScin;
  
public:
  JPetSlot(int p_id, std::string p_name, float p_thetaAngle, JPetLayer &p_JPetLayer, JPetFrame &p_JPetFrame, JPetScin &p_JPetScin);
  virtual ~JPetSlot(void);
  
  virtual int id(void) const;
  virtual std::string name(void) const;
  virtual float thetaAngle(void) const;
  
private:
  ClassDef(JPetSlot, 1);
};

#endif // JPET_SLOT_H

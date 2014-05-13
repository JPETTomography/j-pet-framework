// JPet Layer - JPetLayer.h
#ifndef JPET_LAYER_H
#define JPET_LAYER_H

#include "TNamed.h"
#include "../JPetSlot/JPetSlot.h"
#include "../JPetFrame/JPetFrame.h"


class JPetSlot;
class JPetFrame;

class JPetLayer: public TNamed
{
protected:
  int m_id;
  std::string m_name;
  float m_radius;
  JPetSlot &m_JPetSlot;
  JPetFrame &m_JPetFrame;
  
public:
  JPetLayer(int p_id, std::string p_name, float p_thetaAngle, JPetSlot &p_JPetSlot, JPetFrame &p_JPetFrame);
  virtual ~JPetLayer(void);
  
  virtual int id(void) const;
  virtual std::string name(void) const;
  virtual float radius(void) const;
  
private:
  ClassDef(JPetLayer, 1);
};

#endif // JPET_LAYER_H

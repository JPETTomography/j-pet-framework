// JPet Layer - JPetLayer.h
#ifndef JPET_LAYER_H
#define JPET_LAYER_H

#include "TNamed.h"
#include "../JPetFrame/JPetFrame.h"


class JPetFrame;

/**
 * @brief Parametric class representing database information on a single cyllindrical layer of a JPetFrame.
 *
 * The layer consists of slots represented by JPetBarrelSlot objects.
 */
class JPetLayer: public TNamed
{
protected:
  int m_id;
  std::string m_name;
  float m_radius;
  JPetFrame &m_JPetFrame;
  
public:
  JPetLayer(int p_id, std::string p_name, float p_thetaAngle, JPetFrame &p_JPetFrame);
  virtual ~JPetLayer(void);
  
private:
  JPetLayer(const JPetLayer &layer);
  JPetLayer& operator=(const JPetLayer &layer);
  
public:
  
  virtual int id(void) const;
  virtual std::string name(void) const;
  virtual float radius(void) const;
  
private:
  ClassDef(JPetLayer, 1);
};

#endif // JPET_LAYER_H

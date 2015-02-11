// JPet Layer - JPetLayer.h
#ifndef JPET_LAYER_H
#define JPET_LAYER_H

#include <TRef.h>
#include "../JPetFrame/JPetFrame.h"
#include "TNamed.h"

//class JPetFrame;

/**
 * @brief Parametric class representing database information on a single cyllindrical layer of a JPetFrame.
 *
 * The layer consists of slots represented by JPetBarrelSlot objects.
 */
class JPetLayer: public TNamed
{
protected:
  int fId;
  bool fIsActive;
  std::string fName;
  float fRadius;
  TRef fTRefFrame;

public:
  JPetLayer();
  JPetLayer(int id, bool isActive, std::string name, float radius);
  ~JPetLayer();
  
  inline bool operator==(const JPetLayer& layer) { return getId() == layer.getId(); }
  inline bool operator!=(const JPetLayer& layer) { return getId() != layer.getId(); }
  
  int getId() const { return fId; }
  bool getIsActive() const { return fIsActive; }
  std::string getName() const { return fName; }
  float getRadius() const { return fRadius; }
  const JPetFrame& getFrame() { return static_cast<JPetFrame&>(*(fTRefFrame.GetObject())); }
  void setFrame(JPetFrame &frame)
  {
    fTRefFrame = &frame;
  }
  
protected:
  void clearTRefFrame()
  {
    fTRefFrame = NULL;
  }
  
private:
  ClassDef(JPetLayer, 1);
};

#endif // JPET_LAYER_H

/**
 *  @copyright Copyright (c) 2015, The J-Pet Framework Authors.
 *  @file JPetLayer.h
 */

#ifndef JPET_LAYER_H
#define JPET_LAYER_H

#include <TRef.h>
#include "../JPetFrame/JPetFrame.h"
#include "TNamed.h"


/**
 * @brief Parametric class representing database information on a single cyllindrical layer of a JPetFrame.
 *
 * The layer consists of slots represented by JPetBarrelSlot objects.
 */
class JPetLayer: public TNamed
{
protected:
  const int fId;
  bool fIsActive;
  std::string fName;
  float fRadius;
  TRef fTRefFrame;

public:
  JPetLayer();
  JPetLayer(int id, bool isActive, std::string name, float radius);
  
  inline bool operator==(const JPetLayer& layer) { return getId() == layer.getId(); }
  inline bool operator!=(const JPetLayer& layer) { return getId() != layer.getId(); }
  
  inline int getId() const { return fId; }
  inline bool getIsActive() const { return fIsActive; }
  inline std::string getName() const { return fName; }
  inline float getRadius() const { return fRadius; }
  inline const JPetFrame& getFrame() { return static_cast<JPetFrame&>(*(fTRefFrame.GetObject())); }
  inline void setFrame(JPetFrame &frame) { fTRefFrame = &frame; }
  
protected:
  void clearTRefFrame()
  {
    fTRefFrame = NULL;
  }
  
private:
  ClassDef(JPetLayer, 2);
};

#endif // JPET_LAYER_H

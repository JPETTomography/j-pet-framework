/**
 *  @copyright Copyright (c) 2015, The J-Pet Framework Authors.
 *  @file JPetBarrelSlot.h
 */

#ifndef _JPETBARRELSLOT_H_
#define	_JPETBARRELSLOT_H_

#include <TRef.h>
#include "../JPetLayer/JPetLayer.h"
#include "TNamed.h"

/**
 * @brief Parametric class representing database information on a single slot of the physical PET barrel.
 *
 * A BarrelSlot consists of one scintillator strip and two photomultipliers at the scintillator's ends.
 */
class JPetBarrelSlot: public TNamed
{
public:
  /// Default constructor sets fId, fTheta to -1. 
  JPetBarrelSlot();
  JPetBarrelSlot(int id, bool isActive, std::string name, float theta, int inFrameID);
  
  inline bool operator==(const JPetBarrelSlot& bslot) { return getID() == bslot.getID(); }
  inline bool operator!=(const JPetBarrelSlot& bslot) { return getID() != bslot.getID(); }

  inline int getID() const { return fId; }
  inline float getTheta() const { return fTheta; }
  inline bool isActive() const { return fIsActive; }
  inline std::string getName() const { return fName; }
  inline int getInFrameID() const {return fInFrameID; }
  inline const JPetLayer & getLayer() const { return static_cast<JPetLayer&>(*(fTRefLayer.GetObject())); }
  
  void setLayer(JPetLayer &p_layer)
  {
    fTRefLayer = &p_layer;
  }
  
private:
  int fId;
  bool fIsActive;
  std::string fName;
  float fTheta;
  int fInFrameID;
  TRef fTRefLayer;
  
protected:
  void clearTRefLayer()
  {
    fTRefLayer = NULL;
  }

  ClassDef(JPetBarrelSlot, 3);
};

#endif

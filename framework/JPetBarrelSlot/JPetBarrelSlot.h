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
  JPetBarrelSlot();
  JPetBarrelSlot(int slotId, int layerID, int layerRad, float slotTheta);
  JPetBarrelSlot(int id, bool isActive, std::string name, float theta, int layerId, int inFrameId);
  ~JPetBarrelSlot();
  
  inline int getSlotID() const { return fSlotID; }
  inline int getLayerID() const { return fLayerID; }
  inline int getLayerRad() const { return fLayerRad; }
  inline float getSlotTheta() const { return fSlotTheta; }

  inline bool operator==(const JPetBarrelSlot& bslot) { return getSlotID() == bslot.getSlotID(); }
  inline bool operator!=(const JPetBarrelSlot& bslot) { return getSlotID() != bslot.getSlotID(); }

  inline void setSlotID(int id) { fSlotID = id; }
  inline void setLayerID(int id) { fLayerID = id; }
  inline void setLayerRad(int layerRad) { fLayerRad = layerRad; }
  inline void setSlotTheta(float slotTheta) { fSlotTheta = slotTheta;}
  
  int getId() const { return fId; }
  bool getIsActive() const { return fIsActive; }
  std::string getName() const { return fName; }
  float getTheta() const { return fTheta; }
  int getLayerId() const { return fLayerId; }
  int getInFrameId() const { return fInFrameId; }
  const JPetLayer & getLayer() { return (JPetLayer&)*(fTRefLayer.GetObject()); }
  
  void setLayer(JPetLayer &p_layer)
  {
    fTRefLayer = &p_layer;
  }
  
private:
  int fId;
  bool fIsActive;
  std::string fName;
  float fTheta;
  int fLayerId;
  int fInFrameId;
  TRef fTRefLayer;
  
protected:
  void clearTRefLayer()
  {
    fTRefLayer = NULL;
  }
  
private:
  int fSlotID;
  int fLayerID;
  int fLayerRad;
  float fSlotTheta;
  
  ClassDef(JPetBarrelSlot, 1);
};

#endif

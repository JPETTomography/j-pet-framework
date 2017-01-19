/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
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
  JPetBarrelSlot(bool isNull);
  
  inline bool operator==(const JPetBarrelSlot& bslot) const { return getID() == bslot.getID(); }
  inline bool operator!=(const JPetBarrelSlot& bslot) const { return getID() != bslot.getID(); }

  inline int getID() const { return fId; }
  inline float getTheta() const { return fTheta; }
  inline bool isActive() const { return fIsActive; }
  inline std::string getName() const { return fName; }
  inline int getInFrameID() const {return fInFrameID; }
  inline const JPetLayer & getLayer() const {
    static JPetLayer DummyResult(true);
    if(fTRefLayer.GetObject()) return static_cast<JPetLayer&>(*(fTRefLayer.GetObject()));
    else  {
      ERROR("No JPetLayer slot set, Null object will be returned");
      return DummyResult;
    }
  }

  inline bool isNullObject() const { return fIsNullObject; }
  
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
  bool fIsNullObject = false;
  
protected:
  void clearTRefLayer()
  {
    fTRefLayer = NULL;
  }

  ClassDef(JPetBarrelSlot, 3);
};

#endif

/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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

#include "./JPetLayer/JPetLayer.h"
#include "./JPetLoggerInclude.h"
#include "TNamed.h"
#include <TRef.h>

/**
 * @brief Representation of a single slot in J-PET barrel
 *
 * Parametric class representing database information about a single slot
 * of the J-PET barrel. A BarrelSlot consists of one scintillator strip
 * and two photomultipliers at the scintillator's ends.
 */
class JPetBarrelSlot: public TNamed
{
public:
  JPetBarrelSlot();
  JPetBarrelSlot(int id, bool isActive, std::string name, float theta, int inFrameID);
  explicit JPetBarrelSlot(bool isNull);
  bool operator==(const JPetBarrelSlot& bslot) const;
  bool operator!=(const JPetBarrelSlot& bslot) const;
  int getID() const;
  float getTheta() const;
  bool isActive() const;
  std::string getName() const;
  int getInFrameID() const;
  bool hasLayer() const;
  const JPetLayer& getLayer() const;
  bool isNullObject() const;
  static  JPetBarrelSlot& getDummyResult();
  void setLayer(JPetLayer& p_layer);

protected:
  void clearTRefLayer();

#ifndef __CINT__
  int fId = -1;
  bool fIsActive = false;
  std::string fName = "";
  float fTheta = -1.f;
  int fInFrameID = -1;
  TRef fTRefLayer;
  bool fIsNullObject = false;
#else
  int fId;
  bool fIsActive;
  std::string fName;
  float fTheta;
  int fInFrameID;
  TRef fTRefLayer;
  bool fIsNullObject;
#endif

  ClassDef(JPetBarrelSlot, 4);
};

#endif /* !_JPETBARRELSLOT_H_ */

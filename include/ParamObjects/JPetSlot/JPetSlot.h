/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetSlot.h
 */

#ifndef JPETSLOT_H
#define JPETSLOT_H

#include "JPetLayer/JPetLayer.h"
#include <TNamed.h>
#include <TRef.h>

/**
 * @brief Representation of a single slot in J-PET barrel
 *
 * Parametric class representing database information about a single slot
 * of the J-PET Detector. A Slot consists of one scintillator strip
 * and photomultipliers at the scintillator's ends.
 */
class JPetSlot : public TNamed
{
public:
  enum Type
  {
    Barrel,
    Module
  };
  JPetSlot();
  JPetSlot(int id, double theta, JPetSlot::Type type);
  JPetSlot(const JPetSlot& slot);
  explicit JPetSlot(bool isNull);
  virtual ~JPetSlot();
  void setID(int id);
  void setTheta(double theta);
  void setType(JPetSlot::Type type);
  void setLayer(JPetLayer& layer);
  int getID() const;
  double getTheta() const;
  JPetSlot::Type getType() const;
  const JPetLayer& getLayer() const;
  bool operator==(const JPetSlot& slot) const;
  bool operator!=(const JPetSlot& slot) const;
  bool isNullObject() const;
  static JPetSlot& getDummyResult();

protected:
  void clearTRefLayer();

  int fID = -1;
  double fTheta = -1.0;
  Type fType = Barrel;
  bool fIsNullObject = false;
  TRef fTRefLayer;

  ClassDef(JPetSlot, 1);
};

#endif /* !JPETSLOT_H */

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
 *  @file JPetScin.h
 */

#ifndef _JPETSCIN_H_
#define _JPETSCIN_H_

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetLoggerInclude.h"
#include "TNamed.h"
#include <TRef.h>

/**
 * @brief Representation of a scintillator.
 *
 * Parametric class representing database information of a scintillator in the
 * JPetBarrelSlot object.
 */
class JPetScin: public TNamed
{
public:
  enum Dimension {kLength, kHeight, kWidth};
  struct ScinDimensions {
    ScinDimensions(): fLength(0), fHeight(0), fWidth(0) {}
    ScinDimensions(float len, float h, float w): fLength(len), fHeight(h), fWidth(w) {}
    float fLength;
    float fHeight;
    float fWidth;
  };

  JPetScin();
  explicit JPetScin(int id);
  explicit JPetScin(bool isNull);
  JPetScin(int id, float attenLen, float length, float height, float width);
  ~JPetScin();
  bool operator==(const JPetScin& scin) const;
  bool operator!=(const JPetScin& scin) const;
  int getID() const;
  void setScinSize(ScinDimensions size);
  void setScinSize(Dimension dim, float value);
  void setAttenLen(float attenLen);
  void setBarrelSlot(JPetBarrelSlot& p_barrelSlot);
  float getAttenLen() const;
  float getScinSize(Dimension dim) const;
  ScinDimensions getScinSize() const;
  JPetBarrelSlot& getBarrelSlot() const;
  static JPetScin& getDummyResult();
  bool isNullObject() const;

protected:
  void clearTRefBarrelSlot();

#ifndef __CINT__
  int fID = 0;
  float fAttenLen = 0.0;
  ScinDimensions fScinSize;
  bool fIsNullObject = false;
#else
  int fID;
  float fAttenLen;
  ScinDimensions fScinSize;
  bool fIsNullObject;
#endif
  TRef fTRefBarrelSlot;

  friend class JPetParamManager;

  ClassDef(JPetScin, 4);
};

#endif /* !_JPETSCIN_H_ */

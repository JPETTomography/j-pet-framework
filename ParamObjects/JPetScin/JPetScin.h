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
 *  @file JPetScin.h
 */

#ifndef _JPETSCIN_H_
#define _JPETSCIN_H_

#include "TNamed.h"
#include <TRef.h>
#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetLoggerInclude.h"


/**
 * @brief Parametric class representing database information on parameters of a scintillator.
 *
 */
class JPetScin: public TNamed
{
public:
  enum Dimension {kLength, kHeight, kWidth};
  struct ScinDimensions {
    ScinDimensions(): fLength(0), fHeight(0), fWidth(0) { }
    ScinDimensions(float len, float h, float w): fLength(len), fHeight(h), fWidth(w) { }
    float fLength;
    float fHeight;
    float fWidth;
  };

  JPetScin();
  explicit JPetScin(int id);
  JPetScin(int id, float attenLen, float length, float height, float width);
  explicit JPetScin(bool isNull);
  ~JPetScin();

  bool operator==(const JPetScin& scin) const;
  bool operator!=(const JPetScin& scin) const;

  int getID() const;
  float getAttenLen() const;
  ScinDimensions getScinSize() const;
  float getScinSize(Dimension dim) const;
  void setAttenLen(float attenLen);
  void setScinSize(ScinDimensions size);
  void setScinSize(Dimension dim, float value);
  void setBarrelSlot(JPetBarrelSlot& p_barrelSlot);
  JPetBarrelSlot& getBarrelSlot() const;
  bool isNullObject() const;
  static JPetScin& getDummyResult();

protected:
  void clearTRefBarrelSlot();

#ifndef __CINT__
  int fID = 0;
  float fAttenLen = 0.0;  /// attenuation length
  ScinDimensions fScinSize; /// @todo check if there is no problem with the ROOT dictionnary
  bool fIsNullObject = false;
#else
  int fID;
  float fAttenLen;  /// attenuation length
  ScinDimensions fScinSize; /// @todo check if there is no problem with the ROOT dictionnary
  bool fIsNullObject;
#endif
  TRef fTRefBarrelSlot;

  friend class JPetParamManager;

  ClassDef(JPetScin, 4);
};

#endif

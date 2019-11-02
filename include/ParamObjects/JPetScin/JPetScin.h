/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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

#ifndef JPETSCIN_H
#define JPETSCIN_H

#include "./JPetSlot/JPetSlot.h"
#include <TVector3.h>
#include <TNamed.h>
#include <TRef.h>

/**
 * @brief Representation of a scintillator.
 *
 * Parametric class representing database information of a scintillator in the
 * JPetSlot object.
 */
class JPetScin: public TNamed
{
public:
  JPetScin();
  JPetScin(
    int id, float length, float height, float width,
    float center_x, float center_y, float center_z
  );
  JPetScin(const JPetScin &scin);
  explicit JPetScin(bool isNull);
  virtual ~JPetScin();

  void setID(int id);
  void setLength(float length);
  void setHeight(float height);
  void setWidth(float width);
  void setCenter(TVector3 center);
  void setCenterX(float centerX);
  void setCenterY(float centerY);
  void setCenterZ(float centerZ);
  void setSlot(JPetSlot& slot);
  int getID() const;
  float getLength() const;
  float getHeight() const;
  float getWidth() const;
  TVector3 getCenter() const;
  float getCenterX() const;
  float getCenterY() const;
  float getCenterZ() const;
  const JPetSlot& getSlot() const;
  bool operator==(const JPetScin& scin) const;
  bool operator!=(const JPetScin& scin) const;
  static JPetScin& getDummyResult();
  bool isNullObject() const;

protected:
  void clearTRefSlot();

#ifndef __CINT__
  int fID = -1;
  float fLength = 0.0;
  float fHeight = 0.0;
  float fWidth = 0.0;
  bool fIsNullObject = false;
#else
  int fID;
  float fLength;
  float fHeight;
  float fWidth;
  bool fIsNullObject;
#endif
  TVector3 fScinCenter;
  TRef fTRefSlot;

  friend class JPetParamManager;

  ClassDef(JPetScin, 6);
};

#endif /* !JPETSCIN_H */

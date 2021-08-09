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
 *  @file JPetScin.h
 */

#ifndef JPETSCIN_H
#define JPETSCIN_H

#include "JPetSlot/JPetSlot.h"
#include <TNamed.h>
#include <TRef.h>
#include <TVector3.h>

/**
 * @brief Representation of a scintillator.
 *
 * Parametric class representing database information of a scintillator in the
 * JPetSlot object.
 */
class JPetScin : public TNamed
{
public:
  JPetScin();
  JPetScin(int id, double length, double height, double width, double center_x, double center_y, double center_z, double rotX, double rotY,
           double rotZ);
  JPetScin(const JPetScin& scin);
  explicit JPetScin(bool isNull);
  virtual ~JPetScin();

  void setID(int id);
  void setLength(double length);
  void setHeight(double height);
  void setWidth(double width);
  void setCenter(TVector3 center);
  void setCenterX(double centerX);
  void setCenterY(double centerY);
  void setCenterZ(double centerZ);
  void setRotation(TVector3 rotation);
  void setRotationX(double rotationX);
  void setRotationY(double rotationY);
  void setRotationZ(double rotationZ);
  void setSlot(JPetSlot& slot);
  int getID() const;
  double getLength() const;
  double getHeight() const;
  double getWidth() const;
  TVector3 getCenter() const;
  double getCenterX() const;
  double getCenterY() const;
  double getCenterZ() const;
  TVector3 getRotation() const;
  double getRotationX() const;
  double getRotationY() const;
  double getRotationZ() const;
  const JPetSlot& getSlot() const;
  bool operator==(const JPetScin& scin) const;
  bool operator!=(const JPetScin& scin) const;
  static JPetScin& getDummyResult();
  bool isNullObject() const;

protected:
  int fID = -1;
  double fLength = 0.0;
  double fHeight = 0.0;
  double fWidth = 0.0;
  bool fIsNullObject = false;
  TVector3 fScinCenter;
  TVector3 fScinRotation;
  TRef fTRefSlot = nullptr;
  void clearTRefSlot();

  friend class JPetParamManager;

  ClassDef(JPetScin, 6);
};

#endif /* !JPETSCIN_H */

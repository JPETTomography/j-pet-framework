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
 *  @file JPetBaseHit.h
 */

#ifndef JPETBASEHIT_H
#define JPETBASEHIT_H

#include "JPetScin/JPetScin.h"
#include <TObject.h>
#include <TRef.h>
#include <TVector3.h>

/**
 * @brief Base class for hit data classes
 *
 * This is the base class of a scintillator hit represenatation, that all other hits
 * should inherit from. It contains minimal required information about physical interaction
 * of a gamma quanta with the material and a reference to Scin object.
 */
class JPetBaseHit : public TObject
{
public:
  JPetBaseHit();
  JPetBaseHit(float time, float energy, const TVector3& position);
  JPetBaseHit(float time, float energy, const TVector3& position, JPetScin& scin);
  virtual ~JPetBaseHit();
  float getTime() const;
  float getEnergy() const;
  float getPosX() const;
  float getPosY() const;
  float getPosZ() const;
  float getPos(int index) const;
  const TVector3& getPos() const;
  const JPetScin& getScin() const;
  void setTime(float time);
  void setEnergy(float energy);
  void setPosX(float x);
  void setPosY(float y);
  void setPosZ(float z);
  void setPos(float x, float y, float z);
  void setPos(const TVector3& position);
  void setScin(JPetScin& scin);
  void Clear(Option_t*) override;
  static JPetBaseHit& getDummyResult();

protected:
  float fTime = 0.0;
  float fEnergy = 0.0;
  TVector3 fPos;
  TRef fScin = nullptr;

  ClassDef(JPetBaseHit, 1);
};
#endif /* !JPETBASEHIT_H */

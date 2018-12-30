/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetLayer.h
 */

#ifndef JPET_LAYER_H
#define JPET_LAYER_H

#include "./JPetFrame/JPetFrame.h"
#include "./JPetLoggerInclude.h"
#include "TNamed.h"
#include <cassert>
#include <TRef.h>

/**
 * @brief Representation of a layer in the JPetFrame.
 *
 * Parametric class representing database information on a single cyllindrical
 * layer of a JPetFrame. The layer consists of slots represented by JPetBarrelSlot
 * objects.
 */
class JPetLayer: public TNamed
{
public:
  JPetLayer();
  JPetLayer(int id, bool isActive, std::string name, float radius);
  explicit JPetLayer(bool isNull);
  bool operator==(const JPetLayer& layer) const;
  bool operator!=(const JPetLayer& layer) const;
  int getID() const;
  bool getIsActive() const;
  std::string getName() const;
  float getRadius() const;
  const JPetFrame& getFrame() const;
  void setFrame(JPetFrame& frame);
  bool isNullObject() const;
  static JPetLayer& getDummyResult();

protected:
  void clearTRefFrame();

#ifndef __CINT__
  const int fId = -1;
  bool fIsActive = false;
  std::string fName = "";
  float fRadius = -1.f;
  TRef fTRefFrame = NULL;
  bool fIsNullObject = false;
#else
  const int fId;
  bool fIsActive;
  std::string fName;
  float fRadius;
  TRef fTRefFrame;
  bool fIsNullObject;
#endif

  ClassDef(JPetLayer, 4);
};
#endif /* !JPET_LAYER_H */

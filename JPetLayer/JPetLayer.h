/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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

#include <TRef.h>
#include "../JPetFrame/JPetFrame.h"
#include "TNamed.h"
#include <cassert>

/**
 * @brief Parametric class representing database information on a single cyllindrical layer of a JPetFrame.
 *
 * The layer consists of slots represented by JPetBarrelSlot objects.
 */
class JPetLayer: public TNamed
{
protected:
  const int fId;
  bool fIsActive;
  std::string fName;
  float fRadius;
  TRef fTRefFrame;

public:
  JPetLayer();
  JPetLayer(int id, bool isActive, std::string name, float radius);

  bool operator==(const JPetLayer& layer) const;
  bool operator!=(const JPetLayer& layer) const;

  inline int getID() const {
    return fId;
  }
  inline bool getIsActive() const {
    return fIsActive;
  }
  inline std::string getName() const {
    return fName;
  }
  inline float getRadius() const {
    return fRadius;
  }
  inline const JPetFrame& getFrame() const {
    return static_cast<JPetFrame&>(*(fTRefFrame.GetObject()));
  }
  inline void setFrame(JPetFrame& frame) {
    fTRefFrame = &frame;
  }

protected:
  void clearTRefFrame() {
    fTRefFrame = NULL;
  }

private:
  ClassDef(JPetLayer, 3);
};

#endif // JPET_LAYER_H

/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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

#include "JPetSetup/JPetSetup.h"
#include <TNamed.h>
#include <TRef.h>

/**
 * @brief Representation of a layer in the JPetSetup.
 *
 * Parametric class representing database information on a single
 * layer of a JPetSetup. The layer consists of slots represented by JPetSlot
 * objects.
 */
class JPetLayer : public TNamed
{
public:
  JPetLayer();
  JPetLayer(int id, std::string name, double radius);
  JPetLayer(const JPetLayer& layer);
  explicit JPetLayer(bool isNull);
  virtual ~JPetLayer();
  void setID(int id);
  void setName(std::string name);
  void setRaduis(double radius);
  void setSetup(JPetSetup& setup);
  int getID() const;
  std::string getName() const;
  double getRadius() const;
  const JPetSetup& getSetup() const;
  bool operator==(const JPetLayer& layer) const;
  bool operator!=(const JPetLayer& layer) const;
  bool isNullObject() const;
  static JPetLayer& getDummyResult();

protected:
  void clearTRefSetup();

#ifndef __CINT__
  int fID = -1;
  std::string fName = "";
  double fRadius = -1.0;
  bool fIsNullObject = false;
  TRef fTRefSetup = nullptr;

  friend class JPetParamManager;

  ClassDef(JPetLayer, 6);
};
#endif /* !JPET_LAYER_H */

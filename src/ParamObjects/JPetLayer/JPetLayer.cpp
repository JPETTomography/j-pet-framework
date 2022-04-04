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
 *  @file JPetLayer.cpp
 */

#include "JPetLayer/JPetLayer.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetLayer);

JPetLayer::JPetLayer() { SetName("JPetLayer"); }

JPetLayer::JPetLayer(int id, std::string name, float radius) : fID(id), fName(name), fRadius(radius) { SetName("JPetLayer"); }

JPetLayer::JPetLayer(const JPetLayer& layer) : fID(layer.getID()), fName(layer.getName()), fRadius(layer.getRadius()) { SetName("JPetLayer"); }

JPetLayer::JPetLayer(bool isNull) : fIsNullObject(isNull) { SetName("JPetLayer"); }

JPetLayer::~JPetLayer() {}

void JPetLayer::setID(int id) { fID = id; }

void JPetLayer::setName(std::string name) { fName = name; }

void JPetLayer::setRaduis(float radius) { fRadius = radius; }

void JPetLayer::setSetup(JPetSetup& setup) { fTRefSetup = &setup; }

int JPetLayer::getID() const { return fID; }

std::string JPetLayer::getName() const { return fName; }

float JPetLayer::getRadius() const { return fRadius; }

const JPetSetup& JPetLayer::getSetup() const
{
  if (fTRefSetup.GetObject())
  {
    return static_cast<JPetSetup&>(*(fTRefSetup.GetObject()));
  }
  else
  {
    ERROR("No JPetSetup set, Null object will be returned");
    return JPetSetup::getDummyResult();
  }
}

bool JPetLayer::operator==(const JPetLayer& layer) const
{
  return this->getID() == layer.getID() && this->getName() == layer.getName() && this->getRadius() == layer.getRadius() &&
         this->getSetup() == layer.getSetup();
}

bool JPetLayer::operator!=(const JPetLayer& layer) const { return !(*this == layer); }

bool JPetLayer::isNullObject() const { return fIsNullObject; }

JPetLayer& JPetLayer::getDummyResult()
{
  static JPetLayer dummyResult(true);
  return dummyResult;
}

void JPetLayer::clearTRefSetup() { fTRefSetup = nullptr; }

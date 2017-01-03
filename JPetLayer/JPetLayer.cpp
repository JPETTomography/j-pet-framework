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
 *  @file JPetLayer.cpp
 */

#include "JPetLayer.h"


JPetLayer::JPetLayer() :
  fId(-1),
  fIsActive(false),
  fName(std::string("")),
  fRadius(-1.f),
  fTRefFrame(NULL)
{
  SetName("JPetLayer");
}

JPetLayer::JPetLayer(int id, bool isActive, std::string name, float radius) :
  fId(id),
  fIsActive(isActive),
  fName(name),
  fRadius(radius),
  fTRefFrame(NULL)
{
  SetName("JPetLayer");
}

bool JPetLayer::operator==(const JPetLayer& layer) const
{
  if ( getID() == layer.getID() ) {
    // assure consistency
    assert( getRadius() == layer.getRadius() );
    assert( getName() == layer.getName() );
    assert( getIsActive() == layer.getIsActive() );
    return true;
  }

  return false;
}

bool JPetLayer::operator!=(const JPetLayer& layer) const
{
  return ! (*this == layer);
}


ClassImp(JPetLayer);

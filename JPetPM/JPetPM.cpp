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
 *  @file JPetPM.cpp
 */

#include "JPetPM.h"
#include <cassert>

JPetPM::JPetPM() :
  fHVgain(std::make_pair(0.0, 0.0)) // it is possible to initialize pair in header by 
                                    // std::pair<float, float> fHVgain {0.0 , 0.0}; 
                                    // but then there is some error generating dictionary for file
{
  SetName("JPetPM");
}

JPetPM::JPetPM(int id) :
  fID(id),
  fHVgain(std::make_pair(0.0, 0.0))
{
  SetName("JPetPM");
}

JPetPM::JPetPM(Side side, 
         int id, 
         int HVset, 
         int HVopt, 
         std::pair<float, float> HVgainNumber):
  fSide(side),
  fID(id),
  fHVset(HVset),
  fHVopt(HVopt),
  fHVgain(HVgainNumber)
{
  SetName("JPetPM");
}

JPetPM::JPetPM(bool isNull) :
  fHVgain(std::make_pair(0.0, 0.0)),
  fIsNullObject(isNull) 
{
  SetName("JPetPM");
}

JPetPM::~JPetPM()
{
}

bool JPetPM::operator==(const JPetPM& pm) const {
  if( getID() == pm.getID() ){
    assert(getSide()==pm.getSide());
    assert(getHVopt()==pm.getHVopt());
    assert(getHVset()==pm.getHVset());
    return true;
  }
  
  return false;
}

bool JPetPM::operator!=(const JPetPM& pm) const {
  return !(*this==pm);
}


ClassImp(JPetPM);

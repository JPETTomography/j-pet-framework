/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetMatrixSignal.cpp
 */

#include "JPetMatrixSignal/JPetMatrixSignal.h"
#include <vector>

ClassImp(JPetMatrixSignal);

JPetMatrixSignal::JPetMatrixSignal(): fTime(0) {}

JPetMatrixSignal::JPetMatrixSignal(float time): fTime(time) {}

JPetMatrixSignal::~JPetMatrixSignal() {}

/**
 * Constructor with is null setting
 */
JPetMatrixSignal::JPetMatrixSignal(bool isNull): fIsNullObject(isNull) {}

bool JPetMatrixSignal::isNullObject() const
{
  return fIsNullObject;
}

float JPetMatrixSignal::getTime() const
{
  return fTime;
}

void JPetMatrixSignal::setTime(float time)
{
  fTime = time;
}

float JPetMatrixSignal::getTOT() const
{
  double tot = 0.0;
  for(auto element : fRawSignalsMap){
    auto leads = element.second.getPoints(JPetSigCh::Leading, JPetRawSignal::ByThrValue);
    auto trails = element.second.getPoints(JPetSigCh::Trailing, JPetRawSignal::ByThrValue);
    if(leads.size()==trails.size()){
      for(uint i = 0; i<leads.size(); i++){
        tot += trails.at(i).getTime()-leads.at(i).getTime();
      }
    }
  }
  return tot;
}

bool JPetMatrixSignal::addRawSignal(const JPetRawSignal& rawSignal)
{

  int mtxPos = rawSignal.getPM().getMatrixPosition();
  auto search = fRawSignalsMap.find(mtxPos);
  if(search == fRawSignalsMap.end()){
    fRawSignalsMap[mtxPos] = rawSignal;
    return true;
  } else {
    // There is already a signal from this SiPM in this matrix, not adding
    return false;
  }
}

std::map<int, JPetRawSignal> JPetMatrixSignal::getRawSignals() const
{
  return fRawSignalsMap;
}

/**
 * Clear the signals values (set all to zero/null)
 */
void JPetMatrixSignal::Clear(Option_t *)
{
  fTime = 0.0;
}

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
 *  @file JPetRecoSignal.cpp
 */

#include "./JPetRecoSignal.h"

ClassImp(JPetRecoSignal);

JPetRecoSignal::JPetRecoSignal(const int points) :
    fDelay(0), fAmplitude(0), fOffset(0), fCharge(0) {

  if (points > 0) {
    fShape.reserve(points);
  }

}

JPetRecoSignal::~JPetRecoSignal() {
}

void JPetRecoSignal::setShapePoint(double time, double ampl) {
  fShape.push_back(shapePoint(time, ampl));
}

void JPetRecoSignal::sortShapePoints(PointsSortOrder order) {
  std::sort(
      fShape.begin(), fShape.end(),
      (order == ByTime ? compareShapePointsTime : compareShapePointsAmpl));
}

bool JPetRecoSignal::compareShapePointsTime(const shapePoint& A,
                                            const shapePoint& B) {
  if (A.time < B.time) {
    return true;
  }
  return false;
}

bool JPetRecoSignal::compareShapePointsAmpl(const shapePoint& A,
                                            const shapePoint& B) {
  if (A.amplitude < B.amplitude) {
    return true;
  }
  return false;
}

void JPetRecoSignal::setRawSignal(const JPetRawSignal& rawSignal){
   fRawSignal = rawSignal;
   setPM( rawSignal.getPM() );
   setBarrelSlot( rawSignal.getBarrelSlot() );
   setTimeWindowIndex( rawSignal.getTimeWindowIndex() );
}

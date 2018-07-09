/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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

/**
 * Constructor
 *
 * @param points number of (time, amplitude) points in the representation of the
 * signal shape; give only when known (e.g. for scope signals).
 */
JPetRecoSignal::JPetRecoSignal(const int points):
    fDelay(0), fAmplitude(0), fOffset(0), fCharge(0)
{
  if (points > 0) {
    fShape.reserve(points);
  }
}

JPetRecoSignal::~JPetRecoSignal() {}

/**
 * Set one point (i.e. (time, amplitude) pair) in the signal shape.
 *
 * @param time time in [ps]
 * @param ampl aplitude in [mV]
 */
void JPetRecoSignal::setShapePoint(double time, double ampl)
{
  fShape.push_back(shapePoint(time, ampl));
}

/**
 * Sort the vector of shapePoint-s by time (default) or amplitude (always ascending).
 *
 * @param order either JPetRecoSignal::ByTime or JPetRecoSignal::ByAmplitude.
 */
void JPetRecoSignal::sortShapePoints(PointsSortOrder order)
{
  std::sort(fShape.begin(), fShape.end(),
    (order == ByTime ? compareShapePointsTime : compareShapePointsAmpl));
}

/**
 * Private method for comparing shape points by their time.
 */
bool JPetRecoSignal::compareShapePointsTime(
  const shapePoint& A, const shapePoint& B)
{
  if (A.time < B.time) {
    return true;
  }
  return false;
}

/**
 * Private method for comparing shape points by their aplitude.
 */
bool JPetRecoSignal::compareShapePointsAmpl(
  const shapePoint& A, const shapePoint& B) {
  if (A.amplitude < B.amplitude) {
    return true;
  }
  return false;
}

/**
 * Set the JPetRawSignal object from which this RecoSignal was created.
 */
void JPetRecoSignal::setRawSignal(const JPetRawSignal& rawSignal)
{
   fRawSignal = rawSignal;
   setPM( rawSignal.getPM() );
   setBarrelSlot( rawSignal.getBarrelSlot() );
}

/**
 * Reset signal values to zero/null, clear arrays.
 */
void JPetRecoSignal::Clear(Option_t *)
{
  fShape.clear();
  fDelay = 0.;
  fAmplitude = 0.;
  fOffset = 0.;
  fCharge = 0.;
  fRawSignal = JPetRawSignal();
  fRecoTimesAtThreshold.clear();
}

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
 *  @file JPetShapedSignal.cpp
 */

#include "Signals/JPetShapedSignal/JPetShapedSignal.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetShapedSignal);

/**
 * Constructor
 *
 * @param points number of (time, amplitude) points in the representation of the
 * signal shape; give only when known (e.g. for scope signals).
 */
JPetShapedSignal::JPetShapedSignal(const int points) : JPetRecoSignal(), fDelay(0.0), fAmplitude(0.0), fOffset(0.0), fCharge(0.0)
{
  if (points > 0)
  {
    fShape.reserve(points);
  }
}

JPetShapedSignal::~JPetShapedSignal() {}

/**
 * Set one point (i.e. (time, amplitude) pair) in the signal shape.
 *
 * @param time time in [ps]
 * @param ampl aplitude in [mV]
 */
void JPetShapedSignal::setShapePoint(float time, float ampl) { fShape.push_back(shapePoint(time, ampl)); }

/**
 * Sort the vector of shapePoint-s by time (default) or amplitude (always ascending).
 *
 * @param order either JPetShapedSignal::ByTime or JPetShapedSignal::ByAmplitude.
 */
void JPetShapedSignal::sortShapePoints(PointsSortOrder order)
{
  std::sort(fShape.begin(), fShape.end(), (order == ByTime ? compareShapePointsTime : compareShapePointsAmpl));
}

/**
 * Private method for comparing shape points by their time.
 */
bool JPetShapedSignal::compareShapePointsTime(const shapePoint& ptA, const shapePoint& ptB)
{
  if (ptA.time < ptB.time)
  {
    return true;
  }
  return false;
}

/**
 * Private method for comparing shape points by their aplitude.
 */
bool JPetShapedSignal::compareShapePointsAmpl(const shapePoint& ptA, const shapePoint& ptB)
{
  if (ptA.amplitude < ptB.amplitude)
  {
    return true;
  }
  return false;
}

const JPetPM& JPetShapedSignal::getPM() const
{
  if (fPM.GetObject())
  {
    return static_cast<JPetPM&>(*(fPM.GetObject()));
  }
  else
  {
    ERROR("No JPetPM set, null object will be returned");
    return JPetPM::getDummyResult();
  }
}

void JPetShapedSignal::setPM(const JPetPM& pm) { fPM = const_cast<JPetPM*>(&pm); }

/**
 * Reset signal values to zero/null, clear arrays.
 */
void JPetShapedSignal::Clear(Option_t*)
{
  fShape.clear();
  fDelay = 0.0;
  fAmplitude = 0.0;
  fOffset = 0.0;
  fCharge = 0.0;
  JPetRecoSignal::Clear("");
  fRecoTimesAtThreshold.clear();
}

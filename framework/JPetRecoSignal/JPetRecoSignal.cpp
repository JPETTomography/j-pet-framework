/**
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 *  @file JPetRecoSignal.cpp
 *  @author Aleksander Gajos, alek.gajos@gmail.com
 */

#include "./JPetRecoSignal.h"

ClassImp(JPetRecoSignal);

JPetRecoSignal::JPetRecoSignal(const int points) :
    fAmplitude(0), fCharge(0), fDelay(0), fOffset(0) {

  SetNameTitle("JPetRecoSignal", "Working signal structure for reconstruction");

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
   setTSlotIndex( rawSignal.getTSlotIndex() );
}

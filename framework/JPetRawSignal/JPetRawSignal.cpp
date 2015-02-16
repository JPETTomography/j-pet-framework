/**
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 *  @file JPetRawSignal.cpp
 *  @author Aleksander Gajos, alek.gajos@gmail.com
 */
#include "./JPetRawSignal.h"

ClassImp(JPetRawSignal);

JPetRawSignal::JPetRawSignal(const int points){

  SetNameTitle("JPetRawSignal", "Raw signal (from Front-End electronics) structure");

  fLeadingPoints.reserve(points);
  fTrailingPoints.reserve(points);

}

JPetRawSignal::~JPetRawSignal() {
}

int JPetRawSignal::getNPoints(JPetSigCh::EdgeType edge) const {
  if (edge == JPetSigCh::Trailing) {
    return fTrailingPoints.size();
  } else if (edge == JPetSigCh::Leading) {
    return fLeadingPoints.size();
  }
  return 0;
}

void JPetRawSignal::addPoint(const JPetSigCh& sigch) {

  if (sigch.getType() == JPetSigCh::Trailing) {
    fTrailingPoints.push_back(sigch);
  } else if (sigch.getType() == JPetSigCh::Leading) {
    fLeadingPoints.push_back(sigch);
  } else if (sigch.getType() == JPetSigCh::Charge) {
    fTOTPoint = sigch;
  }
}

std::vector<JPetSigCh> JPetRawSignal::getPoints(
    JPetSigCh::EdgeType edge, JPetRawSignal::PointsSortOrder order) const {

  std::vector<JPetSigCh> sorted = (edge==JPetSigCh::Trailing ? fTrailingPoints : fLeadingPoints);

  if ( order == JPetRawSignal::ByThrNum ){
    std::sort(sorted.begin(), sorted.end(), JPetSigCh::compareByThresholdNumber);
  }else{
    std::sort(sorted.begin(), sorted.end(), JPetSigCh::compareByThresholdValue);
  }

  return sorted;
}


const JPetSigCh& JPetRawSignal::getTOTPoint() const {
  return fTOTPoint;
}

void JPetRawSignal::setTOTPoint(const JPetSigCh & totSigCh) {
  if (totSigCh.getType() == JPetSigCh::Charge) {
    fTOTPoint = totSigCh;
  }
}

std::map<int, double> JPetRawSignal::getTimesVsThresholdNumber(JPetSigCh::EdgeType edge) const {
  std::map<int, double> map;
  const std::vector<JPetSigCh> & vec = (edge==JPetSigCh::Trailing ? fTrailingPoints : fLeadingPoints);

  for( std::vector<JPetSigCh>::const_iterator it = vec.begin(); it!=vec.end(); ++it){
     map[ it->getThresholdNumber() ] = it->getValue();
  }
  return map;
}

std::map<int, double> JPetRawSignal::getTimesVsThresholdValue(JPetSigCh::EdgeType edge) const {
  std::map<int, double> map;

  const std::vector<JPetSigCh> & vec = (edge==JPetSigCh::Trailing ? fTrailingPoints : fLeadingPoints);

  for( std::vector<JPetSigCh>::const_iterator it = vec.begin(); it!=vec.end(); ++it){
    map[ it->getThreshold() ] = it->getValue();
  }
  return map;
}

double JPetRawSignal::getTOT() const {
  return fTOTPoint.getValue();
}

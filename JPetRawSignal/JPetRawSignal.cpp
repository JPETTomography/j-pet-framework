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
 *  @file JPetRawSignal.cpp
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

int JPetRawSignal::getNumberOfPoints(JPetSigCh::EdgeType edge) const {
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


/* const JPetSigCh& JPetRawSignal::getTOTPoint() const { */
/*   return fTOTPoint; */
/* } */

/* void JPetRawSignal::setTOTPoint(const JPetSigCh & totSigCh) { */
/*   if (totSigCh.getType() == JPetSigCh::Charge) { */
/*     fTOTPoint = totSigCh; */
/*   } */
/* } */

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

std::map<int, double> JPetRawSignal::getTOTsVsThresholdNumber() const {

  std::map<int, double> map;
  
  for( std::vector<JPetSigCh>::const_iterator it1 = fLeadingPoints.begin(); it1!=fLeadingPoints.end(); ++it1){
    for( std::vector<JPetSigCh>::const_iterator it2 = fTrailingPoints.begin(); it2!=fTrailingPoints.end(); ++it2){
      if( it1->getThresholdNumber() == it2->getThresholdNumber() ){
	map[ it1->getThresholdNumber() ] = it2->getValue() - it1->getValue();	
      }
    }
  }
  return map;
}

std::map<int, double> JPetRawSignal::getTOTsVsThresholdValue() const {
  std::map<int, double> map;

  for( std::vector<JPetSigCh>::const_iterator it1 = fLeadingPoints.begin(); it1!=fLeadingPoints.end(); ++it1){
    for( std::vector<JPetSigCh>::const_iterator it2 = fTrailingPoints.begin(); it2!=fTrailingPoints.end(); ++it2){
      if( it1->getThreshold() == it2->getThreshold() ){
	map[ it1->getThreshold() ] = it2->getValue() - it1->getValue();	
      }
    }
  }

  return map;
}


/* double JPetRawSignal::getTOT() const { */
/*   return fTOTPoint.getValue(); */
/* } */

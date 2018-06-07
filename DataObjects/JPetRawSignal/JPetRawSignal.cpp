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
 *  @file JPetRawSignal.cpp
 */

#include "./JPetRawSignal.h"

ClassImp(JPetRawSignal);

/**
 * @brief Constructor
 *
 * @param Maximal number of points probed at one edge of the signal (defalult = 4)
 */
JPetRawSignal::JPetRawSignal(const int points)
{
  fLeadingPoints.reserve(points);
  fTrailingPoints.reserve(points);
}

/**
 * Destructor
 */
JPetRawSignal::~JPetRawSignal() {}

/**
 * @brief Returns the number of points recorded on a leading or trailing edge of this signal.
 *
 * The number of points should be between 0 and the number set in the class constructor
 * (default=4) depending on whether time signals from all threshold were recorded or not.
 *
 * @param Edge enum: JPetSigCh::Leading or JPetSigCh::Trailing
 */
int JPetRawSignal::getNumberOfPoints(JPetSigCh::EdgeType edge) const
{
  if (edge == JPetSigCh::Trailing) {
    return fTrailingPoints.size();
  } else if (edge == JPetSigCh::Leading) {
    return fLeadingPoints.size();
  }
  return 0;
}

/**
 * @brief Add a JPetSigCh object to the signal.
 *
 * The JPetSigCh object is automatically added to the array of trailing-edge
 * or leading-edge points, depending on the type which was set in it.
 */
void JPetRawSignal::addPoint(const JPetSigCh& sigch)
{
  if (sigch.getType() == JPetSigCh::Trailing) {
    fTrailingPoints.push_back(sigch);
  } else if (sigch.getType() == JPetSigCh::Leading) {
    fLeadingPoints.push_back(sigch);
  }
}

/**
 * @brief Returns a sorted vector of trailing-edge or leading-edge points of this signal.
 *
 * Returns the vector of Signal Channels that occupy leading or trailing edge.
 * Order fo the points in the vector is indicated by an argumet:
 * - threshold values - sort by time value of Signal Channels, that occupy thresholds
 * - threshold number - ascending order of threshol numbers. The thresholds
 * are numbered from 1 to 4 in the usual case.
 * The dafault method of sorting is by threshold values
 *
 * @param Edge enum: JPetSigCh::Leading or JPetSigCh::Trailing
 * @param Sort method: JPetRawSignal::byThrValue or JPetRawSignal::byThrNum
 */
std::vector<JPetSigCh> JPetRawSignal::getPoints(
    JPetSigCh::EdgeType edge,
    JPetRawSignal::PointsSortOrder order) const
{
  std::vector<JPetSigCh> sorted = (edge==JPetSigCh::Trailing ? fTrailingPoints : fLeadingPoints);
  if ( order == JPetRawSignal::ByThrNum ){
    std::sort(sorted.begin(), sorted.end(), JPetSigCh::compareByThresholdNumber);
  } else {
    std::sort(sorted.begin(), sorted.end(), JPetSigCh::compareByThresholdValue);
  }
  return sorted;
}

/**
 * @brief Get a map with (threshold number, time [ps]) pairs.
 */
std::map<int, double> JPetRawSignal::getTimesVsThresholdNumber(JPetSigCh::EdgeType edge) const
{
  std::map<int, double> thrToTime;
  const std::vector<JPetSigCh> & vec = (edge==JPetSigCh::Trailing ? fTrailingPoints : fLeadingPoints);
  for( std::vector<JPetSigCh>::const_iterator it = vec.begin(); it!=vec.end(); ++it) {
     thrToTime[ it->getThresholdNumber() ] = it->getValue();
  }
  return thrToTime;
}

/**
 * @brief Get a map with (threshold value [mV], time [ps]) pairs.
 */
std::map<int, std::pair<float, float> > JPetRawSignal::getTimesVsThresholdValue(JPetSigCh::EdgeType edge) const
{
  std::map<int, std::pair<float, float> > thrToTime;
  const std::vector<JPetSigCh> & vec = (edge==JPetSigCh::Trailing ? fTrailingPoints : fLeadingPoints);
  for(std::vector<JPetSigCh>::const_iterator it = vec.begin(); it!=vec.end(); ++it) {
    thrToTime[it->getThresholdNumber()] = std::make_pair(it->getThreshold(), it->getValue());
  }
  return thrToTime;
}

/**
 * @brief Get a map with (threshold value [mV], TOT [ps]) pairs.
 */
std::map<int, double> JPetRawSignal::getTOTsVsThresholdNumber() const
{
  std::map<int, double> thrToTOT;
  for(std::vector<JPetSigCh>::const_iterator it1 = fLeadingPoints.begin(); it1!=fLeadingPoints.end(); ++it1){
    for(std::vector<JPetSigCh>::const_iterator it2 = fTrailingPoints.begin(); it2!=fTrailingPoints.end(); ++it2){
      if(it1->getThresholdNumber() == it2->getThresholdNumber()){
        thrToTOT[it1->getThresholdNumber()] = it2->getValue() - it1->getValue();
      }
    }
  }
  return thrToTOT;
}

/**
 * @brief Get a map with (threshold number, TOT [ps]) pairs.
 */
std::map<int, double> JPetRawSignal::getTOTsVsThresholdValue() const
{
  std::map<int, double> thrToTOT;
  for(std::vector<JPetSigCh>::const_iterator it1 = fLeadingPoints.begin(); it1!=fLeadingPoints.end(); ++it1){
    for(std::vector<JPetSigCh>::const_iterator it2 = fTrailingPoints.begin(); it2!=fTrailingPoints.end(); ++it2){
      if(it1->getThreshold() == it2->getThreshold()){
        thrToTOT[ it1->getThreshold() ] = it2->getValue() - it1->getValue();
      }
    }
  }
  return thrToTOT;
}

void JPetRawSignal::Clear(Option_t *)
{
  fLeadingPoints.clear();
  fTrailingPoints.clear();
}

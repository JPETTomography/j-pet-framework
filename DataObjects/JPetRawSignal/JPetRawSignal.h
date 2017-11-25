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
 *  @file JPetRawSignal.h
 */

#ifndef JPETRAWSIGNAL_H
#define JPETRAWSIGNAL_H

#include "./JPetSigCh/JPetSigCh.h"
#include "./JPetBaseSignal/JPetBaseSignal.h"
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

/**
 * @brief Data class representing a raw signal from a single photomultiplier as acquired by Front-End Electronics
 *
 * The signal consists of two arrays of time values (JPetSigCh objects) - points probed on the leading and trailing edge.
 */
class JPetRawSignal: public JPetBaseSignal
{
public:

  enum PointsSortOrder
  {
    ByThrValue, ///< Sort by threshold value
    ByThrNum ///< Sort by threshold number
  };

  /**
   * @brief Constructor
   *
   * @param points maximal number of points probed at one edge of the signal (defalult = 4)
   */
  JPetRawSignal(const int points = 4);
  virtual ~JPetRawSignal();

  /**
   * @brief Returns the number of points recorded on a leading or trailing edge of this signal.
   *
   * The number of points should be between 0 and the number set in the class constructor (default=4)
   * depending on whether time signals from all threshold were recorded or not.
   *
   * @param edge Either JPetSigCh::Leading or JPetSigCh::Trailing
   */
  int getNumberOfPoints(JPetSigCh::EdgeType edge) const;

  /**
   * @brief Add a JPetSigCh object to the signal.
   *
   * The JPetSigCh object is automatically added to the array
   * of trailing-edge or leading-edge points depending
   * on the type which was set in it. 
   */
  void addPoint(const JPetSigCh& sigch);

  /**
   * @brief Returns a sorted vector of trailing-edge or leading-edge points of this signal.
   *
   * @param edge Either JPetSigCh::Leading or JPetSigCh::Trailing
   * @param sort_by JPetRawSignal::byThrValue or JPetRawSignal::byThrNum
   *
   * The vector of points will be sorted according to the specified order - by threshold values  (default) or by threshold numbers
   *
   */
  std::vector<JPetSigCh> getPoints(JPetSigCh::EdgeType edge,
                                   JPetRawSignal::PointsSortOrder order =
                                       JPetRawSignal::ByThrValue) const;

  /**
   * @brief Get a map with (threshold number, time [ps]) pairs.
   */
  std::map<int, double> getTimesVsThresholdNumber(JPetSigCh::EdgeType edge) const;

  /**
   * @brief Get a map with (threshold value [mV], time [ps]) pairs.
   */
  std::map<int, std::pair<float, float> > getTimesVsThresholdValue(JPetSigCh::EdgeType edge) const;

  /**
   * @brief Get a map with (threshold value [mV], TOT [ps]) pairs.
   */
  std::map<int, double> getTOTsVsThresholdValue() const;
  
  /**
   * @brief Get a map with (threshold number, TOT [ps]) pairs.
   */
  std::map<int, double> getTOTsVsThresholdNumber() const;

  void Clear(Option_t * opt = "");
  
private:
  std::vector<JPetSigCh> fLeadingPoints; ///< vector of JPetSigCh objects from leading edge of the signal
  std::vector<JPetSigCh> fTrailingPoints; ///< vector of JPetSigCh objects from trailing edge of the signal

  ClassDef(JPetRawSignal, 5)
  ;
};
#endif /*  !JPETRAWSIGNAL_H */

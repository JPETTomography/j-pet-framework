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
 *  @file JPetRawSignal.h
 */

#ifndef JPETRAWSIGNAL_H
#define JPETRAWSIGNAL_H

#include "./JPetBaseSignal/JPetBaseSignal.h"
#include "./JPetSigCh/JPetSigCh.h"
#include <algorithm>
#include <utility>
#include <vector>
#include <map>

/**
 * @brief Data class representing a raw signal from a single photomultiplier
 *
 * The signal consists of two arrays of JPetSigCh objects - time value points
 * probed on the leading and trailing edge.
 */
class JPetRawSignal: public JPetBaseSignal
{
public:
  enum PointsSortOrder
  {
    ByThrValue,
    ByThrNum
  };

  JPetRawSignal(const int points = 4);
  virtual ~JPetRawSignal();
  int getNumberOfPoints(JPetSigCh::EdgeType edge) const;
  void addPoint(const JPetSigCh& sigch);
  std::vector<JPetSigCh> getPoints(JPetSigCh::EdgeType edge,
    JPetRawSignal::PointsSortOrder order = JPetRawSignal::ByThrValue) const;
  std::map<int, double> getTimesVsThresholdNumber(JPetSigCh::EdgeType edge) const;
  std::map<int, std::pair<float, float>> getTimesVsThresholdValue(JPetSigCh::EdgeType edge) const;
  std::map<int, double> getTOTsVsThresholdValue() const;
  std::map<int, double> getTOTsVsThresholdNumber() const;

  void Clear(Option_t * opt = "");

private:
  std::vector<JPetSigCh> fLeadingPoints;
  std::vector<JPetSigCh> fTrailingPoints;

  ClassDef(JPetRawSignal, 5);
};

#endif /* !JPETRAWSIGNAL_H */

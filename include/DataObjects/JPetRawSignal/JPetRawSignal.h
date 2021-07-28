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
 *  @file JPetRawSignal.h
 */

#ifndef JPETRAWSIGNAL_H
#define JPETRAWSIGNAL_H

#include "JPetChannelSignal/JPetChannelSignal.h"
#include "JPetRecoSignal/JPetRecoSignal.h"
#include <map>
#include <vector>
// #include <utility>
// #include <algorithm>

/**
 * @brief Data class representing a raw signal from a single photomultiplier
 *
 * The signal consists of two arrays of JPetSigCh objects - time value points
 * probed on the leading and trailing edge.
 */
class JPetRawSignal : public JPetRecoSignal
{
public:
  enum PointsSortOrder
  {
    ByThrValue,
    ByThrNum
  };

  JPetRawSignal(const int points = 4);
  virtual ~JPetRawSignal();
  int getNumberOfPoints(JPetChannelSignal::EdgeType edge) const;
  void addPoint(const JPetChannelSignal& channelSignal);
  std::vector<JPetChannelSignal> getPoints(JPetSigCh::EdgeType edge, JPetRawSignal::PointsSortOrder order = JPetRawSignal::ByThrValue) const;
  std::map<int, double> getTimesVsThresholdNumber(JPetChannelSignal::EdgeType edge) const;
  std::map<int, std::pair<double, double>> getTimesVsThresholdValue(JPetSigCh::EdgeType edge) const;
  std::map<int, double> getTOTsVsThresholdValue() const;
  std::map<int, double> getTOTsVsThresholdNumber() const;
  void Clear(Option_t*) override;

private:
  std::vector<JPetChannelSignal> fLeadingPoints;
  std::vector<JPetChannelSignal> fTrailingPoints;

  ClassDef(JPetRawSignal, 8);
};

#endif /* !JPETRAWSIGNAL_H */

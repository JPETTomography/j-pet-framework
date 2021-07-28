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
 *  @file JPetPMSignal.h
 */

#ifndef JPETPMSIGNAL_H
#define JPETPMSIGNAL_H

#include "JPetChannelSignal/JPetChannelSignal.h"
#include "JPetRecoSignal/JPetRecoSignal.h"
#include <map>
#include <vector>

/**
 * @brief Data class representing a signal from a single photomultiplier
 *
 * The signal consists of two arrays of JPetChannelSignal objects -
 * points probed on the leading and trailing edge.
 */
class JPetPMSignal : public JPetRecoSignal
{
public:
  enum PointsSortOrder
  {
    ByThrValue,
    ByThrNum
  };

  JPetPMSignal(const int points = 4);
  virtual ~JPetPMSignal();
  int getNumberOfPoints(JPetChannelSignal::EdgeType edge) const;
  void addLeadTrail(const JPetChannelSignal& lead, const JPetChannelSignal& trail);
  std::vector<JPetChannelSignal> getPairs(JPetPMSignal::PointsSortOrder order = JPetPMSignal::ByThrValue) const;
  std::map<int, double> getTOTsVsThresholdNumber() const;
  std::map<double, double> getTOTsVsThresholdValue() const;

  void Clear(Option_t*) override;

private:
  std::vector<std::pair<JPetChannelSignal, JPetChannelSignal>> fLeadTrailPairs;

  ClassDef(JPetPMSignal, 1);
};

#endif /* !JPETPMSIGNAL_H */

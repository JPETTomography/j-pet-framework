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
 *  @file JPetPMSignal.cpp
 */

#include "Signals/JPetPMSignal/JPetPMSignal.h"
#include "JPetLoggerInclude.h"

using namespace std;

ClassImp(JPetPMSignal);

JPetPMSignal::JPetPMSignal(const int points) { fLeadTrailPairs.reserve(points); }

JPetPMSignal::~JPetPMSignal() {}

bool JPetPMSignal::addLeadTrailPair(const JPetChannelSignal& lead, const JPetChannelSignal& trail)
{
  // Validating edge types
  if (lead.getEdgeType() != JPetChannelSignal::Leading)
  {
    ERROR("Cannot add as a Lead a Channel signal with edge type different than JPetChannelSignal::Leading");
    return false;
  }

  if (trail.getEdgeType() != JPetChannelSignal::Trailing)
  {
    ERROR("Cannot add as a Trail a Channel signal with edge type different than JPetChannelSignal::Trailing");
    return false;
  }

  // Validating same thresholds
  if (lead.getChannel().getThresholdNumber() != trail.getChannel().getThresholdNumber())
  {
    ERROR("Cannot add a pair of Channel signals from different threholds.");
    return false;
  }

  // Validating time ordering
  if (lead.getTime() < trail.getTime())
  {
    ERROR("Failed attemp of adding to a PM signal a pair of Channel signals where Lead edge comes after Trail edge.");
    return false;
  }

  fLeadTrailPairs.push_back(make_pair(lead, trail));
  return true;
}

void JPetPMSignal::setToT(double tot) { fToT = tot; }

void JPetPMSignal::setPM(const JPetPM& pm) { fPM = const_cast<JPetPM*>(&pm); }

vector<pair<JPetChannelSignal, JPetChannelSignal>> JPetPMSignal::getLeadTrailPairs(JPetPMSignal::PointsSortOrder order) const
{
  vector<pair<JPetChannelSignal, JPetChannelSignal>> sorted = fLeadTrailPairs;
  if (order == JPetPMSignal::ByThrNum)
  {
    sort(sorted.begin(), sorted.end(), JPetChannelSignal::compareByThresholdNumber);
  }
  else
  {
    sort(sorted.begin(), sorted.end(), JPetChannelSignal::compareByThresholdValue);
  }
  return sorted;
}

double JPetPMSignal::getToT() const { return fToT; }

const JPetPM& JPetPMSignal::getPM() const
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

void JPetPMSignal::Clear(Option_t*)
{
  JPetRecoSignal::Clear("");
  fLeadTrailPairs.clear();
  fToT = 0.0;
  fPM = nullptr;
}

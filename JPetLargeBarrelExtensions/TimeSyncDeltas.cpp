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
 *  @file TimeSyncDeltas.cpp
 */

#include "TimeSyncDeltas.h"
using namespace std;

Synchronization::Synchronization(const shared_ptr < JPetGeomMappingInterface > map, istream& str, const Synchronization::TimeCalculation timecalc)
  : f_mapping(map), f_time_calc(timecalc)
{
  f_offsets = make_shared<JPetMap<SynchroStrip>>(f_mapping->getLayersSizes());
  str >> (*f_offsets);
}
Synchronization::~Synchronization() {}
const SynchroStrip Synchronization::get_times(const JPetHit& hit) const
{
  const auto& offsets = f_offsets->operator[](f_mapping->getStripPos(hit.getBarrelSlot()));
  map<int, double> lead_times_A = hit.getSignalA().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
  map<int, double> lead_times_B = hit.getSignalB().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
  vector<double> A, B;
  for (size_t thr = 1; thr <= 4; thr++) {
    A.push_back(lead_times_A[thr]);
    B.push_back(lead_times_B[thr]);
  }
  SynchroStrip res;
  res.A = f_time_calc(A) + offsets.A;
  res.B = f_time_calc(B) + offsets.B;
  return res;
}

const Synchronization::TimeCalculation Thr(const std::list<size_t>& lst)
{
  return [lst](const vector<double>& P)->const double {
    double res = 0;
    for (const size_t i : lst)res += P[i];
    res /= lst.size();
    return res;
  };
}


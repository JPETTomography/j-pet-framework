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
 *  @file TimeSyncDeltas.h
 */

#ifndef _________DELTAS_H_______
#define _________DELTAS_H_______
#include "./JPetHit/JPetHit.h"
#include "BarrelExtensions.h"
#include <functional>
#include "PetDict.h"
#include <iostream>
#include <memory>
#include <list>

struct SynchroStrip {
  double A, B, dA, dB;
};

inline std::istream& operator>>(std::istream& str, SynchroStrip& item)
{
  return str >> item.A >> item.dA >> item.B >> item.dB;
}

inline std::ostream& operator<<(std::ostream& str, const SynchroStrip& item)
{
  return str << item.A << " " << item.dA << "\t" << item.B << " " << item.dB;
}

/**
 * @brief Adding deltas obtained from time synchronization
 *
 * This class provides adding deltas obtained after time synchronization
 * and can work with different algorithms of signal time calculation.
 * It is considered that deltas are stored in text file, but the constructor
 * accepts any std::istream instance and reads data from it. The stream must be
 * opened correctly before calling the constructor and it should be closed after
 * the constructor call by user in case if it is a text file.
 */
class Synchronization
{
public:
  typedef std::function<double(const std::vector<double>&)> TimeCalculation;
  Synchronization(const std::shared_ptr<JPetGeomMappingInterface>map, std::istream& str, const TimeCalculation timecalc);
  virtual ~Synchronization();
  const SynchroStrip get_times(const JPetHit& hit)const;
private:
  std::shared_ptr<JPetGeomMappingInterface> f_mapping;
  std::shared_ptr<JPetMap<SynchroStrip>> f_offsets;
  TimeCalculation f_time_calc;
};

const Synchronization::TimeCalculation Thr(const std::list<size_t>& lst);

#endif

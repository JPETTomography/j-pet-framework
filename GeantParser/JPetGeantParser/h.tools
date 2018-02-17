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
 *  @file MCHitTranslatorTools.h
 */

#ifndef HITFINDERTOOLS_H
#define HITFINDERTOOLS_H

#include <JPetMCHit/JPetMCHit.h>
#include <JPetStatistics/JPetStatistics.h>

#include <vector>

class MCHitTranslatorTools
{
public:
    std::vector<JPetMCHit> createHits();
    JPetMCHit createHit();
//  typedef std::map<int, std::pair<std::vector<JPetPhysSignal>, std::vector<JPetPhysSignal>>> SignalsContainer;
//  typedef std::map<int, std::pair<double, double>> VelocityMap;
//
//  /**
//  * Map od all signals within a single DAQ time window.
//  * For each scintillator with at least one signal this container stores two vectors
//  * one for physical signals on photomultiplier on side A and second for signals on side B. Then
//  * for each signal on side A it searches for corresponding signal on side B - that is time difference of arrival
//  * of those two signals needs to be less then specified time difference (kTimeWindowWidth)
//  *
//  */
//  std::vector<JPetHit> createHits(
//    JPetStatistics& statistics,
//    const SignalsContainer& allSignalsInTimeWindow,
//    const double timeDifferenceWindow,
//    const VelocityMap& velMap);
//
//  void addIfReferenceSignal(std::vector<JPetHit>& hits, const std::vector<JPetPhysSignal>& sideA, const std::vector<JPetPhysSignal>& sideB, const VelocityMap& velMap);
//  void sortByTime(std::vector<JPetPhysSignal>& side);
//  void setHitXYPosition(JPetHit& hit);
//  void setHitZPosition(JPetHit& hit, const VelocityMap& velMap);
//  JPetHit createHit(const JPetPhysSignal& signalA, const JPetPhysSignal& signalB, const VelocityMap& velMap);
//  JPetHit createDummyRefDefHit(const JPetPhysSignal& signalB, const VelocityMap& velMap);
//  bool checkIsDegreeOrRad(const std::vector<JPetHit>& hits);
};

#endif 

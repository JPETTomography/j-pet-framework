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
 *  @file JPetRecoSignalTools.h
 *  @brief calculates offset for JPetRecoSignal by mean of noise points
 *  S. Niedzwiecki version of the algorithm
 */

#ifndef JPETRECOSIGNALTOOLS_H
#define JPETRECOSIGNALTOOLS_H

#include "../../JPetRecoSignal/JPetRecoSignal.h"
#include <vector>
#include <string>

#include <TH1F.h>
#include <TGraph.h>

namespace JPetRecoSignalTools
{
  enum ERRORS { badOffset, 
                badIndexAtMinimumSignal, 
                badIndexAtValue, 
                badCharge, 
                badStartingIndex, 
                badIndexAtMinimumValue, 
                badTimeAtThr, 
                badAmplitude};

   double calculateOffset(const JPetRecoSignal& signal);
   double calculateAmplitude(const JPetRecoSignal& signal);
   double calculateArea(const JPetRecoSignal& signal);
   double calculateTimeAtThreshold(const JPetRecoSignal& signal, const double threshold);
   TGraph* plotJPetRecoSignal(const JPetRecoSignal& signal);
   void saveTH1FsToRootFile(std::vector<TH1F*> histoCollection, std::string fileName, std::string pdfName);
   double calculateAreaFromStartingIndex(const JPetRecoSignal& signal);
   void savePNGOfBadSignal(const JPetRecoSignal& signal, int numberOfBadSignals);
   void saveBadSignalIntoRootFile(const JPetRecoSignal& signal, const int numberOfBadSignals, const std::string fileName);
   void savePNGwithMarkedOffsetsAndStartingPoints(const JPetRecoSignal& signal, int number);
   double min(const std::vector<double>& vector);
   double max(const std::vector<double>& vector);

   double calculateArithmeticMean(const std::vector<double>& vector);
   int findStartingIndex(const JPetRecoSignal& signal);
   int findIndexOfMaxHisto(std::vector<TH1F*> histoCollection);
   double pktPrzecieciaOX(double x1, double y1, double x2, double y2);
   double absolute(const double number);
   int findIndexAtValue(double value, std::vector<double>& vector);
   double calculateArithmeticMean(const std::vector<double>& vector, const int upToIndex);
   double calculateStandardDeviation(const std::vector<double>& vector, const int upToIndex);
   std::vector<double> copyVectorWithNumbersUpToIndex(std::vector<double>& vector, int index);
   bool isPointFromRecoSignalInNoise(const double noiseMean, const double noiseDeviation, const double point);
   double calculateConstantThreshold(const JPetRecoSignal& signal, const double threshold);
   double calculateConstantFraction(const JPetRecoSignal& signal, const double threshold);
}

#endif // JPETRECOSIGNALTOOLS_H

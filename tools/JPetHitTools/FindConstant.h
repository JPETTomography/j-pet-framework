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
 *  @file FindConstant.h
 */

#ifndef FINDCONSTANT_H
#define FINDCONSTANT_H

#include "../../JPetLoggerInclude.h"
#include <vector>
#include <TString.h>
#include <TF1.h>
#include <TH1F.h>

class FindConstant
{
 public:
  FindConstant(const std::vector<double>& inputEvents, const TString file, const double sourcePos, const int scinID);
  double execute();
  double returnEnergyResolution();

 private:
  void drawChi2AndFitPol2(const std::vector<double>& res, const std::vector<double>& chi2);
  void aproximateParameters();
  void saveFitResultToTxt(std::string name);
  void produceSIMEvents(std::vector<double>& SIMEvents, const double eRes);
  void fillSIMHisto(const double normalisation = 1.0, const double alpha = 1.0);
  void fillEXPHisto(const double normalisation = 1.0, const double alpha = 1.0);
  double compareHistogramsByChi2(const double normalisation, const double alpha);
  void saveFittedHisto();
  void saveSIMHisto();
  void saveEXPHisto();
  void performFit();
  bool isDir(std::string& path);
  double estimateWidthRatio();
  double estimateHeightRatio();

  TString fileName;
  TF1* quadraticFit;
  double initialHeightRatio, initialWidthRatio, heighestCountsInSIM, heighestCountsInEXP;
  std::vector<double> SIMEvents, EXPEvents;
  unsigned int numberOfBins;
  int scintillatorID, binNumber;
  TH1F* EXPHisto;
  TH1F* SIMHisto;
  std::string expHistoTitle;
  double normalisation, alpha, energyResolution, sourcePosition;
  int maxBin, minBin;
  double bestChi2, bestNorm, bestAlpha, bestNumberOfBins;
  TString filePath;
  std::vector<double> alphasForStripes;
  double upperCut, lowerCut;
};
#endif


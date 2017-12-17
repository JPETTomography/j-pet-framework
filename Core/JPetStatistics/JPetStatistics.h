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
 *  @file JPetStatistics.h
 */

#ifndef _JPET_STATISTICS_H_
#define _JPET_STATISTICS_H_

#include <THashTable.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <map>
#include <TGraph.h>
#include <TCanvas.h>

/**
 * @brief An class for storing statistics of the processing (e.g histograms and counters) during execution of a JPetTask
 *
 */

class JPetStatistics: public TObject
{

public:
  JPetStatistics() {}
  JPetStatistics(const JPetStatistics& copy);
  ~JPetStatistics();
  void createHistogram(TObject* object);
  void createGraph(TObject* object);
  void createCanvas(TObject* object);
  TH1F& getHisto1D(const char* name);
  TH2F& getHisto2D(const char* name);
  TGraph& getGraph(const char* name);
  TCanvas& getCanvas(const char* name);
  void createCounter(const char* name);
  double& getCounter(const char* name);

  template <typename T>
  T& getHisto(const char* name)
  {
    TObject* tmp = fStats.FindObject(name);
    if (tmp == null)
      ERROR("getHisto of " + name + " returned nullptr");
    return dynamic_cast<T&>(*(tmp));
  }

  const THashTable* getStatsTable() const;

  ClassDef(JPetStatistics, 4);

protected:
  THashTable fStats;
  std::map<TString, double> fCounters;

};

#endif

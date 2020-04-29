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
 *  @file JPetStatistics.h
 */

#ifndef _JPET_STATISTICS_H_
#define _JPET_STATISTICS_H_

#include "JPetLoggerInclude.h"
#include <THashTable.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TString.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TClass.h>
#include <TEfficiency.h>
#include <string>
#include <map>
#include <set>

class doubleCheck
{
public:
  bool isChanged = false;
  double value = 0.;
  doubleCheck(){}
  doubleCheck(double newValue) {value=newValue; isChanged=true;}
};

/**
 * @brief Cointainer class for processing statistics
 *
 * A class for storing statistics of the processing during the execution of a JPetTask.
 * Available for storing Graphs, Canvases and 1D, 2D Histograms,
 */

class JPetStatistics: public TObject
{
public:
    
  enum AxisLabel
  {
    xAxis,
    yAxis,
    zAxis,
  };

  JPetStatistics();
  JPetStatistics(const JPetStatistics& old);
  ~JPetStatistics();
  void createObject(TObject* object);
  void createHistogram(TObject* object);
  void createHistogramWithAxes(TObject* object, TString xAxisName="Default X axis title [unit]",
                               TString yAxisName="Default Y axis title [unit]", TString zAxisName="Default Z axis title [unit]");
  void setHistogramBinLabel(const char* name, AxisLabel axis, std::vector<std::pair<unsigned, std::string>> binLabels);
  void createGraph(TObject* object);
  void createCanvas(TObject* object);
  void fillHistogram(const char* name, double xValue, doubleCheck yValue=doubleCheck(), doubleCheck zValue=doubleCheck());
  TEfficiency* getEffiHisto(const char* name);
  TH1F* getHisto1D(const char* name);
  TH2F* getHisto2D(const char* name);
  TH3F* getHisto3D(const char* name);
  TGraph* getGraph(const char* name);
  TCanvas* getCanvas(const char* name);
  void createCounter(const char* name);
  double& getCounter(const char* name);
  void writeError(const char* nameOfHistogram, const char* messageEnd );

  template <typename T>
  T* getObject(const char* name)
  {
    TObject* tmp = fStats.FindObject(name);
    if (!tmp) {
      ERROR("getObject of " + std::string(name) + " returned nullptr");
      return nullptr;
    }
    return dynamic_cast<T*>(tmp);
  }

  const THashTable* getStatsTable() const;
  ClassDef(JPetStatistics, 5);

protected:
  THashTable fStats;
  std::map<TString, double> fCounters;
};
#endif /* !_JPET_STATISTICS_H_ */

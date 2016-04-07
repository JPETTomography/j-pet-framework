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
 *  @file JPetStatustics.cpp
 */

#include "JPetStatistics.h"

ClassImp(JPetStatistics);

void JPetStatistics::createHistogram(TObject * object){
  fHistos.Add(object);
}

void JPetStatistics::createGraph(TObject * object){
  fGraphs.Add(object);
}

void JPetStatistics::createCanvas(TObject * object){
  fCanvas.Add(object);
}

TH1F & JPetStatistics::getHisto1D(const char * name){
  return dynamic_cast<TH1F&>(*(fHistos.FindObject(name)));
}

TH2F & JPetStatistics::getHisto2D(const char * name){
  return dynamic_cast<TH2F&>(*(fHistos.FindObject(name)));
}

TGraph & JPetStatistics::getGraph(const char * name){
  return dynamic_cast<TGraph&>(*(fGraphs.FindObject(name)));
}

TCanvas & JPetStatistics::getCanvas(const char * name){
  return dynamic_cast<TCanvas&>(*(fCanvas.FindObject(name)));
}

void JPetStatistics::createCounter(const char * name){
  fCounters[name] = 0.0;
}


double & JPetStatistics::getCounter(const char * name){
  return fCounters[name];
}

const THashTable * JPetStatistics::getHistogramsTable() const{
  return &fHistos;
}

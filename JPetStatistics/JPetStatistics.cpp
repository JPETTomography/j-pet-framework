/**
 *  @file JPetStatustics.cpp
 *  @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 *  @copyright Copyright (c) 2015, J-PET collaboration
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

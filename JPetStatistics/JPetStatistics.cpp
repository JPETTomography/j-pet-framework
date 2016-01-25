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

TH1F & JPetStatistics::getHisto1D(const char * name){
  return dynamic_cast<TH1F&>(*(fHistos.FindObject(name)));
}

TH2F & JPetStatistics::getHisto2D(const char * name){
  return dynamic_cast<TH2F&>(*(fHistos.FindObject(name)));
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

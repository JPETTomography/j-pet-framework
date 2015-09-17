/**
  *  @copyright Copyright (c) 2015, Wojciech Krzemien
  *  @file JPetAnalysisModuleT.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "JPetAnalysisModuleT.h"

#include "../../JPetLoggerInclude.h"

JPetAnalysisModuleT::JPetAnalysisModuleT()
{
}

int JPetAnalysisModuleT::addStatsObject(TObject * statObj) {
  fStats.Add(statObj);
  return fStats.GetEntries();
}

const THashTable * JPetAnalysisModuleT::getStatsObjects() const {
  return &fStats;
}

TH1F * JPetAnalysisModuleT::getHisto1D(const char * name) {
  return dynamic_cast<TH1F*>(fStats.FindObject(name));
}

TH2F * JPetAnalysisModuleT::getHisto2D(const char * name) {
  return dynamic_cast<TH2F*>(fStats.FindObject(name));
}

TObject * JPetAnalysisModuleT::getStatsObject(const char * name) {
  return fStats.FindObject(name);
}

JPetAnalysisModuleT::~JPetAnalysisModuleT()
{
}

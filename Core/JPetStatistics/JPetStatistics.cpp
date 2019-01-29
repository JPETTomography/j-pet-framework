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
 *  @file JPetStatistics.cpp
 */

#include "JPetStatistics.h"

ClassImp(JPetStatistics);

JPetStatistics::JPetStatistics()
{
  ;
}
JPetStatistics::JPetStatistics(const JPetStatistics& old)
{
  fStats.AddAll(old.getStatsTable());
  fCounters = old.fCounters;
}

JPetStatistics::~JPetStatistics()
{
  fStats.Clear("nodelete");
}

void JPetStatistics::createHistogram(TObject* object)
{
  fStats.Add(object);
}

void JPetStatistics::createGraph(TObject* object)
{
  fStats.Add(object);
}

void JPetStatistics::createCanvas(TObject* object)
{
  fStats.Add(object);
}

TEfficiency* JPetStatistics::getEffiHisto(const char* name)
{
  return getObject<TEfficiency>(name);
}

TH1F* JPetStatistics::getHisto1D(const char* name)
{
  return getObject<TH1F>(name);
}

TH2F* JPetStatistics::getHisto2D(const char* name)
{
  return getObject<TH2F>(name);
}

TGraph* JPetStatistics::getGraph(const char* name)
{
  return getObject<TGraph>(name);
}

TCanvas* JPetStatistics::getCanvas(const char* name)
{
  return getObject<TCanvas>(name);
}

void JPetStatistics::createCounter(const char* name)
{
  fCounters[name] = 0.0;
}

double& JPetStatistics::getCounter(const char* name)
{
  return fCounters[name];
}

const THashTable* JPetStatistics::getStatsTable() const
{
  return &fStats;
}

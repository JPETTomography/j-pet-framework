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

#include "JPetStatistics/JPetStatistics.h"

ClassImp(JPetStatistics);

JPetStatistics::JPetStatistics() { ; }
JPetStatistics::JPetStatistics(const JPetStatistics& old)
{
  fStats.AddAll(old.getStatsTable());
  fCounters = old.fCounters;
}

JPetStatistics::~JPetStatistics() { fStats.Clear("nodelete"); }

void JPetStatistics::createHistogram(TObject* object) { fStats.Add(object); }

void JPetStatistics::createObject(TObject* object) { fStats.Add(object); }

void JPetStatistics::createHistogramWithAxes(TObject* object, TString xAxisName, TString yAxisName, TString zAxisName) 
{ 
  TClass *cl = object->IsA();
  if( cl->InheritsFrom("TH1D") )
  {
    TH1D* tempHisto = dynamic_cast<TH1D*>(object);
    tempHisto->GetXaxis()->SetTitle(xAxisName);
    tempHisto->GetYaxis()->SetTitle(yAxisName);
  }
  else if( cl->InheritsFrom("TH2D") )
  {
    TH2D* tempHisto = dynamic_cast<TH2D*>(object);
    tempHisto->GetXaxis()->SetTitle(xAxisName);
    tempHisto->GetYaxis()->SetTitle(yAxisName);
  }
  else if( cl->InheritsFrom("TH3D") )
  {
    TH3D* tempHisto = dynamic_cast<TH3D*>(object);
    tempHisto->GetXaxis()->SetTitle(xAxisName);
    tempHisto->GetYaxis()->SetTitle(yAxisName);
    tempHisto->GetZaxis()->SetTitle(zAxisName);
  }
  fStats.Add(object);
}

void JPetStatistics::createSquareHistogramWithAxes(TObject* object, TString xAxisName, TString yAxisName) 
{ 
  TClass *cl = object->IsA();
  if( cl->InheritsFrom("TH1D") )
  {
    TH1D* tempHisto = dynamic_cast<TH1D*>(object);
    tempHisto->GetXaxis()->SetTitle(xAxisName);
    tempHisto->GetYaxis()->SetTitle(yAxisName);
  }
  else if( cl->InheritsFrom("TH2D") )
  {
    TH2D* tempHisto = dynamic_cast<TH2D*>(object);
    tempHisto->GetXaxis()->SetTitle(xAxisName);
    tempHisto->GetYaxis()->SetTitle(yAxisName);
  }
  fStats.Add(object);
  std::string objName = object->GetName();
  objName += "_Square";
  createCanvas( new TCanvas( objName.c_str(), objName.c_str(), 800, 800 ) );
}


void JPetStatistics::createGraph(TObject* object) { fStats.Add(object); }

void JPetStatistics::createCanvas(TObject* object) { fStats.Add(object); }

void JPetStatistics::fillHistogram(const char* name, double xValue, doubleCheck yValue, doubleCheck zValue)
{
  TObject *tempObject = getObject<TObject>(name);
  if( !tempObject )
  {
    writeError(name, " does not exist" );
    return;
  }
  TClass *cl = tempObject->IsA();
  if( cl->InheritsFrom("TH1D") )
  {
    TH1D* tempHisto = dynamic_cast<TH1D*>(tempObject);
    tempHisto->Fill(xValue);
  }
  else if( cl->InheritsFrom("TH2D") )
  {
    TH2D* tempHisto = dynamic_cast<TH2D*>(tempObject);
    if(yValue.isChanged)
        tempHisto->Fill(xValue, yValue.value);
    else
        writeError(name, " does not received argument for Y axis" );
  }
  else if( cl->InheritsFrom("TH3D") )
  {
    TH3D* tempHisto = dynamic_cast<TH3D*>(tempObject);
    if(zValue.isChanged)
        tempHisto->Fill(xValue, yValue.value, zValue.value);
    else if(yValue.isChanged)
        writeError(name, " does not received argument for Y and Z axis" );
    else
        writeError(name, " does not received argument for Z axis" );
  }  
}

void JPetStatistics::fillSquareHistogram(const char* name, double xValue, doubleCheck yValue)
{
  TObject *tempObject = getObject<TObject>(name);
  if( !tempObject )
  {
    writeError(name, " does not exist" );
    return;
  }
  std::string canvasName = name;
  canvasName += "_Square";
  TCanvas *squareCanvas = getCanvas( canvasName.c_str() );
  if( !squareCanvas )
  {
    writeError(name, " has not defined square Canvas for it" );
    return;
  }
  
  TClass *cl = tempObject->IsA();
  if( cl->InheritsFrom("TH1D") )
  {
    TH1D* tempHisto = dynamic_cast<TH1D*>(tempObject);
    tempHisto->Fill(xValue);
    if( squareCanvas )
    {
        squareCanvas->cd();
        tempHisto->Draw("");
        squareCanvas->Update();
    }
  }
  else if( cl->InheritsFrom("TH2D") )
  {
    TH2D* tempHisto = dynamic_cast<TH2D*>(tempObject);
    if(yValue.isChanged)
        tempHisto->Fill(xValue, yValue.value);
    else
        writeError(name, " does not received argument for Y axis" );
    if( squareCanvas )
    {
        squareCanvas->cd();
        tempHisto->Draw("colz");
        squareCanvas->Update();
    }
  }
}

TEfficiency* JPetStatistics::getEffiHisto(const char* name) { return getObject<TEfficiency>(name); }

TH1F* JPetStatistics::getHisto1D(const char* name) { return getObject<TH1F>(name); }

TH2F* JPetStatistics::getHisto2D(const char* name) { return getObject<TH2F>(name); }

TH3F* JPetStatistics::getHisto3D(const char* name) { return getObject<TH3F>(name); }

TGraph* JPetStatistics::getGraph(const char* name) { return getObject<TGraph>(name); }

TCanvas* JPetStatistics::getCanvas(const char* name) { return getObject<TCanvas>(name); }

void JPetStatistics::createCounter(const char* name) { fCounters[name] = 0.0; }

double& JPetStatistics::getCounter(const char* name) { return fCounters[name]; }

const THashTable* JPetStatistics::getStatsTable() const { return &fStats; }

void JPetStatistics::writeError(const char* nameOfHistogram, const char* messageEnd )
{
  std::set<std::string>::iterator existenceCheck = fErrorCounts.find(std::string(nameOfHistogram));
  if( existenceCheck == fErrorCounts.end() )
  {
    fErrorCounts.insert(std::string(nameOfHistogram));
    ERROR(std::string("Histogram with name ") + std::string(nameOfHistogram) + std::string(messageEnd) );
    std::cout << "!!![Error]!!!  -  Histogram with name " << nameOfHistogram  << " " << messageEnd << std::endl;
  }
}

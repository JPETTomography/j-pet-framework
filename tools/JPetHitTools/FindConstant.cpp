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
 *  @file FindConstant.cpp
 */

#include "./FindConstant.h"
#include "TFile.h"
#include "TCanvas.h"
#include <sstream>
#include <cmath>
#include "TRandom3.h"
#include "TGraph.h"
#include "TStyle.h"
#include <fstream>
#include "TUnixSystem.h"
#include <TMultiGraph.h>

FindConstant::FindConstant(const std::vector<double>& inputEvents, const TString file, const double sourcePos, const int scinID)
{
  scintillatorID = scinID;
  EXPEvents = inputEvents;
  minBin = 0;
  maxBin = 500;
  lowerCut = 200;
  upperCut = 380;
  fileName = file;
  sourcePosition = sourcePos;

  EXPHisto = new TH1F("Experimental charge histogram", "expHisto", 500 / 2, minBin, maxBin);
  SIMHisto = new TH1F("Simulated energy histogram", "simHisto", 500 / 2, minBin, maxBin);
  SIMHisto->SetLineColor(kRed);
  SIMHisto->GetXaxis()->SetTitle("Energy [keV]" );
  SIMHisto->GetYaxis()->SetTitle("Counts" );
  EXPHisto->GetXaxis()->SetTitle("Charge [pC]" );
  EXPHisto->GetYaxis()->SetTitle("Counts" );

  bestChi2 = 999999, bestNorm = 1, bestAlpha = 1, alpha = 1, normalisation = 1, bestNumberOfBins = 0;
  binNumber = (maxBin - minBin) / 2.0;

}


double FindConstant::execute()
{
  std::vector<double> chi2, checkedBetaValues;
  for (double eRes = 1.0; eRes < 2.0; eRes += 0.05) {
    fillEXPHisto(); 	//fills the histogram without prescaling
    produceSIMEvents( SIMEvents, eRes );
    fillSIMHisto();

    aproximateParameters();
    fillSIMHisto(normalisation, alpha);


    performFit();
    fillSIMHisto(normalisation, alpha);

    checkedBetaValues.push_back(eRes);

    numberOfBins = -1.0 * (double(SIMHisto->GetXaxis()->FindBin(lowerCut / alpha)) - double(SIMHisto->GetXaxis()->FindBin(upperCut / alpha)) );
    chi2.push_back(compareHistogramsByChi2(normalisation, alpha) );

    if ( compareHistogramsByChi2(normalisation, alpha)  < bestChi2 ) {
      bestChi2 = compareHistogramsByChi2(normalisation, alpha) ;
      bestNorm = normalisation;
      bestAlpha = alpha;
      bestNumberOfBins = numberOfBins;
    }

    INFO( Form("Beta equal to %f was fitted with chi2: %f for number of bins: %d", eRes, compareHistogramsByChi2(normalisation, alpha)  , numberOfBins) );

    fillEXPHisto(1.0 / normalisation, 1.0 / alpha);
    fillSIMHisto();

    energyResolution = eRes;

    saveFittedHisto();
    SIMEvents.clear();

  }

  drawChi2AndFitPol2(checkedBetaValues, chi2);

  produceSIMEvents(SIMEvents, energyResolution);
  fillSIMHisto();
  fillEXPHisto(1.0 / bestNorm, 1.0 / bestAlpha);

  saveFitResultToTxt("fitResults.txt");

  saveFittedHisto();

  EXPHisto->Reset();
  SIMHisto->Reset();
  delete EXPHisto;
  delete SIMHisto;
  return bestAlpha;
}

void FindConstant::fillEXPHisto(const double normalisation, const double alpha)
{
  EXPHisto->Reset();
  for (unsigned int i = 0; i < EXPEvents.size(); i++) {
    EXPHisto->Fill(EXPEvents[i] / alpha, 1.0 / normalisation);
  }

}

void FindConstant::produceSIMEvents( std::vector<double>& SIMEvents, const double eRes)
{

  // DEKLARACJE ZMIENNYCH
  Double_t przekroj, E_0, E, stala, fi, firad, pi;
  Int_t i;
  Double_t T, kos, x, y, max, Eprim;
  TRandom3 los;
  Double_t rozdzielczosc, g, sigma, rozmyciex, Troz;

  // INICJALIZACJIA
  przekroj = 0.0;
  E = 1.0;
  stala = pow((2.82 * 1E-13), 2.0) * 0.5;
  E_0 = 511.0      ;
  fi = 0.0;
  i = 0;
  firad = 0;
  pi = 3.14159265358979323846;
  kos = 0.0;
  T = 0.0;
  Eprim = 0.0;
  rozdzielczosc = 0.0;
  g = 0.0;
  sigma = 0.0;
  rozmyciex = 0.0;
  Troz = 0.0;     //Ek. Kin. rozmyta

  // jeden stopien to okolo 0.0175 radiana  bo 1* pi /180 = 0.0175
  rozdzielczosc = eRes;

  fi = 0;

  firad = fi * pi / 180.0;
  E = E_0 * 511.0 / (511.0 + E_0 * ( 1 - cos(firad)));

  max = E * (2 * E / 511) / (1 + 2 * E / 511);

  //// PETLA DO RYSOWANIA WIDMA

  for (i = 0; i < 100000;) {



    x = los.Rndm() * max;

    y = los.Rndm() * 10.0;
    g = los.Gaus(0, 1);
    T = x;
    kos = (511.0 / E * T + T - E) / (T - E);
    Eprim = E - T;

    przekroj =  2.0 * 3.14 * stala * pow(Eprim / E, 2.0) * (E / Eprim + Eprim / E - 1.0 + pow(kos, 2.0) ) * ((511.0 / E + 1.0) / (T - E) - (511.0 / E * T + T - E) / (pow((T - E), 2.0))) * (-1.0) * 1E27;



    if (przekroj > y) {

      sigma = rozdzielczosc * sqrt(x);
      rozmyciex = sigma * g;
      Troz = x + rozmyciex;
      SIMEvents.push_back(Troz);
      i++;
    }


  }
}

void FindConstant::fillSIMHisto(const double normalisation, const double alpha)
{
  SIMHisto->Reset();
  for (unsigned int i = 0; i < SIMEvents.size(); i++) {
    SIMHisto->Fill(SIMEvents[i] / alpha, 1.0 / normalisation);
  }

}

void FindConstant::aproximateParameters()
{
  if (NULL == EXPHisto && NULL == SIMHisto) {
    ERROR( Form ("Not initialised histograms in findEnergyConstant! Exiting program") );
    std::exit(1);
  }
  initialWidthRatio = estimateWidthRatio();

  fillSIMHisto( 1.0, initialWidthRatio);

  initialHeightRatio =  estimateHeightRatio();

  normalisation = initialHeightRatio;
  alpha = initialWidthRatio;

  SIMHisto->GetXaxis()->SetRangeUser( minBin, maxBin);
  EXPHisto->GetXaxis()->SetRangeUser( minBin, maxBin);

}

double FindConstant::estimateWidthRatio()
{
  double meanForSimHisto = SIMHisto->GetMean() ;

  SIMHisto->GetXaxis()->SetRangeUser( meanForSimHisto, maxBin);
  EXPHisto->GetXaxis()->SetRangeUser( EXPHisto->GetMean() * 1.2, maxBin );

  initialWidthRatio = ( (double)SIMHisto->GetBinCenter( (SIMHisto->GetMaximumBin( )) ) )
                      /  ( (double) EXPHisto->GetBinCenter( EXPHisto->GetMaximumBin() ) );
  SIMHisto->GetXaxis()->SetRangeUser( minBin, maxBin);
  EXPHisto->GetXaxis()->SetRangeUser( minBin, maxBin);

  return initialWidthRatio;
}

double FindConstant::estimateHeightRatio()
{
  double meanForSimHisto = SIMHisto->GetMean();
  SIMHisto->GetXaxis()->SetRangeUser( meanForSimHisto, maxBin);
  EXPHisto->GetXaxis()->SetRangeUser( EXPHisto->GetMean() * 1.2, maxBin );

  heighestCountsInSIM = (double)SIMHisto->GetBinContent( (SIMHisto->GetMaximumBin( )) );
  heighestCountsInEXP = ( (double)EXPHisto->GetBinContent(EXPHisto->GetMaximumBin() ) );

  SIMHisto->GetXaxis()->SetRangeUser( minBin, maxBin);
  EXPHisto->GetXaxis()->SetRangeUser( minBin, maxBin);

  initialHeightRatio =  heighestCountsInSIM / heighestCountsInEXP;

  return initialHeightRatio;
}

void FindConstant::performFit()
{
  double bestChi2 = 99999.0;
  double bestAlpha = bestNorm = 0;

  for (double currentAlpha = 0.8 * alpha; currentAlpha < 1.2 * alpha; currentAlpha += alpha * 0.01) {
    for (double currentNorm = 0.8 * normalisation; currentNorm < 1.2 * normalisation; currentNorm += normalisation * 0.01) {
      fillSIMHisto( currentNorm, currentAlpha);
      double currentChi2 = compareHistogramsByChi2( currentNorm, currentAlpha) ;
      if (bestChi2 > currentChi2 ) {
        bestChi2 = currentChi2;
        bestAlpha = currentAlpha;
        bestNorm = currentNorm;
      }
    }
  }
  alpha = bestAlpha;
  normalisation = bestNorm;
}

double FindConstant::compareHistogramsByChi2( const double normalisation, const double alpha)
{
  double chi2 = 0.0;

  for (unsigned int i = 0; i < EXPHisto->GetSize() - (unsigned int)2; i++) {
    if ( 0 == EXPHisto->GetBinContent(i) && 0 == SIMHisto->GetBinContent(i) )
      continue;

    if ( double(SIMHisto->GetBinCenter(i)) > lowerCut / alpha && double( SIMHisto->GetBinCenter(i)) < upperCut / alpha) {
      chi2 +=  pow( ( double( SIMHisto->GetBinContent(i) ) - double( EXPHisto->GetBinContent(i) ) ) , 2.0)
               / ( double( EXPHisto->GetBinContent(i) ) + ( double( SIMHisto->GetBinContent(i) ) / normalisation ) ) ;
    }
  }
  return chi2;
}

void FindConstant::saveFittedHisto()
{
  TCanvas* c1 = new TCanvas();
  SIMHisto->Draw();
  EXPHisto->Draw("same");

  filePath = fileName;
  filePath = filePath(filePath.Last('/') + 1, filePath.Length() - 1);
  filePath = filePath(0, filePath.Last('.'));
  std::stringstream buf;
  buf << sourcePosition;
  TString title = "FitResults" + filePath + buf.str() + "/";
  TUnixSystem* system = new TUnixSystem();
  system->mkdir( (std::string(title)).c_str(), 1);
  std::stringstream streamForEResExtraction;
  streamForEResExtraction << energyResolution;
  SIMHisto->SetTitle( (streamForEResExtraction.str()).c_str() );
  streamForEResExtraction << "beta_for_scinID_" << scintillatorID;
  title += streamForEResExtraction.str();
  title += "position";
  title += sourcePosition;
  title += ".png";
  gStyle->SetOptStat(0);
  c1->SaveAs( title);

}

void FindConstant::saveSIMHisto()
{
  TCanvas* c1 = new TCanvas();

  SIMHisto->Draw();

  filePath = fileName;
  filePath = filePath(filePath.Last('/') + 1, filePath.Length() - 1);
  filePath = filePath(0, filePath.Last('.'));
  TString title = "FitResults" + filePath + "/";
  TUnixSystem* system = new TUnixSystem();
  system->mkdir( (std::string(title)).c_str(), 1);
  std::stringstream streamForEResExtraction;
  streamForEResExtraction << scintillatorID;
  title += streamForEResExtraction.str();
  title += "position";
  title += sourcePosition;
  title += "SIMHisto.png";
  gStyle->SetOptStat(0);
  c1->SaveAs( title);

}

void FindConstant::saveEXPHisto()
{
  TCanvas* c1 = new TCanvas();

  EXPHisto->Draw();

  filePath = fileName;
  filePath = filePath(filePath.Last('/') + 1, filePath.Length() - 1);
  filePath = filePath(0, filePath.Last('.'));
  TString title = "FitResults" + filePath + "/";
  TUnixSystem* system = new TUnixSystem();
  system->mkdir( (std::string(title)).c_str(), 1);
  std::stringstream streamForEResExtraction;
  streamForEResExtraction << scintillatorID;
  title += streamForEResExtraction.str();
  title += "position";
  title += sourcePosition;
  title += "EXPHisto.png";
  gStyle->SetOptStat(0);
  c1->SaveAs( title);

}

void FindConstant::saveFitResultToTxt(std::string name)
{
  std::ofstream myfile;
  myfile.open( name.c_str(), std::ios::app);

  if (myfile.is_open() ) {
    myfile << "Final fit result for data:" << filePath  << " for scintillator: " << scintillatorID << " for position " << sourcePosition  << "   alpha: " << bestAlpha << " and beta: " << energyResolution << " and chi2: " << bestChi2 << " for " << bestNumberOfBins << " bins " << std::endl;
  }

  myfile.close();

}

void FindConstant::drawChi2AndFitPol2(const std::vector<double>& res, const std::vector<double>& chi2)
{
  TCanvas* c1 = new TCanvas();
  std::stringstream streamForEResExtraction;
  streamForEResExtraction << scintillatorID << "_beta_" << energyResolution;

  std::vector<double> Chi2ToFit, ResToFit;
  for (size_t i = 0; i < chi2.size(); i++) {
    if (chi2[i] < bestChi2 + 50.0) {
      std::cout << chi2[i] << std::endl;
      Chi2ToFit.push_back( chi2[i] );
      ResToFit.push_back( res[i] );
    }
  }

  TMultiGraph* m = new TMultiGraph();

  TGraph* gr = new TGraph(Chi2ToFit.size(), &ResToFit[0], &Chi2ToFit[0]);
  gr->SetTitle("Chi2 vs #beta");
  gr->GetXaxis()->SetTitle("#beta (#sqrt{keV})");
  gr->GetYaxis()->SetTitle("Chi2 for best fit");
  gr->SetLineColor(2);
  gr->SetLineWidth(4);
  gr->SetMarkerColor(4);
  gr->SetMarkerStyle(21);
  gr->Draw("AP");
  gStyle->SetOptFit(1);

  quadraticFit = new TF1("quadraticFit", "[0]* (x - [1])**2 + [2]", ResToFit[0], ResToFit[ ResToFit.size() - 1 ] );
  quadraticFit->SetParName(0, "a");
  quadraticFit->SetParName(1, "x_min");
  quadraticFit->SetParName(2, "y_min");
  quadraticFit->SetParameter(1, energyResolution);
  quadraticFit->SetParameter(2, bestChi2);
  gr->Fit(quadraticFit, "R");
  quadraticFit->Draw("same");
  std::stringstream buf;
  buf << sourcePosition;
  c1->SaveAs( ("FitResults" + filePath + buf.str() + "/Chi2Plot_strip_fitRegion_" + streamForEResExtraction.str() + expHistoTitle + ".png") );

  m->Add(gr);

  energyResolution = quadraticFit->GetParameter(1);

  TGraph* grFull = new TGraph(chi2.size(), &res[0], &chi2[0]);
  grFull->SetTitle("Chi2 vs #beta");
  grFull->GetXaxis()->SetTitle("#beta (#sqrt{keV})");
  grFull->GetYaxis()->SetTitle("Chi2 for best fit");
  grFull->SetLineColor(2);
  grFull->SetLineWidth(4);
  grFull->SetMarkerColor(4);
  grFull->SetMarkerStyle(21);

  m->Add(grFull);

  m->Draw("AP");

  c1->SaveAs( ("FitResults" + filePath + buf.str() + "/Chi2Plot_strip_" + streamForEResExtraction.str() + expHistoTitle + ".png") );

  delete gr;
  delete c1;
}

double FindConstant::returnEnergyResolution()
{
  return energyResolution;
}

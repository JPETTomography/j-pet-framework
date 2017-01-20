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
 *  @file JPetRecoSignalTools.cpp
 */

#include "./JPetRecoSignalTools.h"
#include <cmath>
#include <sstream>
#include <sys/stat.h>

#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TUnixSystem.h>

void JPetRecoSignalTools::saveBadSignalIntoRootFile(const JPetRecoSignal& signal, const int numberOfBadSignals, const std::string fileName)
{
  TCanvas* c1 = new TCanvas();
  TGraph* badSignal = JPetRecoSignalTools::plotJPetRecoSignal(signal);
  badSignal->Draw("AP");
  std::string title;
  std::stringstream ss;
  ss << numberOfBadSignals;
  std::string str = ss.str();
  ss.str( std::string() );
  ss.clear();
  ss << signal.getPM().getID();
  std::string PMT = ss.str();
  title = "badSignal_PMT" + PMT + "_" + str;

  TFile* outFile = new TFile(fileName.c_str(), "update");
  badSignal->SetTitle(title.c_str());
  badSignal->Write();

  delete badSignal;
  delete c1;
  outFile->Close();
}

void JPetRecoSignalTools::savePNGOfBadSignal(const JPetRecoSignal& signal, int numberOfBadSignals)
{
  TCanvas* c1 = new TCanvas();
  TGraph* badSignal = JPetRecoSignalTools::plotJPetRecoSignal(signal);
  badSignal->Draw("AP");
  std::string title;
  std::stringstream ss;
  ss << numberOfBadSignals;
  std::string str = ss.str();
  ss.str( std::string() );
  ss.clear();
  ss << signal.getPM().getID();
  std::string PMT = ss.str();
  title = "badSignal_PMT" + PMT + "_" + str + ".png";
  c1->SaveAs(title.c_str());
  delete badSignal;
  delete c1;
}

void JPetRecoSignalTools::savePNGwithMarkedOffsetsAndStartingPoints(const JPetRecoSignal& signal, int number)
{
  TCanvas* c1 = new TCanvas();
  TGraph* badSignal = JPetRecoSignalTools::plotJPetRecoSignal(signal);
  badSignal->Draw("AP");
  badSignal->Draw("ALP");
  double offset = signal.getOffset();
  const std::vector< shapePoint > signalPoints = signal.getShape();
  std::vector<double> amplitudePoints;
  for (unsigned int i = 0; i < signalPoints.size(); ++i) {
    amplitudePoints.push_back(signalPoints[i].amplitude - offset);
  }

  TLine* offsetLine = new TLine(signalPoints[0].time / 1000, offset - 100, signal.getRecoTimeAtThreshold(-100) / 1000, offset - 100);
  std::cout << "Time at thr: " << signal.getRecoTimeAtThreshold(-100) / 1000 << std::endl;
  offsetLine->SetLineWidth(2);
  offsetLine->SetLineColor(2);
  offsetLine->Draw();

  std::string title;
  std::stringstream ss;
  ss << number;
  std::string str = ss.str();
  ss.str( std::string() );
  ss.clear();
  ss << signal.getPM().getID();
  std::string PMT = ss.str();
  TUnixSystem* system = new TUnixSystem();
  system->mkdir( "Signals" , 1);
  title = "Signals/badSignal_PMT" + PMT + "_" + str + ".root";
  c1->Update();
  c1->SaveAs(title.c_str());

  delete system;
  delete badSignal;
  delete c1;
}

double JPetRecoSignalTools::calculateTimeAtThreshold(const JPetRecoSignal& signal, const double threshold)
{
  bool isConstantThreshold = true;
  if (threshold < 0) {
    isConstantThreshold = false;
  }

  if (signal.getOffset() == JPetRecoSignalTools::ERRORS::badOffset) {
    return JPetRecoSignalTools::ERRORS::badTimeAtThr;
  }

  if (isConstantThreshold) {
    return calculateConstantThreshold(signal, -1.0 * threshold);
  } else {
  }
  return JPetRecoSignalTools::ERRORS::badTimeAtThr;
}

double JPetRecoSignalTools::calculateConstantThreshold(const JPetRecoSignal& signal, const double threshold)
{
  const std::vector< shapePoint > signalPoints = signal.getShape();

  std::vector<double> amplitudePoints;
  std::vector<double> timePoints;
  for (unsigned int i = 0; i < signalPoints.size(); ++i) {
    amplitudePoints.push_back( (signalPoints[i].amplitude) );
    timePoints.push_back( (signalPoints[i].time));
  }

  double timeAtThr = 0;

  double thresholdPlusOffset =  threshold + signal.getOffset();
  double slope = 1;
  double intercept = 0;
  for (int i = 0 ; i < findIndexAtValue(min(amplitudePoints), amplitudePoints); i++) {

    if (amplitudePoints[i + 1] < thresholdPlusOffset && amplitudePoints[i] > thresholdPlusOffset) {
      slope = (amplitudePoints[i + 1] - amplitudePoints[i]) / (timePoints[i + 1] - timePoints[i]);
      intercept = amplitudePoints[i] - (amplitudePoints[i + 1] - amplitudePoints[i]) / (timePoints[i + 1] - timePoints[i]) * timePoints[i];
      timeAtThr = (thresholdPlusOffset - intercept) / slope;
      break;
    }
  }
  return timeAtThr;
}

double JPetRecoSignalTools::calculateConstantFraction(const JPetRecoSignal& signal, const double threshold)
{
  double amplitude = signal.getAmplitude();
  double fractionValue = amplitude * threshold * -1;

  return calculateConstantThreshold(signal, fractionValue);
}

double JPetRecoSignalTools::calculateAreaFromStartingIndex(const JPetRecoSignal& signal)
{
  if (signal.getOffset() == JPetRecoSignalTools::ERRORS::badOffset) {
    return JPetRecoSignalTools::ERRORS::badCharge;
  }
  const std::vector< shapePoint >& signalPoints = signal.getShape();

  std::vector<double> amplitudePoints;
  std::vector<double> timePoints;
  double offset = signal.getOffset();
  int startingIndex = findStartingIndex(signal);

  if (startingIndex == JPetRecoSignalTools::badStartingIndex) {
    return JPetRecoSignalTools::ERRORS::badCharge;
  }
  //go over starting index and then star calculating area
  for (unsigned int i = startingIndex; i < signalPoints.size(); ++i) {
    amplitudePoints.push_back( (signalPoints[i].amplitude) - offset );
    timePoints.push_back( (signalPoints[i].time));
  }

  double area = 0;
  for (unsigned int i = 0; i < timePoints.size() - 1; i++) {
    if ( (amplitudePoints[i] > 0 && amplitudePoints[i + 1] < 0) || (amplitudePoints[i] < 0 && amplitudePoints[i + 1] > 0) ) {
      double xZero = pktPrzecieciaOX(timePoints[i], amplitudePoints[i], timePoints[i + 1], amplitudePoints[i + 1]);
      if (amplitudePoints[i] > 0 && amplitudePoints[i + 1] < 0) {
        area = area + 0.5 * (xZero - timePoints[i]) * amplitudePoints[i] + 0.5 * (timePoints[i + 1] - xZero) * amplitudePoints[i + 1];
      }
      if (amplitudePoints[i] < 0 && amplitudePoints[i + 1] > 0) {
        area = area + 0.5 * (xZero - timePoints[i]) * amplitudePoints[i] + 0.5 * (timePoints[i + 1] - xZero) * amplitudePoints[i + 1];
      }
    }

    else {
      if (amplitudePoints[i] < amplitudePoints[i + 1]) { // different slopes
        area = area + amplitudePoints[i] * (timePoints[i + 1] - timePoints[i]) + 0.5 * (amplitudePoints[i + 1] - amplitudePoints[i]) * (timePoints[i + 1] - timePoints[i]);
      } else {
        area = area + amplitudePoints[i + 1] * (timePoints[i + 1] - timePoints[i]) + 0.5 * (amplitudePoints[i] - amplitudePoints[i + 1]) * (timePoints[i + 1] - timePoints[i]);
      }
    }
  }

  const double resistance = 50 ; //Ohms
  area = area / resistance / 1000; //50 ohms resistance and units change to pC from m * p t

  timePoints.clear();
  amplitudePoints.clear();
  return area * -1;
}

double JPetRecoSignalTools::calculateArea(const JPetRecoSignal& signal)
{
  if (signal.getOffset() == 999999) {
    std::cout << "Bad signal in calculateAmplitude\n";
    return 999999;
  }
  const std::vector< shapePoint > signalPoints = signal.getShape();

  std::vector<double> amplitudePoints;
  std::vector<double> timePoints;

  for (unsigned int i = 0; i < signalPoints.size(); ++i) {
    amplitudePoints.push_back( (signalPoints[i].amplitude) );
    timePoints.push_back( (signalPoints[i].time));
  }

  double area = 0;
  for (unsigned int i = 0; i < timePoints.size() - 1; i++) {
    if ( (amplitudePoints[i] > 0 && amplitudePoints[i + 1] < 0) || (amplitudePoints[i] < 0 && amplitudePoints[i + 1] > 0) ) {
      double xZero = pktPrzecieciaOX(timePoints[i], amplitudePoints[i], timePoints[i + 1], amplitudePoints[i + 1]);
      if (amplitudePoints[i] > 0 && amplitudePoints[i + 1] < 0) {
        area = area + 0.5 * (xZero - timePoints[i]) * amplitudePoints[i] + 0.5 * (timePoints[i + 1] - xZero) * amplitudePoints[i + 1];
      }
      if (amplitudePoints[i] < 0 && amplitudePoints[i + 1] > 0) {
        area = area + 0.5 * (xZero - timePoints[i]) * amplitudePoints[i] + 0.5 * (timePoints[i + 1] - xZero) * amplitudePoints[i + 1];
      }
    }

    else {
      if (amplitudePoints[i] < amplitudePoints[i + 1]) { // different slopes
        area = area + amplitudePoints[i] * (timePoints[i + 1] - timePoints[i]) + 0.5 * (amplitudePoints[i + 1] - amplitudePoints[i]) * (timePoints[i + 1] - timePoints[i]);
      } else {
        area = area + amplitudePoints[i + 1] * (timePoints[i + 1] - timePoints[i]) + 0.5 * (amplitudePoints[i] - amplitudePoints[i + 1]) * (timePoints[i + 1] - timePoints[i]);
      }
    }
    //~ std::cout<<area<<std::endl;
  }


  area = area / 50 * 1000 ; //50 ohms resistance and units change to pC from m * p t

  double range = 0;

  if (timePoints[timePoints.size() - 1] < 0 && timePoints[0] > 0) range = timePoints[0] - timePoints[timePoints.size() - 1];
  else range = (timePoints[timePoints.size() - 1] - timePoints[0]);
  double offsetArea = signal.getOffset() * range / 50 * 1000;

  area -= offsetArea;

  timePoints.clear();
  amplitudePoints.clear();
  return area * -1;
}


double JPetRecoSignalTools::calculateAmplitude(const JPetRecoSignal& signal)
{
  if (signal.getOffset() == ERRORS::badOffset) {
    std::cout << "Bad signal in calculateAmplitude\n";
    return ERRORS::badAmplitude;
  }
  const std::vector< shapePoint > signalPoints = signal.getShape();

  std::vector<double> amplitudePoints;
  for (unsigned int i = 0; i < signalPoints.size(); ++i) {
    amplitudePoints.push_back(signalPoints[i].amplitude);
  }
  return -1 * (min(amplitudePoints)  - signal.getOffset());
}

int JPetRecoSignalTools::findStartingIndex(const JPetRecoSignal& signal)
{
  const std::vector< shapePoint >& signalPoints = signal.getShape();

  std::vector<double> amplitudePoints;
  for (unsigned int i = 0; i < signalPoints.size(); ++i) {
    amplitudePoints.push_back(signalPoints[i].amplitude);
  }

  //Finding place where minimum of signal is
  int indexAtMinimumOfSignal = findIndexAtValue( min(amplitudePoints), amplitudePoints);

  //Calculating approximate mean and std deviation of noise, estimating on first 20 points
  const int numberOfPointsTakenForAproximation = 20;
  double first20PointsMean = calculateArithmeticMean( amplitudePoints, numberOfPointsTakenForAproximation );
  double first20PointsDeviation = calculateStandardDeviation( amplitudePoints, numberOfPointsTakenForAproximation );

  //Checking if index was calculated correctly

  if (indexAtMinimumOfSignal == JPetRecoSignalTools::ERRORS::badIndexAtMinimumValue) {
    std::cout << "Problem with finding proper index at findStartingIndex\n";
    return JPetRecoSignalTools::ERRORS::badStartingIndex;
  }

  //Checking if minimum was not in first 20 points, which means that signal was not aquisited properly
  if ( indexAtMinimumOfSignal < numberOfPointsTakenForAproximation ) {
    std::cout << "Bad signal found\n";
    return JPetRecoSignalTools::ERRORS::badStartingIndex;
  }

  //Take only those points which are up to minimum
  amplitudePoints = copyVectorWithNumbersUpToIndex(amplitudePoints, indexAtMinimumOfSignal);

  //Start searching for last point in noise, go point by point to left from minium on signal
  //as long as noise will be found

  int index = indexAtMinimumOfSignal;

  while (index > numberOfPointsTakenForAproximation) {
    if ( isPointFromRecoSignalInNoise( first20PointsMean, first20PointsDeviation, amplitudePoints[index] ) ) {
      return index;
    }
    index -= 1;
  }
  return JPetRecoSignalTools::ERRORS::badStartingIndex;
}

double JPetRecoSignalTools::calculateOffset(const JPetRecoSignal& signal)
{
  //Get points for signal
  const std::vector< shapePoint >& signalPoints = signal.getShape();

  //Get only amplitudePoints
  std::vector<double> amplitudePoints;
  for (unsigned int i = 0; i < signalPoints.size(); ++i) {
    amplitudePoints.push_back(signalPoints[i].amplitude);
  }

  //Finding place where minimum of signal is
  const int indexAtMinimumOfSignal = findIndexAtValue( min(amplitudePoints), amplitudePoints);

  //Checking if index was calculated correctly
  if (indexAtMinimumOfSignal == JPetRecoSignalTools::ERRORS::badIndexAtValue) {
    return JPetRecoSignalTools::ERRORS::badOffset;
  }

  const int numberOfPointsTakenForAproximation = 20;
  //Checking if minimum was not in first 20 points, which means that signal was not aquisited properly
  if ( indexAtMinimumOfSignal < numberOfPointsTakenForAproximation ) {
    return JPetRecoSignalTools::ERRORS::badOffset;
  }

  //Calculating approximate mean and std deviation of noise, estimating on numberOfPointsTakenForAproximation points
  double first20PointsMean = calculateArithmeticMean( amplitudePoints, numberOfPointsTakenForAproximation );
  double first20PointsDeviation = calculateStandardDeviation( amplitudePoints, numberOfPointsTakenForAproximation );

  //Start searching for last point in noise, go point by point to left from minium on signal
  //as long as noise will be found
  int index = indexAtMinimumOfSignal;
  while (index > numberOfPointsTakenForAproximation) {
    if ( isPointFromRecoSignalInNoise( first20PointsMean, first20PointsDeviation, amplitudePoints[index] ) ) {
      return calculateArithmeticMean( amplitudePoints, index ); // HERE CORRECT ARITHEMTIC MEAN
    }
    index -= 1;
  }

  return first20PointsMean;
}

bool JPetRecoSignalTools::isPointFromRecoSignalInNoise(const double noiseMean, const double noiseDeviation, const double point)
{
  const double topBorder = noiseMean + 3 * noiseDeviation, bottomBorder = noiseMean - 3 * noiseDeviation;

  return ( ( point < topBorder ) && ( point > bottomBorder ) );
}

double JPetRecoSignalTools::calculateStandardDeviation(const std::vector<double>& vector, const int upToIndex)
{
  if (vector.size() == 1) {
    std::cout << "Cannot calculate standard deviation for this vector!\n";
    return -1;
  }

  double mean = calculateArithmeticMean(vector, vector.size() - 1);
  double deviation = 0;
  for ( int index = 0; index < upToIndex + 1; ++index) {
    deviation += pow( (vector[index] - mean) , 2 );

  }
  return pow(deviation / ( (upToIndex + 1) * (upToIndex ) ), 0.5);
}

std::vector<double> JPetRecoSignalTools::copyVectorWithNumbersUpToIndex(std::vector<double>& vector, int index)
{
  std::vector<double> copy;

  if ( (unsigned int) index > vector.size()) {
    std::cout << "Given index is bigger than vector size\n";
    return copy;
  }

  for (unsigned int i = 0; i < (unsigned int) (index + 1); ++i) {
    copy.push_back(vector[i]);
  }
  return copy;
}

double JPetRecoSignalTools::calculateArithmeticMean(const std::vector<double>& vector)
{
  double mean = 0;
  for ( auto index = 0u; index < vector.size(); ++index) {
    mean += vector[index];
  }
  return mean / vector.size();
}

double JPetRecoSignalTools::calculateArithmeticMean(const std::vector<double>& vector, const int upToIndex)
{
  double mean = 0;
  for ( int index = 0; index < upToIndex + 1; ++index) {
    mean += vector[index];
  }
  return mean / (upToIndex + 1);
}

double JPetRecoSignalTools::pktPrzecieciaOX(double x1, double y1, double x2, double y2)
{
  double slope;
  double intercept;
  slope = (y1 - y2) / (x1 - x2);
  intercept = y2 - (y1 - y2) / (x1 - x2) * x2;
  return -intercept / slope;
}

double JPetRecoSignalTools::min(const std::vector<double>& vector)
{
  if (vector.size() == 0) {
    std::cout << "Vector size is 0, not possible to look for minimum\n";
    std::exit(1);
  }
  double min = vector[0] ;
  for (unsigned int i = 1; i < vector.size(); ++i) {
    if ( min > vector[i] ) {
      min = vector[i];
    }
  }
  return min;
}

double JPetRecoSignalTools::max(const std::vector<double>& vector)
{
  if (vector.size() == 0) {
    std::cout << "Vector size is 0, not possible to look for maximum\n";
    std::exit(1);
  }
  double max = vector[0] ;
  for (unsigned int i = 1; i < vector.size(); ++i) {
    if ( max < vector[i] ) {
      max = vector[i];
    }
  }
  return max;
}


int JPetRecoSignalTools::findIndexAtValue(double value, std::vector<double>& vector)
{
  double epsilon = 0.001;
  for (unsigned int index = 0; index < vector.size(); ++index) {
    if ( absolute(vector[index] - value) < epsilon ) {
      return index;

    }
  }

  return JPetRecoSignalTools::ERRORS::badIndexAtValue;
}

double JPetRecoSignalTools::absolute ( const double number )
{
  if ( number > 0 ) {
    return number;
  } else return number * -1;
}

TGraph* JPetRecoSignalTools::plotJPetRecoSignal(const JPetRecoSignal& signal)
{
  const std::vector< shapePoint > signalPoints = signal.getShape();

  std::vector<double> amplitudePoints;
  std::vector<double> timePoints;
  for (unsigned int i = 0; i < signalPoints.size(); ++i) {
    amplitudePoints.push_back( ((signalPoints[i].amplitude)) );
    timePoints.push_back( (signalPoints[i].time) / 1000);
  }

  TGraph* gr = new TGraph(signalPoints.size(), &timePoints[0], &amplitudePoints[0]);
  gr->SetTitle("");
  gr->GetXaxis()->SetTitle("Time [ns]");
  gr->GetYaxis()->SetTitle("Amplitude [mV]");
  gr->SetMarkerStyle(21);
  gr->SetMarkerSize(0.5);
  gr->Draw("AP");
  return gr;
}


void JPetRecoSignalTools::saveTH1FsToRootFile(std::vector<TH1F*> histoCollection, std::string fileName, std::string pdfName)
{
  /*	Saves histos in vector to rootfile of name fileName.root in directoryName
   * 	assumes that histograms are given by pointers and are stored in vector
   *  saves also a Canvas with all histograms, assumes that first histogram
   *  in a collection is base one, also saves pdfs...
   *  this function is bad as hell!
   */
  TFile* testFile = new TFile(fileName.c_str(), "update");  //plik do historyjek

  for (unsigned i = 0; i < histoCollection.size(); i++) {
    histoCollection[i]->Write();
  }

  TCanvas* c1 = new TCanvas("c1", "", 710, 500);
  c1->SetHighLightColor(2);
  c1->Range(-11.27313, -51.28112, 87.54292, 330.6564);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetLeftMargin(0.114082);
  c1->SetRightMargin(0.08645276);
  c1->SetTopMargin(0.06573427);
  c1->SetBottomMargin(0.1342657);
  c1->SetFrameBorderMode(0);
  c1->SetFrameLineWidth(2);
  c1->SetFrameBorderMode(0);

  int maxIndex = findIndexOfMaxHisto(histoCollection);
  histoCollection[maxIndex]->Draw("");
  histoCollection[maxIndex]->SetLineWidth(4);
  histoCollection[maxIndex]->SetLineColor(maxIndex + 1);
  histoCollection[maxIndex]->SetLineStyle(maxIndex + 1);

  for (unsigned int i = 0; i < histoCollection.size(); i++) {

    if (i != (unsigned int)maxIndex) {
      std::cout << i << std::endl;
      histoCollection[i]->SetLineColor(1 + i);
      histoCollection[i]->SetLineWidth(4);
      histoCollection[i]->SetLineStyle(i + 1);
      histoCollection[i]->Draw("same");
    }

  }

  TLegend* legend = new TLegend(0.6, 0.65, 0.88, 0.85);
  legend->SetTextFont(72);
  legend->SetTextSize(0.04);

  for (unsigned int i = 0; i < histoCollection.size(); i++) {
    legend->AddEntry(histoCollection[i], histoCollection[i]->GetTitle(), "l");
  }
  legend->Draw();

  c1->Write(pdfName.c_str());


  c1->SaveAs( (pdfName + ".png").c_str());
  delete c1;
  testFile->Close();
}

int JPetRecoSignalTools::findIndexOfMaxHisto(std::vector<TH1F*> histoCollection)
{
  int max = -100000.;
  int histoMax = 0;
  int maxIndex = histoCollection.size() + 5;

  for (unsigned int histoNumber = 0; histoNumber < histoCollection.size(); histoNumber++) {
    histoMax = histoCollection[histoNumber]->GetBinContent( histoCollection[histoNumber]->GetMaximumBin() ) ;
    if (histoMax > max) {
      max = histoMax;
      maxIndex = histoNumber;
    }
  }

  return maxIndex;
}


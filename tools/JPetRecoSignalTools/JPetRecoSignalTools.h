/**
 * @copyright Copyright (c) 2015, The J-Pet Framework Authors.
 * @file JPetRecoSignalTools.h
 * @brief calculates offset for JPetRecoSignal by mean of noise points
 * S. Niedzwiecki version of the algorithm
 */

#ifndef JPETRECOSIGNALTOOLS_H
#define JPETRECOSIGNALTOOLS_H

#include "../../JPetRecoSignal/JPetRecoSignal.h"
#include <vector>
#include <cmath>
#include "sstream"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TLegend.h"
#include <sys/stat.h>
#include "TLine.h"
#include "TUnixSystem.h"

class JPetRecoSignalTools
{
	public: 
	static double calculateOffset(const JPetRecoSignal& signal);
	static double calculateAmplitude(const JPetRecoSignal& signal);
	static double calculateArea(const JPetRecoSignal& signal);
	static double calculateTimeAtThreshold(const JPetRecoSignal& signal, const double threshold);
	static TGraph* plotJPetRecoSignal(const JPetRecoSignal& signal);
	static void saveTH1FsToRootFile(std::vector<TH1F*> histoCollection, std::string fileName, std::string pdfName);
	static double calculateAreaFromStartingIndex(const JPetRecoSignal& signal);
	static void savePNGOfBadSignal(const JPetRecoSignal& signal, int numberOfBadSignals);
	static void saveBadSignalIntoRootFile(const JPetRecoSignal& signal, const int numberOfBadSignals, const std::string fileName);
	static void savePNGwithMarkedOffsetsAndStartingPoints(const JPetRecoSignal& signal, int number);
	static double min(const std::vector<double>& vector);
	static double max(const std::vector<double>& vector);
	enum ERRORS{ badOffset, badIndexAtMinimumSignal, badIndexAtValue, badCharge, badStartingIndex, badIndexAtMinimumValue, badTimeAtThr};
		
	private:
	static double calculateArithmeticMean(const std::vector<double>& vector);
	static int findStartingIndex(const JPetRecoSignal& signal);
	static int findIndexOfMaxHisto(std::vector<TH1F*> histoCollection);
	static double pktPrzecieciaOX(double x1, double y1, double x2, double y2);
	static double absolute(const double number);
	static int findIndexAtValue(double value, std::vector<double>& vector);
	static double calculateArithmeticMean(const std::vector<double>& vector, const int upToIndex);
	static double calculateStandardDeviation(const std::vector<double>& vector, const int upToIndex);
	static std::vector<double> copyVectorWithNumbersUpToIndex(std::vector<double>& vector, int index);
	static bool isPointFromRecoSignalInNoise(const double noiseMean, const double noiseDeviation, const double point);
	static double calculateConstantThreshold(const JPetRecoSignal& signal, const double threshold);
	static double calculateConstantFraction(const JPetRecoSignal& signal, const double threshold);
};

#endif // JPETRECOSIGNALTOOLS_H

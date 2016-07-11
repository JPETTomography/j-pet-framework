#ifndef FINDCONSTANT_H
#define FINDCONSTANT_H

#include "../../JPetLoggerInclude.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <sstream>
#include <cmath>
#include "TRandom3.h"
#include "TGraph.h"
#include "TF1.h"
#include "TStyle.h"
#include <fstream>
#include "TUnixSystem.h"
#include <TMultiGraph.h>


class FindConstant{
	public:
  	  FindConstant(const std::vector<double>& inputEvents, const TString file, const double sourcePos, const int scinID);
	  double execute();	
	  double returnEnergyResolution();

	private:
	
	  void drawChi2AndFitPol2(const std::vector<double>& res, const std::vector<double>& chi2);
	  void aproximateParameters();
	  void saveFitResultToTxt(std::string name);
	  void produceSIMEvents(std::vector<double>& SIMEvents, const double eRes);
	  void fillSIMHisto(const double normalisation = 1.0, const double alpha = 1.0);
	  void fillEXPHisto(const double normalisation = 1.0, const double alpha = 1.0);
	   double compareHistogramsByChi2(const double normalisation, const double alpha);
	   void saveFittedHisto();
	   void saveSIMHisto();
	   void saveEXPHisto();
	   void performFit();
	   bool isDir(std::string& path);
	  double estimateWidthRatio();
	  double estimateHeightRatio();
		
	   TString fileName;
	   TF1* quadraticFit;
	   double initialHeightRatio, initialWidthRatio, heighestCountsInSIM, heighestCountsInEXP;
	   std::vector<double> SIMEvents, EXPEvents;
	   unsigned int numberOfBins;
	   int scintillatorID, binNumber;
	   TH1F* EXPHisto;
	   TH1F* SIMHisto;
	   std::string expHistoTitle;
	   double normalisation, alpha, energyResolution, sourcePosition;
	   int maxBin, minBin;
	   double bestChi2, bestNorm, bestAlpha, bestNumberOfBins;
	   TString filePath;
	   std::vector<double> alphasForStripes;
	   double upperCut, lowerCut;
	};
#endif


/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetRandomTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSmearingFunctionsTest
#include <boost/test/unit_test.hpp>

#include <JPetSmearingFunctions/JPetSmearingFunctions.h>
#include <TRandom.h>
#include "TH1F.h"
#include "TCanvas.h"



BOOST_AUTO_TEST_SUITE(FirstSuite)

const bool plotControlHisto = false;

BOOST_AUTO_TEST_CASE( checkSeed )
{
  UInt_t seed = 65529;
  gRandom->SetSeed(seed);
  double r1= gRandom->Rndm();

  gRandom->SetSeed(seed);
  double r2= gRandom->Rndm();

  BOOST_REQUIRE_EQUAL(r1,r2);

}

BOOST_AUTO_TEST_CASE( addZHitSmearing )
{
  UInt_t seed = 65529;
  int scinID = 200;
  double zIn = 5.0;
  double eneIn = 200.0;
  
  gRandom->SetSeed(seed);
  double r2 = JPetSmearingFunctions::addZHitSmearing(scinID,zIn,eneIn);
  gRandom->SetSeed(seed);
  double r1 = JPetSmearingFunctions::addZHitSmearing(scinID,zIn,eneIn);

  BOOST_REQUIRE_EQUAL(r1,r2);
}

BOOST_AUTO_TEST_CASE( addEnergySmearing )
{
  UInt_t seed = 65529;
  int scinID = 200;
  double zIn = 5.0;
  double eneIn = 4.0;
  
  gRandom->SetSeed(seed);
  double r2 = JPetSmearingFunctions::addEnergySmearing(scinID,zIn,eneIn);
  gRandom->SetSeed(seed);
  double r1 = JPetSmearingFunctions::addEnergySmearing(scinID,zIn,eneIn);

  BOOST_REQUIRE_EQUAL(r1,r2);
}


BOOST_AUTO_TEST_CASE( addTimeSmearing )
{
  UInt_t seed = 65529;
  int scinID = 200;
  double zIn = 5.0;
  double eneIn = 200.0;
  double timeIn = -590.0;
  
  gRandom->SetSeed(seed);
  double r2 = JPetSmearingFunctions::addTimeSmearing(scinID,zIn,eneIn,timeIn);
  gRandom->SetSeed(seed);
  double r1 = JPetSmearingFunctions::addTimeSmearing(scinID,zIn,eneIn,timeIn);

  BOOST_REQUIRE_EQUAL(r1,r2);
}

double oldZHitSmearing(double zIn, double z_res)
{
  return gRandom->Gaus(zIn, z_res);
}

double oldEnergySmearing(double eneIn)
{
  /// @param eneIn in keV
  double alpha = 0.044 / sqrt(eneIn / 1000.);
  return eneIn + alpha * eneIn * gRandom->Gaus(0., 1.);
}




BOOST_AUTO_TEST_CASE( CompareOldZHitSmearing )
{

  UInt_t seed = 65529;
  double zIn = 5.0;
  double res = 0.976;
  int nEvents  = 1000;

  TH1F* h1 = new TH1F("h1","title",200,-10+zIn,10+zIn);
  TH1F* h2 = new TH1F("h2","title",200,-10+zIn,10+zIn);


  gRandom->SetSeed(seed);
  for (int i=0; i<nEvents;i++)
  {
    h1->Fill(oldZHitSmearing(zIn, res));
  }

  gRandom->SetSeed(seed);
  for (int i=0; i<nEvents;i++)
  {
    h2->Fill(JPetSmearingFunctions::addZHitSmearing(20, zIn, 540.));
  }

  double k = h1->KolmogorovTest(h2);

  if(plotControlHisto)
  {
    TCanvas *myCanvas = new TCanvas();
    h1->Draw("");
    h2->SetLineColor(2);
    h2->Draw("SAME");
    myCanvas->Print("ZHitSmearing.pdf");
  }
  BOOST_CHECK_CLOSE(k,1.0,10.);
  delete h1;
  delete h2;
}


BOOST_AUTO_TEST_CASE( CompareOldEnergySmearing )
{

  UInt_t seed = 65529;
  double eneIn = 100.0;
  int nEvents  = 1000;

  TH1F* h1 = new TH1F("h1","title",200,-50+eneIn,50+eneIn);
  TH1F* h2 = new TH1F("h2","title",200,-50+eneIn,50+eneIn);


  gRandom->SetSeed(seed);
  for (int i=0; i<nEvents;i++)
  {
    h1->Fill(oldEnergySmearing(eneIn));
  }

  gRandom->SetSeed(seed);
  for (int i=0; i<nEvents;i++)
  {
    h2->Fill(JPetSmearingFunctions::addEnergySmearing(20, 4., eneIn));
  }

  double k = h1->KolmogorovTest(h2);

  if(plotControlHisto)
  {
    TCanvas *myCanvas = new TCanvas();
    h1->Draw("");
    h2->SetLineColor(2);
    h2->Draw("SAME");
    myCanvas->Print("EnergySmearing.pdf");
  }
  BOOST_CHECK_CLOSE(k,1.0,10.);
  delete h1;
  delete h2;

}

double oldTimeSmearing(double timeIn, double eneIn)
{
  /// @param eneIn in keV
  /// @param timeIn in ps
  const double kEnergyThreshold = 200.; ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5 
  const double kReferenceEnergy = 270.; ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5
  const double kTimeResolutionConstant = 80.; ///< see Eur. Phys. J. C (2016) 76:445  equation 3


  double time =0.;

  if ( eneIn > kEnergyThreshold ) {
    time = timeIn + kTimeResolutionConstant * gRandom->Gaus(0., 1.);
  } else {
    time = timeIn + kTimeResolutionConstant * gRandom->Gaus(0., 1.) / sqrt(eneIn / kReferenceEnergy);
  }
  return time;
}



BOOST_AUTO_TEST_CASE( CompareOldTimeSmearing )
{

  UInt_t seed = 65529;
  double timeIn = -100.0;
  double eneIn = 350.0;
  int nEvents  = 1000;

  TH1F* h1 = new TH1F("h1","title",200,-350+timeIn,350+timeIn);
  TH1F* h2 = new TH1F("h2","title",200,-350+timeIn,350+timeIn);


  gRandom->SetSeed(seed);
  for (int i=0; i<nEvents;i++)
  {
    h1->Fill(oldTimeSmearing(timeIn,eneIn));
  }

  gRandom->SetSeed(seed);
  for (int i=0; i<nEvents;i++)
  {
    h2->Fill(JPetSmearingFunctions::addTimeSmearing(20, 4., eneIn, timeIn));
  }

  double k = h1->KolmogorovTest(h2);

  if(plotControlHisto)
  {
    TCanvas *myCanvas = new TCanvas();
    h1->Draw("");
    h2->SetLineColor(2);
    h2->Draw("SAME");
    myCanvas->Print("TimeSmearing.pdf");
  }
  BOOST_CHECK_CLOSE(k,1.0,10.);
  delete h1;
  delete h2;

}


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(SecondSuite)

class NewSmearingFunctions
{
  public:
    double newHitZSmearing(double *x, double *p){return 7.;}
}; 


BOOST_AUTO_TEST_CASE( overrrideSmearingFunctions )
{

  double point = 6.;

  NewSmearingFunctions* sf = new NewSmearingFunctions();
  TF1* fun = new TF1("newEnergySmearing",sf,&NewSmearingFunctions::newHitZSmearing, -200., 200.,3,"NewSmearingFunctions","newHitZSmearing");
  JPetSmearingFunctions::getSmearingFunctions().setFunZHitSmearing(fun);

  auto r1 = JPetSmearingFunctions::getSmearingFunctions().getFunZHitSmearing()->Eval(point);

  BOOST_REQUIRE_EQUAL(r1,7.);


}

BOOST_AUTO_TEST_SUITE_END()

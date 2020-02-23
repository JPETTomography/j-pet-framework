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
 *  @file JPetSmearingFunctionsNew.cpp
 */

#include <JPetSmearingFunctions/JPetSmearingFunctionsNew.h>
#define _USE_MATH_DEFINES
#include <math.h>

double JPetHitExperimentalParametrizer::addZHitSmearing(int scinID, double zIn, double eneIn) const
{
  //fSmearingFunctionsNew.getFunZHitSmearing()->SetParameters(double(scinID),zIn,eneIn);
  //fSmearingFunctionsNew.getFunZHitSmearing()->SetRange(zIn-5.,zIn+5.);
  //return fSmearingFunctionsNew.getFunZHitSmearing()->GetRandom();
  return 0;
}

double JPetHitExperimentalParametrizer::addEnergySmearing(int scinID, double zIn, double eneIn) const
{
  //fSmearingFunctionsNew.getFunEnergySmearing()->SetParameters(double(scinID),zIn,eneIn);
  //fSmearingFunctionsNew.getFunEnergySmearing()->SetRange(eneIn-100.,eneIn+100.);
  //return fSmearingFunctionsNew.getFunEnergySmearing()->GetRandom();
  return 0;
}

double JPetHitExperimentalParametrizer::addTimeSmearing(int scinID, double zIn, double eneIn, double timeIn) const
{
  //fSmearingFunctionsNew.getFunTimeHitSmearing()->SetParameters(double(scinID),zIn,eneIn,timeIn);
  //fSmearingFunctionsNew.getFunTimeHitSmearing()->SetRange(timeIn-300.,timeIn+300.);
  //return fSmearingFunctionsNew.getFunTimeHitSmearing()->GetRandom();
  return 0;
}

JPetSmearingFunctionsNewContainer JPetSmearingFunctionsNew::fSmearingFunctionsNew = JPetSmearingFunctionsNewContainer();

JPetSmearingFunctionsNewContainer::JPetSmearingFunctionsNewContainer()
{
  sf = new JPetHitSmearingFunctionsNew();
  fFunEnergySmearing = new TF1("funEnergySmearing",sf,&JPetHitSmearingFunctionsNew::hitEnergySmearing, -200., 200.,3,"JPetHitSmearingFunctionsNew","hitEnergySmearing");
  fFunZHitSmearing = new TF1("funZHitSmearing",sf,&JPetHitSmearingFunctionsNew::hitZSmearing, -200., 200.,3,"JPetHitSmearingFunctionsNew","hitZSmearing");
  fFunTimeHitSmearing = new TF1("funTimeHitSmearing",sf,&JPetHitSmearingFunctionsNew::hitTimeSmearing, -200., 200.,4,"JPetHitSmearingFunctionsNew","hitTimeSmearing");
}

JPetSmearingFunctionsNewContainer& JPetSmearingFunctionsNew::getSmearingFunctionsNew()
{
  return fSmearingFunctionsNew;
}

void JPetSmearingFunctionsNewContainer::setFunEnergySmearing(TF1* fun)
{
  fFunEnergySmearing = fun;
}

void JPetSmearingFunctionsNewContainer::setFunZHitSmearing(TF1* fun)
{
  fFunZHitSmearing = fun;
}

void JPetSmearingFunctionsNewContainer::setFunTimeHitSmearing(TF1* fun)
{
  fFunTimeHitSmearing = fun;
}

double JPetHitSmearingFunctionsNew::hitEnergySmearing(double *x, double *p)
{
  // p[0] = scinID
  // p[1] = zIn
  // p[2] = eneIn
  double eneIn = p[2];
  double sigma = eneIn*0.044 / sqrt(eneIn / 1000.);

  return exp(-0.5*pow((x[0]-eneIn)/sigma,2))/(sqrt(2*M_PI)*sigma);
}

double JPetHitSmearingFunctionsNew::hitZSmearing(double *x, double *p)
{
  // p[0] = scinID
  // p[1] = zIn
  // p[2] = eneIn
  double zIn = p[1];
  double sigma = 0.976;

  return exp(-0.5*pow((x[0]-zIn)/sigma,2))/(sqrt(2*M_PI)*sigma);
}

double JPetHitSmearingFunctionsNew::hitTimeSmearing(double *x, double *p)
{
  // p[0] = scinID
  // p[1] = zIn
  // p[2] = eneIn
  // p[3] = timeIn
  const double kEnergyThreshold = 200.; ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5 
  const double kReferenceEnergy = 270.; ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5
  const double kTimeResolutionConstant = 80.; ///< see Eur. Phys. J. C (2016) 76:445  equation 3

  double eneIn = p[2];
  double timeIn = p[3];


  double sigma = kTimeResolutionConstant; 
  if ( eneIn < kEnergyThreshold ) {
    sigma = sigma/ sqrt(eneIn / kReferenceEnergy);
  }
  return exp(-0.5*pow((x[0]-timeIn)/sigma,2))/(sqrt(2*M_PI)*sigma);
}


TF1* JPetSmearingFunctionsNewContainer::getFunEnergySmearing()
{
  return fFunEnergySmearing;
}

TF1* JPetSmearingFunctionsNewContainer::getFunZHitSmearing()
{
  return fFunZHitSmearing;
}

TF1* JPetSmearingFunctionsNewContainer::getFunTimeHitSmearing()
{
  return fFunTimeHitSmearing;
}


double JPetSmearingFunctionsNew::addZHitSmearing(int scinID, double zIn, double eneIn)
{
  fSmearingFunctionsNew.getFunZHitSmearing()->SetParameters(double(scinID),zIn,eneIn);
  fSmearingFunctionsNew.getFunZHitSmearing()->SetRange(zIn-5.,zIn+5.);
  return fSmearingFunctionsNew.getFunZHitSmearing()->GetRandom();
}

double JPetSmearingFunctionsNew::addEnergySmearing(int scinID, double zIn, double eneIn)
{
  fSmearingFunctionsNew.getFunEnergySmearing()->SetParameters(double(scinID),zIn,eneIn);
  fSmearingFunctionsNew.getFunEnergySmearing()->SetRange(eneIn-100.,eneIn+100.);
  return fSmearingFunctionsNew.getFunEnergySmearing()->GetRandom();
}

double JPetSmearingFunctionsNew::addTimeSmearing(int scinID, double zIn, double eneIn, double timeIn)
{
  fSmearingFunctionsNew.getFunTimeHitSmearing()->SetParameters(double(scinID),zIn,eneIn,timeIn);
  fSmearingFunctionsNew.getFunTimeHitSmearing()->SetRange(timeIn-300.,timeIn+300.);
  return fSmearingFunctionsNew.getFunTimeHitSmearing()->GetRandom();
}



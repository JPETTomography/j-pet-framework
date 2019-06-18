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
 *  @file JPetSmearingFunctions.cpp
 */

#include <JPetSmearingFunctions/JPetSmearingFunctions.h>

JPetSmearingFunctionsContainer JPetSmearingFunctions::fSmearingFunctions = JPetSmearingFunctionsContainer();

JPetSmearingFunctionsContainer::JPetSmearingFunctionsContainer()
{
  sf = new JPetHitSmearingFunctions();
  fFunEnergySmearing = new TF1("funEnergySmearing",sf,&JPetHitSmearingFunctions::hitEnergySmearing, -200., 200.,3,"JPetHitSmearingFunctions","hitEnergySmearing");
  fFunZHitSmearing = new TF1("funZHitSmearing",sf,&JPetHitSmearingFunctions::hitZSmearing, -200., 200.,3,"JPetHitSmearingFunctions","hitZSmearing");
  fFunTimeHitSmearing = new TF1("funTimeHitSmearing",sf,&JPetHitSmearingFunctions::hitTimeSmearing, -200., 200.,4,"JPetHitSmearingFunctions","hitTimeSmearing");
}

JPetSmearingFunctionsContainer& JPetSmearingFunctions::getSmearingFunctions()
{
  return fSmearingFunctions;
}

void JPetSmearingFunctionsContainer::setFunEnergySmearing(TF1* fun)
{
  fFunEnergySmearing = fun;
}

void JPetSmearingFunctionsContainer::setFunZHitSmearing(TF1* fun)
{
  fFunZHitSmearing = fun;
}

void JPetSmearingFunctionsContainer::setFunTimeHitSmearing(TF1* fun)
{
  fFunTimeHitSmearing = fun;
}

double JPetHitSmearingFunctions::hitEnergySmearing(double *x, double *p)
{
  // p[0] = scinID
  // p[1] = zIn
  // p[2] = eneIn
  double eneIn = p[2];
  double sigma = eneIn*0.044 / sqrt(eneIn / 1000.);

  return exp(-0.5*pow((x[0]-eneIn)/sigma,2))/(sqrt(2*M_PI)*sigma);
}

double JPetHitSmearingFunctions::hitZSmearing(double *x, double *p)
{
  // p[0] = scinID
  // p[1] = zIn
  // p[2] = eneIn
  double zIn = p[1];
  double sigma = 0.976;

  return exp(-0.5*pow((x[0]-zIn)/sigma,2))/(sqrt(2*M_PI)*sigma);
}

double JPetHitSmearingFunctions::hitTimeSmearing(double *x, double *p)
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


TF1* JPetSmearingFunctionsContainer::getFunEnergySmearing()
{
  return fFunEnergySmearing;
}

TF1* JPetSmearingFunctionsContainer::getFunZHitSmearing()
{
  return fFunZHitSmearing;
}

TF1* JPetSmearingFunctionsContainer::getFunTimeHitSmearing()
{
  return fFunTimeHitSmearing;
}


double JPetSmearingFunctions::addZHitSmearing(int scinID, double zIn, double eneIn)
{
  fSmearingFunctions.getFunZHitSmearing()->SetParameters(double(scinID),zIn,eneIn);
  fSmearingFunctions.getFunZHitSmearing()->SetRange(zIn-5.,zIn+5.);
  return fSmearingFunctions.getFunZHitSmearing()->GetRandom();
}

double JPetSmearingFunctions::addEnergySmearing(int scinID, double zIn, double eneIn)
{
  fSmearingFunctions.getFunEnergySmearing()->SetParameters(double(scinID),zIn,eneIn);
  fSmearingFunctions.getFunEnergySmearing()->SetRange(eneIn-100.,eneIn+100.);
  return fSmearingFunctions.getFunEnergySmearing()->GetRandom();
}

double JPetSmearingFunctions::addTimeSmearing(int scinID, double zIn, double eneIn, double timeIn)
{
  fSmearingFunctions.getFunTimeHitSmearing()->SetParameters(double(scinID),zIn,eneIn,timeIn);
  fSmearingFunctions.getFunTimeHitSmearing()->SetRange(timeIn-300.,timeIn+300.);
  return fSmearingFunctions.getFunTimeHitSmearing()->GetRandom();
}



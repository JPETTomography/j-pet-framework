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
 *  @file JPetSmearingFunctionsNewNew.h
 */

#ifndef JPETSMEARINGFUNCTIONSNEW_H
#define JPETSMEARINGFUNCTIONSNEW_H

#include <TF1.h>

class JPetHitExperimentalParametrizer
{
  public:
  JPetHitExperimentalParametrizer()=default;
  double addEnergySmearing(int scinID, double zIn, double eneIn) const;
  double addZHitSmearing(int scinID, double zIn, double eneIn) const;
  double addTimeSmearing(int scinID, double zIn, double eneIn, double timeIn) const;
};


#ifdef __CINT__
//when cint is used instead of compiler, override word is not recognized
//nevertheless it's needed for checking if the structure of project is correct
#   define override
#endif

class JPetHitSmearingFunctionsNew
{
  public:
    double hitEnergySmearing(double *x, double *p);
    double hitZSmearing(double *x, double *p);
    double hitTimeSmearing(double *x, double *p);
};



class JPetSmearingFunctionsNewContainer
{
  public:
    JPetSmearingFunctionsNewContainer();
    TF1* getFunEnergySmearing();
    TF1* getFunZHitSmearing();
    TF1* getFunTimeHitSmearing();
    void setFunEnergySmearing(TF1* fun);
    void setFunZHitSmearing(TF1* fun);
    void setFunTimeHitSmearing(TF1* fun);

  private:
    JPetHitSmearingFunctionsNew* sf = nullptr;
    TF1* fFunEnergySmearing;
    TF1* fFunZHitSmearing;
    TF1* fFunTimeHitSmearing;
};


/**
 * @brief stores smearing functions that should be applied to generated computer simulations in
 * order to reproduce collected data 
 */

class JPetSmearingFunctionsNew
{
  public:
    static double addEnergySmearing(int scinID, double zIn, double eneIn);
    static double addZHitSmearing(int scinID, double zIn, double eneIn);
    static double addTimeSmearing(int scinID, double zIn, double eneIn, double timeIn);
    static JPetSmearingFunctionsNewContainer& getSmearingFunctionsNew();

  private:
    static JPetSmearingFunctionsNewContainer fSmearingFunctionsNew; 
};



#endif

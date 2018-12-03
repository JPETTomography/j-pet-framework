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
 *  @file JPetGeantEventInformation.h
 */

#ifndef JPET_GEANT_EVENT_INFORMATION_H
#define JPET_GEANT_EVENT_INFORMATION_H 1

#include "TObject.h"
#include <vector>
#include "TVector3.h" 
#include "TBits.h"


/**
 * @brief keeps information about initial simulation parameters
 * e.g. vertices and times distributions for annihilation 
 * and prompt gamma photons
 */ 
class JPetGeantEventInformation : public TObject {
    public:
        JPetGeantEventInformation();
        ~JPetGeantEventInformation();
        void Clear();

        void SetThreeGammaGen(bool tf){fGenGammaNum.SetBitNumber(2,tf);};
        void SetTwoGammaGen(bool tf){fGenGammaNum.SetBitNumber(1,tf);};
        void SetPromptGammaGen(bool tf){fGenGammaNum.SetBitNumber(0,tf);};
        void SetRunNr(int x){fnRun =x;};
        void SetVtxPosition(double x, double y, double z){fVtxPosition.SetXYZ(x,y,z);};
        void SetVtxPromptPosition(double x, double y, double z){fVtxPromptPosition.SetXYZ(x,y,z);};
        void SetLifetime(double x){fLifetime=x;};
        void SetPromptLifetime(double x){fPromptLifetime=x;};

        bool GetThreeGammaGen(){return fGenGammaNum.TestBitNumber(2);};
        bool GetTwoGammaGen(){return fGenGammaNum.TestBitNumber(1);};
        bool GetPromptGammaGen(){return fGenGammaNum.TestBitNumber(0);};
        int GetRunNr(){return fnRun;};
        double GetVtxPositionX(){return fVtxPosition.X();};
        double GetVtxPositionY(){return fVtxPosition.Y();};
        double GetVtxPositionZ(){return fVtxPosition.Z();};
        double GetVtxPromptPositionX(){return fVtxPromptPosition.X();};
        double GetVtxPromptPositionY(){return fVtxPromptPosition.Y();};
        double GetVtxPromptPositionZ(){return fVtxPromptPosition.Z();};

        double GetLifetime(){return fLifetime;};
        double GetPromptLifetime(){return fPromptLifetime;};


    private:
      const unsigned int fMaxGammaNumberIndex = 3;
        TVector3 fVtxPosition; ///< xyz annihilation coordinated
        TVector3 fVtxPromptPosition; ///< xyz of prompt photon emmision
        TBits fGenGammaNum; ///< bitNR 0-prompt; 1-back-to-back; 2- oPs 
        int fnRun; ///< number should follow the JPet run numbering scheme
        double fLifetime; ///< lifetime of generated bound state or direct annihilation; see specific simulation details
        double fPromptLifetime; ///< generated lifetime of emmited prompt photon; filled only if prompt gamma is generated

    private:
     ClassDef(JPetGeantEventInformation,3)

};


#endif

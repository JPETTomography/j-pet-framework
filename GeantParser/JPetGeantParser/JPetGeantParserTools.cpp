/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetGeantParserTools.cpp
 */

#include <JPetGeantParser/JPetGeantParserTools.h>
#include<TRandom3.h>
#include<TMath.h>

JPetMCHit JPetGeantParserTools::createJPetMCHit(JPetGeantScinHits* geantHit, const JPetParamBank& paramBank  )
{

    JPetMCHit mcHit = JPetMCHit(
            0,//UInt_t MCDecayTreeIndex,
            0,//UInt_t MCVtxIndex,
            geantHit->GetEneDepos(), //  keV 
            geantHit->GetTime(),   //  ps   
            geantHit->GetHitPosition(),
            geantHit->GetPolarizationIn(),
            geantHit->GetMomentumIn()
            );


    JPetScin& scin =  paramBank.getScintillator(geantHit->GetScinID()); 
    mcHit.setScintillator(scin);

    return mcHit;
}


JPetHit JPetGeantParserTools::reconstructHit(JPetMCHit& mcHit,const JPetParamBank& paramBank, const float timeShift, const float z_resolution )
{
    JPetHit hit = dynamic_cast<JPetHit&>(mcHit);
    hit.setEnergy( addEnergySmearing(mcHit.getEnergy()) );
    // adjust to time window and smear
    hit.setTime( addTimeSmearing( -(mcHit.getTime()-timeShift)  ,mcHit.getEnergy()) );

    auto radius = paramBank.getScintillator(mcHit.getScintillator().getID()).getBarrelSlot().getLayer().getRadius();
    auto theta = TMath::DegToRad() * paramBank.getScintillator(mcHit.getScintillator().getID()).getBarrelSlot().getTheta();
    hit.setPosX(radius * std::cos(theta));
    hit.setPosY(radius * std::sin(theta));
    hit.setPosZ( addZHitSmearing(hit.getPosZ(), z_resolution) );

    return hit;
}

float JPetGeantParserTools::addZHitSmearing(float zIn, float z_res)
{
    std::unique_ptr<TRandom3> random(new TRandom3(0));

    return random->Gaus(zIn,z_res);
}

float JPetGeantParserTools::addEnergySmearing(float eneIn)
{
    // eneIn in keV
    float alpha = 0.044/sqrt(eneIn/1000.);
    std::unique_ptr<TRandom3> random(new TRandom3(0));

    return eneIn + alpha*eneIn*random->Gaus(0,1);
}

float JPetGeantParserTools::addTimeSmearing(float timeIn, float eneIn)
{
    // eneIn in keV, timeIn in ps
    float time;
    std::unique_ptr<TRandom3> random(new TRandom3(0));

    if ( eneIn > 200 ) {
        time = timeIn + 80*random->Gaus(0,1);
    } else {
        time = timeIn+  80*random->Gaus(0,1)/sqrt(eneIn/270);
    }

    return time;
}

bool JPetGeantParserTools::isHitReconstructed(JPetHit& hit, const float th)
{
    bool isOk = true;
    if( hit.getEnergy() < th ) isOk = false;

    return isOk;
}

void JPetGeantParserTools::identifyRecoHits(JPetGeantScinHits* geantHit,const JPetHit& recHit,
        bool& isRecPrompt , std::array<bool,2>& isSaved2g, std::array<bool,3>& isSaved3g,
        float& enePrompt, std::array<float,2>& ene2g, std::array<float,3>& ene3g )
{


    // identify generated hits        
    if( geantHit->GetGenGammaMultiplicity() == 1)  
    {
        isRecPrompt = true;
        enePrompt = recHit.getEnergy();
    }

    if( geantHit->GetGenGammaMultiplicity() == 2)
    {
        isSaved2g[ geantHit->GetGenGammaIndex()-1] = true;
        ene2g[ geantHit->GetGenGammaIndex()-1] = recHit.getEnergy();
    }

    if( geantHit->GetGenGammaMultiplicity() == 3)
    {
        isSaved3g[ geantHit->GetGenGammaIndex()-1] = true;
        ene3g[ geantHit->GetGenGammaIndex()-1] = recHit.getEnergy();
    }

}

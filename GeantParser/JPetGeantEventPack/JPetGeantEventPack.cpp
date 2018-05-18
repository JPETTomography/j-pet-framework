#include "JPetGeantEventPack.h"

ClassImp(JPetGeantEventPack)

JPetGeantEventPack::JPetGeantEventPack():
    fMCHits("JPetGeantScinHits",10000), fMCDecayTrees("JPetGeantDecayTree",1000),
    fEvtIndex(0), fHitIndex(0), fMCDecayTreesIndex(0)
{
    fGenInfo = new JPetGeantEventInformation();
}

JPetGeantScinHits* JPetGeantEventPack::ConstructNextHit()
{
  return (JPetGeantScinHits*) fMCHits.ConstructedAt(fHitIndex++);
}


JPetGeantDecayTree* JPetGeantEventPack::ConstructNextDecayTree()
{
  return (JPetGeantDecayTree*) fMCDecayTrees.ConstructedAt(fMCDecayTreesIndex++); 
}


JPetGeantEventPack::~JPetGeantEventPack()
{
    fMCHits.Clear("C");
    fMCDecayTrees.Clear("C");

    fEvtIndex = 0;  
    fHitIndex = 0;
    fMCDecayTreesIndex = 0;

    fGenInfo->Clear();
}

void JPetGeantEventPack::Clear()
{
    fMCHits.Clear("C");
    fMCDecayTrees.Clear("C");

    fEvtIndex = 0;  
    fHitIndex = 0;
    fMCDecayTreesIndex = 0;

    fGenInfo->Clear();
}



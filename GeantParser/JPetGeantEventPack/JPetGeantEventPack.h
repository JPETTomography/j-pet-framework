#ifndef JPETGEANTEVENTPACK_H
#define JPETGEANTEVENTPACK_H

#include <TObject.h>
#include <TVector3.h> 
#include <TClonesArray.h>
#include <TBits.h>
#include <JPetGeantScinHits/JPetGeantScinHits.h>
#include <JPetGeantDecayTree/JPetGeantDecayTree.h>


class JPetGeantEventPack : public TObject
{
    public:
        JPetGeantEventPack();
        ~JPetGeantEventPack();
        void Clear();


        JPetGeantScinHits* ConstructNextHit();
        JPetGeantDecayTree* ConstructNextDecayTree();

        JPetGeantScinHits* GetHit(int i){return dynamic_cast<JPetGeantScinHits*>(fMCHits[i]);};
        JPetGeantDecayTree* GetDecayTree(int i){return dynamic_cast<JPetGeantDecayTree*>(fMCDecayTrees[i]);};

        unsigned int GetNumberOfHits(){ return fHitIndex;};
        unsigned int GetNumberOfDecayTrees(){ return fMCDecayTreesIndex;};
        unsigned int GetEventNumber(){ return fEvtIndex;};
        
        void SetEventNumber(int x){fEvtIndex = x;};
          


    private:
        TClonesArray fMCHits;
        TClonesArray fMCDecayTrees;

        unsigned int fEvtIndex;
        unsigned int fHitIndex;
        unsigned int fMCDecayTreesIndex;

        TBits    fGenInfo; ///< expand those information later; no getter no setter now

        ClassDef(JPetGeantEventPack,1)
};
#endif

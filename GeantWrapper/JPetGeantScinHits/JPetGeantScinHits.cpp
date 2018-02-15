#include "JPetGeantScinHits.h"

ClassImp(JPetGeantScinHits);

JPetGeantScinHits::JPetGeantScinHits()
    :TObject(), fEvtID(0), fScinID(0), fTrackID(0), fTrackPDGencoding(0),
    fNumOfInteractions(0), fEneDep(0), fTime(0), fPosition(0,0,0),
    fPolarizationIn(0,0,0), fPolarizationOut(0,0,0), fMomentumIn(0,0,0), fMomentumOut(0,0,0)
{}


JPetGeantScinHits::JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, 
        int nInter, float ene, float time, TVector3 hit )
    :TObject(), fEvtID(evID), fScinID(scinID), fTrackID(trkID), fTrackPDGencoding(trkPDG),
    fNumOfInteractions(nInter), fEneDep(ene), fTime(time), fPosition(hit),
    fPolarizationIn(0,0,0), fPolarizationOut(0,0,0), fMomentumIn(0,0,0), fMomentumOut(0,0,0)
{}


JPetGeantScinHits::JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, 
        int nInter, float ene, float time, TVector3 hit, 
        TVector3 fPolarizationIn, TVector3 fPolarizationOut,
        TVector3 fMomentumIn, TVector3 fMomentumOut)
    :TObject(), fEvtID(evID), fScinID(scinID), fTrackID(trkID), fTrackPDGencoding(trkPDG),
    fNumOfInteractions(nInter), fEneDep(ene), fTime(time), fPosition(hit),
    fPolarizationIn(fPolarizationIn), fPolarizationOut(fPolarizationOut), fMomentumIn(fMomentumIn), fMomentumOut(fMomentumOut)
{}


JPetGeantScinHits::~JPetGeantScinHits()
{}

void JPetGeantScinHits::Clean()
{
        fEvtID = 0;
        fScinID = 0;
        fTrackID = 0;
        fTrackPDGencoding = 0 ;
        fNumOfInteractions = 0; 
        fEneDep = 0.0;
        fTime = 0.0;
        fPosition = TVector3();
        fPolarizationIn = TVector3();
        fPolarizationOut =TVector3();
        fMomentumIn =TVector3();
        fMomentumOut =TVector3();
}

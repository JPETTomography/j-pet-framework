#ifndef JPETGEANTSCINHITS_H
#define JPETGEANTSCINHITS_H

#include "TObject.h"
#include <vector> 
#include "TVector3.h"




/**
 * \class JPetGeantScinHits
 * \brief class is containing the hits registered in scintillators created by Geant software  
 *
 */
class JPetGeantScinHits : public TObject
{
    public:
        JPetGeantScinHits();

        JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, 
                int nInter, float ene, float time, TVector3 hit); 

        JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, 
                int nInter, float ene, float time, TVector3 hit, 
                TVector3 polIn, TVector3 polOut,
                TVector3 momeIn, TVector3 momeOut);

        void Fill(int evID, int scinID, int trkID, int trkPDG, 
                int nInter, float ene, float time); 


        void Fill(int evID, int scinID, int trkID, int trkPDG, 
                int nInter, float ene, float time, TVector3 hit, 
                TVector3 polIn, TVector3 polOut,
                TVector3 momeIn, TVector3 momeOut);

   
        ~JPetGeantScinHits();

        void Clean();

        // setters 
        void SetEvtID(int x){fEvtID = x;};
        void SetScinID(int x){fScinID =x;};
        void SetTrackID(int x){fTrackID = x;};
        void SetTrackPDG(int x){fTrackPDGencoding=x;};
        void SetNumOfInteractions(int x){fNumOfInteractions=x;};
        void SetEneDepos(float x){fEneDep=x;};
        void SetTime(float x){fTime=x;};

        void SetHitPosition(TVector3 x){fPosition=x;};
        void SetHitPosition(float x, float y, float z){fPosition.SetXYZ(x,y,z);};
        
        void SetPolarizationIn(TVector3 x){fPolarizationIn=x;};
        void SetPolarizationIn(float x, float y, float z){fPolarizationIn.SetXYZ(x,y,z);};

        void SetPolarizationOut(TVector3 x){fPolarizationOut=x;};
        void SetPolarizationOut(float x, float y, float z){fPolarizationOut.SetXYZ(x,y,z);};

        void SetMomentumIn(TVector3 x){fMomentumIn=x;};
        void SetMomentumIn(float x, float y, float z){fMomentumIn.SetXYZ(x,y,z);};

        void SetMomentumOut(TVector3 x){fMomentumOut=x;};
        void SetMomentumOut(float x, float y, float z){fMomentumOut.SetXYZ(x,y,z);};

        // getters
        int GetEvtID(){return fEvtID;};
        int GetScinID(){return fScinID;};
        int GetTrackID(){return fTrackID;};
        int GetTrackPDG(){return fTrackPDGencoding;};
        int GetNumOfInteractions(){return fNumOfInteractions;};
        float GetEneDepos(){return fEneDep;};
        float GetTime(){return fTime;};
        TVector3 GetHitPosition(){return fPosition;};
        TVector3 GetPolarizationIn(){return fPolarizationIn;};
        TVector3 GetPolarizationOut(){return fPolarizationOut;};
        TVector3 GetMomentumIn(){return fMomentumIn;};
        TVector3 GetMomentumOut(){return fMomentumOut;};

    private:
        int fEvtID;
        int fScinID;
        int fTrackID;
        int fTrackPDGencoding;
        int fNumOfInteractions; ///< number of interaction taking place in single scintillator whish was classified as single hit; it may be a big number since electron deposits energy in many steps
        float fEneDep;
        float fTime;
        TVector3 fPosition;
        TVector3 fPolarizationIn;
        TVector3 fPolarizationOut;
        TVector3 fMomentumIn;
        TVector3 fMomentumOut;

        ClassDef(JPetGeantScinHits,1)     
};


#endif

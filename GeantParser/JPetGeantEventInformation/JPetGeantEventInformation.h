#ifndef JPET_GEANT_EVENT_INFORMATION_H
#define JPET_GEANT_EVENT_INFORMATION_H 1

#include "TObject.h"
#include <vector>
#include "TVector3.h" 


class JPetGeantEventInformation : public TObject {
    public:
        JPetGeantEventInformation();
        ~JPetGeantEventInformation();
        void Clear();

        void SetThreeGammaGen(bool tf){fThreeGammaGen=tf;};
        void SetTwoGammaGen(bool tf){fTwoGammaGen=tf;};
        void SetPromptGammaGen(bool tf){fPromptGammaGen=tf;};
        void SetRunNr(int x){fnRun =x;};
        void SetVtxPosition(double x, double y, double z){fVtxPosition.SetXYZ(x,y,z);};
        void SetVtxPromptPosition(double x, double y, double z){fVtxPromptPosition.SetXYZ(x,y,z);};
        void SetLifetime(double x){fLifetime=x;};
        void SetPromptLifetime(double x){fPromptLifetime=x;};

        bool GetThreeGammaGen(){return fThreeGammaGen;};
        bool GetTwoGammaGen(){return fTwoGammaGen;};
        bool GetPromptGammaGen(){return fPromptGammaGen;};
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
        TVector3 fVtxPosition;
        TVector3 fVtxPromptPosition;
        bool fTwoGammaGen;
        bool fThreeGammaGen;
        bool fPromptGammaGen;
        int fnRun;
        double fLifetime;
        double fPromptLifetime;

    private:
     ClassDef(JPetGeantEventInformation,2)

};


#endif

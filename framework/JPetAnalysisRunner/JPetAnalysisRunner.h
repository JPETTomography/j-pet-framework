//
// Created by karol on 12.05.15.
//

#ifndef FRAMEWORK_JPETANALYSISRUNNER_H
#define FRAMEWORK_JPETANALYSISRUNNER_H

#include <TSelector.h>

class TH1F;
class TRandom;
class JPetAnalysisRunner : public TSelector {
public :

    // Define members here
    TH1F   *fH1F;             //! Output histogram
    TRandom *fRandom;  //! Random number generator

    JPetAnalysisRunner();
    virtual ~JPetAnalysisRunner();
    virtual Int_t   Version() const { return 2; }
    virtual void    Begin(TTree *tree){}
    virtual void    SlaveBegin(TTree *tree);
    virtual Bool_t  Process(Long64_t entry);
    virtual void    SetOption(const char *option) { fOption = option; }
    virtual void    SetObject(TObject *obj) { fObject = obj; }
    virtual void    SetInputList(TList *input) { fInput = input; }
    virtual TList  *GetOutputList() const { return fOutput; }
    virtual void    SlaveTerminate(){}
    virtual void    Terminate();

    ClassDef(JPetAnalysisRunner,2);
};


#endif //FRAMEWORK_JPETANALYSISRUNNER_H

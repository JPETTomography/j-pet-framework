/**
 *  @copyright Copyright (c) 2014, Wojciech Krzemien
 *  @file JPetParamBank.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETPARAMBANK_H 
#define JPETPARAMBANK_H 

#include "../JPetScin/JPetScin.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetFEB/JPetFEB.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetTOMB/JPetTOMB.h"
#include <TClonesArray.h>

class JPetParamBank:public TObject {
 public:
  JPetParamBank(); 
  void clear();
  // Scintillators
  inline void addScintillator(JPetScin& scintillator) { new (fScintillators[getScintillatorsSize()]) JPetScin(scintillator); }
  inline const TClonesArray& getScintillators() const { return fScintillators; }
  inline JPetScin& getScintillator(int i) const { return *((JPetScin*)fScintillators[i]); }
  inline int getScintillatorsSize() const { return fScintillators.GetEntries(); }

  // PMs
  inline void addPM(JPetPM& pm) { new (fPMs[getPMsSize()]) JPetPM(pm);}
  inline const TClonesArray& getPMs() const { return fPMs; }
  inline JPetPM& getPM(int i) const { return *((JPetPM*)fPMs[i]);}
  int getPMsSize() const { return fPMs.GetEntries();}

  // FEBs
  inline void addFEB(JPetFEB& kb) { new (fFEBs[getFEBsSize()]) JPetFEB(kb); }
  inline const TClonesArray& getFEBs() const { return fFEBs; }
  inline JPetFEB& getFEB(int i) const { return *((JPetFEB*)fFEBs[i]); }
  inline int getFEBsSize() const { return fFEBs.GetEntries();}

  // TRBs
  inline void addTRB(JPetTRB& trb) { new (fTRBs[getTRBsSize()]) JPetTRB(trb);}
  inline const TClonesArray& getTRBs() const {return fTRBs;}
  inline JPetTRB& getTRB(int i) const { return *((JPetTRB*)fTRBs[i]);}
  inline int getTRBsSize() const { return fTRBs.GetEntries();}

  // TOMB
  inline void setTOMB(JPetTOMB& tomb) { fTOMB = tomb;}
  inline JPetTOMB getTOMB() const { return fTOMB; }
  inline JPetTOMB* getTOMBAddress() { return &fTOMB; } /// @todo to remove
 private:
  TClonesArray fScintillators;
  TClonesArray fPMs;
  TClonesArray fFEBs;
  TClonesArray fTRBs;
  JPetTOMB fTOMB;
  ClassDef (JPetParamBank, 1);
};
#endif /*  !JPETPARAMBANK_H */

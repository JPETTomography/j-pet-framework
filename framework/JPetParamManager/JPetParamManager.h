#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include "../../JPetLoggerInclude.h"
#include "../JPetScin/JPetScin.h"
#include <TClonesArray.h>
#include "../JPetWriter/JPetWriter.h"
#include "../JPetReader/JPetReader.h"

class JPetParamManager
{
public:
  JPetParamManager();
  JPetParamManager(const char* dBConfigFile);
  void readFile(const char* file_name);
  //int getTRBNumber(int i) const { return fTRBNumbers[i]; }
  //int getScinNumber(int i) const { return fScinNumbers[i]; }
  //int getDataSize() const { assert(fTRBNumbers.size() == fScinNumbers.size()); return fTRBNumbers.size() ;}

  bool setWriter(JPetWriter* writer);
  bool setReader(JPetReader* reader);

  // Scintillators
  void addScintillator(JPetScin& scintillator) {
    new (fScintillators[fScintillatorsSize++]) JPetScin(scintillator);
  }
  inline const TClonesArray& getScintillators() const {
    return fScintillators;
  }
  //inline JPetScin & operator[](int i) const { return *((JPetScin*)fScintillators[i]); }
  inline JPetScin& getScintillator(int i) const {
    return *((JPetScin*)fScintillators[i]);
  }
  int getScintillatorsSize() const {
    return fScintillatorsSize;
  }

  // PMs
  void addPM(JPetPM& pm) {
    new (fPMs[fPMsSize++]) JPetPM(pm);
  }
  inline const TClonesArray& getPMs() const {
    return fPMs;
  }
  //inline JPetPM & operator[](int i) const { return *((JPetPM*)fPMs[i]); }
  inline JPetPM& getPM(int i) const {
    return *((JPetPM*)fPMs[i]);
  }
  int getPMsSize() const {
    return fPMsSize;
  }

  // KBs
  void addKB(JPetFEB& kb) {
    new (fKBs[fKBsSize++]) JPetFEB(kb);
  }
  inline const TClonesArray& getKBs() const {
    return fKBs;
  }
  //inline JPetFEB & operator[](int i) const { return *((JPetFEB*)fKBs[i]); }
  inline JPetFEB& getKB(int i) const {
    return *((JPetFEB*)fKBs[i]);
  }
  int getKBsSize() const {
    return fKBsSize;
  }

  // TRBs
  void addTRB(JPetTRB& trb) {
    new (fTRBs[fTRBsSize++]) JPetTRB(trb);
  }
  inline const TClonesArray& getTRBs() const {
    return fTRBs;
  }
  //inline JPetTRB & operator[](int i) const { return *((JPetTRB*)fTRBs[i]); }
  inline JPetTRB& getTRB(int i) const {
    return *((JPetTRB*)fTRBs[i]);
  }
  int getTRBsSize() const {
    return fTRBsSize;
  }

  // TOMB
  void setTOMB(JPetTOMB& tomb) {
    new (fTOMB[fTOMBSize++]) JPetTOMB(tomb);
  }
  inline JPetTOMB& getTOMB() const {
    return *((JPetTOMB*)fTOMB[0]);
  }
  int getTOMBSize() const {
    return fTOMBSize;  // only 0 or 1
  }

  /*void addScintillator(JPetScin &scintillator);
  std::vector<JPetScin*> getScintillators();
  JPetScin* getScintillator(int i);
  int getScintillatorsSize() const { return fScintillators.size(); }*/

  /*void addPM(JPetPM &pm);
  std::vector<JPetPM*> getPMs();
  JPetPM* getPM(int i);
  int getPMsSize() const { return fPMs.size(); }*/

  /*void addKB(JPetFEB &kb);
  std::vector<JPetFEB*> getKB();
  JPetFEB* getKB(int i);
  int getKBsSize() const { return fKBs.size(); }*/

  /*void addTRB(JPetTRB &trb);
  std::vector<JPetTRB*> getTRB();
  JPetTRB* getTRB(int i);
  int getTRBsSize() const { return fTRBs.size(); }*/

  /*void setTOMB(JPetTOMB &tomb);
  JPetTOMB* getTOMB();*/

  bool writerAllContainers   (const char* fileName);
  bool readAllContainers     (const char* fileName);

  void fillScintillators     (const int p_run_id);
  void fillPMs               (const int p_run_id);
  void fillKBs               (const int p_run_id);
  void fillTRBs              (const int p_run_id);
  void fillTOMB              (const int p_run_id);

  void fillAllContainers     (const int p_run_id);

  void fillScintillatorsTRefs(void);
  void fillPMsTRefs          (void);
  void fillKBsTRefs          (void);
  void fillTRBsTRefs         (void);

  void fillAllTRefs          (void);

private:
  //std::vector<int> fTRBNumbers;
  //std::vector<int> fScinNumbers;
  JPetWriter* fWriter;
  JPetReader* fReader;

  int fScintillatorsSize;
  TClonesArray fScintillators;
  int fPMsSize;
  TClonesArray fPMs;
  int fKBsSize;
  TClonesArray fKBs;
  int fTRBsSize;
  TClonesArray fTRBs;
  int fTOMBSize;
  TClonesArray fTOMB;	// for one run it is only one TOMB module

  //std::vector<JPetScin*> fScintillators;
  //std::vector<JPetPM*> fPMs;
  //std::vector<JPetFEB*> fKBs;
  //std::vector<JPetTRB*> fTRBs;
  //JPetTOMB* fTOMB;		//for one run it is only one TOMB module
};

#endif

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
  void readFile(const char* file_name); /// @todo what file ???

  bool setWriter(JPetWriter* writer);
  bool setReader(JPetReader* reader);

  // Scintillators
  inline void addScintillator(JPetScin& scintillator) { new (fScintillators[fScintillatorsSize++]) JPetScin(scintillator); }
  inline const TClonesArray& getScintillators() const { return fScintillators; }
  inline JPetScin& getScintillator(int i) const { return *((JPetScin*)fScintillators[i]); }
  inline int getScintillatorsSize() const { return fScintillatorsSize; }

  // PMs
  inline void addPM(JPetPM& pm) { new (fPMs[fPMsSize++]) JPetPM(pm);}
  inline const TClonesArray& getPMs() const { return fPMs; }
  inline JPetPM& getPM(int i) const { return *((JPetPM*)fPMs[i]);}
  int getPMsSize() const { return fPMsSize;}

  // KBs
  inline void addKB(JPetFEB& kb) { new (fKBs[fKBsSize++]) JPetFEB(kb); }
  inline const TClonesArray& getKBs() const { return fKBs; }
  inline JPetFEB& getKB(int i) const { return *((JPetFEB*)fKBs[i]); }
  inline int getKBsSize() const { return fKBsSize;}

  // TRBs
  inline void addTRB(JPetTRB& trb) { new (fTRBs[fTRBsSize++]) JPetTRB(trb);}
  inline const TClonesArray& getTRBs() const {return fTRBs;}
  inline JPetTRB& getTRB(int i) const { return *((JPetTRB*)fTRBs[i]);}
  inline int getTRBsSize() const { return fTRBsSize;}

  // TOMB
  inline void setTOMB(JPetTOMB& tomb) { new (fTOMB[fTOMBSize++]) JPetTOMB(tomb);}
  inline JPetTOMB& getTOMB() const { return *((JPetTOMB*)fTOMB[0]); }
  inline int getTOMBSize() const { return fTOMBSize; }// only 0 or 1

  bool writerAllContainers   (const char* fileName);
  bool readAllContainers     (const char* fileName);

  void getParametersFromDatabase(const int run);
  void clearAllContainers();

 private:
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

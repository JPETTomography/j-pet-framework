#ifndef _JPETPHYSSIGWRITER_H_
#define _JPETPHYSDIGWRITER_H_

#include "../JPetReader/JPetReader.h"
#include "../JPetSignal/JPetSignal.h"

#include "TFile.h"
#include "TTree.h"

#include <cstddef>
#include <vector>

class JPetPhysSigReader: public JPetReader{
  
  public:
 
  JPetPhysSigReader();
  JPetPhysSigReader(const char* filename);
  ~JPetPhysSigReader();
  void CloseFile();
  long long GetEntries() const;
  int GetEntry(int number);
  JPetSignal* GetSignal() const {return fSignal;}
  void OpenFile(const char* filename);

  protected:
  
  JPetSignal* fSignal;
  TBranch* fBranch;
  TFile* fFile;
  TTree* fTree;

};

#endif

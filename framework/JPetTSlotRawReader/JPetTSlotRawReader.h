#ifndef _JPETPHYSSIGWRITER_H_
#define _JPETPHYSDIGWRITER_H_

#include "../JPetReader/JPetReader.h"
#include "../JPetTSlot/JPetTSlot.h"

#include "TFile.h"
#include "TTree.h"

#include <cstddef>
#include <vector>

class JPetTSlotRawReader: public JPetReader{
  
  public:
 
  JPetTSlotRawReader();
  JPetTSlotRawReader(const char* filename);
  virtual ~JPetTSlotRawReader();
  void CloseFile();
  long long GetEntries() const;
  int GetEntry(int number);
  inline JPetTSlot* GetTSlot() const {return fTSlot;}
  void OpenFile(const char* filename);

  protected:
  
  JPetTSlot* fTSlot;
  TBranch* fBranch;
  TFile* fFile;
  TTree* fTree;

};

#endif

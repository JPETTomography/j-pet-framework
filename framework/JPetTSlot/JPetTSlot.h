#ifndef _JPETTSLOT_H_
#define _JPETTSLOT_H_

#include <vector>
#include <map>
#include <TNamed.h>
#include "../JPetSigCh/JPetSigCh.h"
#include <TClonesArray.h>

class JPetTSlot: public TNamed
{
 public:
 JPetTSlot() : fSigChannels("JPetSigCh", 100)
  {
    SetName("JPetTSlot");
    fSize = 0;
  }

  inline void addCh(JPetSigCh& new_ch) { new (fSigChannels[fSize++]) JPetSigCh(new_ch); }

  inline size_t size() const { return fSigChannels.GetEntries(); }
  inline size_t getNumberOfSigCh() const { return fSigChannels.GetEntries(); }
  inline const TClonesArray & getSigChVect() const { return fSigChannels; }
  inline JPetSigCh * operator[](int index) const { return (JPetSigCh*)fSigChannels[index]; }
  inline unsigned int getIndex() const { return fIndex; }
  inline void setIndex(unsigned int index) { fIndex = index; }

  virtual ~JPetTSlot() {
    fSigChannels.Delete();
  }

  ClassDef(JPetTSlot, 1);
 private:
  int fSize;
  TClonesArray fSigChannels;
  unsigned int fIndex;
};

#endif

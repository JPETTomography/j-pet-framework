#ifndef _JPETTSLOT_H_
#define _JPETTSLOT_H_

#include <vector>
#include <map>
#include <TNamed.h>
#include "../JPetSigCh/JPetSigCh.h"


class JPetTSlot: public TNamed
{
 public:
  JPetTSlot() {
    SetName("JPetTSlot");
  }
  JPetTSlot(const std::vector<JPetSigCh>& new_vector): fSigChannels(new_vector) {}

  inline void addCh(const JPetSigCh& new_ch ) { fSigChannels.push_back(new_ch);}

  inline size_t size() const { return fSigChannels.size(); }
  inline size_t getNumberOfSigCh() const { return fSigChannels.size(); }
  inline const std::vector<JPetSigCh>& getSigChVect() const { return fSigChannels; }
  inline const JPetSigCh& operator[](int index) const { return fSigChannels[index]; }

  virtual ~JPetTSlot() {}

  ClassDef(JPetTSlot, 1);
 private:
  std::vector<JPetSigCh> fSigChannels;
};

#endif

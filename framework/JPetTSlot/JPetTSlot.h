#ifndef _JPETTSLOT_H_
#define _JPETTSLOT_H_

#include <vector>
#include <map>
#include <TNamed.h>
#include "../JPetSigCh/JPetSigCh.h"
#include <TClonesArray.h>

/**
 * @brief Data class representing a time window of the TRB board.
 *
 * A single TSlot contains many SigCh objects representing TDC hits recorded during a time window of the TRB board. 
 */
class JPetTSlot: public TNamed
{
 public:
 JPetTSlot() : fSigChannels("JPetSigCh", 100)
  {
    SetName("JPetTSlot");
    fSize = 0;
  }

  void AddCh(JPetSigCh& new_ch);

  inline size_t Size() const { return fSigChannels.GetEntries(); }
  inline size_t GetNumberOfSigCh() const { return fSigChannels.GetEntries(); }
  inline const TClonesArray & getSigChVect() const { return fSigChannels; }
  /**
   * @brief Get i-th SigCh object from this time window as if from an array
   *
   * @param i number of SigCh object to be returned; i should be between 0 and getNumberOfSigCh-1 
   */
  inline JPetSigCh & operator[](int i) const { return *((JPetSigCh*)fSigChannels[i]); }
  /**
   * @brief Get the index number of this TSlot
   *
   * Each TSlot (time window) in a HLD file is assigned an index number, counting from first TSlot in the file. This number may be useful if empty TSlots are skipped during analysis.
   */
  inline unsigned int GetIndex() const { return fIndex; }

  /**
   * @brief Get the index number of this TSlot
   *
   * Each TSlot (time window) in a HLD file is assigned an index number, counting from first TSlot in the file. This number may be useful if empty TSlots are skipped during analysis.
   * @oaram index a squential number of this TSlot counting from sirst TSlot in a HLD file
   */
  inline void SetIndex(unsigned int index) { fIndex = index; }
  
  virtual ~JPetTSlot() {
    //    fSigChannels.Clear("C");
  }

  ClassDef(JPetTSlot, 1);

 private:
  int fSize;
  TClonesArray fSigChannels;
  unsigned int fIndex; ///< sequential number of this TSlot in the HLD file
};

#endif

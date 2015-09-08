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
/// @todo think about changing TClonesArray to something else ? what about cleaning
  JPetTSlot()
  {
    SetName("JPetTSlot");
  }

  void addCh(JPetSigCh& new_ch);

  inline size_t size() const {
    return fSigChannels.size();
  }
  inline size_t getNumberOfSigCh() const {
    return fSigChannels.size();
  }
  inline const std::vector<JPetSigCh*>& getSigChVect() const {
    return fSigChannels;
  }
  /**
   * @brief Get i-th SigCh object from this time window as if from an array
   *
   * @param i number of SigCh object to be returned; i should be between 0 and getNumberOfSigCh-1
   */
  inline JPetSigCh& operator[](int i) const {
    return *((JPetSigCh*)fSigChannels[i]);
  }


  virtual ~JPetTSlot() {
    //    fSigChannels.Clear("C");
  }

  /**
   * @brief Get the index number of this TSlot
   *
   * Each TSlot (time window) in a HLD file is assigned an index number, counting from first TSlot in the file. This number may be useful if empty TSlots are skipped during analysis.
   * @oaram index a squential number of this TSlot counting from sirst TSlot in a HLD file
   */
  inline unsigned int getIndex() const { return fIndex; }

  inline void setIndex(unsigned int index) { fIndex = index; }

  ClassDef(JPetTSlot, 1);

private:
  std::vector<JPetSigCh*> fSigChannels; 
  unsigned int fIndex; ///< sequential number of this TSlot in the HLD file
};

#endif

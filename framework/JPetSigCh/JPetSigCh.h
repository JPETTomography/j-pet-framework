#ifndef _JPETSIGCH_H_
#define _JPETSIGCH_H_


#include <cassert>
#include <vector>
#include <map>
#include <TClass.h>

#include "../JPetPM/JPetPM.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetTRB/JPetTRB.h"
#include "../../JPetLoggerInclude.h"



class JPetSigCh: public TNamed
{

 public:
  enum EdgeType { kRising, kFalling };
  typedef std::map < EdgeType, float > SingleCh;
  typedef std::vector < SingleCh > ChSet;

  /// @warning here I dont know who should be the owner of JPetTRB etc elements
  friend void my_swap(JPetSigCh& first, JPetSigCh& second) {
    using std::swap;
    swap(first.fAmpl, second.fAmpl);
    swap(first.fChannels, second.fChannels);
    swap(first.fIsSlow, second.fIsSlow);
    swap(first.fPM, second.fPM);
    swap(first.fScin, second.fScin);
    swap(first.fBarrelSlot, second.fBarrelSlot);
  }

  JPetSigCh() { init(); }
  JPetSigCh(const JPetSigCh& obj);
  /// @todo must be added~JPetSigCh();
  JPetSigCh& operator= (const JPetSigCh obj);
  JPetSigCh(float EdgeTime, float FallEdgeTime = 0);
  inline bool isSlow() const { return fIsSlow; }
  inline size_t size() const { return fChannels.size(); }
  inline float getAmpl() const { return fAmpl; }
  /**
   * @warning This method may cause seg fault, when is called with kFalling as first argument and object is of type "slow".
   */
  float getTime(EdgeType type = kRising, int ch_no = 0) const;
  inline const JPetPM& getPM() const { /*assert(fPM != NULL);*/ return *fPM; }
  inline const JPetTRB& getTRB() const { /*assert(fTRB != NULL);*/ return *fTRB; }
  inline const JPetScin& getScin() const { /*assert(fScin != NULL);*/ return *fScin; }
  inline const JPetBarrelSlot& getBarrelSlot() const { /*assert(fBarrelSlot != NULL);*/ return *fBarrelSlot; }
  inline const ChSet& getChSet() const { return fChannels; }
  void addCh(float edge_time, float fall_edge_time);
  inline void setPM(const JPetPM& pm) { set(&fPM, pm); }
  inline void setTRB(const JPetTRB& trb) { set(&fTRB, trb); }
  inline void setScin(const JPetScin& scin) { set(&fScin, scin); }
  inline void setBarrelSlot(const JPetBarrelSlot& barrel_slot) { set(&fBarrelSlot, barrel_slot); }


  ClassDef(JPetSigCh, 1);

 protected:
  float fAmpl;
  ChSet fChannels;
  bool fIsSlow;
  JPetPM* fPM;
  JPetTRB* fTRB;
  JPetScin* fScin;
  JPetBarrelSlot* fBarrelSlot;

  template <class T> void set(T** dest, const T& source) throw(bad_alloc);
  void init();
};

#endif

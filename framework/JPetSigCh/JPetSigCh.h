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
  typedef std::pair < float, float > Channels;

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
  inline float getAmpl() const { return fAmpl; }
  /**
   * @warning This method may cause seg fault, when is called with kFalling as first argument and object is of type "slow".
   */
  inline JPetPM getPM() const { return fPM; }
  inline JPetTRB getTRB() const {return fTRB; }
  inline JPetScin getScin() const { return fScin; }
  inline JPetBarrelSlot getBarrelSlot() const { return fBarrelSlot; }

  float getTime(EdgeType type) const ;
  
  inline Channels getChannels() const { return fChannels; }
  void addCh(float rise_edge_time, float fall_edge_time);
  inline void setPM(const JPetPM& pm) { fPM = pm; }
  inline void setTRB(const JPetTRB& trb) { fTRB = trb; }
  inline void setScin(const JPetScin& scin) { fScin = scin; }
  inline void setBarrelSlot(const JPetBarrelSlot& barrel_slot) { fBarrelSlot = barrel_slot; }

  ClassDef(JPetSigCh, 1);

 protected:
  float fAmpl;
  Channels fChannels; /// fChannels.first is rising edge and fChannels.second is falling edge
  bool fIsSlow;
  JPetPM fPM;
  JPetTRB fTRB;
  JPetScin fScin;
  JPetBarrelSlot fBarrelSlot;

  template <class T> void set(T** dest, const T& source) throw(std::bad_alloc);
  void init();
};

#endif

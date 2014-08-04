#ifndef _JPETSIGCH_H_
#define _JPETSIGCH_H_

#include <cassert>
#include <vector>
#include <TClass.h>
#include <TRef.h>

#include "../JPetPM/JPetPM.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetKB/JPetKB.h"
#include "../../JPetLoggerInclude.h"


/**
 * @brief Class respresenting a SIGnal from a single tdc CHannel.
 *
 * Contains either time corresponding to a single threshold and slpe type of a frontend board or charge from a single PM (if available in a given setup). 
 */
class JPetSigCh: public TNamed
{
public:
enum EdgeType { kRising, kFalling, kCharge };
const static float kTimeUnset;

JPetSigCh() { Init(); }
JPetSigCh(EdgeType Edge, float EdgeTime);
~JPetSigCh() {}

/**
 * @brief Used to obtain the time or charge carried by the TDC signal.
 *
 * @return either time with respect to beginning of the time window [ps] (TSlot) or charge (if getType()==kCharge)
 */
  inline float GetValue() const { return fValue; }

  /**
   * @brief Used to obtain the type of the signal information
   *
   * Rising edge, falling edge or charge (kCharge)
   */
  inline EdgeType GetType() const { return fType; }

  inline JPetPM * GetPM() const { return (JPetPM*) fPM.GetObject(); }
  inline JPetTRB * GetTRB() const {return (JPetTRB*) fTRB.GetObject(); }
  inline JPetKB * GetKB() const {return (JPetKB*) fKB.GetObject(); }

/**
 * Returns true if the value of the signal represents charge information (integral of the signal calculated by front-end board)
 */
  bool IsCharge() const ;
 
/**
 * Returns true if the value of the signal represents time information from the TDC
 */
  bool IsTime() const ;

  inline void SetPM(JPetPM * pm) { fPM.SetObject( pm ); }
  inline void SetTRB(JPetTRB * trb) { fTRB.SetObject( trb ); }
  inline void SetKB(JPetKB * kb) { fKB.SetObject( kb ); }
  // Set time wrt beginning of TSlot [ps] or charge
  inline void SetValue( float val ) { fValue = val; }
  inline void SetType( EdgeType type ) { fType = type; }

  inline void SetPMID( Int_t pmid ) { fPMID = pmid; }
  inline void SetThreshold( float thr ) { fThreshold = thr; }
  inline void SetDAQch( Int_t daqch ) { fDAQch = daqch; }
  
  inline Int_t GetPMID() const { return fPMID; }
  inline float GetThreshold() const { return fThreshold; }
  inline Int_t GetDAQch() const { return fDAQch; }

  /**
   * @brief Compares this SigCh with another by their threshold value
   *
   * This method overrides TObject::Compare, see its reference.
   */
  Int_t Compare(const TObject* obj) const;
  inline Bool_t IsSortable() const { return true; }
  

  ClassDef(JPetSigCh, 1);

 protected:
  EdgeType fType; ///< type of the SigCh: kFalling, kRising (time) or kCharge (charge)
  float fValue; ///< main value of the SigCh; either time [ps] (if fType is kRiging or kFalling) or charge (if fType is kCharge)

  // these members can be used for simple analysis
  // if no parametric objects are available
  Int_t fPMID; ///< ID of Photomultiplier
  float fThreshold; ///< value of threshold [mV]
  int fDAQch; ///< Number of DAQ channer from the raw HLD file

  // if parametric objects are available, these references should be used
  // rather than the above members
  TRef fPM;
  TRef fKB;
  TRef fTRB;
  

  /* template <class T> void set(T** dest, const T& source) throw(std::bad_alloc); */
  void Init();
};

#endif

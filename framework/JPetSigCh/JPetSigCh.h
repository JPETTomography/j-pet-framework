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

JPetSigCh() { init(); }
JPetSigCh(EdgeType Edge, float EdgeTime);
~JPetSigCh() {}

/**
 * @brief Used to obtain the time or charge carried by the TDC signal.
 *
 * @return either time with respect to beginning of the time window (TSlot) or charge (if getType()==kCharge)
 */
  inline float getValue() const { return fValue; }

  /**
   * @brief Used to obtain the type of the signal information
   *
   * Rising edge, falling edge or charge (kCharge)
   */
  inline EdgeType getType() const { return fType; }

  inline JPetPM * getPM() const { return (JPetPM*) fPM.GetObject(); }
  inline JPetTRB * getTRB() const {return (JPetTRB*) fTRB.GetObject(); }
  inline JPetKB * getKB() const {return (JPetKB*) fKB.GetObject(); }

/**
 * Returns true if the value of the signal represents charge information (integral of the signal calculated by front-end board)
 */
  bool isCharge() const ;
 
/**
 * Returns true if the value of the signal represents time information from the TDC
 */
  bool isTime() const ;

  inline void setPM(JPetPM * pm) { fPM.SetObject( pm ); }
  inline void setTRB(JPetTRB * trb) { fTRB.SetObject( trb ); }
  inline void setKB(JPetKB * kb) { fKB.SetObject( kb ); }

  inline void setValue( float val ) { fValue = val; }
  inline void setType( EdgeType type ) { fType = type; }

  inline void setPMID( Int_t pmid ) { fPMID = pmid; }
  inline void setThreshold( float thr ) { fThreshold = thr; }
  inline void setDAQch( Int_t daqch ) { fDAQch = daqch; }
  
  inline Int_t getPMID() const { return fPMID; }
  inline float getThreshold() const { return fThreshold; }
  inline Int_t getDAQch() const { return fDAQch; }

  ClassDef(JPetSigCh, 1);

 protected:
  EdgeType fType; ///< type of the SigCh: kFalling, kRising (time) or kCharge (charge)
  float fValue; ///< main value of the SigCh; either time (if fType is kRiging or kFalling) or charge (if fType is kCharge)

  // these members can be used for simple analysis
  // if no parametric objects are available
  Int_t fPMID; ///< ID of Photomultiplier
  float fThreshold; ///< value of threshold
  int fDAQch; ///< Number of DAQ channer from the raw HLD file

  // if parametric objects are available, these references should be used
  // rather than the above members
  TRef fPM;
  TRef fKB;
  TRef fTRB;
  

  /* template <class T> void set(T** dest, const T& source) throw(std::bad_alloc); */
  void init();
};

#endif

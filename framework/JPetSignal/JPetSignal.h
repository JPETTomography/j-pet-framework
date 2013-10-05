/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetSignal.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETSIGNAL_H 
#define JPETSIGNAL_H 

#include "../JPetSigCh/JPetSigCh.h"
#include <TNamed.h>
#include <cassert> 
#include <vector> 

//struct History {
//  History(int hld, int tslot, int channel, int daq):
//    hldID(hld),
//    tslot(t),    
//    chSig(channel),
//    DAQch(DAQ)    
//  { 
//    assert(hldID > 0);
//    assert(hldID > 0);
//    assert(hldID > 0);
//    assert(hldID > 0);
//  }
//  int hldID;
//  int tslot;
//  int chSig;
//  int DAQch;
//};

class JPetSignal: public TNamed {
 public:
  enum Edge {kFalling, kRising};

  JPetSignal();
  JPetSignal(double time, double qual, bool left, const std::vector<JPetSigCh>& falling, const std::vector<JPetSigCh>& rising);  
  virtual ~JPetSignal();
  inline float GetT() const { 
    assert(fTime >= 0);
    return fTime; 
  }
  inline float GetQual() const { 
    assert(fQualityOfTime >= 0);
    return fQualityOfTime; 
  } 
  inline bool IsLeft() const { return fLeft; }
  int GetNTresholds(Edge edge) const;

 private:
  double fTime;
  double fQualityOfTime;
  bool fLeft;
  std::vector<JPetSigCh> fFallingPoints;
  std::vector<JPetSigCh> fRisingPoints;
};
#endif /*  !JPETSIGNAL_H */

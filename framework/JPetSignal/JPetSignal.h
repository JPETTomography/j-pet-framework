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

/// @todo structure mimics the structure History described in the  PET UJ Report 19 ->table 39 (p.18)
struct History: public TObject {
 public:
  History(int hld = 0, int tslot = 0, int channel = 0, int daq = 0) :
  fHldID(hld),
  fTslot(tslot),
  fChSig(channel),
  fDAQch(daq)
{ }
  int fHldID;
  int fTslot;
  int fChSig;
  int fDAQch;
  ClassDef(History,1);
};


/// @todo structure mimics the structure described in the  PET UJ Report 19 ->table 39 (p.18) which is then put into the array trh[2][nTrh]. Personally I dont like it :P
struct ExtendedThreshold {
  ExtendedThreshold() :
  fThreshold(0),
  fTime(0),
  fQuality(0)
{ }
  ExtendedThreshold(History hist, float thres, float time, float qual, const JPetSigCh& sigCh) :
  fThreshold(thres),
  fTime(time),
  fQuality(qual),
  fSigCh(sigCh)
{ }
  History fHistory;
  float fThreshold;
  float fTime;
  float fQuality;
  JPetSigCh fSigCh;
  ClassDef(ExtendedThreshold,1);
};



class JPetSignal: public TNamed
{
 public:
  enum Edge {kFalling, kRising};

  JPetSignal();
  JPetSignal(double time, double qual, bool left, const std::vector<ExtendedThreshold>& falling, const std::vector<ExtendedThreshold>& rising);
  virtual ~JPetSignal();
  inline float GetT() const {
    assert(fTime >= 0);
    return fTime;
  }
  inline float GetQual() const {
    assert(fQualityOfTime >= 0);
    return fQualityOfTime;
  }
  inline bool IsLeft() const {
    return fLeft;
  }
  int GetNTresholds(Edge edge) const;


  inline void setExtendedThreshold(const ExtendedThreshold& thr, Edge edge, int index) {
    assert((edge == kRising) || (edge == kFalling));
    assert(index >= 0);
    assert(index < GetNTresholds( edge));
    if (edge == kRising) {
      fRisingPoints[index] = thr;
    } else {
      fFallingPoints[index] = thr;
    }
  }

  inline ExtendedThreshold getExtendedThreshold(const ExtendedThreshold& thr, Edge edge, int index) const {
    assert((edge == kRising) || (edge == kFalling));
    assert(index >= 0);
    assert(index < GetNTresholds( edge));
    if (edge == kRising) {
      return fRisingPoints.at(index);
    } else {
      return fFallingPoints.at(index);
    }
  }

  inline const std::vector<ExtendedThreshold>& getFallingPoints() const {
    return fFallingPoints;
  }
  inline const std::vector<ExtendedThreshold>& getRisingPoints() const {
    return fRisingPoints;
  }
 private:
  double fTime;
  double fQualityOfTime;
  bool fLeft;
  std::vector<ExtendedThreshold> fFallingPoints;
  std::vector<ExtendedThreshold> fRisingPoints;
  ClassDef(JPetSignal, 1);
};
#endif /*  !JPETSIGNAL_H */

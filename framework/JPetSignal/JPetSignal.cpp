/**
  *  @copyright Copyright (c) 2013, Wojciech Krzemien
  *  @file JPetSignal.cc
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetSignal.h"

ClassImp(JPetSignal);

JPetSignal::JPetSignal() :
  TNamed("JPetSignal", "Signal Structure"),
  fTime(0),
  fQualityOfTime(0),
  fLeft(true),
  fFallingPoints("JPetSigCh", 4),
  fRisingPoints("JPetSigCh", 4),
  fNRising(0),
  fNFalling(0)
{ }

/*
JPetSignal::JPetSignal(double time, double qual, bool left, const std::vector<ExtendedThreshold>& falling, const std::vector<ExtendedThreshold>& rising) :
  TNamed("JPetSignal", "Signal Structure"),
  fTime(time),
  fQualityOfTime(qual),
  fLeft(left),
  fFallingPoints(falling),
  fRisingPoints(rising)
{ }
*/

JPetSignal::~JPetSignal()
{ }

int JPetSignal::GetNPoints(JPetSigCh::EdgeType edge) const
{
  assert((edge == JPetSigCh::kRising) || (edge == JPetSigCh::kFalling));
  if (edge == JPetSigCh::kRising) {
    return fRisingPoints.GetEntries();
  } else {
    return fFallingPoints.GetEntries();
  }
}

void JPetSignal::AddPoint(const JPetSigCh& sigch){
  
  assert((sigch.getType() == JPetSigCh::kRising) || (sigch.getType() == JPetSigCh::kFalling));

  if (sigch.getType() == JPetSigCh::kRising && fNRising < 4) {
    new (fRisingPoints[fNRising++]) JPetSigCh(sigch);
  } else if(fNFalling < 4) {
    new (fFallingPoints[fNFalling++]) JPetSigCh(sigch);
  }
  
}

const TClonesArray & JPetSignal::GetPoints(JPetSigCh::EdgeType edge) const{
  assert((edge == JPetSigCh::kRising) || (edge == JPetSigCh::kFalling));
  if (edge == JPetSigCh::kRising) {
    return fRisingPoints;
  } else {
    return fFallingPoints;
  }
}

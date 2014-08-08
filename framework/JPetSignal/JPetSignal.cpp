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
  fLeadingPoints("JPetSigCh", 4),
  fTrailingPoints("JPetSigCh", 4),
  fNTrailing(0),
  fNLeading(0)
{ }

/*
JPetSignal::JPetSignal(double time, double qual, bool left, const std::vector<ExtendedThreshold>& leading, const std::vector<ExtendedThreshold>& trailing) :
  TNamed("JPetSignal", "Signal Structure"),
  fTime(time),
  fQualityOfTime(qual),
  fLeft(left),
  fLeadingPoints(leading),
  fTrailingPoints(trailing)
{ }
*/

JPetSignal::~JPetSignal()
{ }

int JPetSignal::GetNPoints(JPetSigCh::EdgeType edge) const
{
  assert((edge == JPetSigCh::Trailing) || (edge == JPetSigCh::Leading));
  if (edge == JPetSigCh::Trailing) {
    return fTrailingPoints.GetEntries();
  } else {
    return fLeadingPoints.GetEntries();
  }
}

void JPetSignal::AddPoint(const JPetSigCh& sigch){
  
  assert((sigch.GetType() == JPetSigCh::Trailing) || (sigch.GetType() == JPetSigCh::Leading));
  
  if (sigch.GetType() == JPetSigCh::Trailing && fNTrailing < 4) {
    new (fTrailingPoints[fNTrailing++]) JPetSigCh(sigch);
    fTrailingPoints.Sort();
  } else if(fNLeading < 4) {
    new (fLeadingPoints[fNLeading++]) JPetSigCh(sigch);
    fLeadingPoints.Sort();
  }
  
}

const TClonesArray & JPetSignal::GetPoints(JPetSigCh::EdgeType edge) const{
  assert((edge == JPetSigCh::Trailing) || (edge == JPetSigCh::Leading));
  if (edge == JPetSigCh::Trailing) {
    return fTrailingPoints;
  } else {
    return fLeadingPoints;
  }
}

const JPetSigCh & JPetSignal::GetPoint(int i, JPetSigCh::EdgeType edge) const{
  assert( i>=0 && i<GetNPoints( edge ) );
  
  JPetSigCh * sc = (JPetSigCh*)(GetPoints( edge )[i]);
  return *sc;
}

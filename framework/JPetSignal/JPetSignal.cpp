/**
  *  @copyright Copyright (c) 2013, Wojciech Krzemien
  *  @file JPetSignal.cc
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetSignal.h"

ClassImp(JPetSignal);

JPetSignal::JPetSignal(const int points) :
  TNamed("JPetSignal", "Signal Structure"),
  fTime(0),
  fQualityOfTime(0),
  fLeft(true),
  fLeadingPoints("JPetSigCh", points),
  fTrailingPoints("JPetSigCh", points)
{ }


JPetSignal::~JPetSignal()
{ }

int JPetSignal::getNPoints(JPetSigCh::EdgeType edge) const
{
  assert((edge == JPetSigCh::Trailing) || (edge == JPetSigCh::Leading));
  if (edge == JPetSigCh::Trailing) {
    return fTrailingPoints.GetEntries();
  } else {
    return fLeadingPoints.GetEntries();
  }
}

void JPetSignal::addPoint(const JPetSigCh& sigch, bool sortData){
  
  assert((sigch.getType() == JPetSigCh::Trailing) || (sigch.getType() == JPetSigCh::Leading));
  
  if (sigch.getType() == JPetSigCh::Trailing) {
    new (fTrailingPoints[getNumberOfTrailingEdgePoints()]) JPetSigCh(sigch);
    if (sortData) fTrailingPoints.Sort();
  } else {
    new (fLeadingPoints[getNumberOfLeadingEdgePoints()]) JPetSigCh(sigch);
    if (sortData) fLeadingPoints.Sort();
  }
  
}

const TClonesArray & JPetSignal::getPoints(JPetSigCh::EdgeType edge) const{
  assert((edge == JPetSigCh::Trailing) || (edge == JPetSigCh::Leading));
  if (edge == JPetSigCh::Trailing) {
    return fTrailingPoints;
  } else {
    return fLeadingPoints;
  }
}

const JPetSigCh & JPetSignal::getPoint(int i, JPetSigCh::EdgeType edge) const{
  assert( i >= 0 && i < getNPoints( edge ) );
  
  JPetSigCh * sc = (JPetSigCh*)(getPoints( edge )[i]);
  return *sc;
}

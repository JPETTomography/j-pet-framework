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
  fLeft(true)
{ }


JPetSignal::JPetSignal(double time, double qual, bool left, const std::vector<ExtendedThreshold>& falling, const std::vector<ExtendedThreshold>& rising) :
  TNamed("JPetSignal", "Signal Structure"),
  fTime(time),
  fQualityOfTime(qual),
  fLeft(left),
  fFallingPoints(falling),
  fRisingPoints(rising)
{ }

JPetSignal::~JPetSignal()
{ }

int JPetSignal::GetNTresholds(Edge edge) const
{
  assert((edge == kRising) || (edge == kFalling));
  if (edge == kRising) {
    return fRisingPoints.size();
  } else {
    return fFallingPoints.size();
  }
}


/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetParamBank.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */ 

#include "./JPetParamBank.h"

JPetParamBank::JPetParamBank():
  fScintillators("JPetScin", 100),
  fPMs("JPetPM", 100),
  fFEBs("JPetFEB", 100),
  fTRBs("JPetTRB", 100),
  fTOMB(0,"")
{ /* */}

void JPetParamBank::clear() 
{
  fScintillators.Clear();
  fPMs.Clear();
  fFEBs.Clear();
  fTRBs.Clear();
  fTOMB.Clear();
}

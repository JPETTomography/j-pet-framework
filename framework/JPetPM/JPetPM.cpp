#include "JPetPM.h"

JPetPM::JPetPM():
  fSide(SideA),
  fID(0),
  fHVset(0),
  fHVopt(0),
  fHVgain(std::make_pair(0.0, 0.0))
{
  SetName("JPetPM");
}


ClassImp(JPetPM);

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

JPetPM::JPetPM(Side side, 
	       int id, 
	       int HVset, 
	       int HVopt, 
	       std::pair<float, float> HVgainNumber):
  fSide(side),
  fID(id),
  fHVset(HVset),
  fHVopt(HVopt),
  fHVgain(HVgainNumber)
{
  SetName("JPetPM");
}

JPetPM::~JPetPM()
{
}

ClassImp(JPetPM);

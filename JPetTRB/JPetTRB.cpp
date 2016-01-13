#include "JPetTRB.h"

ClassImp(JPetTRB);

JPetTRB::JPetTRB():
  fID(0), 
  fType(0),
  fChannel(0)
{
  SetName("JPetTRB");
}

JPetTRB::JPetTRB(int id, int type, int ch): 
  fID(id), 
  fType(type),
  fChannel(ch)
{
  SetName("JPetTRB");
}

JPetTRB::~JPetTRB()
{
}

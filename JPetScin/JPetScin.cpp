#include "JPetScin.h"
#include <cassert>


ClassImp(JPetScin);

JPetScin::JPetScin():
fID(0),
fAttenLen(0.0),
fScinSize(0., 0., 0.)
{
  /* */
  SetName("JPetScin");
}

JPetScin::JPetScin(int id, float attenLen, float length, float height, float width):
fID(id),
fAttenLen(attenLen),
fScinSize(length, height, width)
{
  /* */
  SetName("JPetScin");
}

JPetScin::~JPetScin()
{
}

float JPetScin::getScinSize(JPetScin::Dimension dim) const
{
  float value = 0;
  switch (dim) {
  case kLength:
    value = fScinSize.fLength;
    break;
  case kHeight:
    value = fScinSize.fHeight;
    break;
  case kWidth:
    value = fScinSize.fWidth;
    break;
  default:
    assert(1 == 0);
  }
  return value;
}


void JPetScin::setScinSize(JPetScin::Dimension dim, float value)
{
  switch (dim) {
  case kLength:
    fScinSize.fLength = value;
    break;
  case kHeight:
    fScinSize.fHeight = value;
    break;
  case kWidth:
    fScinSize.fWidth = value;
    break;
  default:
    assert(1 == 0);
  }
}

#include "JPetSigCh.h"
#include <limits>

ClassImp(JPetSigCh);

const float JPetSigCh::kTimeUnset = std::numeric_limits<float>::infinity();

void JPetSigCh::init()
{
  SetNameTitle("JPetSigCh", "Signal Channel Structure");
  fValue = kTimeUnset;
}


JPetSigCh::JPetSigCh(EdgeType Edge, float EdgeTime)
{
  init();
  // @todo: perform some sanity checks of the given values
  assert( EdgeTime > 0. );

  fType = Edge;
  fValue = EdgeTime;

}

bool JPetSigCh::isCharge() const{
  if( fType == kCharge ){
    return true;
  }
  return false;
}

bool JPetSigCh::isTime() const{
  if( fType == kRising || fType == kFalling ){
    return true;
  }
  return false;
}

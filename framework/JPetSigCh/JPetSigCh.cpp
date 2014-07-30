#include "JPetSigCh.h"
#include <limits>
#include <cstring>

ClassImp(JPetSigCh);

const float JPetSigCh::kTimeUnset = std::numeric_limits<float>::infinity();

void JPetSigCh::Init()
{
  SetNameTitle("JPetSigCh", "Signal Channel Structure");
  fValue = kTimeUnset;
}


JPetSigCh::JPetSigCh(EdgeType Edge, float EdgeTime)
{
  Init();
  // @todo: perform some sanity checks of the given values
  assert( EdgeTime > 0. );

  fType = Edge;
  fValue = EdgeTime;

}

bool JPetSigCh::IsCharge() const{
  if( fType == kCharge ){
    return true;
  }
  return false;
}

bool JPetSigCh::IsTime() const{
  if( fType == kRising || fType == kFalling ){
    return true;
  }
  return false;
}

Int_t JPetSigCh::Compare(const TObject* obj) const{

  if( strcmp( obj->GetName(), this->GetName()) != 0 ){
    return 0;
  }

  JPetSigCh * that = (JPetSigCh*)obj;

  if( that->GetThreshold() > this->GetThreshold() ){
    return -1;
  }else if( that->GetThreshold() < this->GetThreshold() ){
    return 1;
  }
 
  return 0;
}

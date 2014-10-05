#include "JPetSigCh.h"
#include <limits>
#include <cstring>

ClassImp(JPetSigCh);

const float JPetSigCh::kUnset = std::numeric_limits<float>::infinity();

void JPetSigCh::Init()
{
  SetNameTitle("JPetSigCh", "Signal Channel Structure");
  fValue = kUnset;
  fType = Leading;
  fThreshold = kUnset;
}


JPetSigCh::JPetSigCh(EdgeType Edge, float EdgeTime)
{
  Init();
  /// @todo: perform some sanity checks of the given values
  assert( EdgeTime > 0. );

  fType = Edge;
  fValue = EdgeTime;

}

bool JPetSigCh::IsCharge() const{
  if( fType == Charge ){
    return true;
  }
  return false;
}

bool JPetSigCh::IsTime() const{
  if( fType == Trailing || fType == Leading ){
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
    //  if( that->GetValue() > this->GetValue() ){
    return -1;
  }else if( that->GetThreshold() < this->GetThreshold() ){
    //}else if( that->GetValue() < this->GetValue() ){
    return 1;
  }
  
  return 0;
}

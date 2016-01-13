#include "JPetSigCh.h"
#include <limits>
#include <cstring>

ClassImp(JPetSigCh);

const float JPetSigCh::kUnset = std::numeric_limits<float>::infinity();

void JPetSigCh::Init() {
  SetNameTitle("JPetSigCh", "Signal Channel Structure");
  fValue = kUnset;
  fType = Leading;
  fThreshold = kUnset;
  fThresholdNumber = 0;
}

JPetSigCh::JPetSigCh(EdgeType Edge, float EdgeTime) {
  Init();
  /// @todo: perform some sanity checks of the given values
  assert(EdgeTime > 0.);

  fType = Edge;
  fValue = EdgeTime;

}

bool JPetSigCh::isCharge() const {
  if (fType == Charge) {
    return true;
  }
  return false;
}

bool JPetSigCh::isTime() const {
  if (fType == Trailing || fType == Leading) {
    return true;
  }
  return false;
}

bool JPetSigCh::compareByThresholdValue(const JPetSigCh& A,
                                        const JPetSigCh& B) {
  if (A.getThreshold() < B.getThreshold()) {
    return true;
  }
  return false;
}

bool JPetSigCh::compareByThresholdNumber(const JPetSigCh& A,
                                         const JPetSigCh& B) {
  if (A.getThresholdNumber() < B.getThresholdNumber()) {
    return true;
  }
  return false;
}

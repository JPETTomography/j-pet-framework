#include "FakeParamBank.h"
ClassImp (FakeParamBank);

FakeParamBank::FakeParamBank(): fParams("TestEvent", 100)
{
  fParamList = new TList();
}

FakeParamBank::~FakeParamBank()
{
  if (fParamList) {
    delete fParamList;
    fParamList = 0;
  }
}

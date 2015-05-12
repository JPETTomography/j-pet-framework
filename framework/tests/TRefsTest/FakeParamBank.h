#ifndef FAKEPARAMBANK_H
#define FAKEPARAMBANK_H
#include  "TestEvent.h"
#include <TClonesArray.h>
#include <TNamed.h>
#include <TList.h>
class FakeParamBank: public TObject
{
 public:
  FakeParamBank();
  ~FakeParamBank();
  void addParam(TestEvent& param) {
    new (fParams[getParamsSize()]) TestEvent(param);
  }
  inline const TClonesArray& getParams() const {
    return fParams;
  }
  inline TestEvent& getParam(int i) const {
    return *((TestEvent*)fParams[i]);
  }
  inline int getParamsSize() const {
    return fParams.GetEntries();
  }
  inline TList* getList() {
    return fParamList;
  }

 private:
  TClonesArray fParams;
  TList* fParamList;
  ClassDef (FakeParamBank, 1);
};
#endif

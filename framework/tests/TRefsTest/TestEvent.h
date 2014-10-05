#ifndef _TESTEVENT_
#define _TESTEVENT_

#include <TNamed.h>
#include <TRef.h>

class TestEvent: public TNamed
{
public:
  TestEvent();
  TestEvent(TestEvent* ev, int id);
  int getId() const {
    return fId;
  }
  void setId(int id) {
    fId = id;
  }
  TRef getRef() const {
    return fRef;
  }
  TestEvent* getRefEvent() const {
    return static_cast<TestEvent*>(fRef.GetObject());
  }

  ClassDef (TestEvent, 1);
private:
  int fId;
  TRef fRef;
};

#endif

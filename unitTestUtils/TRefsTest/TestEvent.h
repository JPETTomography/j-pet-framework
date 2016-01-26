#ifndef _TESTEVENT_
#define _TESTEVENT_

#include <TNamed.h>
#include <TRef.h>
#include <vector>

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
  void addSubEvent(const TestEvent& event) { fSubEvents.push_back(event);}
  size_t getNbSubEvents() const { return fSubEvents.size();}
  TestEvent getSubEvent(int index) const { return fSubEvents.at(index);}

  ClassDef (TestEvent, 1);
private:
  int fId;
  TRef fRef;
  std::vector <TestEvent> fSubEvents;
};

#endif

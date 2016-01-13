#include "TestEvent.h"
ClassImp (TestEvent);

TestEvent::TestEvent(): TNamed("TestEvent", "TestEvent"),
  fId(0),
  fRef(0)
{
  /* */
};
TestEvent::TestEvent(TestEvent* ev, int id): TNamed("TestEvent", "TestEvent"),
  fId(id),
  fRef(ev)
{
  /* */
};

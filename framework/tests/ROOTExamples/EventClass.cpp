#include "./EventClass.h"

ClassImp(EventClass);

EventClass::EventClass () :
	TNamed ("EventClass", "EventClass"),
	fParam (0),
	fId (0)//,
	//fScintillatorsSize(0),
	//fScintillators("Scintillators", 100)
{
}

EventClass::EventClass (ParamClass* param, Long_t id) :
	TNamed ("EventClass", "EventClass"),
	fParam (param),
	fId (id)//,
	//fScintillatorsSize(0),
	//fScintillators("Scintillators", 100)
{
  //fParam = param; // tak tez dziala
}

EventClass::~EventClass () {
}

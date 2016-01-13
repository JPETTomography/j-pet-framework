#include "./EventClass.h"

ClassImp(EventClass);

EventClass::EventClass () :
	TNamed ("EventClass", "EventClass"),
	fParam (0),
	fId (0) {
}

EventClass::EventClass (ParamClass* param, Long_t id) :
	TNamed ("EventClass", "EventClass"),
	fParam (param),
	fId (id) {
}

EventClass::~EventClass () {
}

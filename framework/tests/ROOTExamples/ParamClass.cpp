#include "./ParamClass.h"

ClassImp(ParamClass);

ParamClass::ParamClass () : 
	TNamed ("ParamClass", "ParamClass"),
        fInfo (0),
	fId (0),
	simpleField(99)
{
}

ParamClass::ParamClass (const char* info, Long_t id) : 
	TNamed ("ParamClass", "ParamClass"),
        fInfo (new TString(info)),
	fId (id),
	simpleField(99)
{
}

ParamClass::~ParamClass () {
}

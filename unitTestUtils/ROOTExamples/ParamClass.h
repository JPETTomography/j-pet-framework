#ifndef _PARAMCLASS_
#define _PARAMCLASS_

#include <TNamed.h>
#include <TString.h>

class TNamed;
class TString;

class ParamClass : public TNamed {
  
  public:

  ParamClass ();
  ParamClass (const char* info, Long_t id);
  virtual ~ParamClass ();

  TString* GetInfo () { return fInfo; }
  Long_t   GetId () { return fId; }

  ClassDef (ParamClass, 1);

  protected:

  TString*  fInfo;
  Long_t   fId;
  
public: // for test demand
  int simpleField;
};

#endif

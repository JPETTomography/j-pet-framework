#include "./ParamClass.h"

#include <TNamed.h>
#include <TRef.h>

class ParamClass;
class TNamed;

class EventClass : public TNamed {
  
  public:

  EventClass ();
  EventClass (ParamClass* param, Long_t id);
  virtual ~EventClass ();

  ParamClass* GetParam () { return (ParamClass*)fParam.GetObject (); }
  Long_t      GetId ()    { return fId; }

  ClassDef (EventClass, 1);

  protected:

  TRef   fParam;
  Long_t fId;

};

#include "./ParamClass.h"

#include <TNamed.h>
#include <TRef.h>
#include <vector>
//#include <TClonesArray.h>

class ParamClass;
class TNamed;

class EventClass : public TNamed {
  
public:
  
  /******* Simple TRef *******/
  TRef fTRef;
    
  ParamClass* getTRef()
  { 
    return (ParamClass*)fTRef.GetObject();
  }
  
  void setTRef(ParamClass &ref)
  {
    fTRef = &ref;
  }
  
  /******* std::vector<TRef> *******/
  std::vector<TRef> fTRefKBs;
  
  std::vector<TRef> getTRefKBs() const { return fTRefKBs; }

  ParamClass* getTRefKB(int p_index)
  {
    if(p_index < fTRefKBs.size())
    {
      return (ParamClass*)fTRefKBs[p_index].GetObject();
    }
    return NULL;
  }
  
  void setTRefKBs(std::vector<TRef> &p_TRefKBs)
  {
    fTRefKBs = p_TRefKBs;
  }
  
  void addTRefKB(ParamClass &p_KB)
  {
    fTRefKBs.push_back(&p_KB);
  }
  
  /******* TClonesArray TRef *******/
  /*
  int fScintillatorsSize;
  TClonesArray fScintillators; //	cause "*** Break *** segmentation violation" for each tests !!!
  
  void AddCh(ParamClass& new_ch)
  {
    new (fScintillators[fScintillatorsSize++]) ParamClass(new_ch);
  }
  
  inline ParamClass & operator[](int i) const { return *((ParamClass*)fScintillators[i]); }
  
  ParamClass* getfScintillators(int p_index)
  {
    if(p_index < fScintillatorsSize)
    {
      return (ParamClass*)fScintillators[p_index];
    }
    return NULL;
  }
  */
  /**************/
  
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

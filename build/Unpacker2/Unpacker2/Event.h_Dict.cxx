//
// File generated by /home/klara/root-system/bin/rootcint at Tue Dec 20 13:10:25 2016

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME EventdOh_Dict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "Event.h_Dict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"

// Direct notice to TROOT of the dictionary's loading.
namespace {
   static struct DictInit {
      DictInit() {
         ROOT::RegisterModule();
      }
   } __TheDictionaryInitializer;
}

// START OF SHADOWS

namespace ROOTShadow {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOTShadow
// END OF SHADOWS

namespace ROOTDict {
   void Event_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_Event(void *p = 0);
   static void *newArray_Event(Long_t size, void *p);
   static void delete_Event(void *p);
   static void deleteArray_Event(void *p);
   static void destruct_Event(void *p);
   static void streamer_Event(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static ROOT::TGenericClassInfo *GenerateInitInstanceLocal(const ::Event*)
   {
      ::Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Event >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Event", ::Event::Class_Version(), "/home/klara/Studia/III_rok/licencjat/j-pet-framework/Unpacker2/Unpacker2/Event.h", 14,
                  typeid(::Event), ::ROOT::DefineBehavior(ptr, ptr),
                  &::Event::Dictionary, isa_proxy, 0,
                  sizeof(::Event) );
      instance.SetNew(&new_Event);
      instance.SetNewArray(&newArray_Event);
      instance.SetDelete(&delete_Event);
      instance.SetDeleteArray(&deleteArray_Event);
      instance.SetDestructor(&destruct_Event);
      instance.SetStreamerFunc(&streamer_Event);
      return &instance;
   }
   ROOT::TGenericClassInfo *GenerateInitInstance(const ::Event*)
   {
      return GenerateInitInstanceLocal((::Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Event*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOTDict

//______________________________________________________________________________
atomic_TClass_ptr Event::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Event::Class_Name()
{
   return "Event";
}

//______________________________________________________________________________
const char *Event::ImplFileName()
{
   return ::ROOTDict::GenerateInitInstanceLocal((const ::Event*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Event::ImplFileLine()
{
   return ::ROOTDict::GenerateInitInstanceLocal((const ::Event*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void Event::Dictionary()
{
   fgIsA = ::ROOTDict::GenerateInitInstanceLocal((const ::Event*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *Event::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gCINTMutex); if(!fgIsA) {fgIsA = ::ROOTDict::GenerateInitInstanceLocal((const ::Event*)0x0)->GetClass();} }
   return fgIsA;
}

//______________________________________________________________________________
void Event::Streamer(TBuffer &R__b)
{
   // Stream an object of class Event.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> totalNTDCHits;
      R__b >> TDCReferenceTime;
      R__b >> errorBits;
      TDCHits->Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, Event::IsA());
   } else {
      R__c = R__b.WriteVersion(Event::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << totalNTDCHits;
      R__b << TDCReferenceTime;
      R__b << errorBits;
      TDCHits->Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

//______________________________________________________________________________
void Event::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class Event.
      TClass *R__cl = ::Event::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "totalNTDCHits", &totalNTDCHits);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "TDCReferenceTime", &TDCReferenceTime);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "errorBits", &errorBits);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*TDCHits", &TDCHits);
      TNamed::ShowMembers(R__insp);
}

namespace ROOTDict {
   // Wrappers around operator new
   static void *new_Event(void *p) {
      return  p ? new(p) ::Event : new ::Event;
   }
   static void *newArray_Event(Long_t nElements, void *p) {
      return p ? new(p) ::Event[nElements] : new ::Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_Event(void *p) {
      delete ((::Event*)p);
   }
   static void deleteArray_Event(void *p) {
      delete [] ((::Event*)p);
   }
   static void destruct_Event(void *p) {
      typedef ::Event current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Event(TBuffer &buf, void *obj) {
      ((::Event*)obj)->::Event::Streamer(buf);
   }
} // end of namespace ROOTDict for class ::Event

/********************************************************
* Event.h_Dict.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableEventdOh_Dict();

extern "C" void G__set_cpp_environmentEventdOh_Dict() {
  G__cpp_reset_tagtableEventdOh_Dict();
}
#include <new>
extern "C" int G__cpp_dllrevEventdOh_Dict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* Event */
static int G__EventdOh_Dict_194_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   Event* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new Event[n];
     } else {
       p = new((void*) gvp) Event[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new Event;
     } else {
       p = new((void*) gvp) Event;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__EventdOh_DictLN_Event));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((Event*) G__getstructoffset())->AddTDCHit((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((Event*) G__getstructoffset())->AddTDCHitExtended((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((Event*) G__getstructoffset())->SetTDCReferenceTime((float) G__double(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((Event*) G__getstructoffset())->SetErrorBits((UInt_t) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((Event*) G__getstructoffset())->GetTotalNTDCHits());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 102, (double) ((Event*) G__getstructoffset())->GetTDCReferenceTime());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 104, (long) ((Event*) G__getstructoffset())->GetErrorBits());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((Event*) G__getstructoffset())->GetTDCHitsArray());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((Event*) G__getstructoffset())->Clear();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) Event::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) Event::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) Event::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      Event::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((Event*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) Event::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) Event::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_21(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) Event::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__EventdOh_Dict_194_0_22(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) Event::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__EventdOh_Dict_194_0_23(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   Event* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new Event(*(Event*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__EventdOh_DictLN_Event));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef Event G__TEvent;
static int G__EventdOh_Dict_194_0_24(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 1
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (Event*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((Event*) (soff+(sizeof(Event)*i)))->~G__TEvent();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (Event*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((Event*) (soff))->~G__TEvent();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__EventdOh_Dict_194_0_25(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   Event* dest = (Event*) G__getstructoffset();
   *dest = *(Event*) libp->para[0].ref;
   const Event& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* Event */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncEventdOh_Dict {
 public:
  G__Sizep2memfuncEventdOh_Dict(): p(&G__Sizep2memfuncEventdOh_Dict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncEventdOh_Dict::*p)();
};

size_t G__get_sizep2memfuncEventdOh_Dict()
{
  G__Sizep2memfuncEventdOh_Dict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceEventdOh_Dict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__EventdOh_DictLN_Event))) {
     Event *G__Lderived;
     G__Lderived=(Event*)0x1000;
     {
       TNamed *G__Lpbase=(TNamed*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__EventdOh_DictLN_Event),G__get_linked_tagnum(&G__EventdOh_DictLN_TNamed),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__EventdOh_DictLN_Event),G__get_linked_tagnum(&G__EventdOh_DictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableEventdOh_Dict() {

   /* Setting up typedef entry */
   G__search_typename2("Int_t",105,-1,0,-1);
   G__setnewtype(-1,"Signed integer 4 bytes (int)",0);
   G__search_typename2("UInt_t",104,-1,0,-1);
   G__setnewtype(-1,"Unsigned integer 4 bytes (unsigned int)",0);
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__EventdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__EventdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__EventdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__EventdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<std::bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long,const TObject**>",117,G__get_linked_tagnum(&G__EventdOh_DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* Event */
static void G__setup_memvarEvent(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__EventdOh_DictLN_Event));
   { Event *p; p=(Event*)0x1000; if (p) { }
   G__memvar_setup((void*)0,105,0,0,-1,G__defined_typename("Int_t"),-1,4,"totalNTDCHits=",0,(char*)NULL);
   G__memvar_setup((void*)0,102,0,0,-1,-1,-1,4,"TDCReferenceTime=",0,(char*)NULL);
   G__memvar_setup((void*)0,104,0,0,-1,G__defined_typename("UInt_t"),-1,4,"errorBits=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->TDCHits)-(long)(p)),85,0,0,G__get_linked_tagnum(&G__EventdOh_DictLN_TClonesArray),-1,-1,1,"TDCHits=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__EventdOh_DictLN_TClass),G__defined_typename("atomic_TClass_ptr"),-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarEventdOh_Dict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncEvent(void) {
   /* Event */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__EventdOh_DictLN_Event));
   G__memfunc_setup("Event",514,G__EventdOh_Dict_194_0_1, 105, G__get_linked_tagnum(&G__EventdOh_DictLN_Event), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("AddTDCHit",777,G__EventdOh_Dict_194_0_2, 85, G__get_linked_tagnum(&G__EventdOh_DictLN_TDCHit), -1, 0, 1, 1, 1, 0, "i - - 0 - channel", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("AddTDCHitExtended",1594,G__EventdOh_Dict_194_0_3, 85, G__get_linked_tagnum(&G__EventdOh_DictLN_TDCHitExtended), -1, 0, 1, 1, 1, 0, "i - - 0 - channel", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetTDCReferenceTime",1829,G__EventdOh_Dict_194_0_4, 121, -1, -1, 0, 1, 1, 1, 0, "f - - 0 - t", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetErrorBits",1224,G__EventdOh_Dict_194_0_5, 121, -1, -1, 0, 1, 1, 1, 0, "h - 'UInt_t' 0 - err", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetTotalNTDCHits",1509,G__EventdOh_Dict_194_0_6, 105, -1, G__defined_typename("Int_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetTDCReferenceTime",1817,G__EventdOh_Dict_194_0_7, 102, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetErrorBits",1212,G__EventdOh_Dict_194_0_8, 104, -1, G__defined_typename("UInt_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetTDCHitsArray",1426,G__EventdOh_Dict_194_0_9, 85, G__get_linked_tagnum(&G__EventdOh_DictLN_TClonesArray), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Clear",487,G__EventdOh_Dict_194_0_10, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__EventdOh_Dict_194_0_11, 85, G__get_linked_tagnum(&G__EventdOh_DictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&Event::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__EventdOh_Dict_194_0_12, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&Event::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__EventdOh_Dict_194_0_13, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&Event::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__EventdOh_Dict_194_0_14, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&Event::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__EventdOh_DictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__EventdOh_Dict_194_0_18, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - ClassDef_StreamerNVirtual_b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__EventdOh_Dict_194_0_19, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&Event::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__EventdOh_Dict_194_0_20, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&Event::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__EventdOh_Dict_194_0_21, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&Event::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__EventdOh_Dict_194_0_22, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&Event::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("Event", 514, G__EventdOh_Dict_194_0_23, (int) ('i'), G__get_linked_tagnum(&G__EventdOh_DictLN_Event), -1, 0, 1, 1, 1, 0, "u 'Event' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~Event", 640, G__EventdOh_Dict_194_0_24, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__EventdOh_Dict_194_0_25, (int) ('u'), G__get_linked_tagnum(&G__EventdOh_DictLN_Event), -1, 1, 1, 1, 1, 0, "u 'Event' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncEventdOh_Dict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalEventdOh_Dict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {
}

static void G__cpp_setup_func13() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcEventdOh_Dict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
  G__cpp_setup_func13();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__EventdOh_DictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_TNamed = { "TNamed" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_TClonesArray = { "TClonesArray" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR = { "iterator<bidirectional_iterator_tag,TObject*,long,const TObject**,const TObject*&>" , 115 , -1 };
G__linked_taginfo G__EventdOh_DictLN_TDCHit = { "TDCHit" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_TDCHitExtended = { "TDCHitExtended" , 99 , -1 };
G__linked_taginfo G__EventdOh_DictLN_Event = { "Event" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableEventdOh_Dict() {
  G__EventdOh_DictLN_TClass.tagnum = -1 ;
  G__EventdOh_DictLN_TBuffer.tagnum = -1 ;
  G__EventdOh_DictLN_TMemberInspector.tagnum = -1 ;
  G__EventdOh_DictLN_TObject.tagnum = -1 ;
  G__EventdOh_DictLN_TNamed.tagnum = -1 ;
  G__EventdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__EventdOh_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__EventdOh_DictLN_TClonesArray.tagnum = -1 ;
  G__EventdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__EventdOh_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__EventdOh_DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR.tagnum = -1 ;
  G__EventdOh_DictLN_TDCHit.tagnum = -1 ;
  G__EventdOh_DictLN_TDCHitExtended.tagnum = -1 ;
  G__EventdOh_DictLN_Event.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableEventdOh_Dict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_TClass);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_TObject);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_TNamed);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_TClonesArray);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_TDCHit);
   G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_TDCHitExtended);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__EventdOh_DictLN_Event),sizeof(Event),-1,62720,(char*)NULL,G__setup_memvarEvent,G__setup_memfuncEvent);
}
extern "C" void G__cpp_setupEventdOh_Dict(void) {
  G__check_setup_version(30051515,"G__cpp_setupEventdOh_Dict()");
  G__set_cpp_environmentEventdOh_Dict();
  G__cpp_setup_tagtableEventdOh_Dict();

  G__cpp_setup_inheritanceEventdOh_Dict();

  G__cpp_setup_typetableEventdOh_Dict();

  G__cpp_setup_memvarEventdOh_Dict();

  G__cpp_setup_memfuncEventdOh_Dict();
  G__cpp_setup_globalEventdOh_Dict();
  G__cpp_setup_funcEventdOh_Dict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncEventdOh_Dict();
  return;
}
class G__cpp_setup_initEventdOh_Dict {
  public:
    G__cpp_setup_initEventdOh_Dict() { G__add_setup_func("EventdOh_Dict",(G__incsetup)(&G__cpp_setupEventdOh_Dict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initEventdOh_Dict() { G__remove_setup_func("EventdOh_Dict"); }
};
G__cpp_setup_initEventdOh_Dict G__cpp_setup_initializerEventdOh_Dict;


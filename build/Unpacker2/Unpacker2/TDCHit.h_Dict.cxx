//
// File generated by /home/klara/root-system/bin/rootcint at Tue Dec 20 13:10:25 2016

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME TDCHitdOh_Dict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "TDCHit.h_Dict.h"

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
   void TDCHit_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_TDCHit(void *p = 0);
   static void *newArray_TDCHit(Long_t size, void *p);
   static void delete_TDCHit(void *p);
   static void deleteArray_TDCHit(void *p);
   static void destruct_TDCHit(void *p);
   static void streamer_TDCHit(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static ROOT::TGenericClassInfo *GenerateInitInstanceLocal(const ::TDCHit*)
   {
      ::TDCHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDCHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TDCHit", ::TDCHit::Class_Version(), "/home/klara/Studia/III_rok/licencjat/j-pet-framework/Unpacker2/Unpacker2/TDCHit.h", 8,
                  typeid(::TDCHit), ::ROOT::DefineBehavior(ptr, ptr),
                  &::TDCHit::Dictionary, isa_proxy, 0,
                  sizeof(::TDCHit) );
      instance.SetNew(&new_TDCHit);
      instance.SetNewArray(&newArray_TDCHit);
      instance.SetDelete(&delete_TDCHit);
      instance.SetDeleteArray(&deleteArray_TDCHit);
      instance.SetDestructor(&destruct_TDCHit);
      instance.SetStreamerFunc(&streamer_TDCHit);
      return &instance;
   }
   ROOT::TGenericClassInfo *GenerateInitInstance(const ::TDCHit*)
   {
      return GenerateInitInstanceLocal((::TDCHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TDCHit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOTDict

//______________________________________________________________________________
atomic_TClass_ptr TDCHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TDCHit::Class_Name()
{
   return "TDCHit";
}

//______________________________________________________________________________
const char *TDCHit::ImplFileName()
{
   return ::ROOTDict::GenerateInitInstanceLocal((const ::TDCHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TDCHit::ImplFileLine()
{
   return ::ROOTDict::GenerateInitInstanceLocal((const ::TDCHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void TDCHit::Dictionary()
{
   fgIsA = ::ROOTDict::GenerateInitInstanceLocal((const ::TDCHit*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *TDCHit::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gCINTMutex); if(!fgIsA) {fgIsA = ::ROOTDict::GenerateInitInstanceLocal((const ::TDCHit*)0x0)->GetClass();} }
   return fgIsA;
}

//______________________________________________________________________________
void TDCHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDCHit.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> channel;
      R__b >> leadsNum;
      R__b.ReadStaticArray((int*)leadFineTimes);
      R__b.ReadStaticArray((int*)leadCoarseTimes);
      R__b.ReadStaticArray((int*)leadEpochs);
      R__b >> trailsNum;
      R__b.ReadStaticArray((int*)trailFineTimes);
      R__b.ReadStaticArray((int*)trailCoarseTimes);
      R__b.ReadStaticArray((int*)trailEpochs);
      R__b.CheckByteCount(R__s, R__c, TDCHit::IsA());
   } else {
      R__c = R__b.WriteVersion(TDCHit::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << channel;
      R__b << leadsNum;
      R__b.WriteArray(leadFineTimes, 50);
      R__b.WriteArray(leadCoarseTimes, 50);
      R__b.WriteArray(leadEpochs, 50);
      R__b << trailsNum;
      R__b.WriteArray(trailFineTimes, 50);
      R__b.WriteArray(trailCoarseTimes, 50);
      R__b.WriteArray(trailEpochs, 50);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

//______________________________________________________________________________
void TDCHit::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class TDCHit.
      TClass *R__cl = ::TDCHit::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "channel", &channel);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "leadsNum", &leadsNum);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "leadFineTimes[50]", leadFineTimes);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "leadCoarseTimes[50]", leadCoarseTimes);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "leadEpochs[50]", leadEpochs);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "trailsNum", &trailsNum);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "trailFineTimes[50]", trailFineTimes);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "trailCoarseTimes[50]", trailCoarseTimes);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "trailEpochs[50]", trailEpochs);
      TObject::ShowMembers(R__insp);
}

namespace ROOTDict {
   // Wrappers around operator new
   static void *new_TDCHit(void *p) {
      return  p ? new(p) ::TDCHit : new ::TDCHit;
   }
   static void *newArray_TDCHit(Long_t nElements, void *p) {
      return p ? new(p) ::TDCHit[nElements] : new ::TDCHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_TDCHit(void *p) {
      delete ((::TDCHit*)p);
   }
   static void deleteArray_TDCHit(void *p) {
      delete [] ((::TDCHit*)p);
   }
   static void destruct_TDCHit(void *p) {
      typedef ::TDCHit current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDCHit(TBuffer &buf, void *obj) {
      ((::TDCHit*)obj)->::TDCHit::Streamer(buf);
   }
} // end of namespace ROOTDict for class ::TDCHit

/********************************************************
* TDCHit.h_Dict.cxx
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

extern "C" void G__cpp_reset_tagtableTDCHitdOh_Dict();

extern "C" void G__set_cpp_environmentTDCHitdOh_Dict() {
  G__cpp_reset_tagtableTDCHitdOh_Dict();
}
#include <new>
extern "C" int G__cpp_dllrevTDCHitdOh_Dict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* TDCHit */
static int G__TDCHitdOh_Dict_168_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   TDCHit* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new TDCHit[n];
     } else {
       p = new((void*) gvp) TDCHit[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new TDCHit;
     } else {
       p = new((void*) gvp) TDCHit;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TDCHit));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TDCHit*) G__getstructoffset())->SetChannel((Int_t) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TDCHit*) G__getstructoffset())->AddLeadTime((int) G__int(libp->para[0]), (int) G__int(libp->para[1])
, (int) G__int(libp->para[2]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TDCHit*) G__getstructoffset())->AddTrailTime((int) G__int(libp->para[0]), (int) G__int(libp->para[1])
, (int) G__int(libp->para[2]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TDCHit*) G__getstructoffset())->GetChannel());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TDCHit*) G__getstructoffset())->GetLeadsNum());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TDCHit*) G__getstructoffset())->GetLeadFine((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TDCHit*) G__getstructoffset())->GetLeadCoarse((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TDCHit*) G__getstructoffset())->GetLeadEpoch((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TDCHit*) G__getstructoffset())->GetTrailsNum());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TDCHit*) G__getstructoffset())->GetTrailFine((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TDCHit*) G__getstructoffset())->GetTrailCoarse((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((TDCHit*) G__getstructoffset())->GetTrailEpoch((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) TDCHit::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TDCHit::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) TDCHit::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      TDCHit::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_21(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TDCHit*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_22(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TDCHit::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_23(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) TDCHit::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_24(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TDCHit::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TDCHitdOh_Dict_168_0_25(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) TDCHit::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__TDCHitdOh_Dict_168_0_26(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   TDCHit* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new TDCHit(*(TDCHit*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TDCHit));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef TDCHit G__TTDCHit;
static int G__TDCHitdOh_Dict_168_0_27(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
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
       delete[] (TDCHit*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((TDCHit*) (soff+(sizeof(TDCHit)*i)))->~G__TTDCHit();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (TDCHit*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((TDCHit*) (soff))->~G__TTDCHit();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__TDCHitdOh_Dict_168_0_28(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   TDCHit* dest = (TDCHit*) G__getstructoffset();
   *dest = *(TDCHit*) libp->para[0].ref;
   const TDCHit& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* TDCHit */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncTDCHitdOh_Dict {
 public:
  G__Sizep2memfuncTDCHitdOh_Dict(): p(&G__Sizep2memfuncTDCHitdOh_Dict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncTDCHitdOh_Dict::*p)();
};

size_t G__get_sizep2memfuncTDCHitdOh_Dict()
{
  G__Sizep2memfuncTDCHitdOh_Dict a;
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
extern "C" void G__cpp_setup_inheritanceTDCHitdOh_Dict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TDCHit))) {
     TDCHit *G__Lderived;
     G__Lderived=(TDCHit*)0x1000;
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TDCHit),G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableTDCHitdOh_Dict() {

   /* Setting up typedef entry */
   G__search_typename2("Int_t",105,-1,0,-1);
   G__setnewtype(-1,"Signed integer 4 bytes (int)",0);
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* TDCHit */
static void G__setup_memvarTDCHit(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TDCHit));
   { TDCHit *p; p=(TDCHit*)0x1000; if (p) { }
   G__memvar_setup((void*)0,105,0,0,-1,G__defined_typename("Int_t"),-1,2,"channel=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,G__defined_typename("Int_t"),-1,2,"leadsNum=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"leadFineTimes[50]=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"leadCoarseTimes[50]=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"leadEpochs[50]=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,G__defined_typename("Int_t"),-1,2,"trailsNum=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"trailFineTimes[50]=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"trailCoarseTimes[50]=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,2,"trailEpochs[50]=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TClass),G__defined_typename("atomic_TClass_ptr"),-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarTDCHitdOh_Dict() {
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
static void G__setup_memfuncTDCHit(void) {
   /* TDCHit */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TDCHit));
   G__memfunc_setup("TDCHit",512,G__TDCHitdOh_Dict_168_0_1, 105, G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TDCHit), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetChannel",997,G__TDCHitdOh_Dict_168_0_2, 121, -1, -1, 0, 1, 1, 1, 0, "i - 'Int_t' 0 - channel", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("AddLeadTime",1038,G__TDCHitdOh_Dict_168_0_3, 121, -1, -1, 0, 3, 1, 1, 0, 
"i - - 0 - fine i - - 0 - coarse "
"i - - 0 - epoch", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("AddTrailTime",1172,G__TDCHitdOh_Dict_168_0_4, 121, -1, -1, 0, 3, 1, 1, 0, 
"i - - 0 - fine i - - 0 - coarse "
"i - - 0 - epoch", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetChannel",985,G__TDCHitdOh_Dict_168_0_5, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetLeadsNum",1081,G__TDCHitdOh_Dict_168_0_6, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetLeadFine",1048,G__TDCHitdOh_Dict_168_0_7, 105, -1, -1, 0, 1, 1, 1, 0, "i - - 0 - mult", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetLeadCoarse",1267,G__TDCHitdOh_Dict_168_0_8, 105, -1, -1, 0, 1, 1, 1, 0, "i - - 0 - mult", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetLeadEpoch",1157,G__TDCHitdOh_Dict_168_0_9, 105, -1, -1, 0, 1, 1, 1, 0, "i - - 0 - mult", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetTrailsNum",1215,G__TDCHitdOh_Dict_168_0_10, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetTrailFine",1182,G__TDCHitdOh_Dict_168_0_11, 105, -1, -1, 0, 1, 1, 1, 0, "i - - 0 - mult", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetTrailCoarse",1401,G__TDCHitdOh_Dict_168_0_12, 105, -1, -1, 0, 1, 1, 1, 0, "i - - 0 - mult", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetTrailEpoch",1291,G__TDCHitdOh_Dict_168_0_13, 105, -1, -1, 0, 1, 1, 1, 0, "i - - 0 - mult", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__TDCHitdOh_Dict_168_0_14, 85, G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&TDCHit::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__TDCHitdOh_Dict_168_0_15, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TDCHit::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__TDCHitdOh_Dict_168_0_16, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&TDCHit::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__TDCHitdOh_Dict_168_0_17, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&TDCHit::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__TDCHitdOh_Dict_168_0_21, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - ClassDef_StreamerNVirtual_b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__TDCHitdOh_Dict_168_0_22, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TDCHit::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__TDCHitdOh_Dict_168_0_23, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&TDCHit::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__TDCHitdOh_Dict_168_0_24, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TDCHit::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__TDCHitdOh_Dict_168_0_25, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&TDCHit::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("TDCHit", 512, G__TDCHitdOh_Dict_168_0_26, (int) ('i'), G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TDCHit), -1, 0, 1, 1, 1, 0, "u 'TDCHit' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~TDCHit", 638, G__TDCHitdOh_Dict_168_0_27, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__TDCHitdOh_Dict_168_0_28, (int) ('u'), G__get_linked_tagnum(&G__TDCHitdOh_DictLN_TDCHit), -1, 1, 1, 1, 1, 0, "u 'TDCHit' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncTDCHitdOh_Dict() {
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
extern "C" void G__cpp_setup_globalTDCHitdOh_Dict() {
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

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcTDCHitdOh_Dict() {
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
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__TDCHitdOh_DictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__TDCHitdOh_DictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__TDCHitdOh_DictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__TDCHitdOh_DictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__TDCHitdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__TDCHitdOh_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__TDCHitdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__TDCHitdOh_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__TDCHitdOh_DictLN_TDCHit = { "TDCHit" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableTDCHitdOh_Dict() {
  G__TDCHitdOh_DictLN_TClass.tagnum = -1 ;
  G__TDCHitdOh_DictLN_TBuffer.tagnum = -1 ;
  G__TDCHitdOh_DictLN_TMemberInspector.tagnum = -1 ;
  G__TDCHitdOh_DictLN_TObject.tagnum = -1 ;
  G__TDCHitdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__TDCHitdOh_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__TDCHitdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__TDCHitdOh_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__TDCHitdOh_DictLN_TDCHit.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableTDCHitdOh_Dict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__TDCHitdOh_DictLN_TClass);
   G__get_linked_tagnum_fwd(&G__TDCHitdOh_DictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__TDCHitdOh_DictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__TDCHitdOh_DictLN_TObject);
   G__get_linked_tagnum_fwd(&G__TDCHitdOh_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__TDCHitdOh_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__TDCHitdOh_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__TDCHitdOh_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__TDCHitdOh_DictLN_TDCHit),sizeof(TDCHit),-1,29952,(char*)NULL,G__setup_memvarTDCHit,G__setup_memfuncTDCHit);
}
extern "C" void G__cpp_setupTDCHitdOh_Dict(void) {
  G__check_setup_version(30051515,"G__cpp_setupTDCHitdOh_Dict()");
  G__set_cpp_environmentTDCHitdOh_Dict();
  G__cpp_setup_tagtableTDCHitdOh_Dict();

  G__cpp_setup_inheritanceTDCHitdOh_Dict();

  G__cpp_setup_typetableTDCHitdOh_Dict();

  G__cpp_setup_memvarTDCHitdOh_Dict();

  G__cpp_setup_memfuncTDCHitdOh_Dict();
  G__cpp_setup_globalTDCHitdOh_Dict();
  G__cpp_setup_funcTDCHitdOh_Dict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncTDCHitdOh_Dict();
  return;
}
class G__cpp_setup_initTDCHitdOh_Dict {
  public:
    G__cpp_setup_initTDCHitdOh_Dict() { G__add_setup_func("TDCHitdOh_Dict",(G__incsetup)(&G__cpp_setupTDCHitdOh_Dict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initTDCHitdOh_Dict() { G__remove_setup_func("TDCHitdOh_Dict"); }
};
G__cpp_setup_initTDCHitdOh_Dict G__cpp_setup_initializerTDCHitdOh_Dict;


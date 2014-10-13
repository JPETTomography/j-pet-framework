#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSigChTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetSigCh/JPetSigCh.h"

/// @todo update the method list - tests are outdated
//  JPetSigCh() { init(); }
//  JPetSigCh(EdgeType Edge, float EdgeTime);
//  bool IsCharge() const;
//  bool IsTime() const;
//  inline float GetValue() const { return fValue; }
//  inline EdgeType GetType() const { return fType; }
//  inline JPetPM * GetPM() const { return (JPetPM*) fPM.GetObject(); }
//  inline JPetTRB * GetTRB() const {return (JPetTRB*) fTRB.GetObject(); }
//  inline JPetFEB * GetFEB() const {return (JPetFEB*) fFEB.GetObject(); }
//  inline void SetPM(JPetPM * pm) { fPM = pm; }
//  inline void SetTRB(JPetTRB * trb) { fTRB = trb; }
//  inline void SetFEB(JPetFEB * feb) { fFEB= feb; }
//  inline void SetValue( float val ) { fValue = val; }
//  inline void SetType( EdgeType type ) { fType = type; }
//  inline void SetPMID( Int_t pmid ) { fPMID = pmid; }
//  inline void SetThreshold( float thr ) { fThreshold = thr; }
//  inline void SetDAQch( Int_t daqch ) { fDAQch = daqch; }
//  inline Int_t GetPMID() const { return fPMID; }
//  inline float GetThreshold() const { return fThreshold; }
//  inline Int_t GetDAQch() const { return fDAQch; }
//  Int_t Compare(const TObject* obj) const;
//  inline Bool_t IsSortable() const { return true; }


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( first )
{
  JPetSigCh test;
  BOOST_REQUIRE_EQUAL(test.IsCharge(), 0);
  BOOST_REQUIRE_EQUAL(test.IsTime(), 1);
  BOOST_REQUIRE_EQUAL(test.GetValue(), JPetSigCh::kUnset);
  BOOST_REQUIRE_EQUAL(test.GetType(), JPetSigCh::Leading);
  BOOST_REQUIRE_EQUAL(test.GetThreshold(), JPetSigCh::kUnset);
}

BOOST_AUTO_TEST_CASE( second )
{
  float epsilon = 0.001;
  JPetSigCh test;
  JPetPM pm_test;
  JPetFEB feb_test(43, true, "", "", 1, 1);
  JPetTRB trb_test;
  float thr_test = 210.043;
  float time_test = 1.2345;

  test.SetPM(&pm_test);
  test.SetTRB(&trb_test);
  test.SetFEB(&feb_test);
  test.SetThreshold(thr_test);
  test.SetType(JPetSigCh::Leading);
  test.SetValue(time_test);
  
  BOOST_REQUIRE_EQUAL(test.IsTime(), 1);
  BOOST_REQUIRE_EQUAL(test.IsCharge(), 0);
  BOOST_REQUIRE_CLOSE(test.GetValue(), time_test, epsilon);
  BOOST_REQUIRE_EQUAL(test.GetType(), JPetSigCh::Leading);
  
  JPetSigCh test2(test);
  
  BOOST_REQUIRE_EQUAL(test.GetPM()->getID(), test2.GetPM()->getID());
  BOOST_REQUIRE_EQUAL(test.GetTRB()->getID(), test2.GetTRB()->getID());
  BOOST_REQUIRE_EQUAL(test.GetFEB()->id(), test2.GetFEB()->id());
  BOOST_REQUIRE_EQUAL(test.GetType(), test2.GetType());
  BOOST_REQUIRE_CLOSE(test.GetValue(), test2.GetValue(), epsilon);
  BOOST_REQUIRE_CLOSE(test.GetThreshold(), test2.GetThreshold(), epsilon);
}

BOOST_AUTO_TEST_CASE( third )
{
  JPetSigCh test;
  JPetSigCh test2;
 
  test.SetThreshold(  1.2345 );
  test2.SetThreshold( 2.3456 );
  
  BOOST_REQUIRE_EQUAL(test.IsSortable(), 1);
  BOOST_REQUIRE_EQUAL(test2.IsSortable(), 1);

  BOOST_REQUIRE_EQUAL( test.Compare(&test2), -1 );
  BOOST_REQUIRE_EQUAL( test2.Compare(&test), 1 );

  test2 = test;
  BOOST_REQUIRE_EQUAL( test2.Compare(&test), 0 );
}

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSigChTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetSigCh/JPetSigCh.h"

/// @todo update the method list - tests are outdated
//  JPetSigCh() { init(); }
//  JPetSigCh(EdgeType Edge, float EdgeTime);
//  bool isCharge() const;
//  bool isTime() const;
//  inline float getValue() const { return fValue; }
//  inline EdgeType getType() const { return fType; }
//  inline JPetPM * getPM() const { return (JPetPM*) fPM.GetObject(); }
//  inline JPetTRB * getTRB() const {return (JPetTRB*) fTRB.GetObject(); }
//  inline JPetFEB * getFEB() const {return (JPetFEB*) fFEB.GetObject(); }
//  inline void setPM(JPetPM * pm) { fPM = pm; }
//  inline void setTRB(JPetTRB * trb) { fTRB = trb; }
//  inline void setFEB(JPetFEB * feb) { fFEB= feb; }
//  inline void setValue( float val ) { fValue = val; }
//  inline void setType( EdgeType type ) { fType = type; }
//  inline void setThreshold( float thr ) { fThreshold = thr; }
//  inline void setDAQch( Int_t daqch ) { fDAQch = daqch; }
//  inline float getThreshold() const { return fThreshold; }
//  inline Int_t getDAQch() const { return fDAQch; }
//  Int_t Compare(const TObject* obj) const;
//  inline Bool_t IsSortable() const { return true; }


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( first )
{
  JPetSigCh test;
  BOOST_REQUIRE_EQUAL(test.isCharge(), 0);
  BOOST_REQUIRE_EQUAL(test.isTime(), 1);
  BOOST_REQUIRE_EQUAL(test.getValue(), JPetSigCh::kUnset);
  BOOST_REQUIRE_EQUAL(test.getType(), JPetSigCh::Leading);
  BOOST_REQUIRE_EQUAL(test.getThreshold(), JPetSigCh::kUnset);
}

BOOST_AUTO_TEST_CASE( second )
{
  float epsilon = 0.001;
  JPetSigCh test;
  JPetPM pm_test;
  JPetFEB feb_test(43, true, "", "", 1, 1, 8, 1);
  JPetTRB trb_test;
  float thr_test = 210.043;
  float time_test = 1.2345;

  test.setPM(pm_test);
  test.setTRB(trb_test);
  test.setFEB(feb_test);
  test.setThreshold(thr_test);
  test.setType(JPetSigCh::Leading);
  test.setValue(time_test);
  
  BOOST_REQUIRE_EQUAL(test.isTime(), 1);
  BOOST_REQUIRE_EQUAL(test.isCharge(), 0);
  BOOST_REQUIRE_CLOSE(test.getValue(), time_test, epsilon);
  BOOST_REQUIRE_EQUAL(test.getType(), JPetSigCh::Leading);
  
  JPetSigCh test2(test);
  
  BOOST_REQUIRE_EQUAL(test.getPM().getID(), test2.getPM().getID());
  BOOST_REQUIRE_EQUAL(test.getTRB().getID(), test2.getTRB().getID());
  BOOST_REQUIRE_EQUAL(test.getFEB().getID(), test2.getFEB().getID());
  BOOST_REQUIRE_EQUAL(test.getType(), test2.getType());
  BOOST_REQUIRE_CLOSE(test.getValue(), test2.getValue(), epsilon);
  BOOST_REQUIRE_CLOSE(test.getThreshold(), test2.getThreshold(), epsilon);
}


BOOST_AUTO_TEST_SUITE_END()

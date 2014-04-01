#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetSignal/JPetSignal.h"
#include <vector>


//  JPetSigCh() { init(); }
//  JPetSigCh(const JPetSigCh& obj);
//  /// @todo must be added~JPetSigCh();
//  JPetSigCh& operator= (const JPetSigCh obj);
//  JPetSigCh(float EdgeTime, float FallEdgeTime = 0); 
//  inline bool isSlow() const;
//  inline float getAmpl() const;
//  inline JPetPM getPM() const;
//  inline JPetTRB getTRB() const;
//  inline JPetScin getScin() const;
//  inline JPetBarrelSlot getBarrelSlot() const;
//  inline float getTime(EdgeType type) const;
//  inline Channels getChannels() const;
//  void addCh(float rise_edge_time, float fall_edge_time);
//  inline void setPM(const JPetPM& pm) { fPM = pm; }
//  inline void setTRB(const JPetTRB& trb) { fTRB = trb; }
//  inline void setScin(const JPetScin& scin) { fScin = scin; }
//  inline void setBarrelSlot(const JPetBarrelSlot& barrel_slot) { fBarrelSlot = barrel_slot; }


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( first )
{
  JPetSigCh test;
  BOOST_CHECK_EQUAL(test.isSlow(), 0);
  BOOST_CHECK_EQUAL(test.getAmpl(), 0);
  BOOST_CHECK_EQUAL(test.getTime(JPetSigCh::kFalling), 0);
  BOOST_CHECK_EQUAL(test.getTime(JPetSigCh::kRising), 0);
}

BOOST_AUTO_TEST_CASE( second )
{
  float epsilon = 0.001;
  JPetSigCh test;
  JPetPM pm_test;
  JPetScin scin_test;
  JPetTRB trb_test;

  test.setPM(pm_test);
  test.setScin(scin_test);
  test.setTRB(trb_test);
  test.addCh(1.2345, 6.789);
  BOOST_CHECK_CLOSE(test.getTime(JPetSigCh::kRising), 1.2345, epsilon);
  BOOST_CHECK_CLOSE(test.getTime(JPetSigCh::kFalling), 6.789, epsilon);
  test.addCh(9.876, 5.4321);
  BOOST_CHECK_CLOSE(test.getTime(JPetSigCh::kRising), 9.876, epsilon);
  BOOST_CHECK_CLOSE(test.getTime(JPetSigCh::kFalling), 5.4321, epsilon);
  test.addCh(6.66, 6.66);
  BOOST_CHECK_CLOSE(test.getTime(JPetSigCh::kRising), 6.66, epsilon);
  BOOST_CHECK_CLOSE(test.getTime(JPetSigCh::kFalling), 6.66, epsilon);

  JPetSigCh test2(test);

  BOOST_CHECK_EQUAL(test.getPM().getID(), test2.getPM().getID());
  BOOST_CHECK_EQUAL(test.getTRB().getID(), test2.getTRB().getID());
  BOOST_CHECK_EQUAL(test.getScin().getID(), test2.getScin().getID());
  BOOST_CHECK_CLOSE(test.getTime(JPetSigCh::kFalling), test2.getTime(JPetSigCh::kFalling), epsilon);
  BOOST_CHECK_CLOSE(test.getTime(JPetSigCh::kRising), test2.getTime(JPetSigCh::kRising), epsilon);

}

BOOST_AUTO_TEST_CASE( third )
{
  float epsilon = 0.001;
  JPetSigCh test, test2;
  JPetPM pm_test;
  JPetScin scin_test;
  JPetTRB trb_test;

  test.setPM(pm_test);
  test.setScin(scin_test);
  test.setTRB(trb_test);
  test.addCh(1.2345, 6.789);

  test2 = test;

  BOOST_CHECK_CLOSE(test.getTime(JPetSigCh::kFalling), test2.getTime(JPetSigCh::kFalling), epsilon);
  BOOST_CHECK_CLOSE(test.getTime(JPetSigCh::kRising), test2.getTime(JPetSigCh::kRising), epsilon);
  BOOST_CHECK_EQUAL(test.getPM().getID(), test2.getPM().getID());
  BOOST_CHECK_EQUAL(test.getTRB().getID(), test2.getTRB().getID());
}

BOOST_AUTO_TEST_SUITE_END()

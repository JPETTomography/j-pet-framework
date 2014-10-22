#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTSlotTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetSigCh/JPetSigCh.h"
#include "../../JPetTSlot/JPetTSlot.h"

/// @todo update methods tests are outdated
//#include <TError.h> /// gErrorIgnoreLevel
//  gErrorIgnoreLevel = 7000;


/// class JPetTSlot:
///  JPetTSlot();
///  void AddCh(JPetSigCh& new_ch);
///  inline size_t size() const ;
///  inline size_t getNumberOfSigCh() const;
///  inline const TClonesArray & getSigChVect() const;
///  inline JPetSigCh & operator[](int i) const;
///  virtual ~JPetTSlot();



BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetTSlot test;
  BOOST_REQUIRE(test.size() == 0);
  BOOST_REQUIRE(test.GetNumberOfSigCh() == 0);
  BOOST_REQUIRE(test.GetSigChVect().GetEntries() == 0);

}

BOOST_AUTO_TEST_CASE( some_channels )
{
  JPetTSlot test;
  JPetSigCh ch_test(JPetSigCh::Trailing, 1.2), ch_test2(JPetSigCh::Leading, 1.5), ch_test3(JPetSigCh::Charge, 98);
  test.AddCh(ch_test);
  test.AddCh(ch_test2);
  test.AddCh(ch_test3);

  BOOST_REQUIRE(test.size() == 3);
  BOOST_REQUIRE(test.GetNumberOfSigCh() == 3);
  BOOST_REQUIRE(test.GetSigChVect().GetEntries() == 3);
  double epsilon = 0.001;
  BOOST_REQUIRE_CLOSE(test[0].GetValue(), 1.2, epsilon);
  BOOST_REQUIRE_CLOSE(test[1].GetValue(), 1.5, epsilon);
  BOOST_REQUIRE_CLOSE(test[2].GetValue(), 98, epsilon);

  TClonesArray array = test.GetSigChVect();
  BOOST_REQUIRE_CLOSE(static_cast<JPetSigCh*>(array.At(0))->GetValue(), 1.2, epsilon);
  BOOST_REQUIRE_CLOSE(static_cast<JPetSigCh*>(array.At(1))->GetValue(), 1.5, epsilon);
  BOOST_REQUIRE_CLOSE(static_cast<JPetSigCh*>(array.At(2))->GetValue(), 98, epsilon);

}

BOOST_AUTO_TEST_SUITE_END()

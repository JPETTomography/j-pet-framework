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
///  inline const std::vector<JPetSigCh*> & getSigChVect() const;
///  inline JPetSigCh & operator[](int i) const;
///  virtual ~JPetTSlot();



BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetTSlot test;
  BOOST_REQUIRE(test.size() == 0);
  BOOST_REQUIRE(test.getNumberOfSigCh() == 0);
  BOOST_REQUIRE(test.getSigChVect().size() == 0);

}

BOOST_AUTO_TEST_CASE( some_channels )
{
  JPetTSlot test;
  JPetSigCh ch_test(JPetSigCh::Trailing, 1.2), ch_test2(JPetSigCh::Leading, 1.5), ch_test3(JPetSigCh::Charge, 98);
  test.addCh(ch_test);
  test.addCh(ch_test2);
  test.addCh(ch_test3);

  BOOST_REQUIRE(test.size() == 3);
  BOOST_REQUIRE(test.getNumberOfSigCh() == 3);
  BOOST_REQUIRE(test.getSigChVect().size() == 3);
  double epsilon = 0.001;
  BOOST_REQUIRE_CLOSE(test[0].getValue(), 1.2, epsilon);
  BOOST_REQUIRE_CLOSE(test[1].getValue(), 1.5, epsilon);
  BOOST_REQUIRE_CLOSE(test[2].getValue(), 98, epsilon);

  std::vector<JPetSigCh*> array = test.getSigChVect();
  BOOST_REQUIRE_CLOSE((array.at(0))->getValue(), 1.2, epsilon);
  BOOST_REQUIRE_CLOSE((array.at(1))->getValue(), 1.5, epsilon);
  BOOST_REQUIRE_CLOSE((array.at(2))->getValue(), 98, epsilon);

}

BOOST_AUTO_TEST_SUITE_END()

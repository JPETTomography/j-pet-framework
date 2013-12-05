#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamManagerTest
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetParamManager/JPetParamManager.h"

#include <cstddef>


BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( read_file )
{
  JPetParamManager param_manager;
  param_manager.readFile("jpetparammanagertest.txt");
  BOOST_CHECK_EQUAL(param_manager.getDataSize(), 4);
  BOOST_CHECK_EQUAL(param_manager.getTRBNumber(0), 1);
  BOOST_CHECK_EQUAL(param_manager.getTRBNumber(1), 3);
  BOOST_CHECK_EQUAL(param_manager.getTRBNumber(2), 5);
  BOOST_CHECK_EQUAL(param_manager.getTRBNumber(3), 7);
  
  //BOOST_CHECK_EQUAL(event.GetTime(), 0.0f);
  //BOOST_CHECK_EQUAL(event.GetQualityOfTime(), 0.0f);
  
  //BOOST_CHECK(event.fHits->first == NULL);
  //BOOST_CHECK(event.fHits->second == NULL);
}

BOOST_AUTO_TEST_SUITE_END()
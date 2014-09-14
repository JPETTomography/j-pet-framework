#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamManagerTest
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetParamManager/JPetParamManager.h"

#include <cstddef>


BOOST_AUTO_TEST_SUITE(FirstSuite)
  
//BOOST_AUTO_TEST_CASE( read_file )
//{
//  JPetParamManager param_manager;
//  param_manager.readFile("jpetparammanagertest.txt");
//  BOOST_CHECK_EQUAL(param_manager.getDataSize(), 4);
//  BOOST_CHECK_EQUAL(param_manager.getTRBNumber(0), 1);
//  BOOST_CHECK_EQUAL(param_manager.getTRBNumber(1), 3);
//  BOOST_CHECK_EQUAL(param_manager.getTRBNumber(2), 5);
//  BOOST_CHECK_EQUAL(param_manager.getTRBNumber(3), 7);
//  
//  //BOOST_CHECK_EQUAL(event.GetTime(), 0.0f);
//  //BOOST_CHECK_EQUAL(event.GetQualityOfTime(), 0.0f);
//  
//  //BOOST_CHECK(event.fHits->first == NULL);
//  //BOOST_CHECK(event.fHits->second == NULL);
//}

BOOST_AUTO_TEST_CASE(fillContainersTest)
{
  JPetParamManager l_paramManagerInstance;
  l_paramManagerInstance.fillAllContainers(1);
  
  BOOST_CHECK(l_paramManagerInstance.getScintillatorsSize() > 0);
  BOOST_CHECK(l_paramManagerInstance.getPMsSize() > 0);
  BOOST_CHECK(l_paramManagerInstance.getKBsSize() > 0);
  BOOST_CHECK(l_paramManagerInstance.getTRBsSize() > 0);
  BOOST_CHECK(l_paramManagerInstance.getTOMBSize() > 0);
}

BOOST_AUTO_TEST_CASE(fillContainersTRefsTest)
{
  JPetParamManager l_paramManagerInstance;
  l_paramManagerInstance.fillAllContainers(1);
  
  l_paramManagerInstance.fillAllTRefs();
}

BOOST_AUTO_TEST_CASE(fillWriteAndReadContainersTest)
{
  JPetParamManager l_paramManagerInstance;
  l_paramManagerInstance.fillAllContainers(1);
  
  const char* l_fileName = "param_manager_test_file.txt";
  JPetWriter l_writerInstance(l_fileName);
  JPetReader l_readerInstance(l_fileName);
  
  l_paramManagerInstance.setWriter(&l_writerInstance);
  l_paramManagerInstance.setReader(&l_readerInstance);
  
  l_paramManagerInstance.writerAllContainers(l_fileName);
  l_paramManagerInstance.readAllContainers(l_fileName);
}

BOOST_AUTO_TEST_CASE(containersIdTest)
{
  JPetParamManager l_paramManagerInstance;
  l_paramManagerInstance.fillAllContainers(1);
  
  BOOST_CHECK(l_paramManagerInstance.getScintillator(0).getID() >= 0);
  BOOST_CHECK(l_paramManagerInstance.getPM(0).getID() >= 0);
  BOOST_CHECK(l_paramManagerInstance.getKB(0).id() >= 0);
  BOOST_CHECK(l_paramManagerInstance.getTRB(0).getID() >= 0);
  BOOST_CHECK(l_paramManagerInstance.getTOMB().id() >= 0);
}

BOOST_AUTO_TEST_SUITE_END()

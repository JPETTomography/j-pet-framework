#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamManagerTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetParamManager/JPetParamManager.h"

#include <cstddef>

const char* gDefaultConfigFile ="../../DBHandler/Config/configDB.cfg";

BOOST_AUTO_TEST_SUITE(FirstSuite)
  

BOOST_AUTO_TEST_CASE(fillContainersTest)
{
  JPetParamManager l_paramManagerInstance(gDefaultConfigFile);
  l_paramManagerInstance.fillAllContainers(1);
  BOOST_REQUIRE(l_paramManagerInstance.getScintillatorsSize() > 0);
  BOOST_REQUIRE(l_paramManagerInstance.getPMsSize() > 0);
  BOOST_REQUIRE(l_paramManagerInstance.getKBsSize() > 0);
  BOOST_REQUIRE(l_paramManagerInstance.getTRBsSize() > 0);
  BOOST_REQUIRE(l_paramManagerInstance.getTOMBSize() > 0);
}

BOOST_AUTO_TEST_CASE(fillContainersTRefsTest)
{
  JPetParamManager l_paramManagerInstance(gDefaultConfigFile);
  l_paramManagerInstance.fillAllContainers(1);
  
  l_paramManagerInstance.fillAllTRefs();
}

//BOOST_AUTO_TEST_CASE(fillWriteAndReadContainersTest)
//{
//  JPetParamManager l_paramManagerInstance(gDefaultConfigFile);
//  l_paramManagerInstance.fillAllContainers(1);
//  
//  const char* l_fileName = "param_manager_test_file.txt";
//  JPetWriter l_writerInstance(l_fileName);
//  JPetReader l_readerInstance(l_fileName);
//  
//  l_paramManagerInstance.setWriter(&l_writerInstance);
//  l_paramManagerInstance.setReader(&l_readerInstance);
//  
//  l_paramManagerInstance.writerAllContainers(l_fileName);
//  l_paramManagerInstance.readAllContainers(l_fileName);
//}
//
//BOOST_AUTO_TEST_CASE(containersIdTest)
//{
//  JPetParamManager l_paramManagerInstance(gDefaultConfigFile);
//  l_paramManagerInstance.fillAllContainers(1);
//  
//  BOOST_REQUIRE(l_paramManagerInstance.getScintillator(0).getID() >= 0);
//  BOOST_REQUIRE(l_paramManagerInstance.getPM(0).getID() >= 0);
//  BOOST_REQUIRE(l_paramManagerInstance.getKB(0).id() >= 0);
//  BOOST_REQUIRE(l_paramManagerInstance.getTRB(0).getID() >= 0);
//  BOOST_REQUIRE(l_paramManagerInstance.getTOMB().id() >= 0);
//}

BOOST_AUTO_TEST_SUITE_END()

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetDBParamGetterTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetDBParamGetter/JPetDBParamGetter.h"

const char* gDefaultConfigFile ="DBConfig/configDB.cfg";

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetDBParamGetter paramMgr;
  
}  

BOOST_AUTO_TEST_CASE(some_filling)
{
  JPetDBParamGetter paramMgr(gDefaultConfigFile);
  paramMgr.fillScintillators(1);
  BOOST_REQUIRE(paramMgr.fBank.getScintillatorsSize() > 0);
  paramMgr.fillPMs(1);
  BOOST_REQUIRE(paramMgr.fBank.getPMsSize() > 0);
  paramMgr.fillFEBs(1);
  BOOST_REQUIRE(paramMgr.fBank.getFEBsSize() > 0);
  paramMgr.fillTRBs(1);
  BOOST_REQUIRE(paramMgr.fBank.getTRBsSize() > 0);
  
}  
BOOST_AUTO_TEST_CASE(fillContainersTest)
{
  JPetDBParamGetter l_paramManagerInstance(gDefaultConfigFile);
  l_paramManagerInstance.fillAllContainers(1);
  BOOST_REQUIRE(l_paramManagerInstance.fBank.getScintillatorsSize() > 0);
  BOOST_REQUIRE(l_paramManagerInstance.fBank.getPMsSize() > 0);
  BOOST_REQUIRE(l_paramManagerInstance.fBank.getFEBsSize() > 0);
  BOOST_REQUIRE(l_paramManagerInstance.fBank.getTRBsSize() > 0);
}

BOOST_AUTO_TEST_CASE(fillContainersTRefsTest)
{
  JPetDBParamGetter l_paramManagerInstance(gDefaultConfigFile);
  l_paramManagerInstance.fillAllContainers(1);
  
  l_paramManagerInstance.fillAllTRefs();
}

//BOOST_AUTO_TEST_CASE(fillWriteAndReadContainersTest)
//{
//  JPetDBParamGetter l_paramManagerInstance(gDefaultConfigFile);
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
//  JPetDBParamGetter l_paramManagerInstance(gDefaultConfigFile);
//  l_paramManagerInstance.fillAllContainers(1);
//  
//  BOOST_REQUIRE(l_paramManagerInstance.getScintillator(0).getID() >= 0);
//  BOOST_REQUIRE(l_paramManagerInstance.getPM(0).getID() >= 0);
//  BOOST_REQUIRE(l_paramManagerInstance.getKB(0).id() >= 0);
//  BOOST_REQUIRE(l_paramManagerInstance.getTRB(0).getID() >= 0);
//  BOOST_REQUIRE(l_paramManagerInstance.getTOMB().id() >= 0);
//}


BOOST_AUTO_TEST_SUITE_END()

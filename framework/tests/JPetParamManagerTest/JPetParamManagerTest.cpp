#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamManagerTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetParamManager/JPetParamManager.h"

#include <cstddef>

const char* gDefaultConfigFile ="DBConfig/configDB.cfg";

/// class JPetParamManager
//  JPetParamManager();
//  JPetParamManager(const char* dBConfigFile);
//  void readFile(const char* file_name); /// @todo what file ???
//  bool setWriter(JPetWriter* writer);
//  // Scintillators
//  inline void addScintillator(JPetScin& scintillator);
//  inline const TClonesArray& getScintillators() const;
//  inline JPetScin& getScintillator(int i) const; 
//  inline int getScintillatorsSize() const; 
//
//  // PMs
//  inline void addPM(JPetPM& pm); 
//  inline const TClonesArray& getPMs() const
//  inline JPetPM& getPM(int i) const
//  int getPMsSize() const
//
//  // KBs
//  inline void addKB(JPetFEB& kb)
//  inline const TClonesArray& getKBs() const
//  inline JPetFEB& getKB(int i) const
//  inline int getKBsSize() const
//
//  // TRBs
//  inline void addTRB(JPetTRB& trb)
//  inline const TClonesArray& getTRBs() const
//  inline JPetTRB& getTRB(int i) const
//  inline int getTRBsSize() const
//
//  // TOMB
//  inline void setTOMB(JPetTOMB& tomb)
//  inline JPetTOMB& getTOMB() const 
//  inline int getTOMBSize() const 
//
//  bool writerAllContainers   
//
//  void getParametersFromDatabase(const int run);
//  void clearAllContainers();


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetParamManager paramMgr;
  
}  

BOOST_AUTO_TEST_CASE(some_filling)
{
  JPetParamManager paramMgr(gDefaultConfigFile);
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
  JPetParamManager l_paramManagerInstance(gDefaultConfigFile);
  l_paramManagerInstance.fillAllContainers(1);
  BOOST_REQUIRE(l_paramManagerInstance.fBank.getScintillatorsSize() > 0);
  BOOST_REQUIRE(l_paramManagerInstance.fBank.getPMsSize() > 0);
  BOOST_REQUIRE(l_paramManagerInstance.fBank.getFEBsSize() > 0);
  BOOST_REQUIRE(l_paramManagerInstance.fBank.getTRBsSize() > 0);
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

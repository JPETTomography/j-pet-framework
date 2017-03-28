#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamManagerTest
#include <cstddef>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetParamGetterAscii/JPetParamGetterAscii.h"

const std::string dataDir = "unitTestData/JPetParamManagerTest/";
const std::string dataFileName = dataDir+"data.json";

BOOST_AUTO_TEST_SUITE(JPetParamManagerTestSuite)

void checkContainersSize(const JPetParamBank &bank)
{
  JPetDBParamGetter::clearParamCache();
  JPetScopeParamGetter::clearParamCache();
  BOOST_REQUIRE_EQUAL(bank.getScintillatorsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(bank.getPMCalibsSize(), 0);// It is not 0 for e.g. run_id = 2 - FOR run_id=2 NOT for run_id=1 YES. In test run_id is set to 1 so the size=0
  BOOST_REQUIRE_EQUAL(bank.getFEBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getTRBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getBarrelSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getTOMBChannelsSize(), 4);
}

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetDBParamGetter::clearParamCache();
  JPetScopeParamGetter::clearParamCache();
  JPetParamManager paramMgr;
}  
BOOST_AUTO_TEST_CASE(generateParamBankTest)
{
  JPetDBParamGetter::clearParamCache();
  JPetScopeParamGetter::clearParamCache();
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  l_paramManagerInstance.fillParameterBank(1);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  
  checkContainersSize(l_paramManagerInstance.getParamBank());
}

// BOOST_AUTO_TEST_CASE(writeAndReadDataFromFileByWriterAndReaderObjectsTest)
// {
//  DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
//
//   JPetParamManager l_paramManagerInstance;
//   
//   l_paramManagerInstance.getParametersFromDatabase(1);
// 
//   const char* testDatafile = "testDataFile.txt";
//   JPetWriter writer(testDatafile);
//   BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);
//   
//   JPetReader reader(testDatafile);
//   BOOST_CHECK(l_paramManagerInstance.readParametersFromFile(&reader) == true);
// }

BOOST_AUTO_TEST_CASE(writeAndReadDataFromFileByFileNameTest)
{
  JPetDBParamGetter::clearParamCache();
  JPetScopeParamGetter::clearParamCache();
  std::string testDatafile = dataDir+"testDataFile.txt";
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  
  
  l_paramManagerInstance.fillParameterBank(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  
  BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);
  
  boost::filesystem::remove(testDatafile);
}

BOOST_AUTO_TEST_CASE(some_Test_that_had_no_name)
{
  JPetDBParamGetter::clearParamCache();
  JPetScopeParamGetter::clearParamCache();

  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  
  l_paramManagerInstance.fillParameterBank(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(),false);
  
  checkContainersSize(l_paramManagerInstance.getParamBank());
  
  l_paramManagerInstance.clearParameters();
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getScintillatorsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getPMsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getPMCalibsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getFEBsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getTRBsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getBarrelSlotsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getTOMBChannelsSize(), 0);
}

BOOST_AUTO_TEST_CASE(getParamBankTest)
{
  JPetDBParamGetter::clearParamCache();
  JPetScopeParamGetter::clearParamCache();

  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  
  l_paramManagerInstance.fillParameterBank(1);
  
  const JPetParamBank &bank = l_paramManagerInstance.getParamBank();
  
  checkContainersSize(bank);
}

BOOST_AUTO_TEST_CASE(getParametersFromScopeConfigFile)
{
  JPetScopeParamGetter::clearParamCache();
  using namespace scope_config;
  using VecOfStrings = std::vector<std::string>;

  const char* testConfigFile = "unitTestData/JPetParamManagerTest/conf.json";
  Config config;
  config.fLocation="data";
  config.fCollimatorPositions = VecOfStrings { "1 5 2", "12", "6"};
  config.fBSlots= std::vector<BSlot>{ BSlot(1,true,"aa",1., 1), BSlot(2,false,"bb",2., 2)};
  config.fPMs = std::vector<PM>{PM(3,"C2"), PM(98, "C4"), PM(32, "C1"), PM(42, "C3")}; 
  config.fScins=std::vector<Scin>{Scin(32), Scin(12)};
  config.fName="config1";
  JPetParamManager paramManagerInstance;
  BOOST_REQUIRE(paramManagerInstance.getParametersFromScopeConfig(testConfigFile));
  const JPetParamBank& bank = paramManagerInstance.getParamBank();
  BOOST_REQUIRE(!bank.isDummy());
  auto bslots = bank.getBarrelSlots();
  BOOST_REQUIRE_EQUAL(bslots.size(), 2u);
  for(const BSlot& BSlotConf: config.fBSlots) {
    BOOST_REQUIRE(bslots.at(BSlotConf.fId));
    BOOST_REQUIRE_EQUAL(bslots.at(BSlotConf.fId)->getID(), BSlotConf.fId);
    BOOST_REQUIRE_EQUAL(bslots.at(BSlotConf.fId)->isActive(), BSlotConf.fActive);
    BOOST_REQUIRE_EQUAL(bslots.at(BSlotConf.fId)->getName(), BSlotConf.fName);
    BOOST_REQUIRE_EQUAL(bslots.at(BSlotConf.fId)->getInFrameID(), BSlotConf.fFrame);
    BOOST_REQUIRE_EQUAL(bslots.at(BSlotConf.fId)->getTheta(), BSlotConf.fTheta);
  }
  auto pms = bank.getPMs();
  BOOST_REQUIRE_EQUAL(pms.size(), 4u);
  for(const PM& PMConf: config.fPMs) {
    BOOST_REQUIRE(pms.at(PMConf.fId));
    BOOST_REQUIRE_EQUAL(pms.at(PMConf.fId)->getID(), PMConf.fId);
  }
  auto scintillators = bank.getScintillators();
  BOOST_REQUIRE_EQUAL(scintillators.size(), 2u);
  for(const Scin& ScinConf: config.fScins) {
    BOOST_REQUIRE(scintillators.at(ScinConf.fId));
    BOOST_REQUIRE_EQUAL(scintillators.at(ScinConf.fId)->getID(), ScinConf.fId);
  }
    
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[0].fId)->getSide(), JPetPM::SideA);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[1].fId)->getSide(), JPetPM::SideB);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[2].fId)->getSide(), JPetPM::SideA);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[3].fId)->getSide(), JPetPM::SideB);

  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[0].fId)->getScin().getID(), config.fScins[0].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[1].fId)->getScin().getID(), config.fScins[0].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[2].fId)->getScin().getID(), config.fScins[1].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[3].fId)->getScin().getID(), config.fScins[1].fId);

  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[0].fId)->getBarrelSlot().getID(), config.fBSlots[0].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[1].fId)->getBarrelSlot().getID(), config.fBSlots[0].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[2].fId)->getBarrelSlot().getID(), config.fBSlots[1].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[3].fId)->getBarrelSlot().getID(), config.fBSlots[1].fId);

  BOOST_REQUIRE_EQUAL(scintillators.at(config.fScins[0].fId)->getBarrelSlot().getID(), config.fBSlots[0].fId);
  BOOST_REQUIRE_EQUAL(scintillators.at(config.fScins[1].fId)->getBarrelSlot().getID(), config.fBSlots[1].fId);
}

BOOST_AUTO_TEST_CASE(getParametersFromScopeConfigFileTwice)
{
  JPetScopeParamGetter::clearParamCache();
  using namespace scope_config;
  using VecOfStrings = std::vector<std::string>;

  const char* testConfigFile = "unitTestData/JPetParamManagerTest/conf.json";
  Config config;
  config.fLocation="data";
  config.fCollimatorPositions = VecOfStrings { "1 5 2", "12", "6"};
  config.fBSlots= std::vector<BSlot>{ BSlot(1,true,"aa",1., 1), BSlot(2,false,"bb",2., 2)};
  config.fPMs = std::vector<PM>{PM(3,"C2"), PM(98, "C4"), PM(32, "C1"), PM(42, "C3")}; 
  config.fScins=std::vector<Scin>{Scin(32), Scin(12)};
  config.fName="config1";
  JPetParamManager paramManagerInstance;
  BOOST_REQUIRE(paramManagerInstance.getParametersFromScopeConfig(testConfigFile));
  BOOST_REQUIRE(paramManagerInstance.getParametersFromScopeConfig(testConfigFile));
  const JPetParamBank& bank = paramManagerInstance.getParamBank();
  BOOST_REQUIRE(!bank.isDummy());
  auto bslots = bank.getBarrelSlots();
  BOOST_REQUIRE_EQUAL(bslots.size(), 2u);
  for(const BSlot& BSlotConf: config.fBSlots) {
    BOOST_REQUIRE(bslots.at(BSlotConf.fId));
    BOOST_REQUIRE_EQUAL(bslots.at(BSlotConf.fId)->getID(), BSlotConf.fId);
    BOOST_REQUIRE_EQUAL(bslots.at(BSlotConf.fId)->isActive(), BSlotConf.fActive);
    BOOST_REQUIRE_EQUAL(bslots.at(BSlotConf.fId)->getName(), BSlotConf.fName);
    BOOST_REQUIRE_EQUAL(bslots.at(BSlotConf.fId)->getInFrameID(), BSlotConf.fFrame);
    BOOST_REQUIRE_EQUAL(bslots.at(BSlotConf.fId)->getTheta(), BSlotConf.fTheta);
  }
  auto pms = bank.getPMs();
  BOOST_REQUIRE_EQUAL(pms.size(), 4u);
  for(const PM& PMConf: config.fPMs) {
    BOOST_REQUIRE(pms.at(PMConf.fId));
    BOOST_REQUIRE_EQUAL(pms.at(PMConf.fId)->getID(), PMConf.fId);
  }

  auto scintillators = bank.getScintillators();
  BOOST_REQUIRE_EQUAL(scintillators.size(), 2u);
  for(const Scin& ScinConf: config.fScins) {
    BOOST_REQUIRE(scintillators.at(ScinConf.fId));
    BOOST_REQUIRE_EQUAL(scintillators.at(ScinConf.fId)->getID(), ScinConf.fId);
  }

  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[0].fId)->getSide(), JPetPM::SideA);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[1].fId)->getSide(), JPetPM::SideB);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[2].fId)->getSide(), JPetPM::SideA);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[3].fId)->getSide(), JPetPM::SideB);

  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[0].fId)->getScin().getID(), config.fScins[0].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[1].fId)->getScin().getID(), config.fScins[0].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[2].fId)->getScin().getID(), config.fScins[1].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[3].fId)->getScin().getID(), config.fScins[1].fId);

  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[0].fId)->getBarrelSlot().getID(), config.fBSlots[0].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[1].fId)->getBarrelSlot().getID(), config.fBSlots[0].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[2].fId)->getBarrelSlot().getID(), config.fBSlots[1].fId);
  BOOST_REQUIRE_EQUAL(pms.at(config.fPMs[3].fId)->getBarrelSlot().getID(), config.fBSlots[1].fId);

  BOOST_REQUIRE_EQUAL(scintillators.at(config.fScins[0].fId)->getBarrelSlot().getID(), config.fBSlots[0].fId);
  BOOST_REQUIRE_EQUAL(scintillators.at(config.fScins[1].fId)->getBarrelSlot().getID(), config.fBSlots[1].fId);
}

BOOST_AUTO_TEST_SUITE_END()

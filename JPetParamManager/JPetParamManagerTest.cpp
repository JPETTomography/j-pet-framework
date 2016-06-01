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
  BOOST_REQUIRE_EQUAL(bank.getScintillatorsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(bank.getPMCalibsSize(), 0);// It is not 0 for e.g. run_id = 2 - FOR run_id=2 NOT for run_id=1 YES. In test run_id is set to 1 so the size=0
  BOOST_REQUIRE_EQUAL(bank.getFEBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getTRBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getBarrelSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getTOMBChannelsSize(), 4);
}

BOOST_AUTO_TEST_CASE(generateParamBankTest)
{
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  l_paramManagerInstance.fillParameterBank(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  
  checkContainersSize(l_paramManagerInstance.getParamBank());
}

// BOOST_AUTO_TEST_CASE(writeAndReadDataFromFileByWriterAndReaderObjectsTest)
// {
// 	DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
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
	std::string testDatafile = dataDir+"testDataFile.txt";
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  
  l_paramManagerInstance.fillParameterBank(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  
  BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);
  
		boost::filesystem::remove(testDatafile);
}

BOOST_AUTO_TEST_CASE(some_Test_that_had_no_name)
{
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
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  
  l_paramManagerInstance.fillParameterBank(1);
  
  const JPetParamBank &bank = l_paramManagerInstance.getParamBank();
  
  checkContainersSize(bank);
}

BOOST_AUTO_TEST_CASE(getParametersFromScopeConfig)
{
	
  using namespace scope_config;
  using VecOfStrings = std::vector<std::string>;

  Config config;
  config.fLocation="data";
  config.fCollimatorPositions = VecOfStrings { "1 5 2", "12", "6"};
  config.fBSlots= std::vector<BSlot>{ BSlot(1,true,"aa",1., 1), BSlot(2,false,"bb",2., 2)};
  config.fPMs = std::vector<PM>{PM(3,"C2"), PM(98, "C4"), PM(32, "C1"), PM(42, "C3")}; 
  config.fScins=std::vector<Scin>{Scin(32), Scin(12)};
  config.fName="config1";
  JPetParamManager paramManagerInstance;
  BOOST_REQUIRE(paramManagerInstance.getParametersFromScopeConfig(config));
  const JPetParamBank& bank = paramManagerInstance.getParamBank();
  BOOST_REQUIRE(!bank.isDummy());
  auto bslots = bank.getBarrelSlots();
  BOOST_REQUIRE_EQUAL(bslots.size(), 2);
  int i = 0;
  for(const BSlot& BSlotConf: config.fBSlots) {
    BOOST_REQUIRE(bslots[i]);
    BOOST_REQUIRE_EQUAL(bslots[i]->getID(), BSlotConf.fId);
    BOOST_REQUIRE_EQUAL(bslots[i]->isActive(), BSlotConf.fActive);
    BOOST_REQUIRE_EQUAL(bslots[i]->getName(), BSlotConf.fName);
    BOOST_REQUIRE_EQUAL(bslots[i]->getInFrameID(), BSlotConf.fFrame);
    BOOST_REQUIRE_EQUAL(bslots[i]->getTheta(), BSlotConf.fTheta);
    i++;
  }
  auto pms = bank.getPMs();
  BOOST_REQUIRE_EQUAL(pms.size(), 4);
  i = 0;
  for(const PM& PMConf: config.fPMs) {
    BOOST_REQUIRE(pms[i]);
    BOOST_REQUIRE_EQUAL(pms[i]->getID(), PMConf.fId);
    i++;
  }
  auto scintillators = bank.getScintillators();
  BOOST_REQUIRE_EQUAL(scintillators.size(), 2);
  i = 0;
  for(const Scin& ScinConf: config.fScins) {
    BOOST_REQUIRE(scintillators[i]);
    BOOST_REQUIRE_EQUAL(scintillators[i]->getID(), ScinConf.fId);
    i++;
  }

  BOOST_REQUIRE_EQUAL(pms[0]->getSide(), JPetPM::SideA);
  BOOST_REQUIRE_EQUAL(pms[1]->getSide(), JPetPM::SideB);
  BOOST_REQUIRE_EQUAL(pms[2]->getSide(), JPetPM::SideA);
  BOOST_REQUIRE_EQUAL(pms[3]->getSide(), JPetPM::SideB);

  BOOST_REQUIRE_EQUAL(pms[0]->getScin().getID(), config.fScins[0].fId);
  BOOST_REQUIRE_EQUAL(pms[1]->getScin().getID(), config.fScins[0].fId);
  BOOST_REQUIRE_EQUAL(pms[2]->getScin().getID(), config.fScins[1].fId);
  BOOST_REQUIRE_EQUAL(pms[3]->getScin().getID(), config.fScins[1].fId);

  BOOST_REQUIRE_EQUAL(pms[0]->getBarrelSlot().getID(), config.fBSlots[0].fId);
  BOOST_REQUIRE_EQUAL(pms[1]->getBarrelSlot().getID(), config.fBSlots[0].fId);
  BOOST_REQUIRE_EQUAL(pms[2]->getBarrelSlot().getID(), config.fBSlots[1].fId);
  BOOST_REQUIRE_EQUAL(pms[3]->getBarrelSlot().getID(), config.fBSlots[1].fId);

  BOOST_REQUIRE_EQUAL(scintillators[0]->getBarrelSlot().getID(), config.fBSlots[0].fId);
  BOOST_REQUIRE_EQUAL(scintillators[1]->getBarrelSlot().getID(), config.fBSlots[1].fId);
}

BOOST_AUTO_TEST_SUITE_END()

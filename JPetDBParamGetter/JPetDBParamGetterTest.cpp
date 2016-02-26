#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetDBParamGetterTest
#include <boost/test/unit_test.hpp>
#include "../DBHandler/HeaderFiles/DBHandler.h"
#define private public
#include "../JPetDBParamGetter/JPetDBParamGetter.h"
#undef private

const char* gDefaultConfigFile = "../DBConfig/configDB.cfg";

BOOST_AUTO_TEST_SUITE(DBParamGetterTS)

//public:
//  JPetDBParamGetter();
//  JPetDBParamGetter(const char* dBConfigFile);
//  JPetParamBank* generateParamBank(const int p_run_id);
//private:
//  pqxx::result getDataFromDB(const std::string& sqlFunction, const std::string& args);
//  std::string generateSelectQuery(const std::string& sqlFunction, const std::string& args);
//  void printErrorMessageDB(std::string sqlFunction, int p_run_id);
//  JPetScin generateScintillator(pqxx::result::const_iterator row);
//  JPetPM generatePM(pqxx::result::const_iterator row);
//  JPetPMCalib generatePMCalib(pqxx::result::const_iterator row);
//  JPetFEB generateFEB(pqxx::result::const_iterator row);
//  JPetTRB generateTRB(pqxx::result::const_iterator row);
//  JPetTOMBChannel generateTOMBChannel(pqxx::result::const_iterator row);
//
//  void fillScintillators(const int p_run_id, JPetParamBank& paramBank);
//  void fillParamContainer(ParamObjectType type, const int p_run_id, JPetParamBank& paramBank);
//
//  void fillPMs(const int p_run_id, JPetParamBank& paramBank);
//  void fillPMCalibs(const int p_run_id, JPetParamBank& paramBank);
//  void fillFEBs(const int p_run_id, JPetParamBank& paramBank);
//  void fillTOMBChannels(const int p_run_id, JPetParamBank& paramBank);
//  void fillTRBs(const int p_run_id, JPetParamBank& paramBank);
//  void fillPMsTRefs(const int p_run_id, JPetParamBank& paramBank);
//  void fillFEBsTRefs(const int p_run_id, JPetParamBank& paramBank);
//  void fillTOMBChannelsTRefs(const int p_run_id, JPetParamBank& paramBank);
//  void fillAllTRefs(const int p_run_id, JPetParamBank& paramBank);
//

BOOST_AUTO_TEST_CASE(defaultConstructorTest)
{
  JPetDBParamGetter paramGetter;
}

BOOST_AUTO_TEST_CASE(dummyFillingTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
  JPetDBParamGetter paramGetter;
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  
  /* std::cout << "Scintillators number:" << bank->getScintillatorsSize() <<std::endl; */
  /* std::cout << "PM numbers:" << bank->getPMsSize() <<std::endl; */
  /* std::cout << "PMCalib numbers:" << bank->getPMCalibsSize() <<std::endl; */
  /* std::cout << "BarrelSlot numbers:" << bank->getBarrelSlotsSize() <<std::endl; */
  /* std::cout << "Layer numbers:" << bank->getLayersSize() <<std::endl; */
  /* std::cout << "Frame numbers:" << bank->getFramesSize() <<std::endl; */
  /* std::cout << "FEB numbers:" << bank->getFEBsSize() <<std::endl; */
  /* std::cout << "TRB numbers:" << bank->getTRBsSize() <<std::endl; */
  /* std::cout << "TOMB channel numbers:" << bank->getTOMBChannelsSize() <<std::endl; */

  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getPMCalibsSize() == 0); // 0 due to run id == 1  // TODO Check it with DB // RESOLVED sql function returns (0 rows) for run_id=1
  BOOST_REQUIRE(bank->getBarrelSlotsSize() == 2);
  BOOST_REQUIRE(bank->getLayersSize() == 1);
  BOOST_REQUIRE(bank->getFramesSize() == 1);
  BOOST_REQUIRE(bank->getFEBsSize() == 1);
  BOOST_REQUIRE(bank->getTRBsSize() == 1);
  BOOST_REQUIRE(bank->getTOMBChannelsSize() == 4);
}

BOOST_AUTO_TEST_CASE(run28Test)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	JPetDBParamGetter paramGetter;
  int run  = 28;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  /* std::cout << "Scintillators number:" << bank->getScintillatorsSize() <<std::endl; */
  /* std::cout << "PM numbers:" << bank->getPMsSize() <<std::endl; */
  /* std::cout << "PMCalib numbers:" << bank->getPMCalibsSize() <<std::endl; */
  /* std::cout << "BarrelSlot numbers:" << bank->getBarrelSlotsSize() <<std::endl; */
  /* std::cout << "Layer numbers:" << bank->getLayersSize() <<std::endl; */
  /* std::cout << "Frame numbers:" << bank->getFramesSize() <<std::endl; */
  /* std::cout << "FEB numbers:" << bank->getFEBsSize() <<std::endl; */
  /* std::cout << "TRB numbers:" << bank->getTRBsSize() <<std::endl; */
  /* std::cout << "TOMB channel numbers:" << bank->getTOMBChannelsSize() <<std::endl; */
  BOOST_REQUIRE(bank->getScintillatorsSize() > 0);
  BOOST_REQUIRE(bank->getPMsSize() > 0);
  BOOST_REQUIRE(bank->getPMCalibsSize() == 0); // 0 due to run id == 26  // TODO Check it with DB // RESOLVED sql function returns (0 rows) for run_id=26
  BOOST_REQUIRE(bank->getBarrelSlotsSize() == 2);
  BOOST_REQUIRE(bank->getLayersSize() == 1);
  BOOST_REQUIRE(bank->getFramesSize() == 1);
  BOOST_REQUIRE(bank->getFEBsSize() > 0);
  BOOST_REQUIRE(bank->getTRBsSize() > 0);
  BOOST_REQUIRE(bank->getTOMBChannelsSize() > 0);
}

BOOST_AUTO_TEST_CASE(fillTRefsTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
  JPetDBParamGetter paramGetter;
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  
  /* std::cout << "Scintillators number:" << bank->getScintillatorsSize() <<std::endl; */
  /* std::cout << "PM numbers:" << bank->getPMsSize() <<std::endl; */
  /* std::cout << "FEB numbers:" << bank->getFEBsSize() <<std::endl; */
  /* std::cout << "TRB numbers:" << bank->getTRBsSize() <<std::endl; */
  /* std::cout << "TOMB channel numbers:" << bank->getTOMBChannelsSize() <<std::endl; */

  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getFEBsSize() == 1);
  BOOST_REQUIRE(bank->getTRBsSize() == 1);
  BOOST_REQUIRE(bank->getTOMBChannelsSize() == 4);
  
  paramGetter.fillPMsTRefs(run, *bank);
  paramGetter.fillFEBsTRefs(run, *bank);
  paramGetter.fillTOMBChannelsTRefs(run, *bank);
  
  // PM TRef to Scint
		// TODO(timorl): this probably doesn't work after the id changes, check and fix
  JPetPM& pm_ref = bank->getPM(0);
  BOOST_REQUIRE(pm_ref.getScin().getID()== bank->getScintillator(1).getID());
  pm_ref = bank->getPM(1);
  BOOST_REQUIRE(pm_ref.getScin().getID()== bank->getScintillator(0).getID());
  pm_ref = bank->getPM(2);
  BOOST_REQUIRE(pm_ref.getScin().getID()== bank->getScintillator(0).getID());
  pm_ref = bank->getPM(3);
  BOOST_REQUIRE(pm_ref.getScin().getID()== bank->getScintillator(1).getID());
  
		for (auto & cs : bank->getPMs()) {
				BOOST_REQUIRE(cs.second->getFEB().isActive());
		}

  // Consistency of TRefs from TOMBChannels
  for (auto & cs : bank->getTOMBChannels()){
    JPetTOMBChannel & TOMBChannel_ref = *cs.second;
    BOOST_REQUIRE(TOMBChannel_ref.getFEB().isActive());
    BOOST_REQUIRE_EQUAL(TOMBChannel_ref.getFEB().getID() ,TOMBChannel_ref.getPM().getFEB().getID());
    BOOST_REQUIRE_EQUAL(TOMBChannel_ref.getTRB().getID() ,TOMBChannel_ref.getFEB().getTRB().getID());
  }
  

  /* 
   * Possible bug in implementation - for the same TOMBChannel two PMs are possible?
  TOMBChannel_ref = bank->getTOMBChannel(1);
  PM_ref = bank->getPM(2);
  */
}  

BOOST_AUTO_TEST_CASE(fillBarrelSlotTRefTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
  JPetDBParamGetter paramGetter;
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  
  /* std::cout << "Scintillators size:" << bank->getScintillatorsSize() <<std::endl; */
  /* std::cout << "PM size:" << bank->getPMsSize() <<std::endl; */
  /* std::cout << "FEB size:" << bank->getFEBsSize() <<std::endl; */
  /* std::cout << "TRB size:" << bank->getTRBsSize() <<std::endl; */
  /* std::cout << "TOMB channel size:" << bank->getTOMBChannelsSize() <<std::endl; */
  /* std::cout << "Barrel slot size:" << bank->getBarrelSlotsSize() <<std::endl; */
  /* std::cout << "Layer size:" << bank->getLayersSize() <<std::endl; */

  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getFEBsSize() == 1);
  BOOST_REQUIRE(bank->getTRBsSize() == 1);
  BOOST_REQUIRE(bank->getTOMBChannelsSize() == 4);
  BOOST_REQUIRE(bank->getBarrelSlotsSize() == 2);
  BOOST_REQUIRE(bank->getLayersSize() == 1);
  
  paramGetter.fillBarrelSlotTRefs(run, *bank);
  
  // BarrelSlot TRef for Layer
  JPetBarrelSlot& barrelSlot = *(bank->getBarrelSlots().begin()->second);
  BOOST_REQUIRE(barrelSlot.getLayer().getId() == 1);
}

BOOST_AUTO_TEST_CASE(fillLayerTRefTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
  JPetDBParamGetter paramGetter;
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  
  /* std::cout << "Scintillators size:" << bank->getScintillatorsSize() <<std::endl; */
  /* std::cout << "PM size:" << bank->getPMsSize() <<std::endl; */
  /* std::cout << "FEB size:" << bank->getFEBsSize() <<std::endl; */
  /* std::cout << "TRB size:" << bank->getTRBsSize() <<std::endl; */
  /* std::cout << "TOMB channel size:" << bank->getTOMBChannelsSize() <<std::endl; */
  /* std::cout << "Barrel slot size:" << bank->getBarrelSlotsSize() <<std::endl; */
  /* std::cout << "Layer size:" << bank->getLayersSize() <<std::endl; */

  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getFEBsSize() == 1);
  BOOST_REQUIRE(bank->getTRBsSize() == 1);
  BOOST_REQUIRE(bank->getTOMBChannelsSize() == 4);
  BOOST_REQUIRE(bank->getBarrelSlotsSize() == 2);
  BOOST_REQUIRE(bank->getLayersSize() == 1);
  
  paramGetter.fillLayerTRefs(run, *bank);
  
  // Layer TRef for Frame
  JPetLayer& layer = *(bank->getLayers().begin()->second);
  BOOST_REQUIRE(layer.getFrame().getId() == 1);
}

BOOST_AUTO_TEST_CASE(getDataFromDBTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
  JPetDBParamGetter paramGetter;
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getDataFromPhotoMultipliers", "1");
  size_t l_sizeResultQuerry = l_runDbResults.size();

  BOOST_REQUIRE(l_sizeResultQuerry > 0);
}

BOOST_AUTO_TEST_CASE(generateSelectQueryTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
  JPetDBParamGetter paramGetter;
  std::string selectQuerry = paramGetter.generateSelectQuery("getDataFromTRBs", "1");
  BOOST_REQUIRE(selectQuerry == "SELECT * FROM getDataFromTRBs(1);");
}

BOOST_AUTO_TEST_CASE(fillContainersTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  int run  = 1;
  JPetParamBank bank;
  
  /* std::cout << "Scintillators number:" << bank.getScintillatorsSize() <<std::endl; */
  /* std::cout << "PM numbers:" << bank.getPMsSize() <<std::endl; */
  /* std::cout << "PMCalib numbers:" << bank.getPMCalibsSize() <<std::endl; */
  /* std::cout << "BarrelSlot numbers:" << bank.getBarrelSlotsSize() <<std::endl; */
  /* std::cout << "Layer numbers:" << bank.getLayersSize() <<std::endl; */
  /* std::cout << "Frame numbers:" << bank.getFramesSize() <<std::endl; */
  /* std::cout << "FEB numbers:" << bank.getFEBsSize() <<std::endl; */
  /* std::cout << "TRB numbers:" << bank.getTRBsSize() <<std::endl; */
  /* std::cout << "TOMB channel numbers:" << bank.getTOMBChannelsSize() <<std::endl; */

  BOOST_REQUIRE(bank.getScintillatorsSize() == 0);
  BOOST_REQUIRE(bank.getPMsSize() == 0);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
  BOOST_REQUIRE(bank.getBarrelSlotsSize() == 0);
  BOOST_REQUIRE(bank.getLayersSize() == 0);
  BOOST_REQUIRE(bank.getFramesSize() == 0);
  BOOST_REQUIRE(bank.getFEBsSize() == 0);
  BOOST_REQUIRE(bank.getTRBsSize() == 0);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 0);
  
  paramGetter.fillScintillators(run, bank);
  paramGetter.fillPMs(run, bank);
  paramGetter.fillPMCalibs(run, bank);
  paramGetter.fillBarrelSlot(run, bank);
  paramGetter.fillLayer(run, bank);
  paramGetter.fillFrame(run, bank);
  paramGetter.fillFEBs(run, bank);
  paramGetter.fillTRBs(run, bank);
  paramGetter.fillTOMBChannels(run, bank);
  
  BOOST_REQUIRE(bank.getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank.getPMsSize() == 4);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 0); // 0 due to run id == 1  // TODO Check it with DB // RESOLVED sql function returns (0 rows) for run_id=1
  BOOST_REQUIRE(bank.getBarrelSlotsSize() == 2);
  BOOST_REQUIRE(bank.getLayersSize() == 1);
  BOOST_REQUIRE(bank.getFramesSize() == 1);
  BOOST_REQUIRE(bank.getFEBsSize() == 1);
  BOOST_REQUIRE(bank.getTRBsSize() == 1);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 4);
  
  bank.clear();
  
  BOOST_REQUIRE(bank.getScintillatorsSize() == 0);
  BOOST_REQUIRE(bank.getPMsSize() == 0);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
  BOOST_REQUIRE(bank.getBarrelSlotsSize() == 0);
  BOOST_REQUIRE(bank.getLayersSize() == 0);
  BOOST_REQUIRE(bank.getFramesSize() == 0);
  BOOST_REQUIRE(bank.getFEBsSize() == 0);
  BOOST_REQUIRE(bank.getTRBsSize() == 0);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 0);
}

BOOST_AUTO_TEST_CASE(generateScintillatorTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  JPetParamBank bank;
  
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getDataFromScintillators", "1");
  size_t l_sizeResultQuerry = l_runDbResults.size();
  
  if(l_sizeResultQuerry) 
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) 
    {
      JPetScin l_scin = paramGetter.generateScintillator(row);
      bank.addScintillator(l_scin);
    }
  }
  BOOST_REQUIRE(bank.getScintillatorsSize() == 2);
}

BOOST_AUTO_TEST_CASE(generatePMTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  JPetParamBank bank;
  
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getDataFromPhotoMultipliers", "1");
  size_t l_sizeResultQuerry = l_runDbResults.size();
  
  if(l_sizeResultQuerry) 
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) 
    {
      JPetPM l_pm = paramGetter.generatePM(row);
      bank.addPM(l_pm);
    }
  }
  BOOST_REQUIRE(bank.getPMsSize() == 4);
}

BOOST_AUTO_TEST_CASE(generatePMCalibTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  JPetParamBank bank;
  
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getPmCalibration", "2"); // TODO Check it with DB // RESOLVED - correct
  size_t l_sizeResultQuerry = l_runDbResults.size();
  
  if(l_sizeResultQuerry) 
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) 
    {
      JPetPMCalib l_pmCalib = paramGetter.generatePMCalib(row);
      bank.addPMCalib(l_pmCalib);
    }
  }
  BOOST_REQUIRE(bank.getPMCalibsSize() == 4); // TODO Check it with DB // RESOLVED sql function returns (1 rows) for run_id=2
}

BOOST_AUTO_TEST_CASE(generateBarrelSlotTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  JPetParamBank bank;
  
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getBarrelSlot", "1");
  size_t l_sizeResultQuerry = l_runDbResults.size();
  
  if(l_sizeResultQuerry) 
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) 
    { 
      JPetBarrelSlot l_barrelSlot = paramGetter.generateBarrelSlot(row);
      bank.addBarrelSlot(l_barrelSlot);
    }
  }
  BOOST_REQUIRE(bank.getBarrelSlotsSize() == 2);
}

BOOST_AUTO_TEST_CASE(generateLayerTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  JPetParamBank bank;
  
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getLayer", "1");
  size_t l_sizeResultQuerry = l_runDbResults.size();
  
  if(l_sizeResultQuerry) 
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) 
    { 
      JPetLayer l_layer = paramGetter.generateLayer(row);
      bank.addLayer(l_layer);
    }
  }
  BOOST_REQUIRE(bank.getLayersSize() == 1);
}

BOOST_AUTO_TEST_CASE(generateFrameTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  JPetParamBank bank;
  
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getFrame", "1");
  size_t l_sizeResultQuerry = l_runDbResults.size();
  
  if(l_sizeResultQuerry) 
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) 
    {
      JPetFrame l_frame = paramGetter.generateFrame(row);
      bank.addFrame(l_frame);
    }
  }
  BOOST_REQUIRE(bank.getFramesSize() == 1);
}

BOOST_AUTO_TEST_CASE(generateFEBTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  JPetParamBank bank;
  
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getDataFromKonradBoards", "1");
  size_t l_sizeResultQuerry = l_runDbResults.size();
  
  if(l_sizeResultQuerry) 
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) 
    {
      JPetFEB l_FEB = paramGetter.generateFEB(row);
      bank.addFEB(l_FEB);
    }
  }
  BOOST_REQUIRE(bank.getFEBsSize() == 1);
}

BOOST_AUTO_TEST_CASE(generateTRBTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  JPetParamBank bank;
  
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getDataFromTRBs", "1");
  size_t l_sizeResultQuerry = l_runDbResults.size();
  
  if(l_sizeResultQuerry) 
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) 
    {
      JPetTRB l_TRB = paramGetter.generateTRB(row);
      bank.addTRB(l_TRB);
    }
  }
  BOOST_REQUIRE(bank.getTRBsSize() == 1);
}

BOOST_AUTO_TEST_CASE(generateTOMBChannelTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  JPetParamBank bank;
  
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getEverythingVsTOMB", "1");
  size_t l_sizeResultQuerry = l_runDbResults.size();
  
  if(l_sizeResultQuerry) 
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) 
    {
      JPetTOMBChannel l_TOMBChannel = paramGetter.generateTOMBChannel(row);
      bank.addTOMBChannel(l_TOMBChannel);
    }
  }
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 4);
}

BOOST_AUTO_TEST_CASE(GetDataFromDBAndFillPMCalibsTest)
{
	DB::SERVICES::DBHandler::createInstance(gDefaultConfigFile);
	
  JPetDBParamGetter paramGetter;
  int run  = 2;
  JPetParamBank bank;
  
  /* std::cout << "PMCalib numbers:" << bank.getPMCalibsSize() <<std::endl; */

  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
  
  paramGetter.fillPMCalibs(run, bank);
  
  BOOST_REQUIRE(bank.getPMCalibsSize() == 4); // 0 due to run id == 1  // TODO Check it with DB // RESOLVED sql function returns (4 rows) for run_id=2

		auto calibs = bank.getPMCalibs().begin();

		JPetPMCalib & calib1 = *(calibs->second);
  
  BOOST_REQUIRE(calib1.GetId() == 1);
  BOOST_REQUIRE(calib1.GetNamePM() == "dummy");
  BOOST_REQUIRE(calib1.GetOpthv() == 0);
  BOOST_REQUIRE(calib1.GetECalConst1() == 0);
  BOOST_REQUIRE(calib1.GetECalConst2() == 0);
  BOOST_REQUIRE(calib1.GetGainalpha() == 0);
  BOOST_REQUIRE(calib1.GetGainbeta() == 0);
  
  BOOST_REQUIRE(calib1.GetPMCalibAssignment().id == 2);
  BOOST_REQUIRE(calib1.GetPMCalibAssignment().photomultiplier_id == 3);
  
		calibs++;
		JPetPMCalib & calib2 = *(calibs->second);

  BOOST_REQUIRE(calib2.GetId() == 1);
  BOOST_REQUIRE(calib2.GetNamePM() == "dummy");
  BOOST_REQUIRE(calib2.GetOpthv() == 0);
  BOOST_REQUIRE(calib2.GetECalConst1() == 0);
  BOOST_REQUIRE(calib2.GetECalConst2() == 0);
  BOOST_REQUIRE(calib2.GetGainalpha() == 0);
  BOOST_REQUIRE(calib2.GetGainbeta() == 0);
  
  BOOST_REQUIRE(calib2.GetPMCalibAssignment().id == 1);
  BOOST_REQUIRE(calib2.GetPMCalibAssignment().photomultiplier_id == 1);
  
		calibs++;
		JPetPMCalib & calib3 = *(calibs->second);

  BOOST_REQUIRE(calib3.GetId() == 1);
  BOOST_REQUIRE(calib3.GetNamePM() == "dummy");
  BOOST_REQUIRE(calib3.GetOpthv() == 0);
  BOOST_REQUIRE(calib3.GetECalConst1() == 0);
  BOOST_REQUIRE(calib3.GetECalConst2() == 0);
  BOOST_REQUIRE(calib3.GetGainalpha() == 0);
  BOOST_REQUIRE(calib3.GetGainbeta() == 0);
  
  BOOST_REQUIRE(calib3.GetPMCalibAssignment().id == 3);
  BOOST_REQUIRE(calib3.GetPMCalibAssignment().photomultiplier_id == 7);
  
		calibs++;
		JPetPMCalib & calib4 = *(calibs->second);

  BOOST_REQUIRE(calib4.GetId() == 1);
  BOOST_REQUIRE(calib4.GetNamePM() == "dummy");
  BOOST_REQUIRE(calib4.GetOpthv() == 0);
  BOOST_REQUIRE(calib4.GetECalConst1() == 0);
  BOOST_REQUIRE(calib4.GetECalConst2() == 0);
  BOOST_REQUIRE(calib4.GetGainalpha() == 0);
  BOOST_REQUIRE(calib4.GetGainbeta() == 0);
  
  BOOST_REQUIRE(calib4.GetPMCalibAssignment().id == 4);
  BOOST_REQUIRE(calib4.GetPMCalibAssignment().photomultiplier_id == 4);
  
  bank.clear();

  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
}

BOOST_AUTO_TEST_SUITE_END()

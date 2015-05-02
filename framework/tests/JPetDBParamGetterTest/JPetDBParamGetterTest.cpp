#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetDBParamGetterTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetDBParamGetter/JPetDBParamGetter.h"

const char* gDefaultConfigFile = "DBConfig/configDB.cfg";

BOOST_AUTO_TEST_SUITE(DBParamGetterTS)

//public:
//  enum ParamObjectType {kScintillator, kPM, kPMCalib, kFEB, kTRB, kTOMBChannel, kBarrelSlot, SIZE};
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
//  int getTOMBChannelFromDescription(std::string p_desc) const;
//

BOOST_AUTO_TEST_CASE(defaultConstructorTest)
{
  JPetDBParamGetter paramGetter;
}

BOOST_AUTO_TEST_CASE(dummyFillingTest)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  
  std::cout << "Scintillators number:" << bank->getScintillatorsSize() <<std::endl;
  std::cout << "PM numbers:" << bank->getPMsSize() <<std::endl;
  std::cout << "PMCalib numbers:" << bank->getPMCalibsSize() <<std::endl;
  std::cout << "BarrelSlot numbers:" << bank->getBarrelSlotsSize() <<std::endl;
  std::cout << "Layer numbers:" << bank->getLayersSize() <<std::endl;
  std::cout << "Frame numbers:" << bank->getFramesSize() <<std::endl;
  std::cout << "FEB numbers:" << bank->getFEBsSize() <<std::endl;
  std::cout << "TRB numbers:" << bank->getTRBsSize() <<std::endl;
  std::cout << "TOMB channel numbers:" << bank->getTOMBChannelsSize() <<std::endl;

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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 28;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  std::cout << "Scintillators number:" << bank->getScintillatorsSize() <<std::endl;
  std::cout << "PM numbers:" << bank->getPMsSize() <<std::endl;
  std::cout << "PMCalib numbers:" << bank->getPMCalibsSize() <<std::endl;
  std::cout << "BarrelSlot numbers:" << bank->getBarrelSlotsSize() <<std::endl;
  std::cout << "Layer numbers:" << bank->getLayersSize() <<std::endl;
  std::cout << "Frame numbers:" << bank->getFramesSize() <<std::endl;
  std::cout << "FEB numbers:" << bank->getFEBsSize() <<std::endl;
  std::cout << "TRB numbers:" << bank->getTRBsSize() <<std::endl;
  std::cout << "TOMB channel numbers:" << bank->getTOMBChannelsSize() <<std::endl;
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  
  std::cout << "Scintillators number:" << bank->getScintillatorsSize() <<std::endl;
  std::cout << "PM numbers:" << bank->getPMsSize() <<std::endl;
  std::cout << "FEB numbers:" << bank->getFEBsSize() <<std::endl;
  std::cout << "TRB numbers:" << bank->getTRBsSize() <<std::endl;
  std::cout << "TOMB channel numbers:" << bank->getTOMBChannelsSize() <<std::endl;

  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getFEBsSize() == 1);
  BOOST_REQUIRE(bank->getTRBsSize() == 1);
  BOOST_REQUIRE(bank->getTOMBChannelsSize() == 4);
  
  paramGetter.fillPMsTRefs(run, *bank);
  paramGetter.fillFEBsTRefs(run, *bank);
  paramGetter.fillTOMBChannelsTRefs(run, *bank);
  
  // PM TRef to Scint
  JPetPM& pm_ref = bank->getPM(0);
  BOOST_REQUIRE(pm_ref.getScin().getID()== bank->getScintillator(1).getID());
  pm_ref = bank->getPM(1);
  BOOST_REQUIRE(pm_ref.getScin().getID()== bank->getScintillator(0).getID());
  pm_ref = bank->getPM(2);
  BOOST_REQUIRE(pm_ref.getScin().getID()== bank->getScintillator(0).getID());
  pm_ref = bank->getPM(3);
  BOOST_REQUIRE(pm_ref.getScin().getID()== bank->getScintillator(1).getID());
  
  BOOST_REQUIRE(bank->getPM(0).getFEB().isActive());
  BOOST_REQUIRE(bank->getPM(1).getFEB().isActive());
  BOOST_REQUIRE(bank->getPM(2).getFEB().isActive());
  BOOST_REQUIRE(bank->getPM(3).getFEB().isActive());

  // Consistency of TRefs from TOMBChannels
  for(int i=0;i<bank->getTOMBChannelsSize();++i){
    JPetTOMBChannel& TOMBChannel_ref = bank->getTOMBChannel(i);
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  
  std::cout << "Scintillators size:" << bank->getScintillatorsSize() <<std::endl;
  std::cout << "PM size:" << bank->getPMsSize() <<std::endl;
  std::cout << "FEB size:" << bank->getFEBsSize() <<std::endl;
  std::cout << "TRB size:" << bank->getTRBsSize() <<std::endl;
  std::cout << "TOMB channel size:" << bank->getTOMBChannelsSize() <<std::endl;
  std::cout << "Barrel slot size:" << bank->getBarrelSlotsSize() <<std::endl;
  std::cout << "Layer size:" << bank->getLayersSize() <<std::endl;

  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getFEBsSize() == 1);
  BOOST_REQUIRE(bank->getTRBsSize() == 1);
  BOOST_REQUIRE(bank->getTOMBChannelsSize() == 4);
  BOOST_REQUIRE(bank->getBarrelSlotsSize() == 2);
  BOOST_REQUIRE(bank->getLayersSize() == 1);
  
  paramGetter.fillBarrelSlotTRefs(run, *bank);
  
  // BarrelSlot TRef for Layer
  JPetBarrelSlot& barrelSlot = bank->getBarrelSlot(0);
  BOOST_REQUIRE(barrelSlot.getLayer().getId() == 1);
}

BOOST_AUTO_TEST_CASE(fillLayerTRefTest)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  
  std::cout << "Scintillators size:" << bank->getScintillatorsSize() <<std::endl;
  std::cout << "PM size:" << bank->getPMsSize() <<std::endl;
  std::cout << "FEB size:" << bank->getFEBsSize() <<std::endl;
  std::cout << "TRB size:" << bank->getTRBsSize() <<std::endl;
  std::cout << "TOMB channel size:" << bank->getTOMBChannelsSize() <<std::endl;
  std::cout << "Barrel slot size:" << bank->getBarrelSlotsSize() <<std::endl;
  std::cout << "Layer size:" << bank->getLayersSize() <<std::endl;

  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getFEBsSize() == 1);
  BOOST_REQUIRE(bank->getTRBsSize() == 1);
  BOOST_REQUIRE(bank->getTOMBChannelsSize() == 4);
  BOOST_REQUIRE(bank->getBarrelSlotsSize() == 2);
  BOOST_REQUIRE(bank->getLayersSize() == 1);
  
  paramGetter.fillLayerTRefs(run, *bank);
  
  // Layer TRef for Frame
  JPetLayer& layer = bank->getLayer(0);
  BOOST_REQUIRE(layer.getFrame().getId() == 1);
}
/*
BOOST_AUTO_TEST_CASE(fillPMTRefsWithBarrelSlotTest)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  
  std::cout << "PM size:" << bank->getPMsSize() <<std::endl;
  std::cout << "Barrel slot size:" << bank->getBarrelSlotsSize() <<std::endl;

  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getBarrelSlotsSize() == 2);
  
  // PM TRef for BarrelSlot
  JPetPM& l_PM = bank->getPM(0);
  std::cout << l_PM.getBarrelSlot().getID() << std::endl;
}

BOOST_AUTO_TEST_CASE(fillScintillatorTRefsWithBarrelSlotTest)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  
  std::cout << "Scintillators size:" << bank->getScintillatorsSize() <<std::endl;
  std::cout << "Barrel slot size:" << bank->getBarrelSlotsSize() <<std::endl;

  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getBarrelSlotsSize() == 2);
  
  // Scintillator TRef for BarrelSlot
  JPetScin& l_scintillator = bank->getScintillator(0);
  std::cout << l_scintillator.getBarrelSlot().getID() << std::endl;
}
*/
BOOST_AUTO_TEST_CASE(getDataFromDBTest)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getDataFromPhotoMultipliers", "1");
  size_t l_sizeResultQuerry = l_runDbResults.size();

  BOOST_REQUIRE(l_sizeResultQuerry > 0);
}

BOOST_AUTO_TEST_CASE(generateSelectQueryTest)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  std::string selectQuerry = paramGetter.generateSelectQuery("getDataFromTRBs", "1");
  BOOST_REQUIRE(selectQuerry == "SELECT * FROM getDataFromTRBs(1);");
}

BOOST_AUTO_TEST_CASE(fillContainersTest)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 1;
  JPetParamBank bank;
  
  std::cout << "Scintillators number:" << bank.getScintillatorsSize() <<std::endl;
  std::cout << "PM numbers:" << bank.getPMsSize() <<std::endl;
  std::cout << "PMCalib numbers:" << bank.getPMCalibsSize() <<std::endl;
  std::cout << "BarrelSlot numbers:" << bank.getBarrelSlotsSize() <<std::endl;
  std::cout << "Layer numbers:" << bank.getLayersSize() <<std::endl;
  std::cout << "Frame numbers:" << bank.getFramesSize() <<std::endl;
  std::cout << "FEB numbers:" << bank.getFEBsSize() <<std::endl;
  std::cout << "TRB numbers:" << bank.getTRBsSize() <<std::endl;
  std::cout << "TOMB channel numbers:" << bank.getTOMBChannelsSize() <<std::endl;

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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
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
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 2;
  JPetParamBank bank;
  
  std::cout << "PMCalib numbers:" << bank.getPMCalibsSize() <<std::endl;

  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
  
  paramGetter.fillPMCalibs(run, bank);
  
  BOOST_REQUIRE(bank.getPMCalibsSize() == 4); // 0 due to run id == 1  // TODO Check it with DB // RESOLVED sql function returns (4 rows) for run_id=2
  
  BOOST_REQUIRE(bank.getPMCalib(0).GetId() == 1);
  BOOST_REQUIRE(bank.getPMCalib(0).GetNamePM() == "dummy");
  BOOST_REQUIRE(bank.getPMCalib(0).GetOpthv() == 0);
  BOOST_REQUIRE(bank.getPMCalib(0).GetECalConst1() == 0);
  BOOST_REQUIRE(bank.getPMCalib(0).GetECalConst2() == 0);
  BOOST_REQUIRE(bank.getPMCalib(0).GetGainalpha() == 0);
  BOOST_REQUIRE(bank.getPMCalib(0).GetGainbeta() == 0);
  
  BOOST_REQUIRE(bank.getPMCalib(0).GetPMCalibAssignment().id == 2);
  BOOST_REQUIRE(bank.getPMCalib(0).GetPMCalibAssignment().photomultiplier_id == 3);
  
  BOOST_REQUIRE(bank.getPMCalib(1).GetId() == 1);
  BOOST_REQUIRE(bank.getPMCalib(1).GetNamePM() == "dummy");
  BOOST_REQUIRE(bank.getPMCalib(1).GetOpthv() == 0);
  BOOST_REQUIRE(bank.getPMCalib(1).GetECalConst1() == 0);
  BOOST_REQUIRE(bank.getPMCalib(1).GetECalConst2() == 0);
  BOOST_REQUIRE(bank.getPMCalib(1).GetGainalpha() == 0);
  BOOST_REQUIRE(bank.getPMCalib(1).GetGainbeta() == 0);
  
  BOOST_REQUIRE(bank.getPMCalib(1).GetPMCalibAssignment().id == 1);
  BOOST_REQUIRE(bank.getPMCalib(1).GetPMCalibAssignment().photomultiplier_id == 1);
  
  BOOST_REQUIRE(bank.getPMCalib(2).GetId() == 1);
  BOOST_REQUIRE(bank.getPMCalib(2).GetNamePM() == "dummy");
  BOOST_REQUIRE(bank.getPMCalib(2).GetOpthv() == 0);
  BOOST_REQUIRE(bank.getPMCalib(2).GetECalConst1() == 0);
  BOOST_REQUIRE(bank.getPMCalib(2).GetECalConst2() == 0);
  BOOST_REQUIRE(bank.getPMCalib(2).GetGainalpha() == 0);
  BOOST_REQUIRE(bank.getPMCalib(2).GetGainbeta() == 0);
  
  BOOST_REQUIRE(bank.getPMCalib(2).GetPMCalibAssignment().id == 3);
  BOOST_REQUIRE(bank.getPMCalib(2).GetPMCalibAssignment().photomultiplier_id == 7);
  
  BOOST_REQUIRE(bank.getPMCalib(3).GetId() == 1);
  BOOST_REQUIRE(bank.getPMCalib(3).GetNamePM() == "dummy");
  BOOST_REQUIRE(bank.getPMCalib(3).GetOpthv() == 0);
  BOOST_REQUIRE(bank.getPMCalib(3).GetECalConst1() == 0);
  BOOST_REQUIRE(bank.getPMCalib(3).GetECalConst2() == 0);
  BOOST_REQUIRE(bank.getPMCalib(3).GetGainalpha() == 0);
  BOOST_REQUIRE(bank.getPMCalib(3).GetGainbeta() == 0);
  
  BOOST_REQUIRE(bank.getPMCalib(3).GetPMCalibAssignment().id == 4);
  BOOST_REQUIRE(bank.getPMCalib(3).GetPMCalibAssignment().photomultiplier_id == 4);
  
  bank.clear();

  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
}

BOOST_AUTO_TEST_SUITE_END()

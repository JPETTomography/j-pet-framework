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
  std::cout << "FEB numbers:" << bank->getFEBsSize() <<std::endl;
  std::cout << "TRB numbers:" << bank->getTRBsSize() <<std::endl;
  std::cout << "TOMB channel numbers:" << bank->getTOMBChannelsSize() <<std::endl;

  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getPMCalibsSize() == 0); // 0 due to run id == 1  // TODO Check it with DB
  BOOST_REQUIRE(bank->getFEBsSize() == 1);
  BOOST_REQUIRE(bank->getTRBsSize() == 1);
  BOOST_REQUIRE(bank->getTOMBChannelsSize() == 4);
}

BOOST_AUTO_TEST_CASE(run26Test)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 26;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  std::cout << "Scintillators number:" << bank->getScintillatorsSize() <<std::endl;
  std::cout << "PM numbers:" << bank->getPMsSize() <<std::endl;
  std::cout << "PMCalib numbers:" << bank->getPMCalibsSize() <<std::endl;
  std::cout << "FEB numbers:" << bank->getFEBsSize() <<std::endl;
  std::cout << "TRB numbers:" << bank->getTRBsSize() <<std::endl;
  std::cout << "TOMB channel numbers:" << bank->getTOMBChannelsSize() <<std::endl;
  BOOST_REQUIRE(bank->getScintillatorsSize() > 0);
  BOOST_REQUIRE(bank->getPMsSize() > 0);
  BOOST_REQUIRE(bank->getPMCalibsSize() == 0); // 0 due to run id == 26  // TODO Check it with DB
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
  
  // TOMBChannels  1
  JPetTOMBChannel& TOMBChannel_ref = bank->getTOMBChannel(0);
  BOOST_REQUIRE(TOMBChannel_ref.getFEB().isActive());
  
  JPetFEB& FEB_ref = bank->getFEB(0);
  const JPetFEB& FEB_ref2 = TOMBChannel_ref.getFEB();
  BOOST_REQUIRE(FEB_ref.getID() == FEB_ref2.getID());
  JPetTRB& TRB_ref = bank->getTRB(0);
  const JPetTRB& TRB_ref2 = TOMBChannel_ref.getTRB();
  BOOST_REQUIRE(TRB_ref.getID() == TRB_ref2.getID());
  JPetPM& PM_ref = bank->getPM(0);
  const JPetPM& PM_ref2 =TOMBChannel_ref.getPM();
  BOOST_REQUIRE(PM_ref.getID() == PM_ref2.getID());


  
//  // TOMBChannels 2 
//  TOMBChannel_ref = bank->getTOMBChannel(1);
//  BOOST_REQUIRE(TOMBChannel_ref.getFEB().isActive());
//  FEB_ref = bank->getFEB(0);
//  FEB_ref2 = TOMBChannel_ref.getFEB();
//  BOOST_REQUIRE(FEB_ref.getID() == FEB_ref2.getID());
//  TRB_ref = bank->getTRB(0);
//  TRB_ref2 = TOMBChannel_ref.getTRB();
//  BOOST_REQUIRE(TRB_ref.getID() == TRB_ref2.getID());
//  PM_ref = bank->getPM(0);
//  PM_ref2 =TOMBChannel_ref.getPM();
//  BOOST_REQUIRE(PM_ref.getID() == PM_ref2.getID());
//  
//  TOMBChannel_ref = bank->getTOMBChannel(2);
//  BOOST_REQUIRE(TOMBChannel_ref.getFEB().isActive());
//  FEB_ref = bank->getFEB(0);
//  FEB_ref2 = TOMBChannel_ref.getFEB();
//  BOOST_REQUIRE(FEB_ref.getID() == FEB_ref2.getID());
//  TRB_ref = bank->getTRB(0);
//  TRB_ref2 = TOMBChannel_ref.getTRB();
//  BOOST_REQUIRE(TRB_ref.getID() == TRB_ref2.getID());
//  PM_ref = bank->getPM(0);
//  PM_ref2 =TOMBChannel_ref.getPM();
//  BOOST_REQUIRE(PM_ref.getID() == PM_ref2.getID());
//
//  TOMBChannel_ref = bank->getTOMBChannel(3);
//  BOOST_REQUIRE(TOMBChannel_ref.getFEB().isActive());
//  FEB_ref = bank->getFEB(0);
//  FEB_ref2 = TOMBChannel_ref.getFEB();
//  BOOST_REQUIRE(FEB_ref.getID() == FEB_ref2.getID());
//  TRB_ref = bank->getTRB(0);
//  TRB_ref2 = TOMBChannel_ref.getTRB();
//  BOOST_REQUIRE(TRB_ref.getID() == TRB_ref2.getID());
//  PM_ref = bank->getPM(0);
//  PM_ref2 =TOMBChannel_ref.getPM();
//  BOOST_REQUIRE(PM_ref.getID() == PM_ref2.getID());

  /* 
   * Possible bug in implementation - for the same TOMBChannel two PMs are possible?
  TOMBChannel_ref = bank->getTOMBChannel(1);
  PM_ref = bank->getPM(2);
  */
}  

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
  std::cout << "FEB numbers:" << bank.getFEBsSize() <<std::endl;
  std::cout << "TRB numbers:" << bank.getTRBsSize() <<std::endl;
  std::cout << "TOMB channel numbers:" << bank.getTOMBChannelsSize() <<std::endl;

  BOOST_REQUIRE(bank.getScintillatorsSize() == 0);
  BOOST_REQUIRE(bank.getPMsSize() == 0);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
  BOOST_REQUIRE(bank.getFEBsSize() == 0);
  BOOST_REQUIRE(bank.getTRBsSize() == 0);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 0);
  
  paramGetter.fillScintillators(run, bank);
  paramGetter.fillPMs(run, bank);
  paramGetter.fillPMCalibs(run, bank);
  paramGetter.fillFEBs(run, bank);
  paramGetter.fillTRBs(run, bank);
  paramGetter.fillTOMBChannels(run, bank);
  
  BOOST_REQUIRE(bank.getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank.getPMsSize() == 4);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 0); // 0 due to run id == 1  // TODO Check it with DB
  BOOST_REQUIRE(bank.getFEBsSize() == 1);
  BOOST_REQUIRE(bank.getTRBsSize() == 1);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 4);
  
  bank.clear();
  
  BOOST_REQUIRE(bank.getScintillatorsSize() == 0);
  BOOST_REQUIRE(bank.getPMsSize() == 0);
  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
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
  
  pqxx::result l_runDbResults = paramGetter.getDataFromDB("getDataFromPhotoMultipliersCalibration", "2"); // TODO Check it with DB
  size_t l_sizeResultQuerry = l_runDbResults.size();
  
  if(l_sizeResultQuerry) 
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row) 
    {
      JPetPMCalib l_pmCalib = paramGetter.generatePMCalib(row);
      bank.addPMCalib(l_pmCalib);
    }
  }
  BOOST_REQUIRE(bank.getPMCalibsSize() == 4); // TODO Check it with DB
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
  
  BOOST_REQUIRE(bank.getPMCalibsSize() == 4); // 0 due to run id == 1  // TODO Check it with DB
  
  BOOST_REQUIRE(bank.getPMCalib(0).GetId() == 1);
  BOOST_REQUIRE(bank.getPMCalib(0).GetNamePM() == "dummy");
  BOOST_REQUIRE(bank.getPMCalib(0).GetOpthv() == 0);
  BOOST_REQUIRE(bank.getPMCalib(0).GetECalConst1() == 0);
  BOOST_REQUIRE(bank.getPMCalib(0).GetECalConst2() == 0);
  BOOST_REQUIRE(bank.getPMCalib(0).GetGainalpha() == 0);
  BOOST_REQUIRE(bank.getPMCalib(0).GetGainbeta() == 0);
  BOOST_REQUIRE(bank.getPMCalib(0).GetPMCalibAssignment().id == 1);
  BOOST_REQUIRE(bank.getPMCalib(0).GetPMCalibAssignment().photomultiplier_id == 1);
  
  BOOST_REQUIRE(bank.getPMCalib(1).GetId() == 1);
  BOOST_REQUIRE(bank.getPMCalib(1).GetNamePM() == "dummy");
  BOOST_REQUIRE(bank.getPMCalib(1).GetOpthv() == 0);
  BOOST_REQUIRE(bank.getPMCalib(1).GetECalConst1() == 0);
  BOOST_REQUIRE(bank.getPMCalib(1).GetECalConst2() == 0);
  BOOST_REQUIRE(bank.getPMCalib(1).GetGainalpha() == 0);
  BOOST_REQUIRE(bank.getPMCalib(1).GetGainbeta() == 0);
  BOOST_REQUIRE(bank.getPMCalib(1).GetPMCalibAssignment().id == 4);
  BOOST_REQUIRE(bank.getPMCalib(1).GetPMCalibAssignment().photomultiplier_id == 4);
  
  BOOST_REQUIRE(bank.getPMCalib(2).GetId() == 1);
  BOOST_REQUIRE(bank.getPMCalib(2).GetNamePM() == "dummy");
  BOOST_REQUIRE(bank.getPMCalib(2).GetOpthv() == 0);
  BOOST_REQUIRE(bank.getPMCalib(2).GetECalConst1() == 0);
  BOOST_REQUIRE(bank.getPMCalib(2).GetECalConst2() == 0);
  BOOST_REQUIRE(bank.getPMCalib(2).GetGainalpha() == 0);
  BOOST_REQUIRE(bank.getPMCalib(2).GetGainbeta() == 0);
  BOOST_REQUIRE(bank.getPMCalib(2).GetPMCalibAssignment().id == 2);
  BOOST_REQUIRE(bank.getPMCalib(2).GetPMCalibAssignment().photomultiplier_id == 3);
  
  BOOST_REQUIRE(bank.getPMCalib(3).GetId() == 1);
  BOOST_REQUIRE(bank.getPMCalib(3).GetNamePM() == "dummy");
  BOOST_REQUIRE(bank.getPMCalib(3).GetOpthv() == 0);
  BOOST_REQUIRE(bank.getPMCalib(3).GetECalConst1() == 0);
  BOOST_REQUIRE(bank.getPMCalib(3).GetECalConst2() == 0);
  BOOST_REQUIRE(bank.getPMCalib(3).GetGainalpha() == 0);
  BOOST_REQUIRE(bank.getPMCalib(3).GetGainbeta() == 0);
  BOOST_REQUIRE(bank.getPMCalib(3).GetPMCalibAssignment().id == 3);
  BOOST_REQUIRE(bank.getPMCalib(3).GetPMCalibAssignment().photomultiplier_id == 7);
  
  bank.clear();

  BOOST_REQUIRE(bank.getPMCalibsSize() == 0);
}

BOOST_AUTO_TEST_SUITE_END()

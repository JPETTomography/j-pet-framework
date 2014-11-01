#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetDBParamGetterTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetDBParamGetter/JPetDBParamGetter.h"

const char* gDefaultConfigFile = "DBConfig/configDB.cfg";

BOOST_AUTO_TEST_SUITE(DBParamGetterTS)

//public:
//  enum ParamObjectType {kScintillator, kPM, kFEB, kTRB, kTOMB, SIZE};
//  JPetDBParamGetter();
//  JPetDBParamGetter(const char* dBConfigFile);
//  JPetParamBank generateParamBank(const int p_run_id);
//
//private:
//  pqxx::result getDataFromDB(std::string sqlFunction, int p_id);
//  std::string generateSelectQuery(std::string sqlFunction, std::string arg);
//  void printErrorMessageDB(std::string sqlFunction, int p_run_id);
//  JPetScin generateScintillator(pqxx::result::const_iterator row);
//  JPetPM generatePM(pqxx::result::const_iterator row);
//  JPetFEB generateFEB(pqxx::result::const_iterator row);
//  JPetTRB generateTRB(pqxx::result::const_iterator row);
//  JPetTOMB generateTOMB(pqxx::result::const_iterator row);
//
//  void fillTRefs(ParamObjectType type);
//
//  void fillScintillators(const int p_run_id, JPetParamBank& paramBank);
//  void fillPMs(const int p_run_id, JPetParamBank& paramBank);
//  void fillFEBs(const int p_run_id, JPetParamBank& paramBank);
//  void fillTRBs(const int p_run_id, JPetParamBank& paramBank);
//  void fillTOMB(const int p_run_id, JPetParamBank& paramBank);
//  void fillScintillatorsTRefs(JPetParamBank& paramBank);
//  void fillPMsTRefs(JPetParamBank& paramBank);
//  void fillFEBsTRefs(JPetParamBank& paramBank);
//  void fillTRBsTRefs(JPetParamBank& paramBank);
//  void fillAllTRefs(JPetParamBank& paramBank);

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
  std::cout << "FEB numbers:" << bank->getFEBsSize() <<std::endl;
  std::cout << "TRB numbers:" << bank->getTRBsSize() <<std::endl;
  std::cout << "TOMB channel numbers:" << bank->getTOMBChannelsSize() <<std::endl;

  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
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
  std::cout << "FEB numbers:" << bank->getFEBsSize() <<std::endl;
  std::cout << "TRB numbers:" << bank->getTRBsSize() <<std::endl;
  std::cout << "TOMB channel numbers:" << bank->getTOMBChannelsSize() <<std::endl;
  BOOST_REQUIRE(bank->getScintillatorsSize() > 0);
  BOOST_REQUIRE(bank->getPMsSize() > 0);
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
  
  paramGetter.fillScintillatorsTRefs(run, *bank);
  paramGetter.fillPMsTRefs(run, *bank);
  paramGetter.fillFEBsTRefs(run, *bank);
  paramGetter.fillTRBsTRefs(run, *bank);
  paramGetter.fillTOMBChannelsTRefs(run, *bank);
  
  // Scintillator 1 TRef
  BOOST_REQUIRE(bank->getScintillator(0).getTRefPMLeft() != NULL);
  
  JPetPM* pm_ptr = bank->getScintillator(0).getTRefPMLeft();
  JPetPM& pm_ref = bank->getPM(2);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
  
  pm_ptr = bank->getScintillator(0).getTRefPMRight();
  pm_ref = bank->getPM(1);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
 
  pm_ptr = bank->getScintillator(1).getTRefPMLeft();
  pm_ref = bank->getPM(3);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
  
  pm_ptr = bank->getScintillator(1).getTRefPMRight();
  pm_ref = bank->getPM(0);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
  
  // Scintillator 2 TRef
  BOOST_REQUIRE(bank->getScintillator(1).getTRefPMLeft() != NULL);
  
  pm_ptr = bank->getScintillator(0).getTRefPMLeft();
  pm_ref = bank->getPM(2);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
 
  pm_ptr = bank->getScintillator(0).getTRefPMRight();
  pm_ref = bank->getPM(1);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
   
  pm_ptr = bank->getScintillator(1).getTRefPMLeft();
  pm_ref = bank->getPM(3);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
  
  pm_ptr = bank->getScintillator(1).getTRefPMRight();
  pm_ref = bank->getPM(0);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());

  // std::cout << "pm_ptr->getID():" << pm_ptr->getID() <<std::endl;
  // std::cout << "pm_ref.getID():" << pm_ref.getID() <<std::endl;
  
  // PM 1 TRef
  BOOST_REQUIRE(bank->getPM(0).getTRefKB() != NULL);
  
  JPetFEB* FEB_ptr = bank->getPM(0).getTRefKB();
  JPetFEB& FEB_ref = bank->getFEB(0);
  
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  // PM 2 TRef
  BOOST_REQUIRE(bank->getPM(1).getTRefKB() != NULL);
  
  FEB_ptr = bank->getPM(0).getTRefKB();
  FEB_ref = bank->getFEB(0);
  
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  // PM 3 TRef
  BOOST_REQUIRE(bank->getPM(2).getTRefKB() != NULL);
  
  FEB_ptr = bank->getPM(0).getTRefKB();
  FEB_ref = bank->getFEB(0);
  
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  // PM 4 TRef
  BOOST_REQUIRE(bank->getPM(3).getTRefKB() != NULL);
  
  FEB_ptr = bank->getPM(0).getTRefKB();
  FEB_ref = bank->getFEB(0);
  
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  // FEB TRef
  BOOST_REQUIRE(bank->getFEB(0).getTRefTRB() != NULL);
  
  JPetTRB* TRB_ptr = bank->getFEB(0).getTRefTRB();
  JPetTRB& TRB_ref = bank->getTRB(0);
  
  BOOST_REQUIRE(TRB_ptr->getID() == TRB_ref.getID());
  
  // TRB TRef
  // Lack of implementation
  
  // TOMBChannels 1 TRefs
  JPetTOMBChannel& TOMBChannel_ref = bank->getTOMBChannel(0);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  
  FEB_ptr = TOMBChannel_ref.getTRefFEB();
  FEB_ref = bank->getFEB(0);
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  TRB_ptr  = TOMBChannel_ref.getTRefTRB();
  TRB_ref = bank->getTRB(0);
  BOOST_REQUIRE(TRB_ptr->getID() == TRB_ref.getID());
  
  JPetPM* PM_ptr = TOMBChannel_ref.getTRefPM();
  JPetPM& PM_ref = bank->getPM(1);
  BOOST_REQUIRE(PM_ptr->getID() == PM_ref.getID());
  
  // TOMBChannels 2 TRefs
  TOMBChannel_ref = bank->getTOMBChannel(1);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  
  FEB_ptr = TOMBChannel_ref.getTRefFEB();
  FEB_ref = bank->getFEB(0);
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  TRB_ptr  = TOMBChannel_ref.getTRefTRB();
  TRB_ref = bank->getTRB(0);
  BOOST_REQUIRE(TRB_ptr->getID() == TRB_ref.getID());
  
  PM_ptr = TOMBChannel_ref.getTRefPM();
  PM_ref = bank->getPM(0);
  BOOST_REQUIRE(PM_ptr->getID() == PM_ref.getID());
  
  /* 
   * Possible bug in implementation - for the same TOMBChannel two PMs are possible?
  TOMBChannel_ref = bank->getTOMBChannel(1);
  PM_ref = bank->getPM(2);
  */
  
  // TOMBChannels 3 TRefs
  TOMBChannel_ref = bank->getTOMBChannel(2);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  
  FEB_ptr = TOMBChannel_ref.getTRefFEB();
  FEB_ref = bank->getFEB(0);
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  TRB_ptr  = TOMBChannel_ref.getTRefTRB();
  TRB_ref = bank->getTRB(0);
  BOOST_REQUIRE(TRB_ptr->getID() == TRB_ref.getID());
  
  PM_ptr = TOMBChannel_ref.getTRefPM();
  PM_ref = bank->getPM(3);
  BOOST_REQUIRE(PM_ptr->getID() == PM_ref.getID());
  
  // TOMBChannels 4 TRefs
  TOMBChannel_ref = bank->getTOMBChannel(3);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  
  FEB_ptr = TOMBChannel_ref.getTRefFEB();
  FEB_ref = bank->getFEB(0);
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  TRB_ptr  = TOMBChannel_ref.getTRefTRB();
  TRB_ref = bank->getTRB(0);
  BOOST_REQUIRE(TRB_ptr->getID() == TRB_ref.getID());
  
  PM_ptr = TOMBChannel_ref.getTRefPM();
  PM_ref = bank->getPM(2);
  BOOST_REQUIRE(PM_ptr->getID() == PM_ref.getID());
}

BOOST_AUTO_TEST_CASE(fillAllTRefsTest)
{
  /// Copy paste detector - must changed
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
  
  paramGetter.fillAllTRefs(run, *bank);
  
  // Scintillator 1 TRef
  BOOST_REQUIRE(bank->getScintillator(0).getTRefPMLeft() != NULL);
  
  JPetPM* pm_ptr = bank->getScintillator(0).getTRefPMLeft();
  JPetPM& pm_ref = bank->getPM(2);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
  
  pm_ptr = bank->getScintillator(0).getTRefPMRight();
  pm_ref = bank->getPM(1);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
 
  pm_ptr = bank->getScintillator(1).getTRefPMLeft();
  pm_ref = bank->getPM(3);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
  
  pm_ptr = bank->getScintillator(1).getTRefPMRight();
  pm_ref = bank->getPM(0);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
  
  // Scintillator 2 TRef
  BOOST_REQUIRE(bank->getScintillator(1).getTRefPMLeft() != NULL);
  
  pm_ptr = bank->getScintillator(0).getTRefPMLeft();
  pm_ref = bank->getPM(2);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
 
  pm_ptr = bank->getScintillator(0).getTRefPMRight();
  pm_ref = bank->getPM(1);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
   
  pm_ptr = bank->getScintillator(1).getTRefPMLeft();
  pm_ref = bank->getPM(3);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());
  
  pm_ptr = bank->getScintillator(1).getTRefPMRight();
  pm_ref = bank->getPM(0);
  BOOST_REQUIRE(pm_ptr->getID() == pm_ref.getID());

  // std::cout << "pm_ptr->getID():" << pm_ptr->getID() <<std::endl;
  // std::cout << "pm_ref.getID():" << pm_ref.getID() <<std::endl;
  
  // PM 1 TRef
  BOOST_REQUIRE(bank->getPM(0).getTRefKB() != NULL);
  
  JPetFEB* FEB_ptr = bank->getPM(0).getTRefKB();
  JPetFEB& FEB_ref = bank->getFEB(0);
  
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  // PM 2 TRef
  BOOST_REQUIRE(bank->getPM(1).getTRefKB() != NULL);
  
  FEB_ptr = bank->getPM(0).getTRefKB();
  FEB_ref = bank->getFEB(0);
  
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  // PM 3 TRef
  BOOST_REQUIRE(bank->getPM(2).getTRefKB() != NULL);
  
  FEB_ptr = bank->getPM(0).getTRefKB();
  FEB_ref = bank->getFEB(0);
  
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  // PM 4 TRef
  BOOST_REQUIRE(bank->getPM(3).getTRefKB() != NULL);
  
  FEB_ptr = bank->getPM(0).getTRefKB();
  FEB_ref = bank->getFEB(0);
  
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  // FEB TRef
  BOOST_REQUIRE(bank->getFEB(0).getTRefTRB() != NULL);
  
  JPetTRB* TRB_ptr = bank->getFEB(0).getTRefTRB();
  JPetTRB& TRB_ref = bank->getTRB(0);
  
  BOOST_REQUIRE(TRB_ptr->getID() == TRB_ref.getID());
  
  // TRB TRef
  // Lack of implementation
  
  // TOMBChannels 1 TRefs
  JPetTOMBChannel& TOMBChannel_ref = bank->getTOMBChannel(0);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  
  FEB_ptr = TOMBChannel_ref.getTRefFEB();
  FEB_ref = bank->getFEB(0);
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  TRB_ptr  = TOMBChannel_ref.getTRefTRB();
  TRB_ref = bank->getTRB(0);
  BOOST_REQUIRE(TRB_ptr->getID() == TRB_ref.getID());
  
  JPetPM* PM_ptr = TOMBChannel_ref.getTRefPM();
  JPetPM& PM_ref = bank->getPM(1);
  BOOST_REQUIRE(PM_ptr->getID() == PM_ref.getID());
  
  // TOMBChannels 2 TRefs
  TOMBChannel_ref = bank->getTOMBChannel(1);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  
  FEB_ptr = TOMBChannel_ref.getTRefFEB();
  FEB_ref = bank->getFEB(0);
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  TRB_ptr  = TOMBChannel_ref.getTRefTRB();
  TRB_ref = bank->getTRB(0);
  BOOST_REQUIRE(TRB_ptr->getID() == TRB_ref.getID());
  
  PM_ptr = TOMBChannel_ref.getTRefPM();
  PM_ref = bank->getPM(0);
  BOOST_REQUIRE(PM_ptr->getID() == PM_ref.getID());
  
  /* 
   * Possible bug in implementation - for the same TOMBChannel two PMs are possible?
  TOMBChannel_ref = bank->getTOMBChannel(1);
  PM_ref = bank->getPM(2);
  */
  
  // TOMBChannels 3 TRefs
  TOMBChannel_ref = bank->getTOMBChannel(2);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  
  FEB_ptr = TOMBChannel_ref.getTRefFEB();
  FEB_ref = bank->getFEB(0);
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  TRB_ptr  = TOMBChannel_ref.getTRefTRB();
  TRB_ref = bank->getTRB(0);
  BOOST_REQUIRE(TRB_ptr->getID() == TRB_ref.getID());
  
  PM_ptr = TOMBChannel_ref.getTRefPM();
  PM_ref = bank->getPM(3);
  BOOST_REQUIRE(PM_ptr->getID() == PM_ref.getID());
  
  // TOMBChannels 4 TRefs
  TOMBChannel_ref = bank->getTOMBChannel(3);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  BOOST_REQUIRE(TOMBChannel_ref.getTRefFEB() != NULL);
  
  FEB_ptr = TOMBChannel_ref.getTRefFEB();
  FEB_ref = bank->getFEB(0);
  BOOST_REQUIRE(FEB_ptr->id() == FEB_ref.id());
  
  TRB_ptr  = TOMBChannel_ref.getTRefTRB();
  TRB_ref = bank->getTRB(0);
  BOOST_REQUIRE(TRB_ptr->getID() == TRB_ref.getID());
  
  PM_ptr = TOMBChannel_ref.getTRefPM();
  PM_ref = bank->getPM(2);
  BOOST_REQUIRE(PM_ptr->getID() == PM_ref.getID());
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
  std::cout << "FEB numbers:" << bank.getFEBsSize() <<std::endl;
  std::cout << "TRB numbers:" << bank.getTRBsSize() <<std::endl;
  std::cout << "TOMB channel numbers:" << bank.getTOMBChannelsSize() <<std::endl;

  BOOST_REQUIRE(bank.getScintillatorsSize() == 0);
  BOOST_REQUIRE(bank.getPMsSize() == 0);
  BOOST_REQUIRE(bank.getFEBsSize() == 0);
  BOOST_REQUIRE(bank.getTRBsSize() == 0);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 0);
  
  paramGetter.fillScintillators(run, bank);
  paramGetter.fillPMs(run, bank);
  paramGetter.fillFEBs(run, bank);
  paramGetter.fillTRBs(run, bank);
  paramGetter.fillTOMBChannels(run, bank);
  
  BOOST_REQUIRE(bank.getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank.getPMsSize() == 4);
  BOOST_REQUIRE(bank.getFEBsSize() == 1);
  BOOST_REQUIRE(bank.getTRBsSize() == 1);
  BOOST_REQUIRE(bank.getTOMBChannelsSize() == 4);
  
  bank.clear();
  
  BOOST_REQUIRE(bank.getScintillatorsSize() == 0);
  BOOST_REQUIRE(bank.getPMsSize() == 0);
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




BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetDBParamGetter paramGetter;
}

BOOST_AUTO_TEST_CASE(some_filling)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 1;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
  std::cout <<"FEB numbers:"<<bank->getFEBsSize()  <<std::endl;

  BOOST_REQUIRE(bank->getScintillatorsSize()== 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getFEBsSize() == 1);
  BOOST_REQUIRE(bank->getTRBsSize() == 1);

}

BOOST_AUTO_TEST_CASE(run_26)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 26;
  JPetParamBank* bank = paramGetter.generateParamBank(run);
std::cout <<"FEB numbers:"<<bank->getFEBsSize()  <<std::endl;
std::cout <<"PM numbers:"<<bank->getPMsSize()  <<std::endl;
std::cout <<"TRB numbers:"<<bank->getTRBsSize()  <<std::endl;
std::cout <<"Scintillators number:"<<bank->getScintillatorsSize()  <<std::endl;
  BOOST_REQUIRE(bank->getScintillatorsSize() > 0);
  BOOST_REQUIRE(bank->getPMsSize() > 0);
  BOOST_REQUIRE(bank->getFEBsSize() > 0);
  BOOST_REQUIRE(bank->getTRBsSize() > 0);

}
//BOOST_AUTO_TEST_CASE(fillContainersTest)
//{
//  JPetDBParamGetter paramGetter(gDefaultConfigFile);
//  paramGetter.fillAllContainers(1);
//  BOOST_REQUIRE(bank.getScintillatorsSize() > 0);
//  BOOST_REQUIRE(bank.getPMsSize() > 0);
//  BOOST_REQUIRE(bank.getFEBsSize() > 0);
//  BOOST_REQUIRE(bank.getTRBsSize() > 0);
//}
//
//BOOST_AUTO_TEST_CASE(fillContainersTRefsTest)
//{
//  JPetDBParamGetter paramGetter(gDefaultConfigFile);
//  paramGetter.fillAllContainers(1);
//
//  paramGetter.fillAllTRefs();
//}
//
//
//BOOST_AUTO_TEST_CASE(fillAllContainers)
//{
//  JPetDBParamGetter paramGetter(gDefaultConfigFile);
//  paramGetter.fillAllContainers(1);
//
//  paramGetter.fillAllTRefs();
//}



//BOOST_AUTO_TEST_CASE(fillWriteAndReadContainersTest)
//{
//  JPetDBParamGetter paramGetter(gDefaultConfigFile);
//  paramGetter.fillAllContainers(1);
//
//  const char* l_fileName = "param_manager_test_file.txt";
//  JPetWriter l_writerInstance(l_fileName);
//  JPetReader l_readerInstance(l_fileName);
//
//  paramGetter.setWriter(&l_writerInstance);
//  paramGetter.setReader(&l_readerInstance);
//
//  paramGetter.writerAllContainers(l_fileName);
//  paramGetter.readAllContainers(l_fileName);
//}
//
//BOOST_AUTO_TEST_CASE(containersIdTest)
//{
//  JPetDBParamGetter paramGetter(gDefaultConfigFile);
//  paramGetter.fillAllContainers(1);
//
//  BOOST_REQUIRE(paramGetter.getScintillator(0).getID() >= 0);
//  BOOST_REQUIRE(paramGetter.getPM(0).getID() >= 0);
//  BOOST_REQUIRE(paramGetter.getKB(0).id() >= 0);
//  BOOST_REQUIRE(paramGetter.getTRB(0).getID() >= 0);
//  BOOST_REQUIRE(paramGetter.getTOMB().id() >= 0);
//}


BOOST_AUTO_TEST_SUITE_END()

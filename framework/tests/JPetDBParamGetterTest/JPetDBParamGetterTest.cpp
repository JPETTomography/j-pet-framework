#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetDBParamGetterTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetDBParamGetter/JPetDBParamGetter.h"

const char* gDefaultConfigFile = "DBConfig/configDB.cfg";

BOOST_AUTO_TEST_SUITE(FirstSuite)

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



BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetDBParamGetter paramGetter;
}

BOOST_AUTO_TEST_CASE(some_filling)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 1;
  JPetParamBank bank = paramGetter.generateParamBank(run);
  std::cout << "FEB numbers:" << bank.getFEBsSize()  << std::endl;

  BOOST_REQUIRE(bank.getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank.getPMsSize() == 4);
  BOOST_REQUIRE(bank.getFEBsSize() == 1);
  BOOST_REQUIRE(bank.getTRBsSize() == 1);

}

BOOST_AUTO_TEST_CASE(run_26)
{
  JPetDBParamGetter paramGetter(gDefaultConfigFile);
  int run  = 26;
  JPetParamBank bank = paramGetter.generateParamBank(run);
  std::cout << "FEB numbers:" << bank.getFEBsSize()  << std::endl;
  std::cout << "PM numbers:" << bank.getPMsSize()  << std::endl;
  std::cout << "TRB numbers:" << bank.getTRBsSize()  << std::endl;
  std::cout << "Scintillators number:" << bank.getScintillatorsSize()  << std::endl;
  BOOST_REQUIRE(bank.getScintillatorsSize() > 0);
  BOOST_REQUIRE(bank.getPMsSize() > 0);
  BOOST_REQUIRE(bank.getFEBsSize() > 0);
  BOOST_REQUIRE(bank.getTRBsSize() > 0);

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

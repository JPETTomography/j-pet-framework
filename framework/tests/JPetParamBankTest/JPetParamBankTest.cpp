#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamBankTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetParamBank/JPetParamBank.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetParamBank bank;
  BOOST_REQUIRE(bank.getScintillatorsSize() == 0);
  BOOST_REQUIRE(bank.getPMsSize() == 0);
  BOOST_REQUIRE(bank.getFEBsSize() == 0);
  BOOST_REQUIRE(bank.getTRBsSize() == 0);

  BOOST_REQUIRE(bank.getScintillators().GetEntries() == 0);
  BOOST_REQUIRE(bank.getPMs().GetEntries() == 0);
  BOOST_REQUIRE(bank.getFEBs().GetEntries() == 0);
  BOOST_REQUIRE(bank.getTRBs().GetEntries()== 0);
  BOOST_REQUIRE(bank.getTOMB().id() == 0);
  BOOST_REQUIRE(bank.getTOMB().description() == "");
}

BOOST_AUTO_TEST_CASE( adding_some_elements )
{
  JPetParamBank bank;
  JPetScin scint;
  JPetPM pm;
  JPetFEB feb(1, true, "testStatus", "descr", 1, 1);
  JPetTRB trb;
  JPetTOMB tomb(111, "testTOMB");
  bank.addScintillator(scint);
  bank.addPM(pm);
  bank.addTRB(trb);
  bank.addFEB(feb);
  bank.setTOMB(tomb);

  BOOST_REQUIRE(bank.getScintillatorsSize() == 1);
  BOOST_REQUIRE(bank.getPMsSize() == 1);
  BOOST_REQUIRE(bank.getFEBsSize() == 1);
  BOOST_REQUIRE(bank.getTRBsSize() == 1);

  BOOST_REQUIRE(bank.getScintillators().GetEntries() == 1);
  BOOST_REQUIRE(bank.getPMs().GetEntries() == 1);
  BOOST_REQUIRE(bank.getFEBs().GetEntries() == 1);
  BOOST_REQUIRE(bank.getTRBs().GetEntries()== 1);
  BOOST_REQUIRE(bank.getTOMB().id() == 111);
  BOOST_REQUIRE(bank.getTOMB().description() == "testTOMB");


  BOOST_REQUIRE(bank.getFEB(0).id()== 1);
  BOOST_REQUIRE(bank.getFEB(0).isActive());
  BOOST_REQUIRE(bank.getFEB(0).status() == "testStatus");
  BOOST_REQUIRE(bank.getFEB(0).description() == "descr");
  BOOST_REQUIRE(bank.getFEB(0).version()== 1);
}

BOOST_AUTO_TEST_SUITE_END()

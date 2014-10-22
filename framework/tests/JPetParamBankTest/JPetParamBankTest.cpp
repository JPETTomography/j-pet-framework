#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamBankTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetParamBank/JPetParamBank.h"
#include <TFile.h>

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
  BOOST_REQUIRE(bank.getTRBs().GetEntries() == 0);
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
  BOOST_REQUIRE(bank.getTRBs().GetEntries() == 1);
  BOOST_REQUIRE(bank.getTOMB().id() == 111);
  BOOST_REQUIRE(bank.getTOMB().description() == "testTOMB");


  BOOST_REQUIRE(bank.getFEB(0).id() == 1);
  BOOST_REQUIRE(bank.getFEB(0).isActive());
  BOOST_REQUIRE(bank.getFEB(0).status() == "testStatus");
  BOOST_REQUIRE(bank.getFEB(0).description() == "descr");
  BOOST_REQUIRE(bank.getFEB(0).version() == 1);
}

BOOST_AUTO_TEST_CASE( saving_reading_file )
{
  JPetParamBank bank;
  JPetScin scint1(1, 0, 0, 0, 0);
  JPetScin scint2(2, 0, 0, 0, 0);
  JPetPM pm1;
  JPetPM pm2;
  JPetPM pm3;
  JPetPM pm4;
  pm1.setID(1);
  pm2.setID(2);
  pm3.setID(3);
  pm4.setID(4);
  scint1.setTRefPMs(pm1, pm2);
  scint2.setTRefPMs(pm3, pm4);
  JPetFEB feb(1, true, "testStatus", "descr", 1, 1);
  JPetTRB trb;
  JPetTOMB tomb(111, "testTOMB");
  bank.setTOMB(tomb);
  bank.addPM(pm1);
  bank.addPM(pm2);
  bank.addPM(pm3);
  bank.addPM(pm4);
  bank.addScintillator(scint1);
  bank.addScintillator(scint2);
  bank.addTRB(trb);
  bank.addFEB(feb);
  for (int i = 0; i < 100; i++) {
    JPetTOMBChannel channel(i);
    bank.addTOMBChannel(channel);
  }

  TFile file("test.root", "UPDATE");
  file.cd();
  file.WriteObject(&bank, "ParamBank");
  file.Close();
  bank.clear();

  TFile file2("test.root", "READ");
  JPetParamBank* pBank = static_cast<JPetParamBank*>(file2.Get("ParamBank"));
  JPetParamBank bank2 = *pBank;

  BOOST_REQUIRE(bank2.getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank2.getPMsSize() == 4);
  BOOST_REQUIRE(bank2.getFEBsSize() == 1);
  BOOST_REQUIRE(bank2.getTRBsSize() == 1);

  BOOST_REQUIRE(bank2.getScintillators().GetEntries() == 2);
  BOOST_REQUIRE(bank2.getPMs().GetEntries() == 4);
  BOOST_REQUIRE(bank2.getFEBs().GetEntries() == 1);
  BOOST_REQUIRE(bank2.getTRBs().GetEntries() == 1);
  BOOST_REQUIRE(bank2.getTOMB().id() == 111);
  BOOST_REQUIRE(bank2.getTOMB().description() == "testTOMB");


  BOOST_REQUIRE(bank2.getFEB(0).id() == 1);
  BOOST_REQUIRE(bank2.getFEB(0).isActive());
  BOOST_REQUIRE(bank2.getFEB(0).status() == "testStatus");
  BOOST_REQUIRE(bank2.getFEB(0).description() == "descr");
  BOOST_REQUIRE(bank2.getFEB(0).version() == 1);

  BOOST_REQUIRE(bank2.getScintillator(0).getTRefPMLeft()->getID() == 1);
  BOOST_REQUIRE(bank2.getScintillator(0).getTRefPMRight()->getID() == 2);
  BOOST_REQUIRE(bank2.getScintillator(1).getTRefPMLeft()->getID() == 3);
  BOOST_REQUIRE(bank2.getScintillator(1).getTRefPMRight()->getID() == 4);
  BOOST_REQUIRE(bank2.getScintillator(0).getID() == 1);
  BOOST_REQUIRE(bank2.getScintillator(1).getID() == 2);

  file2.Close();
}

BOOST_AUTO_TEST_SUITE_END()

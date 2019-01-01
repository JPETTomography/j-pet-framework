#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetInputHandlerTest
#include <boost/test/unit_test.hpp>
#include "./JPetTaskIO/JPetInputHandler.h"
#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetParamGetterAscii/JPetParamGetterAscii.h"

const std::string dataDir = "unitTestData/JPetParamManagerTest/";
const std::string dataFileName = dataDir + "data.json";
const char* kInputTestFile = "unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root";
// Number of events per time window in the file
// unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root"
// time window    |    events
// 0                      34
// 1                      31
// 2                      28
// 99                     32
// 100 (last one)         33

int getEntrysInWindow(JPetInputHandler& handler)
{
  auto&  event = handler.getEntry();
  auto timeWindow = dynamic_cast<const JPetTimeWindow& >(event);
  return timeWindow.getNumberOfEvents();
}


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(basicTest)
{
  gErrorIgnoreLevel = 6000; /// to supress Error in TFile ROOT error invoked by openInput
  JPetParams params;
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();
  JPetInputHandler handler;
  BOOST_REQUIRE(!handler.openInput("", params));
  auto range = handler.getEntryRange();
  BOOST_REQUIRE_EQUAL(range.firstEntry, 0);
  BOOST_REQUIRE_EQUAL(range.lastEntry, 0);
  BOOST_REQUIRE_EQUAL(range.currentEntry, -1);
  BOOST_REQUIRE_EQUAL(handler.getFirstEntryNumber(), 0);
  BOOST_REQUIRE_EQUAL(handler.getLastEntryNumber(), 0);
  BOOST_REQUIRE_EQUAL(handler.getCurrentEntryNumber(), -1);
  BOOST_REQUIRE(!handler.nextEntry());
}


BOOST_AUTO_TEST_CASE(calculateEntryRange)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  auto res = handler.openInput(kInputTestFile, params);
  BOOST_REQUIRE(res);
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  bool isOK = false;
  std::tie(isOK, firstEvent, lastEvent) = handler.calculateEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(firstEvent, 0);
  BOOST_REQUIRE_EQUAL(lastEvent, 100);
}

BOOST_AUTO_TEST_CASE(setEntryRange2)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = 1;
  opts["lastEvent_int"] = 1;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput(kInputTestFile, params);
  bool isOK = false;
  isOK = handler.setEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(1, handler.getFirstEntryNumber());
  BOOST_REQUIRE_EQUAL(1, handler.getLastEntryNumber());
  BOOST_REQUIRE_EQUAL(getEntrysInWindow(handler), 31);
}

BOOST_AUTO_TEST_CASE(calculateEntryRange3)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = 0;
  opts["lastEvent_int"] = 1;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput(kInputTestFile, params);
  bool isOK = false;
  isOK = handler.setEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(0, handler.getFirstEntryNumber());
  BOOST_REQUIRE_EQUAL(1, handler.getLastEntryNumber());
  BOOST_REQUIRE_EQUAL(getEntrysInWindow(handler), 34);
}

BOOST_AUTO_TEST_CASE(calculateEntryRange4)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = 1;
  opts["lastEvent_int"] = -1;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput(kInputTestFile, params);
  bool isOK = false;
  isOK = handler.setEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(1, handler.getFirstEntryNumber());
  BOOST_REQUIRE_EQUAL(100, handler.getLastEntryNumber());
  BOOST_REQUIRE_EQUAL(getEntrysInWindow(handler), 31);
}

BOOST_AUTO_TEST_CASE(calculateEntryRange5)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = -1;
  opts["lastEvent_int"] = -1;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput(kInputTestFile, params);
  bool isOK = false;
  isOK = handler.setEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(0, handler.getFirstEntryNumber());
  BOOST_REQUIRE_EQUAL(100, handler.getLastEntryNumber());
  BOOST_REQUIRE_EQUAL(getEntrysInWindow(handler), 34);
}

BOOST_AUTO_TEST_CASE(calculateEntryRange6)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = -1;
  opts["lastEvent_int"] = 5;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput(kInputTestFile, params);
  bool isOK = false;
  isOK = handler.setEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(0, handler.getFirstEntryNumber());
  BOOST_REQUIRE_EQUAL(5, handler.getLastEntryNumber());
  BOOST_REQUIRE_EQUAL(getEntrysInWindow(handler), 34);
}

BOOST_AUTO_TEST_CASE(calculateEntryRange7)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = 2;
  opts["lastEvent_int"] = 5;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput(kInputTestFile, params);
  bool isOK = false;
  isOK = handler.setEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(2, handler.getFirstEntryNumber());
  BOOST_REQUIRE_EQUAL(5, handler.getLastEntryNumber());
  BOOST_REQUIRE_EQUAL(getEntrysInWindow(handler), 28);
}


BOOST_AUTO_TEST_CASE(getNextEntry)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = -1;
  opts["lastEvent_int"] = 5;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput(kInputTestFile, params);
  handler.setEntryRange(opts);
  BOOST_REQUIRE_EQUAL(getEntrysInWindow(handler), 34);
  BOOST_REQUIRE(handler.nextEntry());
  BOOST_REQUIRE_EQUAL(getEntrysInWindow(handler), 31);
  BOOST_REQUIRE(handler.nextEntry());
  BOOST_REQUIRE_EQUAL(getEntrysInWindow(handler), 28);
  BOOST_REQUIRE(handler.nextEntry());
  BOOST_REQUIRE(handler.nextEntry());
  BOOST_REQUIRE(handler.nextEntry());
  BOOST_REQUIRE(!handler.nextEntry());
}

BOOST_AUTO_TEST_SUITE_END()

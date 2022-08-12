#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetInputHandlerHLDTest

#include "JPetTaskIO/JPetInputHandlerHLD.h"
#include "JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "JPetParamManager/JPetParamManager.h"
#include "JPetTimeWindow/JPetTimeWindow.h"

#include <unpacker_types.hpp>

#include <boost/test/unit_test.hpp>

const std::string dataDir = "unitTestData/JPetParamManagerTest/";
const std::string dataFileName = dataDir + "data.json";
const char* kInputTestFileROOT = "unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root";
const char* kInputTestFileHLD = "unitTestData/JPetTaskIOTest/djpet_data.hld";

int getNumberOfEndpoints(JPetInputHandlerHLD& handler)
{
  auto &event = handler.getEntry();

  auto event_data = dynamic_cast<JPetHLDdata *const>(&event);

  return event_data->fOriginalData.size();
}

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(basicTest)
{
  JPetParams params;
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();
  JPetInputHandlerHLD handler;
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

BOOST_AUTO_TEST_CASE(wrongFileType)
{
  JPetParams params;
  JPetInputHandlerHLD handler;
  auto res = handler.openInput(kInputTestFileROOT, params);
  BOOST_REQUIRE(!res);  
}

BOOST_AUTO_TEST_CASE(calculateEntryRange)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  auto mgr = std::make_shared<JPetParamManager>(new JPetParamGetterAscii(dataFileName));
  JPetParams params(opts, mgr);

  JPetInputHandlerHLD handler;
  auto res = handler.openInput(kInputTestFileHLD, params);
  BOOST_REQUIRE(res);
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  bool isOK = false;
  std::tie(isOK, firstEvent, lastEvent) = handler.calculateEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(firstEvent, 0);
  BOOST_REQUIRE_EQUAL(lastEvent, 999999999); // Unpacker is unable to determine total events number
}

BOOST_AUTO_TEST_CASE(readHLDfile)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = 1;
  opts["lastEvent_int"] = 1;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamGetterAscii(dataFileName));
  JPetParams params(opts, mgr);

  JPetInputHandlerHLD handler;
  handler.openInput(kInputTestFileHLD, params);
  bool isOK = handler.setEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(1, handler.getFirstEntryNumber());
  BOOST_REQUIRE_EQUAL(1, handler.getLastEntryNumber());
  BOOST_REQUIRE_EQUAL(getNumberOfEndpoints(handler), 48);
}

BOOST_AUTO_TEST_CASE(setEntryRange)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = 0;
  opts["lastEvent_int"] = 1;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamGetterAscii(dataFileName));
  JPetParams params(opts, mgr);

  JPetInputHandlerHLD handler;
  handler.openInput(kInputTestFileHLD, params);
  bool isOK = handler.setEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(0, handler.getFirstEntryNumber());
  BOOST_REQUIRE_EQUAL(1, handler.getLastEntryNumber());
  // 0th entry is loaded on openInput
  BOOST_REQUIRE(handler.nextEntry()); // 1
  BOOST_REQUIRE(!handler.nextEntry());
}

BOOST_AUTO_TEST_CASE(setEntryRange2)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = 1;
  opts["lastEvent_int"] = 100;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamGetterAscii(dataFileName));
  JPetParams params(opts, mgr);
  
  JPetInputHandlerHLD handler;
  handler.openInput(kInputTestFileHLD, params);
  bool isOK = handler.setEntryRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(1, handler.getFirstEntryNumber());
  BOOST_REQUIRE_EQUAL(100, handler.getLastEntryNumber());
  // 0th entry is loaded on openInput
  for(int i=1; i<100; ++i){
    BOOST_REQUIRE(handler.nextEntry()); // 1-100
  }  
  BOOST_REQUIRE(!handler.nextEntry());
}

BOOST_AUTO_TEST_CASE(noTDCcalib)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = -1;
  opts["lastEvent_int"] = 5;
  opts["runID_int"] = 1;

  auto mgr = std::make_shared<JPetParamManager>(new JPetParamGetterAscii(dataFileName));
  JPetParams params(opts, mgr);

  JPetInputHandlerHLD handler;
  BOOST_REQUIRE(!handler.loadTDCCalib(params));
}

BOOST_AUTO_TEST_CASE(loadTDCcalib)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = -1;
  opts["lastEvent_int"] = 5;
  opts["runID_int"] = 1;

  auto mgr = std::make_shared<JPetParamManager>(new JPetParamGetterAscii("unitTestData/JPetParamManagerTest/DBv10.json"));
  mgr->fillParameterBank(1);
  
  opts["Unpacker_TDCnonlinearityCalib_std::string"] = std::string("unitTestData/JPetTaskIOTest/tdc_calib.root");
  JPetParams params(opts, mgr);

  JPetInputHandlerHLD handler;
  BOOST_REQUIRE(handler.loadTDCCalib(params));
}

BOOST_AUTO_TEST_SUITE_END()

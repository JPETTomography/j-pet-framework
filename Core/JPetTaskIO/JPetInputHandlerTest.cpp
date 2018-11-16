#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetInputHandlerTest
#include <boost/test/unit_test.hpp>
#include "./JPetTaskIO/JPetInputHandler.h"
#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetParamGetterAscii/JPetParamGetterAscii.h"

const std::string dataDir = "unitTestData/JPetParamManagerTest/";
const std::string dataFileName = dataDir + "data.json";

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(getEventRange)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  auto res = handler.openInput("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root", params);
  BOOST_REQUIRE(res);
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  bool isOK = false;
  std::tie(isOK, firstEvent, lastEvent) = handler.getEventRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(firstEvent, 0);
  BOOST_REQUIRE_EQUAL(lastEvent, 100);
}

BOOST_AUTO_TEST_CASE(getEventRange2)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = 1;
  opts["lastEvent_int"] = 1;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root", params);
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  bool isOK = false;
  std::tie(isOK, firstEvent, lastEvent) = handler.getEventRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(firstEvent, 1);
  BOOST_REQUIRE_EQUAL(lastEvent, 1);
}

BOOST_AUTO_TEST_CASE(getEventRange3)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = 0;
  opts["lastEvent_int"] = 1;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root", params);
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  bool isOK = false;
  std::tie(isOK, firstEvent, lastEvent) = handler.getEventRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(firstEvent, 0);
  BOOST_REQUIRE_EQUAL(lastEvent, 1);
}

BOOST_AUTO_TEST_CASE(getEventRange4)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = 1;
  opts["lastEvent_int"] = -1;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root", params);
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  bool isOK = false;
  std::tie(isOK, firstEvent, lastEvent) = handler.getEventRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(firstEvent, 1);
  BOOST_REQUIRE_EQUAL(lastEvent, 100);
}

BOOST_AUTO_TEST_CASE(getEventRange5)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = -1;
  opts["lastEvent_int"] = -1;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root", params);
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  bool isOK = false;
  std::tie(isOK, firstEvent, lastEvent) = handler.getEventRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(firstEvent, 0);
  BOOST_REQUIRE_EQUAL(lastEvent, 100);
}

BOOST_AUTO_TEST_CASE(getEventRange6)
{
  using namespace jpet_options_generator_tools;
  auto opts = getDefaultOptions();

  opts["firstEvent_int"] = -1;
  opts["lastEvent_int"] = 5;
  auto mgr = std::make_shared<JPetParamManager>(new JPetParamManager(new JPetParamGetterAscii(dataFileName)));
  JPetParams params(opts, mgr);

  JPetInputHandler handler;
  handler.openInput("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root", params);
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  bool isOK = false;
  std::tie(isOK, firstEvent, lastEvent) = handler.getEventRange(opts);
  BOOST_REQUIRE(isOK);
  BOOST_REQUIRE_EQUAL(firstEvent, 0);
  BOOST_REQUIRE_EQUAL(lastEvent, 5);
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
  handler.openInput("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root", params);
  BOOST_REQUIRE(handler.nextEntry());
  BOOST_REQUIRE(handler.nextEntry());
  BOOST_REQUIRE(handler.nextEntry());
}

BOOST_AUTO_TEST_SUITE_END()
